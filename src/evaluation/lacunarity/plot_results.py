import os
import matplotlib.pyplot as plt


def plot_results(data, save_path) -> None:
    """
    Plots all results and saves it
    :param data: evaluation data from lacunarity calculation
    :param save_path: path to save file
    :return: None
    """
    plt.plot(data['lambdas'], data['half_regressions'], marker='o', linestyle='-')
    plt.title('Для каждого среза')
    plt.xlabel('ln (лакунарность)')
    plt.ylabel('ln (размер коробки)')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'each_slice.svg'), format='svg', dpi=1200)
    plt.close()

    plt.plot(data['exp_lambdas'], data['exp_half_regressions'], marker='o', linestyle='-')
    plt.title('Для каждого среза')
    plt.xlabel('лакунарность')
    plt.ylabel('размер коробки')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'each_slice_exp.svg'), format='svg', dpi=1200)
    plt.close()

    plt.plot(data['pressures'], data['external_lands'], label="Внешние острова")
    plt.plot(data['pressures'], data['internal_lands'], label="Вложенные острова")
    plt.plot(data['pressures'], data['holes'], label="Вложенные пропасти")
    plt.title('Распределение количества')
    plt.xlabel('% срезания')
    plt.ylabel('Количество')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'distribution_num.svg'), format='svg', dpi=1200)
    plt.close()

    plt.scatter(data['pressures'], data['derivatives'])
    plt.title('Фрактальная размерность от среза')
    plt.xlabel('%, Срезания')
    plt.ylabel('Размерность Хаусдорфа')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'fractal_slice.svg'), format='svg', dpi=1200)
    plt.close()

    plt.plot(data['pressures'], data['ex_ones_square'], label="Площадь внешних островов")
    plt.plot(data['pressures'], data['in_ones_square'], label="Площадь вложенных островов")
    plt.plot(data['pressures'], data['z_square'], label="Площадь вложенных пропастей")
    plt.title('Распределение площадей')
    plt.xlabel('% срезания')
    plt.ylabel('Площадь, пкс')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'square_distribution.svg'), format='svg', dpi=1200)
    plt.close()

    plt.scatter(data['pressures'], data['relationship'])
    plt.title('Отношение площади вложенных 0 к общей площади на каждом срезе (Интегральные координаты)')
    plt.xlabel('%, Срезания')
    plt.ylabel('Отношение')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'integer_coords.svg'), format='svg', dpi=1200)
    plt.close()

    plt.scatter(data['pressures'], data['relationship_derivatives'])
    plt.title('Отношение площади вложенных 0 к общей площади на каждом срезе (Дифференциальные координаты)')
    plt.xlabel('%, Срезания')
    plt.ylabel('dy/dx')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, 'diff_coords.svg'), format='svg', dpi=1200)
    plt.close()
