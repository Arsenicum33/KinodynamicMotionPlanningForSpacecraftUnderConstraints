import json
import os
import tempfile
from typing import Dict
import astropy.units as u
from astrodynamics.astro_dynamics_simulator import AstroDynamicsSimulator

solar_system_objects = {
    'sun': {'mass': 1.989e30,  #kg
            'radius': 696340}, #km
    'earth': {'mass': 5.972e24,
              'radius': 6400},
    'mars': {'mass': 6.417e23,
             'radius': 3390}
}

class SolverInputGenerator:

    def __init__(self, config, paths: Dict[str, str], test = False):
        self.config = config
        self.paths = paths
        self.data = None
        self.test = test

    def get_solver_input(self):
        if self.data is None:
            self._prepare_input()
        return self.data

    def generate_input_tempfile(self):
        solver_input = self.get_solver_input()

        with tempfile.NamedTemporaryFile(delete=False, suffix=".json", mode='w') as temp_file:
            json.dump(solver_input, temp_file)
            temp_file_path = temp_file.name
        return temp_file_path

    def _prepare_input(self):
        common_input = self._prepare_input_common()
        env_type = self.config.get('env_type')
        if env_type == 'astrodynamic':
            self.data = self._prepare_input_astrodynamic(common_input)
        else:
            self.data = self._prepare_input_default(common_input)

    def _prepare_input_default(self, common):
        target = self.config.get('target')
        if isinstance(target, str):
            target = str(os.path.join(self.paths['animations_dir'], target))
        common['target'] = target
        return common

    def _prepare_input_astrodynamic(self, input_dict):
       astrodynamic_simulator = AstroDynamicsSimulator()
       simulation_time_scale = self.config["simulation_time_scale"]
       celestial_bodies_data = astrodynamic_simulator.get_positions(self.config["celestial_bodies"], self.config["start_time"],
                                            self.config["end_time"], simulation_time_scale, 'dict')

       times = celestial_bodies_data["times"]
       input_dict["target"] = self.config["target"]
       input_dict["celestial_bodies"] = {}
       for body in self.config["celestial_bodies"]:
           positions = celestial_bodies_data["positions"][body]
           initial_velocity = celestial_bodies_data["initial_velocities"][body]
           if self.config["realistic_celestial_object_size"]:
               mesh = str(os.path.join(self.paths['obstacles_dir'], (body + "Realistic" + ".obj")))
           else:
               mesh = str(os.path.join(self.paths['obstacles_dir'], (body + ".obj")))
           input_dict["celestial_bodies"][body] = {
               "times": times,
               "positions": positions,
               "mass": solar_system_objects[body]['mass'],
               "radius": solar_system_objects[body]['radius'],
               "mesh": mesh,
               "initial_velocity": [initial_velocity.x.to(u.km / u.s).value,
                                    initial_velocity.y.to(u.km / u.s).value, initial_velocity.z.to(u.km / u.s).value]
           }
       input_dict["spaceship_model"] = self.config["spaceship_model"]
       return input_dict



    def _prepare_input_common(self):
        obstacles_filepath = ""
        agent_filepath = ""
        dynamic_objects_filepaths = []

        obstacles_filename = self.config.get('obstacles_name', None)
        if obstacles_filename is not None and obstacles_filename != '':
            obstacles_filepath = str(os.path.join(self.paths['obstacles_dir'], obstacles_filename))

        agent_filename = self.config.get('agent_name')
        if agent_filename is not None and agent_filename != '':
            if self.config.get("realistic_celestial_object_size") and self.config["realistic_celestial_object_size"]:
                agent_filepath = str(os.path.join(self.paths['agent_dir'], "rocketSmall.obj"))
            else:
                agent_filepath = str(os.path.join(self.paths['agent_dir'], agent_filename))


        for name in self.config.get('dynamic_objects_names'):
            dynamic_objects_filepaths.append(str(os.path.join(self.paths['animations_dir'], name)))

        boundaries = self.config.get('boundaries')
        start_position = self.config.get('start_position')
        env_type = self.config.get('env_type')

        components_preset = str(os.path.join(self.paths['project_dir'], self.config.get('components_preset')))
        if self.test:
            components_preset = str(os.path.join(self.paths['test_dir'], self.config.get('components_preset')))
        common_input = {
            "obstacles_filepath": obstacles_filepath,
            "agent_filepath": agent_filepath,
            "dynamic_objects_filepaths": dynamic_objects_filepaths,
            "boundaries": boundaries,
            "start_position": start_position,
            "components_preset": components_preset,
            'env_type' : env_type
        }
        return common_input
