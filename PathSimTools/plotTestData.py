import copy
import json
import os
import sys
from collections import defaultdict
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def generate_graphs(run_setup_directory):
    data = prepare_plot_data(run_setup_directory)

    plot_data(data["runtimesX"], data["Y"], data["maxRuntime"]*1.2, 1.0,"Runtime (s)",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "runtime"))
    plot_data(data["iterationsX"], data["Y"], data["maxIterations"], 1.0,"Iterations",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "iterations"))

    plot_data(data["iterationsList"], data["nodesList"], max(data["iterationsList"]), data["nodesList"][-1], "iterations", "nodes", None,
              os.path.join(run_setup_directory, "plots", "nodes"))
    plot_data(data["iterationsList"], data["runtimesList"], max(data["iterationsList"]), max(data["runtimesList"]), "iterations", "mean time per iteration",
              None ,os.path.join(run_setup_directory, "plots", "runtimePerIteration"))


def load_data(filepath):
    with open(filepath, "r") as f:
        data = json.load(f)
    return data

def plot_data(x_values, y_values, x_max, y_max,  x_label, y_label, label, filepath):
    plt.figure(figsize=(6, 4), dpi=900, facecolor="#f9f4f5")

    plt.xlim(0, x_max)
    x_values = copy.copy(x_values)
    y_values = copy.copy(y_values)
    x_values.append(x_max)
    #print(x_values)
    plt.ylim(0, y_max)
    y_values.append(y_max)
    #print(y_values)
    # Plot line with your plum color
    plt.step(
        x_values,
        y_values,
        where='post',
        label=label,
        color="#8b3e67",
        linewidth=2
    )

    # Axis labels and ticks
    plt.xlabel(x_label, fontsize=12, color="#2c2c2c")
    plt.ylabel(y_label, fontsize=12, color="#2c2c2c")
    plt.xticks(fontsize=10)
    plt.yticks(fontsize=10)



    plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
    #plt.tight_layout()

    if label:
        plt.legend(loc="lower right", fontsize=10, frameon=False)

    plt.savefig(filepath, bbox_inches='tight', transparent=False)
    plt.close()


def plot_comparsion(x1_values, y1_values, x2_values, y2_values,  x_label, y_label, filepath):
    plt.figure(figsize=(6, 4), dpi=900, facecolor="#f9f4f5")

    plt.xlim(0, max(x1_values[-1], x2_values[-1]))
    # Plot line with your plum color
    plt.step(
        x1_values,
        y1_values,
        where='post',
        label="SST",
        color="#8b3e67",
        linewidth=2
    )

    plt.step(
        x2_values,
        y2_values,
        where='post',
        label="RRT",
        color="#38686A",
        linewidth=2
    )

    # Axis labels and ticks
    plt.xlabel(x_label, fontsize=12, color="#2c2c2c")
    plt.ylabel(y_label, fontsize=12, color="#2c2c2c")
    plt.xticks(fontsize=10)
    plt.yticks(fontsize=10)

    plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
    plt.tight_layout()

    plt.legend(loc="lower right", fontsize=10, frameon=False)

    plt.savefig(filepath, bbox_inches='tight', transparent=False)
    plt.close()

def prepare_plot_data(run_setup_directory):
    run_directory = os.path.join(run_setup_directory, "runs")
    runtimes = [0.0]
    iterations = [0]
    sums = defaultdict(lambda: [0.0, 0.0, 0])
    hasExtraData = False
    for run in os.listdir(run_directory):
        run_data = load_data(os.path.join(run_directory, run))
        runtimes.append(run_data["runtime"] / 1000)
        iterations.append(run_data["iterations"])
        if run_data.get("iterationsToNodesToRuntime"):
            hasExtraData = True
            for iteration, nodes, runtime in run_data["iterationsToNodesToRuntime"]:
                sums[iteration][0] += nodes
                sums[iteration][1] += runtime
                sums[iteration][2] += 1

    if hasExtraData:
        averaged_data = [[it,
                      sums[it][0] / sums[it][2],
                      sums[it][1] / sums[it][2]]
                     for it in sorted(sums)]
        iterationsList, mean_nodes_list, mean_runtime_list = map(list, zip(*averaged_data))

        mean_times_per_iteration = [0.0]
        lastPositive = 0
        for i in range(1, len(mean_runtime_list)):
            value = (mean_runtime_list[i] - mean_runtime_list[i - 1])
            if value < 0:
                mean_times_per_iteration.append(lastPositive)
            else:
                mean_times_per_iteration.append(value)
                lastPositive = value

    sorted_runtimes = sorted(runtimes)
    sorted_iterations = sorted(iterations)
    total_runs = load_data(os.path.join(run_setup_directory, "testingProfile.json"))["num_runs"]
    success_probabilities = [i / total_runs for i in range(len(sorted_runtimes))]
    Path(os.path.join(run_setup_directory, "plots")).mkdir(parents=True, exist_ok=True)
    max_time = sorted_runtimes[-1]
    maxIter = 1000000

    profileData = load_data(os.path.join(run_setup_directory, "testingProfile.json"))
    envFilename = profileData["env_filename"]

    envData = load_data(os.path.join(run_setup_directory, envFilename))
    componentsFilename = envData["components_preset"]

    componentsData = load_data(os.path.join(run_setup_directory, componentsFilename))
    for component in componentsData["components"]:
        if component["name"] == "Solver":
            maxIter = component["config"]["maxIterations"]

    result = {"runtimesX" : sorted_runtimes,"iterationsX" : sorted_iterations, "Y": success_probabilities,
            "maxRuntime": max_time, "maxIterations": maxIter}
    if hasExtraData:
        result["iterationsList"] = iterationsList
        result["nodesList"] = mean_nodes_list
        result["runtimesList"] = mean_times_per_iteration
    return result

def generate_comparsion_graphs(run_setup_directory1, run_setup_directory2, output_directory_name):
    runtime_limit = 2500
    iter_limit = 1000000
    data1 = prepare_plot_data(run_setup_directory1)
    data1["runtimesX"]= [time for time in data1["runtimesX"] if time < runtime_limit]
    data1["iterationsX"]= [it for it in data1["iterationsX"] if it < iter_limit]
    runtimesY1 = data1["Y"][:len(data1["runtimesX"])]
    runtimesY1.append(runtimesY1[-1])
    iterationsY1 = data1["Y"][:len(data1["iterationsX"])]
    iterationsY1.append(iterationsY1[-1])

    data2 = prepare_plot_data(run_setup_directory2)
    data2["runtimesX"]= [time for time in data2["runtimesX"] if time < runtime_limit]
    data2["iterationsX"]= [it for it in data2["iterationsX"] if it < iter_limit]
    runtimesY2 = data2["Y"][:len(data2["runtimesX"])]
    runtimesY2.append(runtimesY2[-1])
    iterationsY2 = data2["Y"][:len(data2["iterationsX"])]
    iterationsY2.append(iterationsY2[-1])

    extraXruntime = max(data1["runtimesX"][-1],data2["runtimesX"][-1]) * 1.1
    data1["runtimesX"].append(extraXruntime)
    data2["runtimesX"].append(extraXruntime)

    extraXiter = iter_limit
    data1["iterationsX"].append(extraXiter)
    data2["iterationsX"].append(extraXiter)


    itLimitForNodes = 400

    result_path = os.path.join("/home/arseniy/Bachaerlors_thesis/Semester_project/PathPlanning3D/project/comparsionGraphs",
                               output_directory_name, "runtimes")
    Path(result_path).parent.mkdir(parents=True, exist_ok=True)
    plot_comparsion(data1["runtimesX"], runtimesY1, data2["runtimesX"], runtimesY2, "Runtimes", "Success Probability",
                    result_path)

    result_path = os.path.join("/home/arseniy/Bachaerlors_thesis/Semester_project/PathPlanning3D/project/comparsionGraphs",
                               output_directory_name, "iterations")
    Path(result_path).parent.mkdir(parents=True, exist_ok=True)
    plot_comparsion(data1["iterationsX"], iterationsY1, data2["iterationsX"], iterationsY2, "Iterations", "Success Probability",
                    result_path)

    result_path = os.path.join("/home/arseniy/Bachaerlors_thesis/Semester_project/PathPlanning3D/project/comparsionGraphs",
                               output_directory_name, "runtimePerIteration")

    plot_comparsion(data1["iterationsList"][:itLimitForNodes], data1["runtimesList"][:itLimitForNodes], data2["iterationsList"][:itLimitForNodes], data2["runtimesList"][:itLimitForNodes], "Iterations", "Runtime per iteration",
                    result_path)


    result_path = os.path.join("/home/arseniy/Bachaerlors_thesis/Semester_project/PathPlanning3D/project/comparsionGraphs",
                               output_directory_name, "nodes")
    plot_comparsion(data1["iterationsList"][:itLimitForNodes], data1["nodesList"][:itLimitForNodes], data2["iterationsList"][:itLimitForNodes], data2["nodesList"][:itLimitForNodes], "Iterations", "Nodes",
                    result_path)


if __name__ == "__main__":
    if len(sys.argv) == 2:
        generate_graphs(sys.argv[1])
    else:
        generate_comparsion_graphs(sys.argv[1], sys.argv[2], sys.argv[3])