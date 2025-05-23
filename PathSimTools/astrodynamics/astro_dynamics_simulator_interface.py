from abc import ABC, abstractmethod


class IAstroDynamicsSimulator(ABC):
    """Abstract base class for astrodynamics simulators."""

    @abstractmethod
    def get_positions(self, planets, start_time, end_time, time_step, output_format='json'):
        """Retrieve positions for specified planets over a timeframe.

        Args:
            planets (list): List of planet names (e.g., ['earth', 'mars']).
            start_time (str): Start time in ISO format (e.g., '2023-01-01').
            end_time (str): End time in ISO format (e.g., '2023-12-31').
            time_step (float): Time interval in days (e.g., 1 for daily steps).
            output_format (str): Format of the output ('json' or 'dict').

        Returns:
            str or dict: Position data in the specified format.
        """
        pass