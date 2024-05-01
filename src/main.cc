#include <iostream>
#include <fstream>
#include "json.hpp"
#include "snow.h"

using json = nlohmann::json;

int main() {
  json j;
  Snow::create_initial_json(j);

  Snow* s = new Snow();

  
  Snow::add_particles_initial(j, s->get_particles());


  for (int i = 0; i < Snow::m_num_frames; i++) {
    s->update();
    Snow::add_particle_keyframe(j, s->get_particles(), i);
    std::cout << "Frame " << i << " added." << std::endl;
  }

  Snow::write_json_to_file(j);

  return 0;
}