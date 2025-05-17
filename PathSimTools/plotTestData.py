import copy
import json
import os
import sys
from pathlib import Path

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def generate_graphs(run_setup_directory):
    run_directory = os.path.join(run_setup_directory, "runs")
    runtimes = [0.0]
    iterations = [0]
    for run in os.listdir(run_directory):
        run_data = load_data(os.path.join(run_directory, run))
        runtimes.append(run_data["runtime"]/1000)
        iterations.append(run_data["iterations"])
    sorted_runtimes = sorted(runtimes)
    sorted_iterations = sorted(iterations)
    total_runs = load_data(os.path.join(run_setup_directory, "testingProfile.json"))["num_runs"]
    success_probabilities = [i / total_runs for i in range(len(sorted_runtimes))]
    Path( os.path.join(run_setup_directory, "plots")).mkdir(parents=True, exist_ok=True)
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

    plot_data(sorted_runtimes, success_probabilities, max_time*1.2, 1.0,"Runtime (s)",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "runtime"))
    plot_data(sorted_iterations, success_probabilities, maxIter, 1.0,"Iterations",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "iterations"))


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
    print(x_values)
    plt.ylim(0, y_max)
    y_values.append(y_values[-1])
    print(y_values)
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
    plt.tight_layout()

    if label:
        plt.legend(loc="lower right", fontsize=10, frameon=False)

    plt.savefig(filepath, bbox_inches='tight', transparent=False)
    plt.close()





if __name__ == "__main__":
    generate_graphs(sys.argv[1])