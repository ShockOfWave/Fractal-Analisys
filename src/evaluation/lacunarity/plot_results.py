import os
import numpy as np
import matplotlib.pyplot as plt


def plot_results(data, save_path) -> None:
    """
    Plots all results and saves it
    :param data: evaluation data from lacunarity calculation
    :param save_path: path to save file
    :return: None
    """
    #################
    slice_number = 20  # from what slice we wish to build lacunaruty spread
    ################
    plt.scatter(data["half_regressions"], data["lambdas"], marker="o", linestyle="-")
    plt.title("For each slice")
    plt.xlabel("ln (box size)")
    plt.ylabel("ln (lacunarity)")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, "each_slice.svg"), format="svg", dpi=1200)
    plt.close()

    plt.plot(data["pressures"], data["external_lands"], label="External Lands")
    plt.plot(data["pressures"], data["internal_lands"], label="Internal Lands")
    plt.plot(data["pressures"], data["holes"], label="Holes")
    plt.plot(data["pressures"], data["holes_int"], label="Internal Holes")
    plt.title("Objects on slices distrib")
    plt.xlabel("% Slice")
    plt.ylabel("Number")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, "distribution_num.svg"), format="svg", dpi=1200)
    plt.close()

    plt.scatter(data["pressures"], data["derivatives"])
    plt.title("Fractal dimentional vs slice")
    plt.xlabel("%, Slice")
    plt.ylabel("D")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, "fractal_slice.svg"), format="svg", dpi=1200)
    plt.close()

    plt.plot(data["pressures"], data["ex_ones_square"], label="Square ext lands")
    plt.plot(data["pressures"], data["in_ones_square"], label="Square int lands")
    plt.plot(data["pressures"], data["z_bgVec"], label="Square BG holes")
    plt.title("Square distribution")
    plt.xlabel("% Slice")
    plt.ylabel("square, pixels")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(
        os.path.join(save_path, "square_distribution.svg"), format="svg", dpi=1200
    )
    plt.close()

    plt.scatter(data["pressures"], data["relationship"])
    plt.title(
        "Ratio of the area of nested 0s to the total area on each slice (Integral coordinates)"
    )
    plt.xlabel("%, Slice")
    plt.ylabel("Ratio")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, "integer_coords.svg"), format="svg", dpi=1200)
    plt.close()

    plt.scatter(data["pressures"], data["relationship_derivatives"])
    plt.title(
        "Ratio of the area of nested 0s to the total area on each slice (dif coordinates)"
    )
    plt.xlabel("%, Slice")
    plt.ylabel("dy/dx")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(save_path, "diff_coords.svg"), format="svg", dpi=1200)
    plt.close()
    ###############################################################################
    slice_end = (slice_number + 10) * 8
    slice_begin = slice_number * 8
    (
        x_data_set1,
        x_data_set2,
        x_data_set3,
        x_data_set4,
        x_data_set5,
        x_data_set6,
        x_data_set7,
        x_data_set8,
        x_data_set9,
        x_data_set10,
    ) = np.split(data["half_regressions"][slice_begin:slice_end], 10)
    (
        y_data_set1,
        y_data_set2,
        y_data_set3,
        y_data_set4,
        y_data_set5,
        y_data_set6,
        y_data_set7,
        y_data_set8,
        y_data_set9,
        y_data_set10,
    ) = np.split(data["lambdas"][slice_begin:slice_end], 10)

    plt.scatter(x_data_set1, y_data_set1, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set2, y_data_set2, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set3, y_data_set3, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set4, y_data_set4, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set5, y_data_set5, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set6, y_data_set6, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set7, y_data_set7, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set8, y_data_set8, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set9, y_data_set9, label={"slice", slice_number})
    slice_number += 1
    plt.scatter(x_data_set10, y_data_set10, label={"slice", slice_number})

    plt.xlabel("ln(Box size)")
    plt.ylabel("ln(Lacunarity)")
    plt.legend()
    plt.grid(True)
    plt.show()
