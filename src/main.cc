#include <iostream>
#include <fstream>
#include "json.hpp"
#include "snow.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << " <num_frames> <num_particles> <grid_size>" << std::endl;
    return 1;
  }


  int num_frames = std::atoi(argv[1]);
  int num_particles = std::atoi(argv[2]);
  int grid_size = std::atoi(argv[3]);
  string shape = std::string(argv[4]);

  std::cout << "Creating snow simulation of shape " << shape << " with " << num_frames << " frames, " << num_particles << " particles, and a grid size of " << grid_size << std::endl;

  json j;
  Snow::create_initial_json(j, num_frames);

  Snow* s = new Snow(num_frames, num_particles, grid_size, shape);

  Snow::add_particles_initial(j, s->get_particles());


  for (int i = 0; i < num_frames; i++) {
    s->update();
    Snow::add_particle_keyframe(j, s->get_particles(), i);
    std::cout << "Frame " << i << " added." << std::endl;
  }

  Snow::write_json_to_file(j);

  return 0;
}

// int main() {
//     Snow::initialize_alembic("data/simulation.abc");
//     Snow* s = new Snow();
//     Snow::add_initial_particles(s->get_particles());

//     for (int i = 0; i < Snow::m_num_frames; i++) {
//         s->update();
//         Snow::add_particle_keyframes(s->get_particles(), i);
//         std::cout << "Frame " << i << " added." << std::endl;
//     }

//     Snow::finalize_alembic();
//     return 0;
// }