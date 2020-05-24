import numpy as np
from math import sin, cos, pi
import matplotlib.pyplot as plot
from time import time


def function(t):
    return (sin(4 * t) - t) ** 3


def tridiagonal_matrix_algorithm(matrix, f):
    n = len(f)
    matrix[0][2] /= matrix[0][1]
    f[0] /= matrix[0][1]
    matrix[0][1] = 1
    for i in range(1, n - 1):
        coeff = matrix[i][1] - matrix[i - 1][2] * matrix[i][0]
        matrix[i][2] /= coeff
        f[i] = (f[i] - f[i - 1] * matrix[i][0]) / coeff
        matrix[i][1] = 1
        matrix[i][0] = 0
    f[n - 1] = (f[n - 1] - f[n - 2] * matrix[n - 1][0]) / (matrix[n - 1][1] - matrix[n - 2][2] * matrix[n - 1][0])
    matrix[n - 1][1] = 1

    for i in range(n - 2, -1, -1):
        f[i] -= f[i + 1] * matrix[i][2]
        matrix[i][2] = 0


def spline_dot(t, ai, bi, ci, di, xi):
    return ai + bi * (t - xi) + ci / 2 * ((t - xi) ** 2) + di / 6 * ((t - xi) ** 3)


def spline_dots(dots, x, a, b, c, d):
    ind = 1
    ans = []
    for i in dots:
        if i > x[ind]:
            ind += 1
        ans.append(spline_dot(i, a[ind], b[ind], c[ind], d[ind], x[ind]))
    ans = np.asarray(ans)
    return ans


L = -2
R = 2

dots = np.linspace(L, R, 1000)
count_of_dots = [10 * i for i in range(1, 11)]
faults = []
function_dots = [function(t) for t in dots]
times = []
for l in range(len(count_of_dots)):
    N = count_of_dots[l]
    x = np.linspace(L, R, N)
    y = np.empty(N)

    for i in range(0, N):
        y[i] = function(x[i])

    start = time()

    a = np.array([y[i] for i in range(0, N)])
    b = np.empty(N)
    c = np.empty(N)
    c[0] = c[N - 1] = 0
    d = np.empty(N)
    h = x[1] - x[0]

    matrix = np.array([np.array([h, 4 * h, h]) for i in range(0, N - 2)])
    matrix[0][0] = matrix[N - 3][2] = 0
    f = np.array([(a[i + 1] - 2 * a[i] + a[i - 1]) * 6 / h for i in range(1, N - 1)])

    tridiagonal_matrix_algorithm(matrix, f)

    for i in range(1, N - 1):
        c[i] = f[i - 1]

    for i in range(1, N):
        d[i] = (c[i] - c[i - 1]) / h

    for i in range(1, N):
        b[i] = (a[i] - a[i - 1]) / h + c[i] * h / 2 - d[i] * h * h / 6

    spline = spline_dots(dots, x, a, b, c, d)
    max_fault = max(abs(spline[i] - function_dots[i]) for i in range(len(spline)))

    end = time()

    label_info = "Spline in " + str(N) + " nodes(max fault =" + str(max_fault) + ")"
    plot.plot(dots, spline, label=label_info)
    plot.plot(dots, function_dots, label="Function")
    plot.legend()
    plot.ylim(-20, 20)
    plot.show()
    times.append(end - start)
    faults.append(max_fault)

for i in range(len(times)):
    print(str(i + 1) + " : " + str(times[i]))

for i in range(len(faults)):
    print(str(i + 1) + " : " + str(faults[i]))
