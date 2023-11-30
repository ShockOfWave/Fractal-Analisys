import os
import ctypes
import pytest
import numpy as np
from src.utils.paths import PATH_TO_CPP_LIB, get_project_path
from src.calculations.lacunarity.lacunarity import Lacunarity


def test_reproducibility():
    """
    Test the reproducibility of the calculation
    """
    first_lib = ctypes.CDLL(PATH_TO_CPP_LIB)
    second_lib = ctypes.CDLL(PATH_TO_CPP_LIB)
    first_lacunarity = Lacunarity(first_lib)
    second_lacunarity = Lacunarity(second_lib)
    calc1, calcs1 = first_lacunarity.calc_all(os.path.join(get_project_path(), 'example_data', 'text_data.txt'))
    calc2, calcs2 = second_lacunarity.calc_all(os.path.join(get_project_path(), 'example_data', 'text_data_1.txt'))

    # test variables from C++
    assert np.array_equal(calcs1['pressures'], calcs2['pressures'])
    assert np.array_equal(calcs1['holes'], calcs2['holes'])
    assert np.array_equal(calcs1['external_lands'], calcs2['external_lands'])
    assert np.array_equal(calcs1['internal_lands'], calcs2['internal_lands'])
    assert np.array_equal(calcs1['relationship'], calcs2['relationship'])
    assert np.array_equal(calcs1['relationship_derivatives'], calcs2['relationship_derivatives'])
    assert np.array_equal(calcs1['ex_ones_square'], calcs2['ex_ones_square'])
    assert np.array_equal(calcs1['in_ones_square'], calcs2['in_ones_square'])
    assert np.array_equal(calcs1['z_square'], calcs2['z_square'])
    assert np.array_equal(calcs1['half_regressions'], calcs2['half_regressions'])
    assert np.array_equal(calcs1['exp_half_regressions'], calcs2['exp_half_regressions'])

    # check is files on different addresses
    assert calc1 != calc2

    first_lib.memory_free(calc1)
    second_lib.memory_free(calc2)