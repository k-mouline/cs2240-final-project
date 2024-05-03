#include "snow.h"

#include <iostream>
#include <fstream>

Snow::Snow() {
    m_particles = std::vector<Particle*>();
    m_grid = std::vector<GridCell*>(m_grid_size * m_grid_size * m_grid_size);

    for (int i = 0; i < m_num_particles; i++) {
        Particle* p = new Particle;
        p->id = i;
        // int spacing = sqrt(m_num_particles);
        // p->position = Vector3f(((i % spacing) / (float)(spacing)), ((i / spacing) / (float)(spacing)), 1);
        // randomly place the particle in a radius 0.25 sphere about the origin
        float radius = 0.25;
        float phi = 2 * M_PI * (rand() / (float)RAND_MAX);
        float theta = M_PI * (rand() / (float)RAND_MAX);
        float r = radius * pow((rand() / (float)RAND_MAX), 1.f / 3.f);
        float x = r * sin(theta) * cos(phi);
        float y = r * sin(theta) * sin(phi);
        float z = r * cos(theta);
        p->position = Vector3f(x, y, z);
        p->velocity = Vector3f::Zero();
        p->mass = 0.1;
        p->deformation_gradient_elastic = Matrix3f::Identity();
        p->deformation_gradient_plastic = Matrix3f::Identity();
        m_particles.push_back(p);
    }

    int totalCells = m_grid_size * m_grid_size * m_grid_size;
    for (int index = 0; index < totalCells; index++) {
        GridCell* cell = new GridCell;
        cell->grid_index = Vector3f(index % m_grid_size, (index / m_grid_size) % m_grid_size, index / (m_grid_size * m_grid_size));
        cell->mass = 0;
        cell->velocity = Vector3f::Zero();
        cell->force = Vector3f::Zero();
        m_grid[index] = cell;
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
    return Vector3f(floor(m_grid_size * (position.x() + 1) / 2), floor(m_grid_size * (position.y() + 1) / 2), floor(m_grid_size * (position.z() + 1) / 2));
}

int Snow::get_grid_index(Vector3f grid_coords) {
    // gets the index of the grid cell based off of its coordinates
    return grid_coords.x() + grid_coords.y() * m_grid_size + grid_coords.z() * m_grid_size * m_grid_size;
}

void Snow::rasterize_grid() {
    // first step is to rasterize particles into grid cells
    for (int grid_cell = 0; grid_cell < m_grid.size(); grid_cell++) {
        // for each grid cell, we need to calculate the mass and velocity
        float mass = 0;
        Vector3f velocity = Vector3f::Zero();
        // sum across the particles
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            mass += particle->mass + particle_weight(m_grid[grid_cell]->grid_index, particle->position);
        }
        // need to calculate velocity after since we need the normalization factor from the mass
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            velocity += particle->mass * particle->velocity * particle_weight(m_grid[grid_cell]->grid_index, particle->position) / mass;
        }
        m_grid[grid_cell]->mass = mass;
        m_grid[grid_cell]->velocity = velocity;
    }
}

float Snow::particle_weight(Vector3f grid_index, Vector3f evaluation_position) {
    // calcualting the influence of grid cell at grid_index on evaluation_position
    Vector3f eval_grid_coords = get_grid_coords(evaluation_position);
    float n_x = calculate_n((eval_grid_coords.x() - (grid_index.x())));
    float n_y = calculate_n((eval_grid_coords.y() - (grid_index.y())));
    float n_z = calculate_n((eval_grid_coords.z() - (grid_index.z())));
    return n_x * n_y * n_z;
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
    for (int grid_index = 0; grid_index < m_grid.size(); grid_index++)
        gradient += m_grid[grid_index]->velocity_star * (particle_weight_gradient(m_grid[grid_index]->grid_index, evaluation_position)).transpose();
    return gradient;
}

float Snow::calculate_n(float x) {
    if (0 <= abs(x) && abs(x) < 1)
        return (0.5 * pow(abs(x), 3)) - pow(abs(x), 2) + (2.f / 3.f);
    else if (1 <= abs(x) && abs(x) < 2)
        return ((-1.f / 6.f) * pow(abs(x), 3)) + pow(abs(x), 2) - (2 * abs(x)) + (4.f / 3.f);
    else
        return 0;
}

float Snow::calculate_n_prime(float x) {
    if (0 <= abs(x) && abs(x) < 1)
        return (1.5 * pow(abs(x), 2)) - (2 * abs(x));
    else if (1 <= abs(x) && abs(x) < 2)
        return ((-0.5) * pow(abs(x), 2)) + (2 * abs(x)) - 2;
    else
        return 0;
}

void Snow::compute_cell_densities() {
    for (int index = 0; index < m_grid.size(); index++) {
        GridCell* cell = m_grid[index];
        cell->density = cell->mass / pow(m_grid_spacing, 3);
    }
}

void Snow::compute_particle_volumes() {
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
        Particle* particle = m_particles[particle_index];
        float density = 0;
        for (int grid_index = 0; grid_index < m_grid.size(); grid_index++) {
            GridCell* cell = m_grid[grid_index];
            density += cell->density * particle_weight(cell->grid_index, particle->position);
        }
        particle->density = density;
        particle->volume = particle->mass / particle->density;
    }
}

Matrix3f Snow::psi(Matrix3f Fe, Matrix3f Fp){
    float Je = Fe.determinant();
    float Jp = Fp.determinant();
    float exponential = m_hardening * (1 - Jp);
    float mu_fp = m_mu_0 * exp(exponential);
    float lambda_fp = m_lambda_0 * exp(exponential);
    JacobiSVD<Matrix3f> svd(Fe, ComputeFullU | ComputeFullV);
    Matrix3f sigma = svd.singularValues().asDiagonal();
    Matrix3f Re = svd.matrixV() * sigma * svd.matrixV().transpose();

    return (2.f * mu_fp * (Fe - Re) * (Fe.transpose())) + ((lambda_fp * (Je - 1) * Je) * Matrix3f::Identity());
}

void Snow::compute_grid_forces(){
    for (int grid_index = 0; grid_index < m_grid.size(); grid_index++){
        GridCell* cell = m_grid[grid_index];
        Vector3f force = Vector3f::Zero();
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++) {
            Particle* particle = m_particles[particle_index];
            force += -particle->volume * psi(particle->deformation_gradient_elastic, particle->deformation_gradient_plastic) 
                                        * particle_weight_gradient(cell->grid_index, particle->position);
        }
        cell->force = force;
    }
}

void Snow::update_grid_velocity() {
    for (int grid_index = 0; grid_index < m_grid.size(); grid_index++) {
        GridCell* cell = m_grid[grid_index];
        if (cell->mass != 0) {
            float inverse_mass = 1.f / cell->mass;
            cell->force += m_gravity * cell->mass;
            cell->velocity_star = cell->velocity + cell->force * inverse_mass * m_timestep;
        }
    }
}

void Snow::compute_grid_based_collisions() {
    float floor_height = -0.75;
    float mu = 0.3f;

    for (GridCell* cell : m_grid) {
        Vector3f grid_index = cell->grid_index;
        Vector3f grid_pos = Vector3f(
            (grid_index.x() - m_grid_size / 2) * m_grid_spacing,
            (grid_index.y() - m_grid_size / 2) * m_grid_spacing,
            (grid_index.z() - m_grid_size / 2) * m_grid_spacing
        );
        if (grid_pos.z() <= floor_height) {
            Vector3f v_rel = cell->velocity;
            float vn = v_rel.z();

            if (vn < 0) { // THIS VERSION IS FROM OUR FRIEND
                v_rel.z() = -vn * m_restitution;
                Vector3f vt(v_rel.x(), v_rel.y(), 0);
                if (vt.norm() > 0) {
                    v_rel.x() -= mu * vn * vt.normalized().x();
                    v_rel.y() -= mu * vn * vt.normalized().y();
                }
                cell->velocity = v_rel;
            }
//             if (vn < 0) { // THIS IS THE VERSION I WROTE THAT DIDNT REALLY WORK
//                 Vector3f vt = v_rel - vn * up;
//                 if (vt.norm() <= -mu * vn)
//                     v_rel = Vector3f(0, 0, 0);
//                 else
//                     v_rel = vt + mu * vn * vt.normalized() / vt.norm();
//                 cell->velocity = v_rel;
//             }
        }
    }
}

void Snow::update_deformation_gradient(){
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++){
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
        // clamping
        S << clamp(singular_values(0, 0), 1 - m_compression, 1 + m_stretch), 0, 0,
                   0, clamp(singular_values(1, 1), 1 - m_compression, 1 + m_stretch), 0,
                   0, 0, clamp(singular_values(2, 2), 1 - m_compression, 1 + m_stretch);


        next_deformation_gradient_elastic = (u_matrix * S) * v_matrix.transpose();
        next_deformation_gradient_plastic = v_matrix * S.inverse() * u_matrix.transpose() * next_deformation_gradient;

        particle->deformation_gradient_elastic = next_deformation_gradient_elastic;
        particle->deformation_gradient_plastic = next_deformation_gradient_plastic;
    }
}

void Snow::update_particle_velocities() {
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++) {
        Particle* particle = m_particles[particle_index];
        Vector3f velocity_pic = Vector3f::Zero();
        Vector3f velocity_flip = particle->velocity;
        for (int grid_index = 0; grid_index < m_grid.size(); grid_index++) {
            GridCell* cell = m_grid[grid_index];
            velocity_pic += cell->velocity * particle_weight(cell->grid_index, particle->position);
            velocity_flip += (cell->velocity_star - cell->velocity) * particle_weight(cell->grid_index, particle->position);
        }
        particle->velocity = ((1 - m_alpha) * velocity_pic) + (m_alpha * velocity_flip);    
    }
}

void Snow::compute_particle_based_collisions() {
    float floor_height = 0.0;
    float restitution_coefficient = 0.0;
    float mu = 0.3f;

    for (Particle* particle : m_particles) {
        if (particle->position.z() <= floor_height) {
            Vector3f v_rel = particle->velocity;
            float vn = v_rel.z();

            if (vn < 0) { // THIS VERSION IS FROM OUR FRIEND
                v_rel.z() = -vn * restitution_coefficient;

                Vector3f vt(v_rel.x(), v_rel.y(), 0);
                if (vt.norm() > 0) {
                    v_rel.x() -= mu * vn * vt.normalized().x();
                    v_rel.y() -= mu * vn * vt.normalized().y();
                }
                particle->velocity = v_rel;
            }
//             if (vn < 0) { THIS IS WHAT I WROTE THAT DIDN'T RLY WORK
//                 Vector3f vt = v_rel - vn * up;
//                 if (vt.norm() <= -mu * vn)
//                     v_rel = Vector3f(0, 0, 0);
//                 else
//                     v_rel = vt + mu * vn * vt.normalized() / vt.norm();
//                 particle->velocity = v_rel;
//             }

            // Ensure particles do not end up below the floor
            particle->position.z() = floorHeight;
        }
    }
}


void Snow::update_particle_positions() {
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++) {
        Particle* particle = m_particles[particle_index];
        particle->position = particle->position + (particle->velocity * m_timestep);
    }
}

void Snow::compute_particle_based_collisions() {
    float floor_height = -0.75;
    float mu = 0.3f;

    for (Particle* particle : m_particles) {
        if (particle->position.z() <= floor_height) {
            Vector3f v_rel = particle->velocity;
            float vn = v_rel.z();

            if (vn < 0) { // THIS VERSION IS FROM OUR FRIEND
                v_rel.z() = -vn * m_restitution;

                Vector3f vt(v_rel.x(), v_rel.y(), 0);
                if (vt.norm() > 0) {
                    v_rel.x() -= mu * vn * vt.normalized().x();
                    v_rel.y() -= mu * vn * vt.normalized().y();
                }
                particle->velocity = v_rel;
            }
//             if (vn < 0) { THIS IS WHAT I WROTE THAT DIDN'T RLY WORK
//                 Vector3f vt = v_rel - vn * up;
//                 if (vt.norm() <= -mu * vn)
//                     v_rel = Vector3f(0, 0, 0);
//                 else
//                     v_rel = vt + mu * vn * vt.normalized() / vt.norm();
//                 particle->velocity = v_rel;
//             }

            // Ensure particles do not end up below the floor
            particle->position.z() = floor_height;
        }
    }
}

void Snow::update(){
    // STEP 1: Rasterize particle data to the grid
    rasterize_grid();

    // STEP 2: Compute particle volumes and densities
    if (m_first) {
        // first timestep only
        compute_cell_densities();
        compute_particle_volumes();
        m_first = false;
    }

    // STEP 3: Compute grid forces
    compute_grid_forces();

    // STEP 4: Update velocities on grid
    update_grid_velocity();

    // // TODO
    // // STEP 5: Grid based body collisions
    compute_grid_based_collisions();

    // TODO:
    // STEP 6: Solve the linear system
    // for now, we let v_i^n+1 = v_i^*

    // STEP 7: Update deformation gradient
    update_deformation_gradient();

    // STEP 8: Update particle velocities
    update_particle_velocities();

    // // TODO
    // // STEP 9: Particle-based body collisions
    compute_particle_based_collisions();

    // STEP 10: Update particle positions
    update_particle_positions();
}
