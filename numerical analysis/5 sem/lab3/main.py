# coding=utf-8
import numpy as np
from matplotlib import pyplot as plot
import time
from math import fabs


# Искомая функция
def u(x):
    return 1 / (x + 1)


# Функция при u'
def p(x):
    return -3 * (x + 1) ** 2


# Функция при u
def q(x):
    return 2 / (x + 1) ** 2


# Правая часть
def f(x):
    return -3


def check(matrix):
    for i in range(1, len(matrix[1]) - 1):
        if fabs(matrix[0][i - 1]) + fabs(matrix[2][i]) - fabs(matrix[1][i]) > 0:
            raise ValueError("Incorrect matrix")


def tridiagonal_matrix_algorithm(matrix, f):
    check(matrix)
    n = len(f)
    matrix[2][0] /= matrix[1][0]
    f[0] /= matrix[1][0]
    matrix[1][0] = 1
    for i in range(1, n - 1):
        coeff = matrix[1][i] - matrix[2][i - 1] * matrix[0][i - 1]
        matrix[2][i] /= coeff
        f[i] = (f[i] - f[i - 1] * matrix[0][i - 1]) / coeff
        matrix[1][i] = 1
        matrix[0][i - 1] = 0
    f[n - 1] = (f[n - 1] - f[n - 2] * matrix[0][n - 2]) / (matrix[1][n - 1] - matrix[2][n - 2] * matrix[0][n - 2])
    matrix[1][n - 1] = 1

    for i in range(n - 2, -1, -1):
        f[i] -= f[i + 1] * matrix[2][i]
        matrix[2][i] = 0


# y(x0)
y0 = 1
# шаг
h = 0.01
# сигма 1
sigma1 = -0.5
# ню 1
nu1 = -0.5
# границы
L = 0
R = 1
# узлы
dots = np.linspace(L, R, int((R - L) / h) + 1)
# значения функций в узлах
q_values = [q(x) for x in dots]
p_values = [p(x) for x in dots]
f_values = [f(x) for x in dots]

# создание матрицы из трех диагоналях
matrix = np.array([np.zeros(len(dots) - 2), np.zeros(len(dots) - 1), np.zeros(len(dots) - 2)])
# создание правой части
b = np.zeros(len(dots) - 1)

# заполнение матрицы и правой части
matrix[1][0] = -2 / (h ** 2) - q_values[1]
matrix[2][0] = 1 / (h ** 2) + p_values[1] / (2 * h)
b[0] = -f_values[1] - 1 / (h ** 2) + p_values[1] / (2 * h)

for i in range(1, len(b) - 1):
    matrix[0][i - 1] = 1 / (h ** 2) - p_values[i + 1] / (2 * h)
    matrix[1][i] = -2 / (h ** 2) - q_values[i + 1]
    matrix[2][i] = 1 / (h ** 2) + p_values[i + 1] / (2 * h)
    b[i] = -f_values[i + 1]

N = len(b) - 1
matrix[0][N - 1] = -1 / h
matrix[1][N] = 1 / h + sigma1 + h / 2 * p_values[N + 1] * sigma1 + h * q_values[N + 1] / 2
b[N] = nu1 + h * f_values[N + 1] / 2 + h * p_values[N + 1] * nu1 / 2

try:
    # метод прогонки
    tridiagonal_matrix_algorithm(matrix, b)

    # полученное решение
    y = [y0]
    for i in b:
        y.append(i)
    u_values = [u(x) for x in dots]

    # вывод результата
    plot.plot(dots, y, label="Approximation")
    plot.plot(dots, u_values, label="Function")
    plot.legend()
    plot.show()
    print("Max delta: " + str(max([abs(y[i] - u_values[i]) for i in range(len(y))])))
except ValueError as e:
    print(e.message)
