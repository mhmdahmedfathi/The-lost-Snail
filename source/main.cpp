#include <iostream>
#include <fstream>
#include <flags/flags.h>
#include <json/json.hpp>
#include <imgui.h>


#include <application.hpp>

#include "states/play-state.hpp"
#include "states/menu-state.hpp"
#include "states/game-over-state.hpp"
#include "states/mesh-test-state.hpp"
#include "states/transform-test-state.hpp"
#include "states/pipeline-test-state.hpp"
#include "states/texture-test-state.hpp"
#include "states/sampler-test-state.hpp"
#include "states/material-test-state.hpp"
#include "states/entity-test-state.hpp"
#include "states/renderer-test-state.hpp"

int main(int argc, char** argv) {
    

    // -------------------Main menu -------------------------------
    flags::args args(argc, argv); // Parse the command line arguments
    // config_path is the path to the json file containing the application configuration
    // Default: "config/app.json"
    std::string main_menu_mode = args.get<std::string>("c", "config/menu.jsonc");
    // run_for_frames is how many frames to run the application before automatically closing
    // This is useful for testing multiple configurations in a batch
    // Default: 0 where the application runs indefinitely until manually closed
    int run_for_frames = args.get<int>("f", 0);

    // Open the config file and exit if failed, start with the main menu 
    std::ifstream file_in(main_menu_mode);
    if(!file_in){
        std::cerr << "Couldn't open file: " << main_menu_mode << std::endl;
        return -1;
    }
    // Read the file into a json object then close the file
    nlohmann::json main_menu = nlohmann::json::parse(file_in, nullptr, true, true);
    file_in.close();

    
    // --------------------------------------------------------------------

    // Create the application
    our::Application app(main_menu);
    
    // Register all the states of the project in the application
    app.registerState<Menustate>("main_menu");
    app.registerState<Playstate>("game_mode");
    app.registerState<Menustate>("game_over");
    
    // Then choose the state to run based on the option "start-scene" in the config
    if(main_menu.contains(std::string{"start-scene"})){
        app.changeState(main_menu["start-scene"].get<std::string>());
    }

    // Finally run the application
    // Here, the application loop will run till the terminatio condition is statisfied
    return app.run(run_for_frames);
}



    
    // app.registerState<MeshTestState>("mesh-test");
    // app.registerState<TransformTestState>("transform-test");
    // app.registerState<PipelineTestState>("pipeline-test");
    // app.registerState<TextureTestState>("texture-test");
    // app.registerState<SamplerTestState>("sampler-test");
    // app.registerState<MaterialTestState>("material-test");
    // app.registerState<EntityTestState>("entity-test");
    // app.registerState<RendererTestState>("renderer-test");
