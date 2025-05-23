import json
import os
import sys


def transform(filepath: str):
    with open(filepath, 'r') as file:
        data = json.load(file)
        celestial_bodies_data = data["celestial_bodies"]

    with open("../paths.json", 'r') as file:
        paths = json.load(file)
        celestial_bodies_filepath = os.path.join(paths["project_dir"] , "celestialBodies.json")
    with open(celestial_bodies_filepath, 'w') as file:
        file.write(json.dumps(celestial_bodies_data))


if len(sys.argv) > 1:
    filepath = sys.argv[1]
else:
    raise Exception("give path to tempfile")
transform(filepath)