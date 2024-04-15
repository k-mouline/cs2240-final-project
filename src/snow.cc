#include "snow.h"

#include <iostream>
#include <fstream>


Snow::Snow() {
    // initialize some particles
    m_particles = vector<Particle>(m_num_particles);
    for (int i = 0; i < m_num_particles; i++){
        Particle p;
        p.position = Vector3f(-0.5 + (1 / (i % 100)), -0.5 + (1 / (int)((i / 100))), 1);
        p.velocity = Vector3f::Zero(); // zero for now
        p.mass = 1.0;
        p.deformation_gradient = Matrix3f::Identity();
        m_particles[i] = p;
    }
}

