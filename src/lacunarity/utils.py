import ctypes


class Result(ctypes.Structure):  #структура указателей для возвращения в нее массивов с расчитанными данными
    _fields_ = [
        ("pressures", ctypes.POINTER(ctypes.c_double)),
        ("pressures_len", ctypes.c_size_t),

        ("derivatives", ctypes.POINTER(ctypes.c_double)),
        ("derivatives_len", ctypes.c_size_t),

        ("holes", ctypes.POINTER(ctypes.c_int)),
        ("holes_len", ctypes.c_size_t),

        ("external_lands", ctypes.POINTER(ctypes.c_int)),
        ("external_lands_len", ctypes.c_size_t),

        ("internal_lands", ctypes.POINTER(ctypes.c_int)),
        ("internal_lands_len", ctypes.c_size_t),

        ("relationship", ctypes.POINTER(ctypes.c_double)),
        ("relationship_len", ctypes.c_size_t),

        ("relationship_derivatives", ctypes.POINTER(ctypes.c_double)),
        ("relationship_derivatives_len", ctypes.c_size_t),

        ("ex_ones_square", ctypes.POINTER(ctypes.c_int)),
        ("ex_ones_square_len", ctypes.c_size_t),

        ("in_ones_square", ctypes.POINTER(ctypes.c_int)),
        ("in_ones_square_len", ctypes.c_size_t),

        ("z_square", ctypes.POINTER(ctypes.c_int)),
        ("z_square_len", ctypes.c_size_t),

        ("half_regressions", ctypes.POINTER(ctypes.c_double)),
        ("half_regressions_len", ctypes.c_size_t),

        ("lambdas", ctypes.POINTER(ctypes.c_double)),
        ("lambdas_len", ctypes.c_size_t),

        ("exp_half_regressions", ctypes.POINTER(ctypes.c_double)),
        ("exp_half_regressions_len", ctypes.c_size_t),

        ("exp_lambdas", ctypes.POINTER(ctypes.c_double)),
        ("exp_lambdas_len", ctypes.c_size_t)
    ]