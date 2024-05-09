#include "json.hpp"
#include "snow.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

/**
 * WHEN TO CALL EACH FUNCTION
 * 
 * create_initial_json -- called once at beginning of simulation
 * add_particles_initial -- called once at beginning of simulation after particle generation
 * add_particle_keyframe -- called once per frame, after new positions for each particle is generated
 * write_json_to_file -- called once at end of simulation
 */

/**
 * Create the initial json object
 * Scene setup, camera, ground data added
 * Particle data not yet added
 */
void Snow::create_initial_json(json &j, int num_frames) {
  // scene setup
  j["scene_setup"]["resolution"] = {640, 360};
  j["scene_setup"]["frame_range"] = {1, num_frames};
  j["scene_setup"]["frame_rate"] = 24;

  // camera data
  j["camera"]["position"] = {10, 10, 10};
  j["camera"]["rotation"] = {0, 0, 0};
  j["camera"]["fov"] = 60;

  // particles is an array of objects of size m_num_particles
  j["particles"] = json::array();

  // ground data
  j["ground"]["type"] = "plane";
  j["ground"]["position"] = {0, 0, -0.775};
  j["ground"]["scale"] = {3, 3, 3};
  j["ground"]["material"]["color"] = {1, 1, 1, 1};
  j["ground"]["material"]["roughness"] = 0.9;
  j["ground"]["material"]["metallic"] = 0.0;

  // wall data
  // j["wall"]["type"] = "plane";
  // j["wall"]["position"] = {-0.785, 0, 0};
  // j["wall"]["scale"] = {3, 3, 3};
  // j["wall"]["material"]["color"] = {1, 1, 1, 1};
  // j["wall"]["material"]["roughness"] = 0.9;
  // j["wall"]["material"]["metallic"] = 0.0;

  j["ball"]["type"] = "sphere";
  j["ball"]["position"] = {0, 0, -0.3};
  j["ball"]["radius"] = 0.6;
  j["ball"]["material"]["color"] = {1, 1, 1, 1};
  j["ball"]["material"]["roughness"] = 0.9;
  j["ball"]["material"]["metallic"] = 0.0;

}

/**
 * Adds particles to the json object in their initial state
 * Name, Type, Position, Scale, Color, Size, are added
 * Animations are not yet in the json object
 */
void Snow::add_particles_initial(nlohmann::json &j, vector<Particle*> particles) {
  std::map<int, json> particles_map;
  for (Particle* p : particles) {
    json particle = {
      {"id", p->id},
      {"name", "particle " + std::to_string(p->id)},
      {"type", "point"},
      {"position", {p->position.x(), p->position.y(), p->position.z()}},
      {"scale", {1, 1, 1}},
      {"color", {1, 1, 1, 1}}, // RGBA
      {"size", 0.005},
      {"animation", json::array()}
    };
    particles_map[p->id] = particle;
  }

  for (const auto& entry : particles_map) {
    j["particles"].push_back(entry.second);
  }
}

/**
 * Adds a keyframe to the json object for each particle
 * The keyframe contains the frame number provided and the position of the
 * particle when the keyframe was added
 */
void Snow::add_particle_keyframe(nlohmann::json &j, vector<Particle*> particles, int frame) {
  for (Particle* p : particles) {
    json keyframe = {
      {"frame", frame},
      {"position", {p->position.x(), p->position.y(), p->position.z()}}
    };
    j["particles"][p->id]["animation"].push_back(keyframe);
  }
}

/**
 * Writes the json object to a file (data/simulation.json)
 * If the file cannot be opened or writing fails, an error message is printed
 */
void Snow::write_json_to_file(nlohmann::json &j) {
    std::ofstream o("data/simulation.json");
    if (!o) {
        std::cerr << "Error: Unable to open file for writing" << std::endl;
        return;
    }
    o << std::setw(4) << j << std::endl;
    if (!o) {
        std::cerr << "Error: Failed to write data to file" << std::endl;
    }
}
