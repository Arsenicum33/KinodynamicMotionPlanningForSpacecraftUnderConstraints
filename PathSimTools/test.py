import argparse
import concurrent
import concurrent.futures
import json
import os
import time
from datetime import datetime
from pathlib import Path
import shutil

from input_generators.solver_input_generator import SolverInputGenerator
from main import load_config, compile_cpp, run_cpp_executable, load_paths

from plotTestData import generate_graphs

NUM_PARALLEL = 6
def generate_filename(run_id, extension="json"):
    timestamp = datetime.now().strftime("%Y%m%dT%H%M%S")
    return f"{run_id:03d}_{timestamp}.{extension}"

def execute_solver(run_id, executable: str, work_dir: str, temfile_path: str, result_path):
    arguments = [executable, temfile_path, result_path, str(run_id)]
    print(f"[Run {run_id}] Starting...")
    result = run_cpp_executable(arguments, work_dir)
    if result.returncode != 0:
        print(f"[Run {run_id}] Failed with code {result.returncode}")
    else:
        print(f"[Run {run_id}] Finished.")
    print(f"[Run {run_id}] STDOUT:\n{result.stdout}")
    return run_id

def run_test(total_runs, executable,build_dir, tempfile_path, paths, run_name):
    with concurrent.futures.ThreadPoolExecutor(max_workers=NUM_PARALLEL) as executor:
        futures = {}
        filepaths = []
        for i in range(total_runs):
            filename = generate_filename(i, extension="json")

            result_path = str(os.path.join(paths["test_dir"], "runs", run_name, "runs", filename))
            Path(result_path).parent.mkdir(parents=True, exist_ok=True)
            filepaths.append(result_path)
            for json_file in Path(paths["test_dir"]).glob("*.json"):
                shutil.copy(json_file, str(os.path.join(paths["test_dir"], "runs", run_name)))
            future = executor.submit(execute_solver, i, executable, build_dir, tempfile_path, result_path)
            futures[future] = {
                "run_id": i,
                "filename": filename,
                "path": result_path
            }
            time.sleep(0.1)
        for future in concurrent.futures.as_completed(futures):
            run_id = futures[future]
            try:
                future.result()
            except Exception as e:
                print(f"[Run {run_id}] Crashed with error: {e}")

        list_of_dicts = []
        for filepath in filepaths:
            data = load_file(filepath)
            if data is not None:
                list_of_dicts.append(data)
        dict_of_lists = make_dict_of_lists(list_of_dicts)
        result = process_data(dict_of_lists, total_runs)
        print(result)
        timestamp = datetime.now().strftime("%Y%m%dT%H%M%S")
        result_filename = f"result_{timestamp}.json"
        result_filepath = os.path.join(paths["test_dir"], "runs", run_name, result_filename)
        with open(result_filepath, "w") as f:
            json.dump(result, f, indent=4)


def load_file(filepath):
    try:
        with open(filepath, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"File not found: {filepath}")
    except json.JSONDecodeError as e:
        print(f"Invalid JSON in {filepath}: {e}")
    except IOError as e:
        print(f"I/O error reading {filepath}: {e}")
    return None

def make_dict_of_lists(list_of_dicts):
    result = {}
    for d in list_of_dicts:
        for key, value in d.items():
            result.setdefault(key, []).append(value)
    return result

def process_data(dict_of_lists, total_runs):
    result = {}
    result["total_runs"] = total_runs
    result["runtime_median"] = calculate_median(dict_of_lists["runtime"])
    result["runtime_average"] = calculate_average(dict_of_lists["runtime"])
    result["iterations_median"] = calculate_median(dict_of_lists["iterations"])
    result["iterations_average"] = calculate_average(dict_of_lists["iterations"])
    result["success_rate"] = len(dict_of_lists["runtime"]) / total_runs
    return result

def calculate_median(list):
    sorted_list = sorted(list)
    n = len(sorted_list)
    mid = n // 2
    if n % 2 == 1:
        return sorted_list[mid]
    else:
        return (sorted_list[mid - 1] + sorted_list[mid]) / 2

def calculate_average(list):
    return sum(list) / len(list)

def parse_args():
    parser = argparse.ArgumentParser(description="Command-line argument parser")
    parser.add_argument("--profile", type=str, help="Filepath with testing profile", required=True)
    parser.add_argument("--name", type=str, help="Name of the folder with results", required=False)
    args = parser.parse_args()
    return vars(args)

if __name__ == "__main__":
    args = parse_args()

    testingProfile = args['profile']

    paths = load_paths()

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


    cpp_executable_filepath = str(os.path.join(build_dir, "project"))

    compile_cpp(proj_dir, build_dir, False)

    run_name = ""
    if args.get('name'):
        run_name = args['name']
    timestamp = datetime.now().strftime("%Y%m%dT%H%M%S")
    if run_name == "":
        run_name = f"run_{timestamp}"
    else:
        run_name = f"{run_name}_{timestamp}"
    run_test(num_runs,cpp_executable_filepath, build_dir, tempfile_path, paths, run_name)
    generate_graphs(os.path.join(paths["test_dir"], "runs", run_name))



