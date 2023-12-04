import os


def find_files(directory) -> list:
    """
    Finds all files in a directory
    :param directory: directory
    :return: list with utils
    """

    finded_files = []

    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".txt"):
                finded_files.append(os.path.join(root, file))

    return finded_files
