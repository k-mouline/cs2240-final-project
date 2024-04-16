#pragma once

#include <vector>
#include "Eigen/StdVector"

using namespace std;
using namespace Eigen;

class Snow {
    public:
        struct Particle {
            Vector3f position;
            Vector3f velocity;
            float mass;
            Matrix3f deformation_gradient;
            float density;
            float volume;
        };
        struct GridCell{
            Vector3f grid_index;
            float mass;
            Vector3f velocity;
            float density;
        };
        Snow();
        Vector3f get_grid_coords(Vector3f position);
        int get_grid_index(Vector3f grid_coords);
        void set_up_grid();
        void rasterize_grid();
        float particle_weight(Vector3f grid_index, Vector3f evaluation_position);
        float calculate_n(float x);
        void compute_cell_densities();
        void compute_particle_volumes();
    private:
        vector<Particle*> m_particles;
        vector<GridCell*> m_grid;
        int m_num_particles = 1000;
        int m_grid_size = 10;
        int m_grid_spacing = 2.0 / m_grid_size;
};