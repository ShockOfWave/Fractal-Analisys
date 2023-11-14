import os
import ctypes
from src.lacunarity.lacunarity import Lacunarity
from src.output.plot_results import plot_results
from src.output.table_results import table_results
from src.paths.find_files import find_files
from src.paths.paths import PATH_TO_CPP_LIB


def main():
    all_files = find_files('example_data')
    cpp_library = ctypes.CDLL(PATH_TO_CPP_LIB)
    lacunarity = Lacunarity(cpp_library)

    for file in all_files:
        result, results = lacunarity.calc_all(file)
        save_path = file[:-4]
        if not os.path.exists(save_path):
            os.makedirs(save_path)

        plot_results(results, save_path)
        table_results(results, save_path)

        cpp_library.memory_free(result)


if __name__ == '__main__':
    main()
