from scipy import integrate
from matplotlib import pyplot as plt
import numpy as np


def f_calculation(x, g):
    f = np.zeros(4)
    for i in range(0, 4):
        for j in range(0, 4, 2):
            f[i] += x[j] * (x[j + 1] ** i)
        f[i] -= g[i]
    return f


def jacobian_calculation(x):
    J = np.zeros((4, 4), float)
    for i in range(0, 4):
        for j in range(0, 4, 2):
            J[i][j] = (x[j + 1] ** i)
    for i in range(1, 4):
        for j in range(1, 4, 2):
            J[i][j] = i * x[j - 1] * (x[j] ** (i - 1))
    return J


g = np.empty(4)
for i in range(0, 4):
    func = lambda t: ((1 - t) ** 3) * ((1 + t) ** 2) * (t ** i)
    g[i] = (integrate.quad(func, -1, 1))[0]

k = 0
x = np.random.random(4)
delta_x = np.empty(4)
norm = 1.0
norms = []
while norm > 10 ** (-10):
    W = jacobian_calculation(x)
    delta_x = np.linalg.solve(W, f_calculation(x, g))
    x -= delta_x
    norm = np.linalg.norm(delta_x)
    k += 1
    norms.append(norm)
print("Число итераций: ", k)
print("Ответ: ", x)
plt.plot([int(i) for i in range(1, k + 1)], norms)
plt.xlabel("Итерационные шаги")
plt.ylabel("Норма приближения")
plt.yscale("log")
plt.show()
