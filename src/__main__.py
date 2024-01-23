import os
import argparse
from rich.progress import track
from src import __version__
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
    parser.add_argument(
        "-f", "--file", action="store_true", help="path to file instead folder"
    )
    parser.add_argument(
        "-p",
        "--processes",
        action="store_true",
        help="puns calculations without using multiprocessing",
    )

    parser.add_argument(
        "-s", "--slices", type=int, default=100, help="Select number of slices"
    )

    parser.add_argument("-b", "--box", type=int, default=2, help="Select box counting")

    parser.add_argument(
        "-c", "--connectivity", type=int, default=4, help="Select connectivity method"
    )

    parser.add_argument(
        "-v",
        "--version",
        action="version",
        version="%(prog)s {}".format(__version__),
        help="show the version number and exit",
    )

    args = parser.parse_args()

    return args


def run_calculations(
    path,
    file=False,
    without_multiprocess=False,
    number_of_slices=100,
    connectivity=4,
    box_counting=2,
):
    """
    Run calculations
    :param path: path to folder or file to calculate
    :param file: change folder to file if True
    :param without_multiprocess: run calculation without \
    multiprocessing if True
    :param number_of_slices: select number of slices for calculation
    :param connectivity: select connectivity method, should be 4 or 8
    :param box_counting: select box counting method, should be 1 or 2
    """

    if file:
        calc_one_file(
            file_name=path,
            number_of_slices=number_of_slices,
            connectivity=connectivity,
            box_counting=box_counting,
        )

    else:
        files = find_files(path)
        for file in track(files, "[cyan]Completed...", total=len(files)):
            calc_one_file(
                file_name=file,
                number_of_slices=number_of_slices,
                connectivity=connectivity,
                box_counting=box_counting,
            )

        # files = find_files(path)
        # if without_multiprocess:
        #     for file in files:
        #         calc_one_file(file_name=file,
        #                       number_of_slices=number_of_slices,
        #                       connectivity=connectivity,
        #                       box_counting=box_counting)
        #
        # else:
        #     with Progress() as progress:
        #         task_id = progress.add_task("[cyan]Completed...", total=len(files))
        #         with Pool() as p:
        #             results = p.imap(calc_one_file, files)
        #             for _ in results:
        #                 progress.advance(task_id)


def main():
    args = load_args()

    if not os.path.exists(args.path) and not os.path.isfile(args.path):
        print("Folder or file do not exists")
        raise SystemExit(1)

    if int(args.box) != 2 and int(args.box) != 1:
        print("Box counting should be 1 or 2")
        raise SystemExit(1)

    if int(args.connectivity) != 4 and int(args.connectivity) != 8:
        print("Connectivity method should be 4 or 8")
        raise SystemExit(1)

    run_calculations(
        args.path, args.file, args.processes, args.slices, args.connectivity, args.box
    )


if __name__ == "__main__":
    main()
