from astrodynamics.astro_dynamics_simulator_interface import IAstroDynamicsSimulator
from astropy.time import Time
from astropy.coordinates import get_body, solar_system_ephemeris, get_body_barycentric
import numpy as np
import json

class AstroDynamicsSimulator(IAstroDynamicsSimulator):
    """Simulates planetary positions using Astropy's ephemeris data."""
    def __init__(self, ephemeris='builtin'):
        """Initialize with a specific ephemeris source.

        Args:
            ephemeris (str): Ephemeris data source (e.g., 'builtin', 'de421').
        """
        self.ephemeris = ephemeris

    def get_positions(self, planets, start_time, end_time, time_step_seconds, output_format='json'):
        """Retrieve positions for specified planets over a timeframe."""

        start = Time(start_time)
        end = Time(end_time)
        seconds_in_day = 86400
        # Generate array of time steps (in Julian days)
        times = Time(np.arange(start.jd, end.jd, time_step_seconds/seconds_in_day), format='jd', scale='tdb')

        # Fetch positions using Astropy
        positions = {}
        with solar_system_ephemeris.set(self.ephemeris):
            for planet in planets:
                # Get Cartesian coordinates (x, y, z) for each time step
                coords = [get_body_barycentric(planet, t).xyz.value.tolist() for t in times]
                positions[planet] = coords

        # Structure the output data

        total_time_sec = (end - start).sec
        times_sec = np.arange(0, total_time_sec, time_step_seconds)
        data = {
            'times': [t for t in times_sec],  # ISO format timestamps
            'positions': positions            # Planet: [ [x1, y1, z1], [x2, y2, z2], ... ]
        }

        # Return in the requested format
        if output_format == 'json':
            return json.dumps(data)
        elif output_format == 'dict':
            return data
        else:
            raise ValueError(f"Unsupported output format: {output_format}")


#simulator = AstroDynamicsSimulator()
#res = simulator.get_positions(["earth", "mars"], '2023-01-01', '2023-12-31', 0.5, "dict")
#print(res)
