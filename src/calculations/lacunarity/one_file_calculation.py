import os
import ctypes
from src.calculations.lacunarity.lacunarity import Lacunarity
from src.evaluation.lacunarity.table_results import table_results
from src.evaluation.lacunarity.plot_results import plot_results
from src.utils.paths import PATH_TO_CPP_LIB


def calc_one_file(file_name):
    """
    Calculates lacunarity for one topology using C++ library
    :param file_name: absolute path to file with topology
    """
    cpp_library = ctypes.CDLL(PATH_TO_CPP_LIB)
    lacunarity = Lacunarity(cpp_library)

    result, results = lacunarity.calc_all(file_name)

    save_path = file_name[:-4]
    if not os.path.exists(save_path):
        os.makedirs(save_path)

    plot_results(results, save_path)
    table_results(results, save_path)

    cpp_library.memory_free(result)
