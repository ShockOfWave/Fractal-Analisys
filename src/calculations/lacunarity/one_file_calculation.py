import os
import ctypes
from src.calculations.lacunarity.lacunarity import Lacunarity
from src.evaluation.lacunarity.table_results import table_results
from src.evaluation.lacunarity.plot_results import plot_results
from src.utils.paths import PATH_TO_CPP_LIB


def calc_one_file(file_name, number_of_slices=100, connectivity=4, box_counting=2):
    """
    Calculates lacunarity for one topology using C++ library
    :param file_name: absolute path to file with topology
    :param number_of_slices: select number of slices for calculation
    :param connectivity: select connectivity method, should be 4 or 8
    :param box_counting: select box counting method, should be 1 or 2
    """
    cpp_library = ctypes.CDLL(PATH_TO_CPP_LIB)
    lacunarity = Lacunarity(cpp_library)

    result, results = lacunarity.calc_all(
        path_to_matrix=file_name,
        number_of_slices=number_of_slices,
        connectivity=connectivity,
        box_counting=box_counting,
    )

    save_path = file_name[:-4]
    if not os.path.exists(save_path):
        os.makedirs(save_path)

    plot_results(results, save_path)
    table_results(results, save_path)

    cpp_library.memory_free(result)
