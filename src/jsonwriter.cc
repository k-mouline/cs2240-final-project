#include <headers/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int make_json() {
    json j = {};
 
    std::ofstream file("data.json");
    if (file.is_open()) {
        file << std::setw(4) << j << std::endl;
        file.close();
        std::cout << "JSON data has been written to data.json" << std::endl;
        return 0;
    } else {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }
}

void add_keyframe(Particle particle) {

}

void add_particle(Particle particle) {
    
}