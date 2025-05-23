import json
import random
import sys

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from plotTestData import load_data
import plotly.graph_objects as go
import pyvista as pv
import pyassimp
import scipy

def plot_tree(filepath, obstacles_filepath = None, dynamic_objects_filepaths=None):
    scale = 1.0
    point_size = 5.0
    line_width = 1.0

    # 1. Load RRT graph
    with open(filepath) as f:
        data = json.load(f)
    nodes = data["nodes"]
    edges = data["edges"]
    if len(nodes) == 0:
        return

    # 2. Build point array and lookup
    points = np.array([n["position"] for n in nodes], dtype=float) * scale
    id_map = {n["index"]: i for i, n in enumerate(nodes)}

    # 3. Create PolyData for the RRT
    cloud = pv.PolyData(points)

    # 4. Build line connectivity for edges
    lines = []
    for parent, child in edges:
        if parent in id_map and child in id_map:
            lines.extend([2, id_map[parent], id_map[child]])
    cloud.lines = np.array(lines, dtype=np.int64)

    pl = pv.Plotter()

    pl.add_mesh(
        cloud,
        color='#8b3e67',
        point_size=point_size,
        render_points_as_spheres=True,
    )

    pl.add_mesh(
        cloud,
        color='#38686A',
        line_width=line_width,
        style='wireframe',
    )

    if obstacles_filepath is not None:
        obs_mesh = pv.read(obstacles_filepath)
        pl.add_mesh(
            obs_mesh,
            color='#E08024',
            show_edges=False,
        )


    data = import_dynamic_objects(dynamic_objects_filepaths)

    trajectories = convert_dynamic_objects_into_trajectories(data)

    for trajectory in trajectories:
        pl.add_mesh(
        trajectory,
        color='#FF4136',
        line_width=3,
        label='Trajectory'
        )

    cloud.save("tree.vtp")

    def export_pdf_callback():
        fname = "/home/arseniy/Bachaerlors_thesis/tree.png"
        pl.window_size = [1600, 1200]
        pl.screenshot(fname)
        print("SAVED")

    pl.add_key_event("e", export_pdf_callback)

    pl.show()


def import_dynamic_objects(dynamic_objects_filepaths):
    dictsWithData = []
    coord_normalization_constant = 100
    if dynamic_objects_filepaths is not None:
        for filepath in dynamic_objects_filepaths:
            with pyassimp.load(filepath,
                               processing=pyassimp.postprocess.aiProcess_ConvertToLeftHanded |
                                          pyassimp.postprocess.aiProcess_Triangulate) as scene:
                anim = scene.animations[0]
                channel = anim.channels[0]
                times = np.array([key.time for key in channel.positionkeys], dtype=float)
                traj = np.array([key.value for key in channel.positionkeys], dtype=float)/100
            dictsWithData.append({'times': times.tolist(),
        'positions': traj.tolist()})
    return dictsWithData

def convert_dynamic_objects_into_trajectories(data):
    result = []
    for object in data:
        pts = np.array(object['positions'], dtype=float)

        # 2. Create the PolyData
        traj = pv.PolyData(pts)

        # 3. Build the lines connectivity [2,0,1, 2,1,2, 2,2,3, ...]
        n = pts.shape[0]
        # if fewer than 2 points, no lines
        if n < 2:
            return traj

        # each segment has 3 ints: (2, i, i+1)
        # so total length = 3*(n-1)
        cells = np.empty(3 * (n - 1), dtype=np.int64)
        cells[0::3] = 2  # gives the “2” at start of each triplet
        cells[1::3] = np.arange(n - 1, dtype=np.int64)  # i
        cells[2::3] = np.arange(1, n, dtype=np.int64)  # i+1

        traj.lines = cells
        result.append(traj)
    return result



if __name__ == "__main__":
    plot_tree(sys.argv[1], None, ["/home/arseniy/Bachaerlors_thesis/Semester_project/blender/animations/target1.fbx"])