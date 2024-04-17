#include "snow.h"

#include <iostream>
#include <fstream>


Snow::Snow() {
    // initialize some particles
    m_particles = vector<Particle*>(m_num_particles);
    m_grid = vector<GridCell*>(m_grid_size * m_grid_size * m_grid_size);
    for (int i = 0; i < m_num_particles; i++){
        Particle* p;
        p->position = Vector3f(-0.5 + (1 / (i % 100)), -0.5 + (1 / (int)((i / 100))), 1);
        p->velocity = Vector3f::Zero(); // zero for now
        p->mass = 1.0;
        p->deformation_gradient_elastic = Matrix3f::Identity();
        p->deformation_gradient_plastic = Matrix3f::Zero();
        m_particles[i] = p;
    }
}

Vector3f Snow::get_grid_coords(Vector3f position){
    // gets the appropriate grid coordinates for a particle based off of its position
    return Vector3f(m_grid_size * (position.x() + 1) / 2, m_grid_size * (position.y() + 1) / 2, m_grid_size * (position.z() + 1) / 2);
}

int Snow::get_grid_index(Vector3f grid_coords){
    // gets the index of the grid cell based off of its coordinates
    return grid_coords.x() + grid_coords.y() * m_grid_size + grid_coords.z() * m_grid_size * m_grid_size;
}

void Snow::set_up_grid(){
    // first we want to set up each grid cell
    for (int index = 0; index < m_grid.size(); index++){
        GridCell* cell;
        cell->grid_index = Vector3f(index % m_grid_size, (index / m_grid_size) % m_grid_size, index / (m_grid_size * m_grid_size));
        cell->mass = 0;
        cell->velocity = Vector3f::Zero();
        m_grid[index] = cell;
    }
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
        float density = 0;
        for (int grid_index = 0; grid_index < m_grid.size(); grid_index++){
            density += m_grid[grid_index]->density * particle_weight(m_grid[grid_index]->grid_index, particle->position);
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
        cell->velocity += force / cell->mass;
    }
}

