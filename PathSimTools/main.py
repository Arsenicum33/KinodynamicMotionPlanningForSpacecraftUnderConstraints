import subprocess
import os
import json
import tempfile
import time
import statistics


def compile_cpp(project_dir: str, build_dir: str):
    print("Running CMake...")
    subprocess.run(["cmake", "-S", project_dir, "-B", build_dir], check=True)

    print("Building the project...")
    subprocess.run(["cmake", "--build", build_dir], check=True)


def find_path(executable: str, work_dir: str, envSettings, paths):
    obstacles_filepath = str(os.path.join(paths['obstacles_dir'], envSettings['obstacles_name']))
    agent_filepath = str(os.path.join(paths['agent_dir'], envSettings['agent_name']))
    endPosition = envSettings['end_position']
    if isinstance(endPosition, str):
        endPosition = str(os.path.join(paths['animations_dir'], endPosition))
    dynamic_objects_filepaths = []
    for name in envSettings['dynamic_objects_names']:
        dynamic_objects_filepaths.append(str(os.path.join(paths['animations_dir'], name)))
    with tempfile.NamedTemporaryFile(delete=True, suffix=".json", mode='w') as temp_file:
        json.dump({
            "obstacles_filepath": obstacles_filepath,
            "agent_filepath": agent_filepath,
            "dynamic_objects_filepaths": dynamic_objects_filepaths,
            "boundaries": envSettings['boundaries'],
            "start_position": envSettings['start_position'],
            "end_position": endPosition,
            "components_preset": envSettings['components_preset']
        }, temp_file)
        temp_file.flush()
        arguments = [executable, temp_file.name]
        print("Running the C++ executable...")
        result = run_cpp_executable(arguments, work_dir)
        print("STDOUT:", result.stdout)
    return result


def find_path_time_test(executable: str, work_dir: str, envSettings, paths, num_runs: int):
    obstacles_filepath = str(os.path.join(paths['obstacles_dir'], envSettings['obstacles_name']))
    agent_filepath = str(os.path.join(paths['agent_dir'], envSettings['agent_name']))
    dynamic_objects_filepaths = []
    endPosition = envSettings['end_position']
    if endPosition is str:
        endPosition = str(os.path.join(paths['animations_dir'], endPosition))
    for name in envSettings['dynamic_objects_names']:
        dynamic_objects_filepaths.append(str(os.path.join(paths['animations_dir'], name)))
    with tempfile.NamedTemporaryFile(delete=True, suffix=".json", mode='w') as temp_file:
        json.dump({
            "obstacles_filepath": obstacles_filepath,
            "agent_filepath": agent_filepath,
            "dynamic_objects_filepaths" : dynamic_objects_filepaths,
            "boundaries": envSettings['boundaries'],
            "start_position": envSettings['start_position'],
            "end_position": endPosition,
            "components_preset" : envSettings['components_preset']
        }, temp_file)
        temp_file.flush()
        arguments = [executable, temp_file.name]
        execution_times = []
        for i in range(num_runs):
            print(f"Running the C++ executable {i+1}/{num_runs}...")
            start_time = time.time()
            run_cpp_executable(arguments, work_dir)
            end_time = time.time()
            execution_time = end_time - start_time
            execution_times.append(execution_time)
            print(f"Run {i+1}, execution time: {execution_time}")

    return execution_times

def process_execution_time(execution_times: list):
    median = statistics.median(execution_times)
    mean = statistics.mean(execution_times)
    print(f"Median: {median}, Mean: {mean}")


def run_cpp_executable(arguments, work_dir):
    return subprocess.run(arguments, text=True, cwd=work_dir)


def run_blender(blender_executable: str, scene_script: str):
    print("Running Blender executable...")
    blender_command = [
        blender_executable,
        "--python",
        scene_script
    ]
    result = subprocess.run(blender_command, capture_output=True, text=True)
    print("STDOUT:", result.stdout)
    return result


with open("envSettings.json", 'r') as file:
    envSettings = json.load(file)
with open("paths.json", 'r') as file:
    paths = json.load(file)

proj_dir = paths['project_dir']
build_dir = paths['build_dir']
cpp_executable_filepath = str(os.path.join(build_dir, paths['cpp_executable_name']))
blender_exec_filepath = paths['blender_executable_filepath']

open_blender = envSettings['open_blender'] #boolean, if run blender if true

scene_script = paths['scene_script_name']
time_test = envSettings['time_test']
num_runs = envSettings['num_runs']

compile_cpp(proj_dir, build_dir)

if time_test:
    execution_times = find_path_time_test(cpp_executable_filepath, build_dir, envSettings, paths, num_runs)
    process_execution_time(execution_times)
    exit(0)

path_planning_result = find_path(cpp_executable_filepath, build_dir, envSettings, paths)

if path_planning_result.returncode != 0:
    print(f"Error running C++ program: {path_planning_result.stderr}")
    exit(1)

if not open_blender:
    print("Open blender set to false")
    exit(0)


blender_output = run_blender(blender_exec_filepath,scene_script)

if blender_output.returncode != 0:
    print(f"Error running Blender: {blender_output.stderr}")
    exit(1)

print("Blender animation completed successfully.")
