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

  if (sqrt(num_particles) != floor(sqrt(num_particles))) {
    std::cerr << "Number of particles must be a perfect square." << std::endl;
    return 1;
  }

  json j;
  Snow::create_initial_json(j);

  Snow* s = new Snow(num_frames, num_particles, grid_size);

  
  Snow::add_particles_initial(j, s->get_particles());


  for (int i = 0; i < num_frames; i++) {
    s->update();
    Snow::add_particle_keyframe(j, s->get_particles(), i);
    std::cout << "Frame " << i << " added." << std::endl;
  }

  Snow::write_json_to_file(j);

  return 0;
}