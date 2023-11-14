import os
import pandas as pd


def table_results(data, save_path) -> None:
    """
    Creates csv file with results
    :param data: output data from lacunarity calculation
    :param save_path: path to save file
    :return: None
    """
    pd.DataFrame.from_dict(data, orient='index').transpose().to_csv(os.path.join(save_path, 'results.csv'), index=False)
