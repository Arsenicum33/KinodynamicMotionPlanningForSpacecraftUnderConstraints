import pyvista as pv
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <rrt_tree.vtp>")
    sys.exit(1)

filename = sys.argv[1]
mesh = pv.read(filename)

# 1) Extract just the points as their own PolyData
points = pv.PolyData(mesh.points)

# 2) The original mesh still has the lines; we'll draw those separately

pl = pv.Plotter()
# Draw points as little spheres
pl.add_mesh(
    points,
    color='#8b3e67',
    point_size=5.5,
    render_points_as_spheres=True,
    style='points',
    label='nodes'
)
# Draw line‐cells as a polyline mesh
pl.add_mesh(
    mesh,
    color='#38686A',
    line_width=2.0,
    style='wireframe',
    label='edges'
)
pl.show()