#include <iostream>
#include <fstream>
#include "json.hpp"
#include "snow.h"

// using json = nlohmann::json;

// int main() {
//   json j;
//   Snow::create_initial_json(j);

//   Snow* s = new Snow();

//   Snow::add_particles_initial(j, s->get_particles());

//   for (int i = 0; i < Snow::m_num_frames; i++) {
//     s->update();
//     Snow::add_particle_keyframe(j, s->get_particles(), i);
//     std::cout << "Frame " << i << " added." << std::endl;
//   }

//   Snow::write_json_to_file(j);

//   return 0;
// }

int main() {
    Snow::initialize_alembic("data/simulation.abc");
    Snow* s = new Snow();
    Snow::add_initial_particles(s->get_particles());

    for (int i = 0; i < Snow::m_num_frames; i++) {
        s->update();
        Snow::add_particle_keyframes(s->get_particles(), i);
        std::cout << "Frame " << i << " added." << std::endl;
    }

    Snow::finalize_alembic();
    return 0;
}