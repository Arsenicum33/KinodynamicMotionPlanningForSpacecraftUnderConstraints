from config_classes.base_config import BaseConfig


class KinodynamicConfig(BaseConfig):
    def _get_required_keys(self):
        return [
            "obstacles_name",
            "agent_name",
            "dynamic_objects_names",
            "boundaries",
            "start_position",
            "target",
            "open_blender",
            "components_preset",
            "env_type"
        ]