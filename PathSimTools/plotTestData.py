import json
import os
import sys
from pathlib import Path

import matplotlib.pyplot as plt

def generate_graphs(run_setup_directory):
    run_directory = os.path.join(run_setup_directory, "runs")
    runtimes = []
    iterations = []
    for run in os.listdir(run_directory):
        run_data = load_data(os.path.join(run_directory, run))
        runtimes.append(run_data["runtime"]/1000)
        iterations.append(run_data["iterations"])
    sorted_runtimes = sorted(runtimes)
    sorted_iterations = sorted(iterations)
    total_runs = load_data(os.path.join(run_setup_directory, "testingProfile.json"))["num_runs"]
    success_probabilities = [i / total_runs for i in range(len(sorted_runtimes))]
    plot_data(sorted_runtimes, success_probabilities, "Runtime (s)",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "runtime"))
    plot_data(sorted_iterations, success_probabilities, "Iterations",
              "Success Probability", "ECDF", os.path.join(run_setup_directory, "plots", "iterations"))


def load_data(filepath):
    with open(filepath, "r") as f:
        data = json.load(f)
    return data

def plot_data(x_values, y_values, x_label, y_label, label, filepath):
    plt.figure(figsize=(6, 4), dpi=900, facecolor="#f9f4f5")

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

    # Grid and layout
    plt.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
    plt.tight_layout()

    # Optional legend
    if label:
        plt.legend(loc="lower right", fontsize=10, frameon=False)

    # Save to file
    plt.savefig(filepath, bbox_inches='tight', transparent=False)
    plt.close()


if __name__ == "__main__":
    generate_graphs(sys.argv[1])