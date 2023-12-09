import example

# Создание двумерного списка
my_array = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

# Вызов функции C++ через Cython
result_array = example.process_array_py(my_array)

print(result_array)
