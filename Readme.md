Manual:

The project consists of 2 parts: C++ program, which performs all the calculations (can be run standalone, in this case default environment configuration from InputParser.cpp will be used) and a helper python program located in PathSimTools directory. This program handles scene creation in blender, builds and executes C++ program and then launches visualization via blender.

There are 3 configuration files: 
components.json - determines which classes will be used for calculations and their configs. 2 example configs are provided (componentsTARRT.json and componentsRRTconnect.json) copy the desired config into components.json 
PathSimTools/envSettings.json - determines which meshes and animations will be used, as well as the config boundaries and start/goal position for the agent
PathSimTools/paths.json - determines paths to files, required in python program. They shall be set to right values initially except for the blender executable, modify it to match the location on your PC.

To run the program, simply execute PathSimTools/main.py with python interpreter. 
