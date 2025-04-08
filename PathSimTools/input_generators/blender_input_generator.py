import json
import os
import tempfile
from copy import deepcopy
from typing import Dict

class BlenderInputGenerator:

    def __init__(self, config, paths, solver_input):
        self.config = config
        self.paths = paths
        self.solver_input = solver_input
        self.data = None

    def generate_input_tempfile(self):
        blender_input = self.get_blender_input()
        with tempfile.NamedTemporaryFile(delete=False, suffix=".json", mode='w') as temp_file:
            json.dump(blender_input, temp_file)
            temp_file_path = temp_file.name
        return temp_file_path

    def get_blender_input(self):
        if self.data is None:
            self._prepare_input()
        return self.data

    def _prepare_input(self):
        common_input = self._prepare_input_common()
        env_type = self.config.get('env_type')
        if env_type == 'astrodynamic':
            self.data = self._prepare_input_astrodynamic(common_input)
        else:
            self.data = self._preapre_input_default(common_input)

    def _prepare_input_common(self):
        common_input = {}
        agent_filepath = self.solver_input["agent_filepath"]
        build_dir = self.paths['build_dir']
        cpp_output_filepath = str(os.path.join(build_dir, self.paths['output_name']))
        with open(cpp_output_filepath, 'r') as file:
            trajectory = json.load(file)
        common_input["obstacles"] = self.solver_input['obstacles_filepath']
        common_input["agent"] = {"mesh" : agent_filepath, "trajectory" : trajectory}

        common_input["dynamic_objects"] = self.solver_input["dynamic_objects_filepaths"]

        common_input["env_type"] = self.solver_input['env_type']

        common_input["boundaries"] = self.solver_input['boundaries']

        common_input["target"] = self.solver_input['target']
        return common_input


    def _prepare_input_astrodynamic(self, common_input):
        celestial_bodies = deepcopy(self.solver_input['celestial_bodies'])
        distance_scale = self.config['distance_scale']
        time_scale = self.config.get('visualization_time_scale')
        for body, properties in celestial_bodies.items():
            positions = properties['positions']
            positions_as_keyframes = []
            position_as_keyframe = {}
            for i in range(len(positions)):
                position_as_keyframe["time"] = properties["times"][i] / time_scale
                for j in range(len(positions[i])):
                    positions[i][j] *= distance_scale
                position_as_keyframe["position"] = positions[i]
                position_as_keyframe["rotation"] = [0.0,0.0,0.0]
                positions_as_keyframes.append(deepcopy(position_as_keyframe))
                position_as_keyframe.clear()
            celestial_bodies[body]['positions'] = positions_as_keyframes
        common_input['celestial_bodies'] = celestial_bodies

        self._scale_astrodynamic_input(common_input, distance_scale, time_scale)

        return common_input

    def _scale_astrodynamic_input(self, input, distance_scale, time_scale):
        input["boundaries"] = {key: value * distance_scale for key, value in input["boundaries"].items()}
        trajectory = input["agent"]["trajectory"]
        for point in trajectory:
            point["position"] = [coord * distance_scale for coord in point["position"]]
            point["time"] = point["time"] / time_scale



    def _preapre_input_default(self, common_input):
        common_input["obstacles"] = self.solver_input['obstacles_filepath']
        if isinstance(self.config.get('target'), str):
            common_input["target"] = str(os.path.join(self.paths['animations_dir'], self.config.get('target')))
        else:
            common_input["target"] = self.config.get('target')
        return common_input
