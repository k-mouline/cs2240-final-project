#pragma once

#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreOgawa/All.h>
#include <Alembic/AbcCoreHDF5/All.h>
#include "Eigen"
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
            Matrix3f deformation_gradient;
        };
        Snow();
        ~Snow();
        Vector3f get_grid_coords(Vector3f position);
        int get_grid_index(Vector3f grid_coords);
        void rasterize_grid();
        float particle_weight(Vector3f grid_index, Vector3f evaluation_position);
        Vector3f particle_weight_gradient(Vector3f grid_index, Vector3f evaluation_position);
        Matrix3f particle_velocity_gradient(Vector3f evaluation_position);
        float calculate_n(float x);
        float calculate_n_prime(float x);
        void compute_cell_densities();
        void compute_particle_volumes();
        Matrix3f psi(Matrix3f fe, Matrix3f fp);
        void compute_grid_forces();
        void update_grid_velocity();
        void compute_grid_based_collisions();
        void solve_linear_system();
        void update_deformation_gradient();
        void update_particle_velocities();
        void compute_particle_based_collisions();
        void update_particle_positions();
        void update();

        // GETTER FUNCTIONS
        vector<Particle*> get_particles() { return m_particles; };

        // JSON FUNCTIONS
        static void create_initial_json(nlohmann::json &j);
        static void add_particles_initial(nlohmann::json &j, vector<Particle*> particles);
        static void add_particle_keyframe(nlohmann::json &j, vector<Particle*> particles, int frame);
        static void write_json_to_file(nlohmann::json &j);

        // ABC FUNCTIONS
        static void write_scene_setup_to_abc(Alembic::AbcGeom::OObject& parent);
        static void write_camera_to_abc(Alembic::AbcGeom::OObject& parent);
        static void write_ground_to_abc(Alembic::AbcGeom::OObject& parent);
        static void write_particles_to_abc(Alembic::AbcGeom::OObject& parent, std::vector<Particle*>& particles);
        static void write_abc_to_file(const std::string& filename, std::vector<Particle*>& particles);

        static void initialize_alembic(const std::string& filename);
        static void write_initial_scene_setup();
        static void add_initial_particles(const std::vector<Particle*>& particles);
        static void add_particle_keyframes(const std::vector<Particle*>& particles, int frame);
        static void finalize_alembic();

        const static int m_num_frames = 20;

    private:
        vector<Particle*> m_particles;
        vector<GridCell*> m_grid;
        int m_num_particles = 400; // must be perfect square
        int m_grid_size = 5;
        float m_grid_spacing = 2.0 / m_grid_size;
        Vector3f m_gravity = Vector3f(0, 0, -9.8);
        bool m_first = true;
        float m_timestep = (1.f/60.f);
        float m_alpha = 0.95;
        float m_hardening = 10;
        float m_youngs_modulus = 1.4e5;
        float m_poissons_ratio = 0.2;
        float m_lambda_0 = (m_youngs_modulus * m_poissons_ratio) / ((1 + m_poissons_ratio) * (1 - 2 * m_poissons_ratio));
        float m_mu_0 = m_youngs_modulus / (2 * (1 + m_poissons_ratio));
        float m_compression = 2.5e-2;
        float m_stretch = 7.5e-3;
        float m_restitution = 0.15;
        static Alembic::Abc::OArchive m_archive;
        static Alembic::AbcGeom::OObject m_root;
        static std::vector<Alembic::AbcGeom::OXform> m_particleXforms;
};