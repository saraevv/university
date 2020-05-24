import numpy as np
from math import sin, cos, pi
import matplotlib.pyplot as plot
from time import time


def function(t):
    return (sin(4 * t) - t) ** 3


def polynom(t):
    global x, y, c
    for i in range(len(x)):
        if t == x[i]:
            return y[i]

    den = [c[i] / (t - x[i]) for i in range(len(c))]
    return sum(den[i] * y[i] for i in range(len(c))) / sum(den)


L = -2
R = 2

dots = np.linspace(L, R, 1000)
count_of_dots = [10 * i for i in range(1, 11)]
type_of_nodes = "equidistant"
faults = []
times = []
for l in range(2):
    for i in range(len(count_of_dots)):
        N = count_of_dots[i]
        if type_of_nodes == "equidistant":
            x = np.linspace(L, R, N)
        else:
            x = np.empty(N)
            for j in range(1, N + 1):
                x[j - 1] = (L + R) / 2 + (R - L) / 2 * cos((2 * j - 1) * pi / (2 * N))
        y = np.empty(N)

        for j in range(0, N):
            y[j] = function(x[j])

        start = time()

        c = np.ones(N)
        for j in range(len(x)):
            for k in range(len(x)):
                if j != k:
                    c[j] *= x[j] - x[k]
            c[j] = 1 / c[j]
        polynom_dots = [polynom(t) for t in dots]
        function_dots = [function(t) for t in dots]
        max_fault = max(abs(polynom_dots[i] - function_dots[i]) for i in range(len(polynom_dots)))

        end = time()

        if type_of_nodes == "equidistant":
            label_info = "Polynom in " + str(N) + " equidistant nodes (max fault =" + str(max_fault) + ")"
        else:
            label_info = "Polynom in " + str(N) + " chebyshev's nodes (max fault =" + str(max_fault) + ")"

        plot.plot(dots, polynom_dots, label=label_info)
        plot.plot(dots, function_dots, label="Function")
        plot.legend()
        plot.show()
        faults.append(max_fault)
        times.append(end - start)
    type_of_nodes = "chebyshev's"

for i in range(len(times)):
    print(str(i + 1) + " : " + str(times[i]))

for i in range(len(faults)):
    print(str(i + 1) + " : " + str(faults[i]))
