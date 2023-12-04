import ctypes
import numpy as np
from src.calculations.lacunarity.utils import Result


class Lacunarity:
    """
    Lacunarity class
    """

    def __init__(self, loaded_lib):
        """
        Loads cpp library and init ctypes dict
        :param path_to_lib: path to cpp library
        """

        self.loaded_lib = loaded_lib
        self.ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.float64, ndim=2)
        self.results = Result

    def calc_all(self, path_to_matrix):
        """
        Calculates lacunarity and returns results
        :param path_to_matrix: path to matrix
        :return: dict with results of lacunarity calculation
        """

        # ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.float64, ndim=2)
        self.loaded_lib.lacunarity.argtypes = [self.ND_POINTER_2, ctypes.c_size_t]
        self.loaded_lib.lacunarity.restype = Result

        data = np.loadtxt(path_to_matrix, dtype=np.float64)

        result = self.loaded_lib.lacunarity(data, *data.shape)
        results = {
            "pressures": np.ctypeslib.as_array(
                result.pressures, shape=(result.pressures_len,)
            ),
            "derivatives": np.ctypeslib.as_array(
                result.derivatives, shape=(result.derivatives_len,)
            ),
            "holes": np.ctypeslib.as_array(result.holes, shape=(result.holes_len,)),
            "external_lands": np.ctypeslib.as_array(
                result.external_lands, shape=(result.external_lands_len,)
            ),
            "internal_lands": np.ctypeslib.as_array(
                result.internal_lands, shape=(result.internal_lands_len,)
            ),
            "relationship": np.ctypeslib.as_array(
                result.relationship, shape=(result.relationship_len,)
            ),
            "relationship_derivatives": np.ctypeslib.as_array(
                result.relationship_derivatives,
                shape=(result.relationship_derivatives_len,),
            ),
            "ex_ones_square": np.ctypeslib.as_array(
                result.ex_ones_square, shape=(result.ex_ones_square_len,)
            ),
            "in_ones_square": np.ctypeslib.as_array(
                result.in_ones_square, shape=(result.in_ones_square_len,)
            ),
            "z_square": np.ctypeslib.as_array(
                result.z_square, shape=(result.z_square_len,)
            ),
            "half_regressions": np.ctypeslib.as_array(
                result.half_regressions, shape=(result.half_regressions_len,)
            ),
            "lambdas": np.ctypeslib.as_array(
                result.lambdas, shape=(result.lambdas_len,)
            ),
            "exp_half_regressions": np.ctypeslib.as_array(
                result.exp_half_regressions, shape=(result.exp_half_regressions_len,)
            ),
            "exp_lambdas": np.ctypeslib.as_array(
                result.exp_lambdas, shape=(result.exp_lambdas_len,)
            ),
        }

        return result, results
