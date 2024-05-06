// #include <iostream>
// #include <vector>
// #include <map>
// #include <string>

// using namespace Alembic::Abc;
// using namespace Alembic::AbcGeom;

// void Snow::write_abc_to_file(const std::string& filename, std::vector<Particle*>& particles) {
//     // Create an Alembic archive for writing
//     OArchive archive(Alembic::AbcCoreOgawa::WriteArchive(), filename);

//     OObject topObject(archive, kTop);

//     // Write scene setup data
//     write_scene_setup_to_abc(topObject);

//     // Write camera data
//     write_camera_to_abc(topObject);

//     // Write ground data
//     write_ground_to_abc(topObject);

//     // Write particles data
//     write_particles_to_abc(topObject, particles);

//     // Save the archive
//     archive.getCore().getArchive()->save();
// }

// void Snow::write_scene_setup_to_abc(OObject& parent) {
//     OCompoundProperty sceneProps = parent.getProperties();
//     sceneProps.createScalarProperty<std::vector<int32_t>>("resolution").set(std::vector<int32_t>{1920, 1080});
//     sceneProps.createScalarProperty<std::vector<int32_t>>("frame_range").set(std::vector<int32_t>{1, 200});
//     sceneProps.createScalarProperty<int32_t>("frame_rate").set(24);.
// }

// void Snow::write_camera_to_abc(OObject& parent) {
//     OCompoundProperty cameraProps = parent.getProperties();
//     cameraProps.createScalarProperty<std::vector<float>>("position").set(std::vector<float>{10.0f, 10.0f, 10.0f});
//     cameraProps.createScalarProperty<std::vector<float>>("rotation").set(std::vector<float>{0.0f, 0.0f, 0.0f});
//     cameraProps.createScalarProperty<float>("fov").set(60.0f);
// }

// void Snow::write_ground_to_abc(OObject& parent) {
//     OCompoundProperty groundProps = parent.getProperties();
//     groundProps.createScalarProperty<std::string>("type").set("plane");
//     groundProps.createScalarProperty<std::vector<float>>("position").set(std::vector<float>{0.0f, 0.0f, -5.0f});
//     groundProps.createScalarProperty<std::vector<float>>("scale").set(std::vector<float>{50.0f, 1.0f, 50.0f});
//     groundProps.createScalarProperty<std::vector<float>>("material.color").set(std::vector<float>{1.0f, 1.0f, 1.0f, 1.0f});
//     groundProps.createScalarProperty<float>("material.roughness").set(0.9f);
//     groundProps.createScalarProperty<float>("material.metallic").set(0.0f);
// }

// void Snow::write_particles_to_abc(OObject& parent, std::vector<Particle*>& particles) {
//     OCompoundProperty particlesArray = parent.getProperties().createCompoundProperty("particles");
//     for (Particle* p : particles) {
//         OCompoundProperty particleProps = particlesArray.getSchema().createCompoundProperty();
//         particleProps.createScalarProperty<int32_t>("id").set(p->id);
//         particleProps.createScalarProperty<std::string>("name").set("particle " + std::to_string(p->id));
//         particleProps.createScalarProperty<std::string>("type").set("point");
//         particleProps.createScalarProperty<std::vector<float>>("position").set({p->position.x(), p->position.y(), p->position.z()});
//         particleProps.createScalarProperty<std::vector<float>>("scale").set({1.0f, 1.0f, 1.0f});
//         particleProps.createScalarProperty<std::vector<float>>("color").set({1.0f, 1.0f, 1.0f, 1.0f});
//         particleProps.createScalarProperty<float>("size").set(0.01f);

//         OCompoundProperty animationProps = particleProps.createCompoundProperty("animation");
//         for (int frame = 1; frame <= snow::m_num_frames; ++frame) { 
//             OCompoundProperty keyframeProps = animationProps.getSchema().createCompoundProperty();
//             keyframeProps.createScalarProperty<int32_t>("frame").set(frame);
//             keyframeProps.createScalarProperty<std::vector<float>>("position").set({p->position.x(), p->position.y(), p->position.z()});
//         }
//     }
// }