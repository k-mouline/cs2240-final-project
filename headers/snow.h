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
        };
        Snow();
    private:
        vector<Particle> m_particles;
        int m_num_particles = 1000;
        int m_grid_size = 10;
};