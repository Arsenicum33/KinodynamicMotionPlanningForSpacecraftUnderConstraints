import json
import random
import sys

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from plotTestData import load_data
import plotly.graph_objects as go
import pyvista as pv

def plot_tree(filepath, scale=1.0, point_size=5.5, line_width=2.0):
    with open(filepath) as f:
        data = json.load(f)
    nodes = data["nodes"]
    edges = data["edges"]

    # 2. Build point array and lookup
    points = np.array([n["position"] for n in nodes], dtype=float) * scale
    idx_to_pt = {n["index"]: points[i] for i, n in enumerate(nodes)}

    # 3. Create a PolyData point cloud
    cloud = pv.PolyData(points)

    # 4. Create a MultiBlock for edges
    lines = []
    for parent, child in edges:
        if not parent in idx_to_pt:
            continue
        if not child in idx_to_pt:
            continue
        p0 = idx_to_pt[parent]
        p1 = idx_to_pt[child]
        # each line is [n_pts, i0, i1]
        lines.append([2,
                      np.where((points == p0).all(axis=1))[0][0],
                      np.where((points == p1).all(axis=1))[0][0]])

    # Make a single cell array
    lines = np.hstack(lines)
    cloud.lines = lines

    cloud.save("tree.vtp")

    # 5. Plot it
    pl = pv.Plotter()
    pl.add_mesh(cloud, color='#8b3e67', point_size=point_size, render_points_as_spheres=True)
    pl.add_mesh(cloud, color='38686A', line_width=line_width)
    pl.show()


if __name__ == "__main__":
    plot_tree(sys.argv[1], scale=1.0, point_size=0.2, line_width=0.1)