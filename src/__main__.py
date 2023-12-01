import os
import argparse
from src import __version__
from multiprocessing import Pool
from src.calculations.lacunarity.one_file_calculation import calc_one_file
from src.utils.find_files import find_files


def load_args() -> argparse.Namespace:
    """
    Parse command line arguments
    """
    parser = argparse.ArgumentParser(
        prog="TDA calculation",
        description="Calculates TDA values for surface",
        epilog="Thanks for using %(prog)s! \n \n"
               "We will be grateful enough if you cite our articles :)",
    )

    parser.add_argument("path", type=str, help="path to folder with files")
    parser.add_argument("-f", "--file",
                        action="store_true",
                        help="path to file instead folder")
    parser.add_argument('-p', '--processes',
                        action="store_true",
                        help="puns calculations without using multiprocessing")
    parser.add_argument('-v', '--version',
                        action='version',
                        version='%(prog)s {}'.format(__version__),
                        help='show the version number and exit')

    args = parser.parse_args()

    return args


def run_calculations(path, file=False, without_multiprocess=False):
    """
    Run calculations
    :param path: path to folder or file to calculate
    :param file: change folder to file if True
    :param without_multiprocess: run calculation without \
    multiprocessing if True
    """

    if file:
        calc_one_file(path)

    else:
        files = find_files(path)
        if without_multiprocess:
            for file in files:
                calc_one_file(file)

        else:
            with Pool() as p:
                p.map(calc_one_file, files)


def main():
    args = load_args()

    if not os.path.exists(args.path) and not os.path.isfile(args.path):
        print("Folder or file do not exists")
        raise SystemExit(1)

    run_calculations(args.path, args.file, args.processes)


if __name__ == '__main__':
    main()
