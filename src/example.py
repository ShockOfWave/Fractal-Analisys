import matplotlib.pyplot as plt
import ctypes
import numpy as np

# абсолютаня ссылка на скомпилированную библиотеку расширения .so
cpplib = ctypes.CDLL("/home/vladislav/Рабочий стол/tr/build/libgsl_operations.so")

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

# создем массив указателей для отправки в библиотеку
ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.float64, 
                                      ndim=2)


# определяем прототип функции из библиотеки, куда отправлять матрицу 
cpplib.lacunarity.argtypes = [ND_POINTER_2, ctypes.c_size_t] # что отправляется
cpplib.lacunarity.restype = Result # что возвращается

file_name = '/media/sf_ubuntuPubl/text_data.txt' # абсолютный путь до матрицы с АСМ
data = np.loadtxt(file_name, dtype=np.float64) # загружается матрица с АСМ в переменную

'''вызываем библиотеку и отправляем туда данные (преобразуются в указатели автоматически)'''
result = cpplib.lacunarity(data, *data.shape)

pressures = np.ctypeslib.as_array(result.pressures, shape=(result.pressures_len,)) # тут ось икс - значения процента надавливания на поверхность
derivatives = np.ctypeslib.as_array(result.derivatives, shape=(result.derivatives_len,)) # тут массив фракательных размерностей
holes = np.ctypeslib.as_array(result.holes, shape=(result.holes_len,)) # тут масив количества вложенных пропастей
external_lands = np.ctypeslib.as_array(result.external_lands, shape=(result.external_lands_len,)) # кол -во внешних островов
internal_lands = np.ctypeslib.as_array(result.internal_lands, shape=(result.internal_lands_len,)) # кол - во вложенных, вложенных островов
relationship = np.ctypeslib.as_array(result.relationship, shape=(result.relationship_len,)) # отношение кол- ва всех 0 к общей площади 
relationship_derivatives = np.ctypeslib.as_array(result.relationship_derivatives, shape=(result.relationship_derivatives_len,)) # частная производная от предыдущего
ex_ones_square = np.ctypeslib.as_array(result.ex_ones_square, shape=(result.ex_ones_square_len,)) # площадь внешних единиц
in_ones_square = np.ctypeslib.as_array(result.in_ones_square, shape=(result.in_ones_square_len,)) # площадь внутренних единиц
z_square = np.ctypeslib.as_array(result.z_square, shape=(result.z_square_len,)) # площадь нулей
half_regressions = np.ctypeslib.as_array(result.half_regressions, shape=(result.half_regressions_len,)) # натуральный логарифм от размера коробки
lambdas = np.ctypeslib.as_array(result.lambdas, shape=(result.lambdas_len,)) # нат лог от лакунарностей

exp_half_regressions = np.ctypeslib.as_array(result.exp_half_regressions, shape=(result.exp_half_regressions_len,)) # размер коробки
exp_lambdas = np.ctypeslib.as_array(result.exp_lambdas, shape=(result.exp_lambdas_len,)) # лакунарности


# Построение графика 
plt.plot(lambdas, half_regressions, marker='o', linestyle = '-')
plt.title('Для каждого среза')
plt.xlabel('ln (лакунарность)')
plt.ylabel('ln (размер коробки)')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

plt.plot(exp_lambdas, exp_half_regressions, marker='o', linestyle = '-')
plt.title('Для каждого среза')
plt.xlabel(' лакунарность')
plt.ylabel(' размер коробки')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

# Построение графика 2
plt.plot(pressures, external_lands, label = "Внешние острова")
plt.plot(pressures, internal_lands, label = "Вложенные острова")
plt.plot(pressures, holes, label = "Вложенные пропасти")
plt.title('Распределение количества')
plt.xlabel('% срезания')
plt.ylabel('Количество')
plt.grid(True)  # Включение сетки
plt.legend()
# Отображение графика
plt.show()

plt.scatter(pressures, derivatives)
plt.title('Фрактальная размерность от среза')
plt.xlabel('%, Срезания')
plt.ylabel('Размерность Хаусдорфа')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

plt.plot(pressures, ex_ones_square, label = "Площадь внешних островов")
plt.plot(pressures, in_ones_square, label = "Площадь вложенных островов")
plt.plot(pressures, z_square, label = "Площадь вложенных пропастей")
plt.title('Распределение площадей')
plt.xlabel('% срезания')
plt.ylabel('Площадь, пкс')
plt.grid(True)  # Включение сетки
plt.legend()
# Отображение графика
plt.show()

plt.scatter(pressures, relationship)
plt.title('Отношение площади вложенных 0 к общей площади на каждом срезе (Интегральные координаты)')
plt.xlabel('%, Срезания')
plt.ylabel('Отношение')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

plt.scatter(pressures, relationship_derivatives)
plt.title('Отношение площади вложенных 0 к общей площади на каждом срезе (Дифференциальные координаты)')
plt.xlabel('%, Срезания')
plt.ylabel('dy/dx')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

cpplib.memory_free(result) # освобождение памяти структуры (всегда делайте в конце ибо все данные в структуре будут потеряны после освобождения)