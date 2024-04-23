#pragma once

#include "Eigen/StdVector"
#include "Eigen/SVD"
#include "json.hpp"

#include <vector>

using namespace std;
using namespace Eigen;

class Snow {
    public:
        struct Particle {
            int id;
            Vector3f position;
            Vector3f velocity;
            float mass;
            Matrix3f deformation_gradient_elastic;
            Matrix3f deformation_gradient_plastic;
            float density;
            float volume;
        };
        struct GridCell{
            Vector3f grid_index;
            float mass;
            Vector3f velocity;
            Vector3f velocity_star;
            Vector3f velocity_new;
            float density;
            Vector3f force;
        };
        Snow();
        ~Snow();
        Vector3f get_grid_coords(Vector3f position);
        int get_grid_index(Vector3f grid_coords);
        void rasterize_grid();
        float particle_weight(Vector3f grid_index, Vector3f evaluation_position);
        Vector3f particle_weight_gradient(Vector3f grid_index, Vector3f evaluation_position);
        Vector3f particle_velocity_gradient(Vector3f evaluation_position);
        float calculate_n(float x);
        float calculate_n_prime(float x);
        void compute_cell_densities();
        void compute_particle_volumes();
        void compute_grid_forces();
        void update_grid_velocity();
        void update_deformation_gradient();
        void update_particle_velocities();
        void update_particle_positions();
        void update();

        // GETTER FUNCTIONS
        vector<Particle*> get_particles() { return m_particles; };

        // JSON FUNCTIONS
        static void create_initial_json(nlohmann::json &j);
        static void add_particles_initial(nlohmann::json &j, vector<Particle*> particles);
        static void add_particle_keyframe(nlohmann::json &j, vector<Particle*> particles, int frame);
        static void write_json_to_file(nlohmann::json &j);

    private:
        vector<Particle*> m_particles;
        vector<GridCell*> m_grid;
        int m_num_particles = 1000;
        int m_grid_size = 10;
        int m_grid_spacing = 2.0 / m_grid_size;
        Vector3f m_gravity = Vector3f(0, -9.8, 0);
        bool m_first = true;
        float m_timestep = 0.01;
        float m_alpha = 0.95;
};