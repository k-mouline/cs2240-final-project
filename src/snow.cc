#include "snow.h"

#include <iostream>
#include <fstream>

Snow::Snow() {
    m_particles = std::vector<Particle*>(m_num_particles, nullptr);
    m_grid = std::vector<GridCell*>(m_grid_size * m_grid_size * m_grid_size, nullptr);

    for (int i = 0; i < m_num_particles; i++) {
        Particle* p = new Particle;
        p->id = i;
        p->position = Vector3f(-0.5 + (1.0 / (i % 100)), -0.5 + (1.0 / (i / 100)), 1);
        p->velocity = Vector3f::Zero();
        p->mass = 1.0;
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
    for (Particle* particle : m_particles) {
        delete particle;
    }
    m_particles.clear();

    for (GridCell* cell : m_grid) {
        delete cell;
    }
    m_grid.clear();
}

Vector3f Snow::get_grid_coords(Vector3f position){
    // gets the appropriate grid coordinates for a particle based off of its position
    return Vector3f(m_grid_size * (position.x() + 1) / 2, m_grid_size * (position.y() + 1) / 2, m_grid_size * (position.z() + 1) / 2);
}

int Snow::get_grid_index(Vector3f grid_coords){
    // gets the index of the grid cell based off of its coordinates
    return grid_coords.x() + grid_coords.y() * m_grid_size + grid_coords.z() * m_grid_size * m_grid_size;
}

void Snow::rasterize_grid(){
    // first step is to rasterize particles into grid cells
    for (int grid_cell = 0; grid_cell < m_grid.size(); grid_cell++){
        // for each grid cell, we need to calculate the mass and velocity
        float mass = 0;
        Vector3f velocity = Vector3f::Zero();
        // sum across the particles
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++){
            Particle* particle = m_particles[particle_index];
            mass += particle->mass + particle_weight(m_grid[grid_cell]->grid_index, particle->position);
        }
        // need to calculate velocity after since we need the normalization factor from the mass
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++){
            Particle* particle = m_particles[particle_index];
            velocity += particle->mass * particle->velocity * particle_weight(m_grid[grid_cell]->grid_index, particle->position) / mass;
        }
        m_grid[grid_cell]->mass = mass;
        m_grid[grid_cell]->velocity = velocity;
    }
}

float Snow::particle_weight(Vector3f grid_index, Vector3f evaluation_position){
    // calcualting the influence of grid cell at grid_index on evaluation_position
    float h = m_grid_spacing; // h represents the grid spacing
    float n_x = calculate_n((evaluation_position.x() - (grid_index.x() * h)) / h);
    float n_y = calculate_n((evaluation_position.y() - (grid_index.y() * h)) / h);
    float n_z = calculate_n((evaluation_position.z() - (grid_index.z() * h)) / h);
    return n_x * n_y * n_z;
}

Vector3f Snow::particle_weight_gradient(Vector3f grid_index, Vector3f evaluation_position){
    // calculating the gradient of the influence of grid cell at grid_index on evaluation_position
    float h = m_grid_spacing; // h represents the grid spacing
    float n_x = calculate_n((evaluation_position.x() - (grid_index.x() * h)) / h);
    float n_y = calculate_n((evaluation_position.y() - (grid_index.y() * h)) / h);
    float n_z = calculate_n((evaluation_position.z() - (grid_index.z() * h)) / h);
    float n_x_grad = calculate_n_prime((evaluation_position.x() - (grid_index.x() * h)) / h);
    float n_y_grad = calculate_n_prime((evaluation_position.y() - (grid_index.y() * h)) / h);
    float n_z_grad = calculate_n_prime((evaluation_position.z() - (grid_index.z() * h)) / h);
    return Vector3f(n_x_grad * n_y * n_z, n_x * n_y_grad * n_z, n_x * n_y * n_z_grad);
}

Vector3f Snow::particle_velocity_gradient(Vector3f evaluation_position){
    Vector3f gradient = Vector3f::Zero();
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            for (int k = -1; k < 2; k++){
                Vector3f grid_index = Vector3f(evaluation_position.x() + i, evaluation_position.y() + j, evaluation_position.z() + k);
                if (grid_index.x() >= 0 && grid_index.x() < m_grid_size && grid_index.y() >= 0 && 
                    grid_index.y() < m_grid_size && grid_index.z() >= 0 && grid_index.z() < m_grid_size){
                    int grid_index_int = get_grid_index(grid_index);
                    gradient += m_grid[grid_index_int]->velocity_star * (particle_weight_gradient(grid_index, evaluation_position)).transpose();
                }
            }
        }
    }
    return gradient;
}

float Snow::calculate_n(float x){
    if (0 <= abs(x) && abs(x) < 1){
        return (0.5 * pow(abs(x), 3)) - pow(abs(x), 2) + (2.f / 3.f);
    }
    else if (1 <= abs(x) && abs(x) < 2){
        return ((-1.f / 6.f) * pow(abs(x), 3)) + pow(abs(x), 2) - (2 * abs(x)) + (4.f / 3.f);
    }
    else {
        return 0;
    }
}

float Snow::calculate_n_prime(float x){
    if (0 <= abs(x) && abs(x) < 1){
        return (1.5 * pow(abs(x), 2)) - (2 * abs(x));
    }
    else if (1 <= abs(x) && abs(x) < 2){
        return ((-0.5) * pow(abs(x), 2)) + (2 * abs(x)) - 2;
    }
    else {
        return 0;
    }

}

void Snow::compute_cell_densities(){
    for (int index = 0; index < m_grid.size(); index++){
        GridCell* cell = m_grid[index];
        cell->density = cell->mass / pow(m_grid_spacing, 3);
    }
}

void Snow::compute_particle_volumes(){
    for (int particle_index = 0; particle_index < m_num_particles; particle_index++){
        Particle* particle = m_particles[particle_index];
        Vector3f grid_coords = get_grid_coords(particle->position);
        float density = 0;
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                for (int k = -1; k < 2; k++){
                    Vector3f grid_index = Vector3f(grid_coords.x() + i, grid_coords.y() + j, grid_coords.z() + k);
                    if (grid_index.x() >= 0 && grid_index.x() < m_grid_size && grid_index.y() >= 0 && 
                        grid_index.y() < m_grid_size && grid_index.z() >= 0 && grid_index.z() < m_grid_size){
                        int grid_index_int = get_grid_index(grid_index);
                        density += m_grid[grid_index_int]->density * particle_weight(m_grid[grid_index_int]->grid_index, particle->position);
                    }
                }
            }
        }
        particle->density = density;
        particle->volume = particle->mass / particle->density;
    }
}

void Snow::compute_grid_forces(){
    for (int grid_index = 0; grid_index < m_grid.size(); grid_index++){
        GridCell* cell = m_grid[grid_index];
        Vector3f force = Vector3f::Zero();
        for (int particle_index = 0; particle_index < m_num_particles; particle_index++){
            Particle* particle = m_particles[particle_index];
            force += -particle->volume * 1 * particle_weight_gradient(cell->grid_index, particle->position);
            // placeholders for now. particle->volume needs to be multiplied by the determinant of the particle's plastic deformation gradient
            // and the 1 is the complicated thing
        }
        cell->force = force;
    }
}

void Snow::update_grid_velocity(){
    for (int grid_index = 0; grid_index < m_grid.size(); grid_index++){
        GridCell* cell = m_grid[grid_index];
        if (cell->mass != 0){
            float inverse_mass = 1.f / cell->mass;
            cell->force += m_gravity * cell->mass;
            cell->velocity_star = cell->velocity + cell->force * inverse_mass * m_timestep;
        }
    }
}

void Snow::update_deformation_gradient(){
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++){
        Particle* particle = m_particles[particle_index];
        // temporarily define the parts of the deformation gradient
        Matrix3f next_deformation_gradient_elastic = (Matrix3f::Identity() + m_timestep * particle_velocity_gradient(particle->position)) * particle->deformation_gradient_elastic;
        Matrix3f next_deformation_gradient_plastic = particle->deformation_gradient_plastic;
        Matrix3f next_deformation_gradient = next_deformation_gradient_elastic * next_deformation_gradient_plastic;

        // take the part of the elastic deformation gradient that exceeds threshold and push it into plastic
        JacobiSVD<Matrix3f> svd(next_deformation_gradient_elastic, ComputeFullU | ComputeFullV);
        Matrix3f u_matrix = svd.matrixU();
        Matrix3f v_matrix = svd.matrixV();
        Vector3f singular_values = svd.singularValues();

        next_deformation_gradient_elastic = u_matrix * singular_values * v_matrix.transpose();
        next_deformation_gradient_plastic = v_matrix * singular_values.inverse() * u_matrix.transpose() * next_deformation_gradient;

        particle->deformation_gradient_elastic = next_deformation_gradient_elastic;
        particle->deformation_gradient_plastic = next_deformation_gradient_plastic;
    }
}

void Snow::update_particle_velocities(){
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++){
        Particle* particle = m_particles[particle_index];
        Vector3f grid_coords = get_grid_coords(particle->position);
        Vector3f velocity_pic = Vector3f::Zero();
        Vector3f velocity_flip = particle->velocity;
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                for (int k = -1; k < 2; k++){
                    Vector3f grid_index = Vector3f(grid_coords.x() + i, grid_coords.y() + j, grid_coords.z() + k);
                    if (grid_index.x() >= 0 && grid_index.x() < m_grid_size && grid_index.y() >= 0 && 
                        grid_index.y() < m_grid_size && grid_index.z() >= 0 && grid_index.z() < m_grid_size){
                        int grid_index_int = get_grid_index(grid_index);
                        velocity_pic += m_grid[grid_index_int]->velocity * particle_weight(grid_index, particle->position);
                        velocity_flip += (m_grid[grid_index_int]->velocity_star - m_grid[grid_index_int]->velocity) * particle_weight(grid_index, particle->position);
                    }
                }
            }
        }
        particle->velocity = ((1 - m_alpha) * velocity_pic) + (m_alpha * velocity_flip);
    }
}

void Snow::update_particle_positions(){
    for (int particle_index = 0; particle_index < m_particles.size(); particle_index++){
        Particle* particle = m_particles[particle_index];
        // TODO: at what point do we set velocity_n to be velocity_n+1
        particle->position = particle->position + (particle->velocity * m_timestep);
    }
}

void Snow::update(){
    // STEP 1: Rasterize particle data to the grid
    rasterize_grid();

    // STEP 2: Compute particle volumes and densities
    if (m_first){
        // first timestep only
        compute_cell_densities();
        compute_particle_volumes();
        m_first = false;
    }

    // STEP 3: Compute grid forces
    compute_grid_forces();

    // STEP 4: Update velocities on grid
    update_grid_velocity();

    // TODO
    // STEP 5: Grid based body collisions

    // TODO 
    // STEP 6: Solve the linear system
    // for now, we let v_i^n+1 = v_i^*

    // TODO
    // STEP 7: Update deformation gradient
    update_deformation_gradient();

    // STEP 8: Update particle velocities
    update_particle_velocities();

    // TODO
    // STEP 9: Particle-based body collisions

    // STEP 10: Update particle positions
    update_particle_positions();
}
