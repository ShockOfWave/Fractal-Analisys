from pathlib import Path
import os


def get_project_path() -> Path:
    """
    Returns the absolute path to the project
    :return: Path to the project
    """
    return Path(__file__).parent.parent.parent


def find_library() -> str:
    """
    Finds compiled library
    :return: path to compiled library
    """
    for root, _, files in os.walk(os.path.join(get_project_path(), "build")):
        for file in files:
            if (
                file == "liblacunarity.so"
                or file == "liblacunarity.dylib"
                or file == "liblacunarity.dll"
            ):
                return os.path.join(root, file)

    raise


PATH_TO_CPP_LIB = find_library()
PATH_TO_TMP = os.path.join(get_project_path(), "backend", "tmp")
PATH_TO_TMP_FILES_DIR = os.path.join(get_project_path(), "backend", "files")
PATH_TO_TMP_ARCHIVE_DIR = os.path.join(get_project_path(), "backend", "archives")
