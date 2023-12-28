import os
import pandas as pd


def table_results(data, save_path) -> None:
    """
    Creates csv file with results
    :param data: evaluation data from lacunarity calculation
    :param save_path: path to save file
    :return: None
    """
    save_file = os.path.join(save_path, "results.csv")
    data = pd.DataFrame.from_dict(data, orient="index").transpose()
    data.to_csv(save_file, index=False)
