import matplotlib.pyplot as plt
import ctypes
import numpy as np
import pandas as pd
import csv

# абсолютаня ссылка на скомпилированную библиотеку расширения .so
cpplib = ctypes.CDLL("/home/vladislav/Документы/build-Fractal_Analisys-Desktop-Debug/liblacunarity.so")
#cpplib = ctypes.CDLL("/home/vladislav/Fractal-Analisys/build/liblacunarity.so")

#/home/vladislav/Рабочий стол/tr/build/libgsl_operations.so
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

        ("z_bgVec", ctypes.POINTER(ctypes.c_int)),
        ("z_bgVec_len", ctypes.c_size_t),

        #("exp_lambdas", ctypes.POINTER(ctypes.c_double)),
        #("exp_lambdas_len", ctypes.c_size_t)
    ]

# создем массив указателей для отправки в библиотеку
ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.float64, 
                                      ndim=2)

connectivity = 4 #4 or 8 connectivity
box = 2 # 1 - box-counting
Number = 100 #number of slices
wait_k = 20

# определяем прототип функции из библиотеки, куда отправлять матрицу 
cpplib.lacunarity.argtypes = [ND_POINTER_2, ctypes.c_size_t, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int] # что отправляется
cpplib.lacunarity.restype = Result # что возвращается
#'/media/sf_ubuntuPubl/text_data.txt'
file_name = '/media/sf_ubuntuPubl/SEM/height_matrix4.txt'
#file_name = '/media/sf_ubuntuPubl/text_data.txt' # абсолютный путь до матрицы с АСМ
data = np.loadtxt(file_name, dtype=np.float64) # загружается матрица с АСМ в переменную
#data = pd.read_csv(file_name).values
'''
вызываем библиотеку и отправляем туда данные (преобразуются в указатели автоматически)
'''
result = cpplib.lacunarity(data, *data.shape, connectivity, box, Number, wait_k)

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
z_bgVec = np.ctypeslib.as_array(result.z_bgVec, shape=(result.z_bgVec_len,))

#exp_half_regressions = np.ctypeslib.as_array(result.exp_half_regressions, shape=(result.exp_half_regressions_len,)) # размер коробки
#exp_lambdas = np.ctypeslib.as_array(result.exp_lambdas, shape=(result.exp_lambdas_len,)) # лакунарности

#print(exp_half_regressions)

# Построение графика
#plt.plot(lambdas, half_regressions, marker='o', linestyle = '-')
plt.scatter(half_regressions, lambdas)
plt.title('For each slice')
plt.xlabel('ln (box size)')
plt.ylabel('ln (lacunarity)')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

##########

# Разделяем данные на два набора (по 8 элементов в каждом) 120:144  160:184
x_data_set1, x_data_set2, x_data_set3, x_data_set4 = np.split(half_regressions[120:144], 4)
y_data_set1, y_data_set2, y_data_set3, y_data_set4 = np.split(lambdas[120:144], 4)

# Построение графика
plt.scatter(x_data_set1, y_data_set1, label='slice 20')
plt.scatter(x_data_set2, y_data_set2, label='slice 21')
plt.scatter(x_data_set3, y_data_set3, label='slice 22')
plt.scatter(x_data_set4, y_data_set4, label='slice 23')
# plt.scatter(x_data_set5, y_data_set5, label='slice 24')
# plt.scatter(x_data_set6, y_data_set6, label='slice 25')
# plt.scatter(x_data_set7, y_data_set7, label='slice 26')
# plt.scatter(x_data_set8, y_data_set8, label='slice 27')
# plt.scatter(x_data_set9, y_data_set9, label='slice 28')
# plt.scatter(x_data_set10, y_data_set10, label='slice 29')

plt.xlabel('ln(Box size)')
plt.ylabel('ln(Lacunarity)')
plt.legend()
plt.show()
##########

# plt.scatter(exp_half_regressions, exp_lambdas)
# #plt.plot(exp_lambdas, exp_half_regressions, marker='o', linestyle = '-')
# plt.title('for each slice')
# plt.xlabel('box size')
# plt.ylabel('lacunarity')
# plt.grid(True)  # Включение сетки
# # Отображение графика
# plt.show()

# Построение графика 2
plt.scatter(pressures, external_lands, label = "External lands")
plt.scatter(pressures, internal_lands, label = "Internal lands")
plt.scatter(pressures, holes, label = "holes")
plt.title('Distribution of objects on slices')
plt.xlabel('%, Slice')
plt.ylabel('Number')
plt.grid(True)  # Включение сетки
plt.legend()
# Отображение графика
plt.show()

plt.scatter(pressures, derivatives)
plt.title('Fractal dimentional vs slice')
plt.xlabel('%, Slice')
plt.ylabel('D')
plt.grid(True)  # Включение сетки
# Отображение графика
plt.show()

plt.plot(pressures, ex_ones_square, label = "Square ext lands")
plt.plot(pressures, in_ones_square, label = "Square int lands")
plt.plot(pressures, z_bgVec, label = "Square BG holes")
plt.title('Square distribution')
plt.xlabel('%, slice')
plt.ylabel('square, pixels')
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
###*WRITING**DATA**TO**.CSV###########
def write_multiple_arrays_to_csv(arrays, file_name):
    with open(file_name, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for array_name, array_values in arrays.items():
            writer.writerow([array_name, *array_values])

arrays = {
    'Pressures': pressures,
    'Derivatives': derivatives,
    'Holes': holes,
    'External lands': external_lands,
    'INternal lands': internal_lands,
    'Relationship': relationship,
    'Relationship der' : relationship_derivatives,
    'External lands square': ex_ones_square,
    'Internal lands square': in_ones_square,
    'Z square': z_square,
    'Half regression': half_regressions,
    'Lambda': lambdas,
    'Holes background': z_bgVec
    }

write_multiple_arrays_to_csv(arrays, '/home/vladislav/FA/multiple_arrays.csv')



cpplib.memory_free(result) # освобождение памяти структуры (всегда делайте в конце ибо все данные в структуре будут потеряны после освобождения)