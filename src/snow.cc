#include "snow.h"

#include <iostream>
#include <fstream>

#pragma omp declare reduction( \
    VectorSum: Eigen::Vector3f: \
    omp_out += omp_in) \
    initializer(omp_priv = Eigen::Vector3f::Zero())

#pragma omp declare reduction( \
    MatrixSum: Eigen::Matrix3f: \
    omp_out += omp_in) \
    initializer(omp_priv = Eigen::Matrix3f::Zero())

Vector3f Snow::sphere(float radius, float off) {
    float theta =  M_PI * (rand() / (float)RAND_MAX);
    float phi = 2.f * M_PI * (rand() / (float)RAND_MAX);
    float r = radius * pow((rand() / (float)RAND_MAX), 1.f / 3.f);
    float x = r * sin(theta) * cos(phi);
    float y = r * sin(theta) * sin(phi);
    float z = r * cos(theta);
    return Vector3f(x+off, y, z);
}

Vector3f Snow::cube(float radius) {
    float x = (rand() / (float)RAND_MAX) * radius;
    float y = (rand() / (float)RAND_MAX) * radius;
    float z = (rand() / (float)RAND_MAX) * radius;
    return Vector3f(x, y, z);
}

Vector3f Snow::heart() {
    float t = 2.f * M_PI * (rand() / (float)RAND_MAX);
    float x = 16 * pow(sin(t), 3);
    float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
    float z = 0;
    return Vector3f(x, y, z);
}

Vector3f Snow::bunny() {
    // TODO: generate a particle inside the bounds of the bunny object
    return Vector3f::Zero();
}

Snow::Snow(int num_frames, int num_particles, int grid_size, string shape) :
    m_num_frames(num_frames), m_num_particles(num_particles), m_grid_size(grid_size) {
    m_particles = std::vector<Particle*>();
    m_grid = std::vector<GridCell*>(m_grid_size * m_grid_size * m_grid_size);
    bool another_ball = true;
    float off;
    if (!another_ball) {
        off = 0.0f;
    } else {
        off = 0.3f;
    }
    for (int i = 0; i < m_num_particles; i++) {
        if (another_ball) {
            Particle* p2 = new Particle;
            p2->id = i + m_num_particles; // Assign unique IDs for the second set
            p2->position = sphere(0.05f, -off);
            p2->velocity = Vector3f(1.2, 0, 0); // for wall 
            p2->mass = 0.1f;
            p2->deformation_gradient_elastic = Matrix3f::Identity();
            p2->deformation_gradient_plastic = Matrix3f::Identity();
            m_particles.push_back(p2);
        }
        Particle* p = new Particle;
        p->id = i;
        if (shape == "sphere")
            p->position = sphere(0.05f, off);
            // p->position = sphere(0.2f);
        else if (shape == "cube")
            p->position = cube(0.25f);
        else if (shape == "heart")
            p->position = heart();
        else if (shape == "bunny")
            p->position = bunny();
        else
            p->position = sphere(0.05f, off); // changed from 0.1
        // p->velocity = Vector3f::Zero(); // for collisions
        p->velocity = Vector3f(-1.2, 0, 0); // for wall 
        p->mass = 0.1f;
        p->deformation_gradient_elastic = Matrix3f::Identity();
        p->deformation_gradient_plastic = Matrix3f::Identity();
        m_particles.push_back(p);


    }

    int totalCells = m_grid_size * m_grid_size * m_grid_size;
    for (int index = 0; index < totalCells; index++) {
        GridCell* cell = new GridCell;
        cell->grid_index = Vector3f(index % m_grid_size, (index / m_grid_size) % m_grid_size, index / (m_grid_size * m_grid_size));
        cell->mass = 0.f;
        cell->velocity = Vector3f::Zero();
        cell->force = Vector3f::Zero();
        m_grid[index] = cell;
    }
    if (another_ball) {
        m_num_particles *=2;
    }
}

Snow::~Snow() {
    for (Particle* particle : m_particles)
        delete particle;
    m_particles.clear();

    for (GridCell* cell : m_grid)
        delete cell;
    m_grid.clear();
}

Vector3f Snow::get_grid_coords(Vector3f position) {
    // gets the appropriate grid coordinates for a particle based off of its position
    return Vector3f(floor(m_grid_size * (position.x() + 1.f) / 2.f), floor(m_grid_size * (position.y() + 1.f) / 2.f), floor(m_grid_size * (position.z() + 1.f) / 2.f));
}

int Snow::get_grid_index(Vector3f grid_coords) {
    // gets the index of the grid cell based off of its coordinates
    return grid_coords.x() + grid_coords.y() * m_grid_size + grid_coords.z() * m_grid_size * m_grid_size;
}

float Snow::particle_weight(Vector3f grid_index, Vector3f evaluation_position) {
    // calcualting the influence of grid cell at grid_index on evaluation_position
    Vector3f eval_grid_coords = get_grid_coords(evaluation_position);
    float n_x = calculate_n((eval_grid_coords.x() - (grid_index.x())));
    float n_y = calculate_n((eval_grid_coords.y() - (grid_index.y())));
    float n_z = calculate_n((eval_grid_coords.z() - (grid_index.z())));
    return n_x * n_y * n_z;
}

float Snow::calculate_n(float x) {
    if (0 <= abs(x) && abs(x) < 1)
        return (0.5f * pow(abs(x), 3.f)) - pow(abs(x), 2.f) + (2.f / 3.f);
    else if (1 <= abs(x) && abs(x) < 2)
        return ((-1.f / 6.f) * pow(abs(x), 3)) + pow(abs(x), 2.f) - (2.f * abs(x)) + (4.f / 3.f);
    else
        return 0;
}

float Snow::calculate_n_prime(float x) {
    if (0.f <= abs(x) && abs(x) < 1.f)
        return (1.5 * abs(x) * x) - (2.f * x);
    else if (1.f <= abs(x) && abs(x) < 2.f)
        return ((-0.5f) * abs(x) * x) + (2.f * x) - (2.f * abs(x) / x);
    else
        return 0.f;
}

Vector3f Snow::particle_weight_gradient(Vector3f grid_index, Vector3f evaluation_position) {
    // calculating the gradient of the influence of grid cell at grid_index on evaluation_position
    Vector3f eval_grid_coords = get_grid_coords(evaluation_position);
    float n_x = calculate_n((eval_grid_coords.x() - (grid_index.x())));
    float n_y = calculate_n((eval_grid_coords.y() - (grid_index.y())));
    float n_z = calculate_n((eval_grid_coords.z() - (grid_index.z())));
    float n_x_grad = calculate_n_prime((eval_grid_coords.x() - (grid_index.x())));
    float n_y_grad = calculate_n_prime((eval_grid_coords.y() - (grid_index.y())));
    float n_z_grad = calculate_n_prime((eval_grid_coords.z() - (grid_index.z())));
    return Vector3f(n_x_grad * n_y * n_z, n_x * n_y_grad * n_z, n_x * n_y * n_z_grad);
}

Matrix3f Snow::particle_velocity_gradient(Vector3f evaluation_position) {
    Matrix3f gradient = Matrix3f::Zero();
    for (int grid_index = 0; grid_index < (int)m_grid.size(); grid_index++){
        gradient += m_grid[grid_index]->velocity_star * (particle_weight_gradient(m_grid[grid_index]->grid_index, evaluation_position)).transpose();
    }
    return gradient;
}

Matrix3f Snow::psi(Matrix3f Fe, Matrix3f Fp) {
    float Je = Fe.determinant();
    float Jp = Fp.determinant();
    float exponential = m_hardening * (1.f - Jp);
    float mu_fp = m_mu_0 * exp(exponential);
    float lambda_fp = m_lambda_0 * exp(exponential);
    JacobiSVD<Matrix3f> svd(Fe, ComputeFullU | ComputeFullV);
    Matrix3f sigma = svd.singularValues().asDiagonal();
    Matrix3f Re = svd.matrixV() * sigma * svd.matrixV().transpose();

    return ((2.f * mu_fp) * (Fe - Re) * (Fe.transpose())) + ((lambda_fp * (Je - 1.f) * Je) * Matrix3f::Identity());
}

/**
 * STEP 1: Rasterizes particle data to the grid
 * 
 * This function takes the particle data and rasterizes it to the grid. This is done by
 * calculating the mass and velocity of each grid cell based off of the particles that
 * are within the influence of the grid cell. The influence of a particle on a grid cell
 * is calculated using the particle weight function.
 */
void Snow::rasterize_grid() {
    // first step is to rasterize particles into grid cells
    #pragma omp parallel for
    for (int grid_cell = 0; grid_cell < (int)m_grid.size(); grid_cell++) {
        // for each grid cell, we need to calculate the mass and velocity
        float mass = 0.f;
        Vector3f velocity = Vector3f::Zero();
        // sum across the particles
        #pragma omp parallel for reduction(+:mass)
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            mass += particle->mass + particle_weight(m_grid[grid_cell]->grid_index, particle->position);
        }
        // need to calculate velocity after since we need the normalization factor from the mass
        #pragma omp parallel for reduction(VectorSum:velocity)
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            velocity += particle->mass * particle->velocity * particle_weight(m_grid[grid_cell]->grid_index, particle->position) / mass;
        }
        m_grid[grid_cell]->mass = mass;
        m_grid[grid_cell]->velocity = velocity;
    }
}

/**
 * STEP 2.1: Compute particle densities
 * 
 * This function computes the density of each grid cell by dividing the mass of the cell
 * by the volume of the cell. The volume of the cell is calculated by raising the grid spacing
 * to the power of 3.
 */
void Snow::compute_cell_densities() {
    #pragma omp parallel for
    for (int index = 0; index < (int)m_grid.size(); index++) {
        GridCell* cell = m_grid[index];
        cell->density = cell->mass / pow(m_grid_spacing, 3);
    }
}

/**
 * STEP 2.2: Compute particle volumes
 * 
 * This function computes the volume of each particle by dividing the mass of the particle
 * by the density of the particle. The density of the particle is calculated by summing the
 * densities of the grid cells that the particle is influenced by.
 */
void Snow::compute_particle_volumes() {
    #pragma omp parallel for
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
        Particle* particle = m_particles[particle_index];
        float density = 0.f;
        // for (int grid_index = 0; grid_index < (int)m_grid.size(); grid_index++) {
        //     GridCell* cell = m_grid[grid_index];
        //     density += cell->density * particle_weight(cell->grid_index, particle->position);
        // }
        #pragma omp parallel for reduction(+:density)
        for (int x_offset = -1; x_offset < 2; x_offset++) {
            for (int y_offset = -1; y_offset < 2; y_offset++) {
                for (int z_offset = -1; z_offset < 2; z_offset++) {
                    if (x_offset == 0 && y_offset == 0 && z_offset == 0) {
                        continue;
                    }
                    Vector3f grid_index = get_grid_coords(particle->position) + Vector3f(x_offset, y_offset, z_offset);
                    if (grid_index.x() >= 0 && grid_index.x() < m_grid_size && grid_index.y() >= 0 && grid_index.y() < m_grid_size && grid_index.z() >= 0 && grid_index.z() < m_grid_size) {
                        GridCell* cell = m_grid[get_grid_index(grid_index)];
                        density += cell->density * particle_weight(cell->grid_index, particle->position);
                    }
                }
            }
        }
        particle->density = density;
        particle->volume = particle->mass / particle->density;
    }
}

/**
 * STEP 3: Compute grid forces
 * 
 * This function computes the forces on each grid cell by summing the forces on each particle
 * that is influenced by the grid cell. The force on a particle is calculated by multiplying
 * the negative of the volume of the particle by the psi function of the deformation gradient
 * of the particle and the gradient of the weight of the particle.
 */
void Snow::compute_grid_forces() {
    #pragma omp parallel for
    for (int grid_index = 0; grid_index < (int)m_grid.size(); grid_index++) {
        GridCell* cell = m_grid[grid_index];
        Vector3f force = Vector3f::Zero();
        Matrix3f totalDeformationGradient = Matrix3f::Zero();
        float totalWeight = 0.f;

        #pragma omp parallel for reduction(VectorSum:force) reduction(MatrixSum:totalDeformationGradient) reduction(+:totalWeight)
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            float weight = particle_weight(cell->grid_index, particle->position);
            totalDeformationGradient += particle->deformation_gradient_elastic * weight;
            totalWeight += weight;

            force += -particle->volume * psi(particle->deformation_gradient_elastic, particle->deformation_gradient_plastic) 
                    * particle_weight_gradient(cell->grid_index, particle->position);
        }

        cell->force = force;
        if (totalWeight > 0.f) {
            cell->deformation_gradient = totalDeformationGradient / totalWeight;
        } else {
            cell->deformation_gradient = Matrix3f::Identity();
        }
    }
}


/**
 * STEP 4: Update grid velocities
 * 
 * This function updates the velocities of each grid cell by adding the force on the grid cell
 * multiplied by the inverse mass of the grid cell and the timestep to the velocity of the grid cell.
 * The velocity of the grid cell is then set to the sum of the velocity of the grid cell and the force
 * on the grid cell multiplied by the inverse mass of the grid cell and the timestep.
 */
void Snow::update_grid_velocity() {
    #pragma omp parallel for
    for (int grid_index = 0; grid_index < (int)m_grid.size(); grid_index++) {
        GridCell* cell = m_grid[grid_index];
        if (cell->mass != 0) {
            float inverse_mass = 1.f / cell->mass;
            cell->force += m_gravity * cell->mass;
            cell->velocity_star = cell->velocity + cell->force * inverse_mass * m_timestep;
        }
    }
}

/**
 * STEP 5: Grid based body collisions
 * 
 * This function computes the collisions of the grid cells with the ground. If the grid cell is below
 * the ground, the velocity of the grid cell is reflected off of the ground and the grid cell is moved
 * to the ground.
 */
void Snow::compute_grid_based_collisions() {
    float floor_height = -0.75f;
    float mu = 0.4f;

    #pragma omp parallel for
    for (GridCell* cell : m_grid) {
        Vector3f grid_index = cell->grid_index;
        Vector3f grid_pos = Vector3f(
            (grid_index.x() - m_grid_size / 2) * m_grid_spacing,
            (grid_index.y() - m_grid_size / 2) * m_grid_spacing,
            (grid_index.z() - m_grid_size / 2) * m_grid_spacing
        );
        if (grid_pos.z() <= floor_height) {
            Vector3f v_rel = cell->velocity_star;
            // float vn = v_rel.z();
            Vector3f normal = Vector3f(0, 0, 1.0f);
            float vn = v_rel.dot(normal);

            if (vn < 0) {
                Vector3f vt = v_rel - vn * normal;
                if (vt.norm() <= -mu * vn) {
                    cell->velocity_star = Vector3f::Zero();
                } else {
                    cell->velocity_star = vt + mu * vn * vt.normalized();
                }
            }
        }
        // for wall collisions
        if (grid_pos.x() <= floor_height){
            Vector3f v_rel = cell->velocity_star;
            Vector3f normal = Vector3f(1.0f, 0, 0);
            float vn = v_rel.dot(normal);

            if (vn < 0) {
                Vector3f vt = v_rel - vn * normal;
                if (vt.norm() <= -mu * vn) {
                    cell->velocity_star = Vector3f::Zero();
                } else {
                    cell->velocity_star = vt + mu * vn * vt.normalized();
                }
            }
        }




        for (int i = 0; i < m_num_particles; ++i) {
        Particle* particle1 = m_particles[i];
            for (int j = i + 1; j < m_num_particles; ++j) {
                Particle* particle2 = m_particles[j];
                // Check if particles belong to different spheres
                if ((particle1->id < m_num_particles/2 && particle2->id >= m_num_particles/2) ||
                    (particle2->id < m_num_particles /2&& particle1->id >= m_num_particles/2)) {
                    // Calculate the distance between the centers of the particles
                    float distance = (particle1->position - particle2->position).norm();
                    float sum_radii = 2 * 0.05; // Assuming all particles have the same radius

                    // If particles are overlapping, handle collision
                    if (distance < 0.01) {
                        // Calculate relative velocity
                        Vector3f relative_velocity = particle2->position - particle1->position;

                        // Calculate impulse (change in momentum)
                        Vector3f impulse = (0.00171) * relative_velocity;
                        impulse[1] += 0.00001;

                        // Update velocities based on masses
                        particle1->velocity -= impulse; // Vector3f{.0000529,0,0.000001}; // Update velocity of particle 1
                        particle2->velocity += impulse; //Vector3f{.0000529,0,-0.000001}; // Update velocity of particle 2
                    }
                }
            }
        }



        // const float sphere_radius = 0.2f;
        // const Vector3f sphere_centroid(0, 0, -0.4); 

        // Vector3f relative_pos = grid_pos - sphere_centroid; 
        // if (relative_pos.norm() <= sphere_radius) {
        //     // Calculate relative velocity
        //     Vector3f v_rel = cell->velocity;
        //     float vn = v_rel.dot(relative_pos.normalized());

        //     if (vn < 0) {
        //         v_rel -= vn * relative_pos.normalized() * m_restitution;
        //         Vector3f vt = v_rel - vn * relative_pos.normalized();
        //         float vt_norm = vt.norm();
        //         if (vt_norm > 0) {
        //             float friction_factor = mu * vn / vt_norm;
        //             v_rel -= friction_factor * vt;
        //         }
        //         cell->velocity = v_rel;
        //     }
        // }

    }
}

/**
 * STEP 6: Solve the linear system
 * 
 */
void Snow::solve_linear_system() {
    int totalCells = m_grid_size * m_grid_size * m_grid_size;
    MatrixXf A = MatrixXf::Identity(totalCells * 3, totalCells * 3);
    VectorXf v_star(totalCells * 3);
    VectorXf v_next(totalCells * 3);

    float beta = 0.5f;
    float delta_t_squared = m_timestep * m_timestep;
    float mu = m_mu_0;
    float lambda = m_lambda_0;

    for (int i = 0; i < totalCells; i++) {
        GridCell* cell_i = m_grid[i];
        v_star.segment<3>(3 * i) = cell_i->velocity_star;

        for (int j = 0; j < totalCells; j++) {
            GridCell* cell_j = m_grid[j];
            if (cell_i->mass > 0 && cell_j->mass > 0) {
                float mass_inverse = 1.0 / cell_i->mass;
                
                Matrix3f F_i = cell_i->deformation_gradient;
                Matrix3f dFdF = 2 * mu * F_i - 2 * mu * Matrix3f::Identity() + lambda * (F_i.transpose() * F_i - Matrix3f::Identity());

                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        A(3 * i + k, 3 * j + l) += beta * delta_t_squared * mass_inverse * dFdF(k, l);
                    }
                }
            }
        }
    }

    v_next = A.colPivHouseholderQr().solve(v_star);

    for (int i = 0; i < totalCells; i++) {
        m_grid[i]->velocity_new = v_next.segment<3>(3 * i);
    }
}


/**
 * STEP 7: Update deformation gradient
 * 
 * This function updates the deformation gradient of each particle by taking the elastic part of the
 * deformation gradient that exceeds a threshold and pushing it into the plastic part of the deformation
 * gradient. The elastic part of the deformation gradient is clamped to be within the threshold.
 */
void Snow::update_deformation_gradient() {
    #pragma omp parallel for
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
        Particle* particle = m_particles[particle_index];
        // temporarily define the parts of the deformation gradient
        Matrix3f next_deformation_gradient_elastic = (Matrix3f::Identity() + (m_timestep * particle_velocity_gradient(particle->position))) * particle->deformation_gradient_elastic;
        Matrix3f next_deformation_gradient_plastic = particle->deformation_gradient_plastic;
        Matrix3f next_deformation_gradient = next_deformation_gradient_elastic * next_deformation_gradient_plastic;

        // take the part of the elastic deformation gradient that exceeds threshold and push it into plastic
        JacobiSVD<Matrix3f> svd(next_deformation_gradient_elastic, ComputeFullU | ComputeFullV);
        Matrix3f u_matrix = svd.matrixU();
        Matrix3f v_matrix = svd.matrixV();
        Matrix3f singular_values = Matrix3f::Zero();
        singular_values.diagonal() = svd.singularValues();
        Matrix3f S;
        Matrix3f S_inverse;
        // clamping
        S << clamp(singular_values(0, 0), 1 - m_compression, 1 + m_stretch), 0, 0,
                   0, clamp(singular_values(1, 1), 1 - m_compression, 1 + m_stretch), 0,
                   0, 0, clamp(singular_values(2, 2), 1 - m_compression, 1 + m_stretch);

        S_inverse << 1 / S(0, 0), 0, 0,
                      0, 1 / S(1, 1), 0,
                      0, 0, 1 / S(2, 2);

        next_deformation_gradient_elastic = (u_matrix * S) * v_matrix.transpose();
        next_deformation_gradient_plastic = v_matrix * S_inverse * u_matrix.transpose() * next_deformation_gradient;

        particle->deformation_gradient_elastic = next_deformation_gradient_elastic;
        particle->deformation_gradient_plastic = next_deformation_gradient_plastic;
    }
}

/**
 * STEP 8: Update particle velocities
 * 
 * This function updates the velocities of each particle by interpolating between the PIC and FLIP
 * velocities of the particle. The PIC velocity is calculated by summing the velocities of the grid
 * cells that the particle is influenced by and the FLIP velocity is calculated by summing the difference
 * between the star and regular velocities of the grid cells that the particle is influenced by.
 */
void Snow::update_particle_velocities() {
    #pragma omp parallel for
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
        Particle* particle = m_particles[particle_index];
        Vector3f velocity_pic = Vector3f::Zero();
        Vector3f velocity_flip = particle->velocity;

        #pragma omp parallel for reduction(VectorSum:velocity_pic) reduction(VectorSum:velocity_flip)
        for (int x_offset = -1; x_offset < 2; x_offset++) {
            for (int y_offset = -1; y_offset < 2; y_offset++) {
                for (int z_offset = -1; z_offset < 2; z_offset++) {
                    if (x_offset == 0 && y_offset == 0 && z_offset == 0) {
                        continue;
                    }
                    Vector3f grid_index = get_grid_coords(particle->position) + Vector3f(x_offset, y_offset, z_offset);
                    if (grid_index.x() >= 0 && grid_index.x() < m_grid_size && grid_index.y() >= 0 && grid_index.y() < m_grid_size && grid_index.z() >= 0 && grid_index.z() < m_grid_size) {
                        GridCell* cell = m_grid[get_grid_index(grid_index)];
                        velocity_pic += cell->velocity * particle_weight(cell->grid_index, particle->position);
                        velocity_flip += (cell->velocity_star - cell->velocity) * particle_weight(cell->grid_index, particle->position);
                    }
                }
            }
        }
        particle->velocity = ((1 - m_alpha) * velocity_pic) + (m_alpha * velocity_flip);    
    }
}

/**
 * STEP 9: Particle-based body collisions
 * 
 * This function computes the collisions of the particles with the ground. If the particle is below
 * the ground, the velocity of the particle is reflected off of the ground and the particle is moved
 * to the ground.
 */
void Snow::compute_particle_based_collisions() {
    float floor_height = -0.75f;
    float mu = 0.4f;

    #pragma omp parallel for
    for (Particle* particle : m_particles) {
        // if (particle->position.z() <= floor_height) {
        //     Vector3f v_rel = particle->velocity;
        //     float vn = v_rel.z();

        //     if (vn < 0) {
        //         v_rel.z() = -vn * m_restitution;

        //         Vector3f vt(v_rel.x(), v_rel.y(), 0);
        //         if (vt.norm() > 0) {
        //             v_rel.x() -= vn * vt.normalized().x();
        //             v_rel.y() -= vn * vt.normalized().y();
        //         }
        //     }
        //     particle->velocity = mu * v_rel;

        //     particle->position.z() = floor_height;
        // }
        if (particle->position.z() <= floor_height) {
            Vector3f v_rel = particle->velocity;
            // float vn = v_rel.z();
            Vector3f normal = Vector3f(0, 0, 1.0f);
            float vn = v_rel.dot(normal);

            if (vn < 0) {
                Vector3f vt = v_rel - vn * normal;
                if (vt.norm() <= -mu * vn) {
                    particle->velocity = Vector3f::Zero();
                } else {
                    particle->velocity = vt + mu * vn * vt.normalized();
                }
            }
        }



        for (int i = 0; i < m_num_particles; ++i) {
        Particle* particle1 = m_particles[i];
            for (int j = i + 1; j < m_num_particles; ++j) {
                Particle* particle2 = m_particles[j];
                // Check if particles belong to different spheres
                if ((particle1->id < m_num_particles/2 && particle2->id >= m_num_particles/2) ||
                    (particle2->id < m_num_particles/2 && particle1->id >= m_num_particles/2)) {
                    // Calculate the distance between the centers of the particles
                    float distance = (particle1->position - particle2->position).norm();
                    float sum_radii = 2 * 0.05; // Assuming all particles have the same radius

                    // If particles are overlapping, handle collision
                    if (distance < 0.01) {
                        // Calculate relative velocity
                        Vector3f relative_velocity = particle2->position - particle1->position;

                        // Calculate impulse (change in momentum)
                        Vector3f impulse = (0.00171) * relative_velocity;
                        impulse[1] += 0.00001;

                        // Update velocities based on masses
                        particle1->velocity -= impulse;//Vector3f{.0000529,0,0.000001}; // Update velocity of particle 1
                        particle2->velocity += impulse;//Vector3f{.0000529,0,-0.000001}; // Update velocity of particle 2
                    }
                }
            }
        }


        // const float sphere_radius = 0.2f;
        // const Vector3f sphere_centroid(0, 0, -0.4); 
        // Vector3f relative_pos = particle->position - sphere_centroid;
        // if (relative_pos.norm() <= sphere_radius) {
            
        //     Vector3f v_rel = particle->velocity;
        //     float vn = v_rel.dot(relative_pos.normalized());

        //     if (vn < 0) {
        //         v_rel -= vn * relative_pos.normalized() * m_restitution;
        //         Vector3f vt = v_rel - vn * relative_pos.normalized();
        //         float vt_norm = vt.norm();
        //         if (vt_norm > 0) {
        //             float friction_factor = mu * vn / vt_norm;
        //             v_rel -= friction_factor * vt;
        //         }

        //         particle->velocity = v_rel;
        //     }
        //     particle->position = sphere_centroid + sphere_radius * relative_pos.normalized();
        // }

        // wall??
        if (particle->position.x() <= floor_height){
            Vector3f v_rel = particle->velocity;
            Vector3f normal = Vector3f(1.0f, 0, 0);
            float vn = v_rel.dot(normal);

            if (vn < 0) {
                Vector3f vt = v_rel - vn * normal;
                if (vt.norm() <= -mu * vn) {
                    particle->velocity = Vector3f::Zero();
                } else {
                    particle->velocity = vt + mu * vn * vt.normalized();
                }
            }
        }
    }
}

/**
 * STEP 10: Update particle positions
 * 
 * This function updates the positions of each particle by adding the velocity of the particle
 * multiplied by the timestep to the position of the particle. 
 */
void Snow::update_particle_positions() {
    #pragma omp parallel for
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
        Particle* particle = m_particles[particle_index];
        particle->position = particle->position + (particle->velocity * m_timestep);
    }
}

void Snow::update() {
    // STEP 1: Rasterize particle data to the grid
    rasterize_grid();

    // STEP 2: Compute particle volumes and densities
    if (m_first) { // first timestep only
        compute_cell_densities();
        compute_particle_volumes();
        m_first = false;
    }

    // STEP 3: Compute grid forces
    compute_grid_forces();

    // STEP 4: Update velocities on grid
    update_grid_velocity();

    // STEP 5: Grid based body collisions
    compute_grid_based_collisions();

    // STEP 6: Solve the linear system
    // solve_linear_system();

    // STEP 7: Update deformation gradient
    update_deformation_gradient();

    // STEP 8: Update particle velocities
    update_particle_velocities();

    // STEP 9: Particle-based body collisions
    compute_particle_based_collisions();

    // STEP 10: Update particle positions
    update_particle_positions();
}
