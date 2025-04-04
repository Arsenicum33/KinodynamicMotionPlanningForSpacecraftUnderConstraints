import abc

class BaseConfig(abc.ABC):
    def __init__(self, data):
        self.data = data
        self.validate()

    def validate(self):
        required_keys = self._get_required_keys()
        for key in required_keys:
            if key not in self.data:
                raise ValueError(f'Missing required key {key}')

    def get(self, key, default=None):
        return self.data.get(key, default)

    @abc.abstractmethod
    def _get_required_keys(self):
        pass
