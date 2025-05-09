import resource
import subprocess
import os
import json
import statistics
import argparse

from input_generators.solver_input_generator import SolverInputGenerator
from input_generators.blender_input_generator import BlenderInputGenerator


def compile_cpp(project_dir: str, build_dir: str, debug: bool=True):
    print("Running CMake...")
    if debug:
        subprocess.run(["cmake", "-S", project_dir, "-B", build_dir], check=True)
    else:
        subprocess.run(["cmake", "-S", project_dir, "-B", build_dir, "-DCMAKE_BUILD_TYPE=Release"], check=True)

    print("Building the project...")
    subprocess.run(["cmake", "--build", build_dir], check=True)


def execute_solver(executable: str, work_dir: str, temfile_path: str):
    arguments = [executable, temfile_path]
    print("Running the C++ executable...")
    result = run_cpp_executable(arguments, work_dir)
    print("STDOUT:", result.stdout)
    return result


def process_execution_time(execution_times: list):
    median = statistics.median(execution_times)
    mean = statistics.mean(execution_times)
    print(f"Median: {median}, Mean: {mean}")


def run_cpp_executable(arguments, work_dir):
    return subprocess.run(arguments, text=True, cwd=work_dir)


def run_blender(blender_executable: str, scene_script: str, inputFilepath: str):
    print("Running Blender executable...")
    blender_command = [
        blender_executable,
        "--python",
        scene_script,
        "--",
        inputFilepath
    ]
    result = subprocess.run(blender_command, capture_output=True, text=True)
    print("STDOUT:", result.stdout)
    return result

def parse_args():
    parser = argparse.ArgumentParser(description="Command-line argument parser")
    parser.add_argument("--env", type=str, help="Filename with env settings")
    args = parser.parse_args()
    return vars(args)

def load_config(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data
    #env_type = data.get('env_type')
    #config_class = config_classes.get(env_type)
    #if not config_class:
    #    raise ValueError(f'Unknown environment type: {env_type}')
    #return config_class(data)


if __name__ == "__main__":
    args = parse_args()

    envSettingsFilename = args['env']

    with open("paths.json", 'r') as file:
        paths = json.load(file)

    config = load_config(envSettingsFilename)

    input_generator = SolverInputGenerator(config, paths)
    solver_input = input_generator.get_solver_input()
    tempfile_path = input_generator.generate_input_tempfile()

    proj_dir = paths['project_dir']
    build_dir = paths['build_dir']


    cpp_executable_filepath = str(os.path.join(build_dir, paths['cpp_executable_name']))

    compile_cpp(proj_dir, build_dir)

    path_planning_result = execute_solver(cpp_executable_filepath, build_dir, tempfile_path)

    if path_planning_result.returncode != 0:
        print(f"Error running C++ program: {path_planning_result.stderr}")
        exit(1)

    blender_exec_filepath = paths['blender_executable_filepath']

    scene_script = paths['scene_script_name']

    blender_input_generator = BlenderInputGenerator(config, paths, solver_input)
    blender_input = blender_input_generator.get_blender_input()
    blender_tempfile = blender_input_generator.generate_input_tempfile()

    blender_output = run_blender(blender_exec_filepath, scene_script, blender_tempfile)

    if blender_output.returncode != 0:
        print(f"Error running Blender: {blender_output.stderr}")
        exit(1)

    print("Blender animation completed successfully.")

