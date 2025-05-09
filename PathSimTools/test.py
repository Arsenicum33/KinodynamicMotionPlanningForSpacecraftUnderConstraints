import argparse
import concurrent
import concurrent.futures
import json
import os
from datetime import datetime

from input_generators.solver_input_generator import SolverInputGenerator
from main import load_config, compile_cpp, run_cpp_executable

NUM_PARALLEL = 8

def generate_filename(run_id, extension="json"):
    timestamp = datetime.now().strftime("%Y%m%dT%H%M%S")
    return f"{run_id:03d}_{timestamp}.{extension}"

def execute_solver(run_id, executable: str, work_dir: str, temfile_path: str, result_path):
    arguments = [executable, temfile_path, result_path]
    print(f"[Run {run_id}] Starting...")
    result = run_cpp_executable(arguments, work_dir)
    if result.returncode != 0:
        print(f"[Run {run_id}] Failed with code {result.returncode}")
    else:
        print(f"[Run {run_id}] Finished.")
    print(f"[Run {run_id}] STDOUT:\n{result.stdout}")
    return run_id

def run_test(total_runs, executable,build_dir, tempfile_path, paths):
    with concurrent.futures.ThreadPoolExecutor(max_workers=NUM_PARALLEL) as executor:
        futures = {}
        for i in range(total_runs):
            filename = generate_filename(i, extension="json")
            result_path = str(os.path.join(paths["test_dir"], filename))
            future = executor.submit(execute_solver, i, executable, build_dir, tempfile_path, result_path)
            futures[future] = {
                "run_id": i,
                "filename": filename,
                "path": result_path
            }
        for future in concurrent.futures.as_completed(futures):
            run_id = futures[future]
            try:
                future.result()
            except Exception as e:
                print(f"[Run {run_id}] Crashed with error: {e}")


def run_instance(run_id, cpp_executable_filepath,build_dir, tempfile_path):
    result = execute_solver()
    if result.returncode != 0:
        print(f"[Run {run_id}] Failed with code {result.returncode}")
    return run_id

def parse_args():
    parser = argparse.ArgumentParser(description="Command-line argument parser")
    parser.add_argument("--profile", type=str, help="Filepath with testing profile")
    args = parser.parse_args()
    return vars(args)

if __name__ == "__main__":
    args = parse_args()

    testingProfile = args['profile']

    with open("paths.json", 'r') as file:
        paths = json.load(file)

    profile = load_config(testingProfile)
    paths["test_dir"] = profile["test_dir"]
    num_runs = profile["num_runs"]

    configFilepath = str(os.path.join(paths["test_dir"], profile["env_filename"]))
    config = load_config(configFilepath)

    input_generator = SolverInputGenerator(config, paths, True)
    solver_input = input_generator.get_solver_input()
    tempfile_path = input_generator.generate_input_tempfile()

    proj_dir = paths['project_dir']
    build_dir = paths['build_dir']


    cpp_executable_filepath = str(os.path.join(build_dir, paths['cpp_executable_name']))

    compile_cpp(proj_dir, build_dir)

    run_test(num_runs,cpp_executable_filepath, build_dir, tempfile_path, paths)



