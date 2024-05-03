#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreOgawa/All.h>
#include <iostream>
#include <vector>
#include <string>
#include "snow.h"

using namespace Alembic::Abc;
using namespace Alembic::AbcGeom;

// void Snow::write_scene_setup_to_abc(OObject& parent) {
//     OCompoundProperty sceneProps = parent.getProperties();
//     // Use the appropriate property classes directly.
//     OInt32ArrayProperty resolutionProp(sceneProps, "resolution", kSparse);
//     resolutionProp.set(Int32ArraySample({1920, 1080}));
//     OInt32ArrayProperty frameRangeProp(sceneProps, "frame_range", kSparse);
//     frameRangeProp.set(Int32ArraySample({1, 200}));
//     OInt32Property frameRateProp(sceneProps, "frame_rate", kSparse);
//     frameRateProp.set(24);
// }

// void Snow::write_camera_to_abc(OObject& parent) {
//     OCompoundProperty cameraProps = parent.getProperties();
//     OFloatArrayProperty positionProp(cameraProps, "position", kSparse);
//     positionProp.set(FloatArraySample({10.0f, 10.0f, 10.0f}));
//     OFloatArrayProperty rotationProp(cameraProps, "rotation", kSparse);
//     rotationProp.set(FloatArraySample({0.0f, 0.0f, 0.0f}));
//     OFloatProperty fovProp(cameraProps, "fov", kSparse);
//     fovProp.set(60.0f);
// }

// void Snow::write_ground_to_abc(OObject& parent) {
//     OCompoundProperty groundProps = parent.getProperties();
//     OStringProperty typeProp(groundProps, "type", kSparse);
//     typeProp.set("plane");
//     OFloatArrayProperty positionProp(groundProps, "position", kSparse);
//     positionProp.set(FloatArraySample({0.0f, 0.0f, -5.0f}));
//     OFloatArrayProperty scaleProp(groundProps, "scale", kSparse);
//     scaleProp.set(FloatArraySample({50.0f, 1.0f, 50.0f}));
// }

// void Snow::write_particles_to_abc(OObject& parent, std::vector<Particle*>& particles) {
//     OCompoundProperty particlesArray(parent.getProperties(), "particles");
//     for (Particle* p : particles) {
//         OCompoundProperty particleProps(particlesArray, std::to_string(p->id));
//         OInt32Property idProp(particleProps, "id", kSparse);
//         idProp.set(p->id);
//         OStringProperty typeProp(particleProps, "type", kSparse);
//         typeProp.set("point");
//         OFloatArrayProperty positionProp(particleProps, "position", kSparse);
//         positionProp.set(FloatArraySample({p->position.x(), p->position.y(), p->position.z()}));
//     }
// }

// void Snow::write_abc_to_file(const std::string& filename, std::vector<Particle*>& particles) {
//     OArchive archive(Alembic::AbcCoreOgawa::WriteArchive(), filename);
//     OObject topObject(archive, kTop);
//     write_scene_setup_to_abc(topObject);
//     write_camera_to_abc(topObject);
//     write_ground_to_abc(topObject);
//     write_particles_to_abc(topObject, particles);
// }

OArchive Snow::m_archive;
OObject Snow::m_root;
std::vector<OXform> Snow::m_particleXforms;

void Snow::initialize_alembic(const std::string& filename) {
    m_archive = OArchive(Alembic::AbcCoreOgawa::WriteArchive(), filename);
    OObject m_root(m_archive, kTop);
    write_initial_scene_setup();
}

void Snow::write_initial_scene_setup() {
    OCompoundProperty sceneProps = m_root.getProperties();
    OInt32ArrayProperty resolutionProp(sceneProps, "resolution", kSparse);
    resolutionProp.set(Int32ArraySample({1920, 1080}));
    OInt32ArrayProperty frameRangeProp(sceneProps, "frame_range", kSparse);
    frameRangeProp.set(Int32ArraySample({1, 200}));
    OInt32Property frameRateProp(sceneProps, "frame_rate", kSparse);
    frameRateProp.set(24);

    OCompoundProperty cameraProps = m_root.getProperties();
    OFloatArrayProperty camPositionProp(cameraProps, "position", kSparse);
    camPositionProp.set(FloatArraySample({10.0f, 10.0f, 10.0f}));
    OFloatArrayProperty rotationProp(cameraProps, "rotation", kSparse);
    rotationProp.set(FloatArraySample({0.0f, 0.0f, 0.0f}));
    OFloatProperty fovProp(cameraProps, "fov", kSparse);
    fovProp.set(60.0f);

    OCompoundProperty groundProps = m_root.getProperties();
    OStringProperty typeProp(groundProps, "type", kSparse);
    typeProp.set("plane");
    OFloatArrayProperty groundPositionProp(groundProps, "position", kSparse);
    groundPositionProp.set(FloatArraySample({0.0f, 0.0f, -5.0f}));
    OFloatArrayProperty scaleProp(groundProps, "scale", kSparse);
    scaleProp.set(FloatArraySample({50.0f, 1.0f, 50.0f}));
}

void Snow::add_initial_particles(const std::vector<Particle*>& particles) {
    OObject particlesObj(m_root, "particles");
    for (Particle* p : particles) {
        OXform xform(particlesObj, std::to_string(p->id));
        m_particleXforms.push_back(xform);
        OCompoundProperty prop(xform.getProperties());
        OInt32Property(prop, "id", kSparse).set(p->id);
        OStringProperty(prop, "type", kSparse).set("point");
        OFloatArrayProperty(prop, "position", kSparse).set(FloatArraySample({p->position.x(), p->position.y(), p->position.z()}));
    }
}

void Snow::add_particle_keyframes(const std::vector<Particle*>& particles, int frame) {
    for (size_t i = 0; i < particles.size(); i++) {
        Particle* p = particles[i];
        OXform& xform = m_particleXforms[i];
        OFloatArrayProperty positionProp(xform.getProperties(), "position", kSparse);
        positionProp.set(FloatArraySample({p->position.x(), p->position.y(), p->position.z()}));
    }
}

void Snow::finalize_alembic() {
    m_archive = OArchive(); // Closing the archive
}
