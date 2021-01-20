import numpy as np
from math import e, cos, sin, fabs
import matplotlib.pyplot as plt

L1 = 0
R1 = 1
L2 = 0
R2 = 0.5


def u(x, t):
    return e**(-t) * cos(x + t)


def u0(x):
    return cos(x)


def mu0(t):
    return e**(-t) * cos(t)


def mu1(t):
    return e**(-t) * cos(1 + t)


def f(x, t):
    return -e**(-t) * sin(x + t)


# значения функций в узлах
def init_values(h, tau):
    x_values = np.linspace(L1, R1, int((R1 - L1) / h) + 1)
    t_values = np.linspace(L2, R2, int((R2 - L2) / tau) + 1)
    u0_values = np.array([u0(x) for x in x_values])
    mu0_values = np.array([mu0(t) for t in t_values])
    mu1_values = np.array([mu1(t) for t in t_values])
    y_values = np.zeros((len(t_values), len(x_values)))
    u_values = np.array([np.array([u(x, t) for x in x_values]) for t in t_values])
    return x_values, t_values, u0_values, mu0_values, mu1_values, y_values, u_values


# расчет погрешности
def fault(y_values, u_values, N1, N2):
    max_delta = 0
    for i in range(N2):
        for j in range(N1):
            delta = fabs(y_values[i][j] - u_values[i][j])
            if delta > max_delta:
                max_delta = delta
    return max_delta


# вывод графика
def show_graphic(x_values, t_values, y_values, u_values):
    ax = plt.axes(projection="3d")
    xgrid, tgrid = np.meshgrid(x_values, t_values)
    ax.plot_wireframe(xgrid, tgrid, u_values, color='green', label="Function")
    ax.plot_wireframe(xgrid, tgrid, y_values, color='red', label="Approximation")
    ax.set_xlabel('x')
    ax.set_ylabel('t')
    ax.set_zlabel('y')
    plt.legend()
    plt.show()


# прогонка
def tridiagonal_matrix_algorithm(matrix, f):
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


# явный метод
def explicit_method(h, tau):
    gamma = tau / (h ** 2)
    x_values, t_values, u0_values, mu0_values, mu1_values, y_values, u_values = init_values(h, tau)
    N1 = len(x_values)
    N2 = len(t_values)

    def fi(x, t):
        return f(x, t + tau)

    fi_values = np.array([np.array([fi(x, t) for x in x_values]) for t in t_values])

    # заполняю нулевой слой
    for i in range(N1):
        y_values[0][i] = u0_values[i]

    # для всех слоев j от 1 до N1-1
    for j in range(1, N2):
        # берем y_0 из левого граничного условия
        y_values[j][0] = mu0_values[j]
        # рекуррентно вычисляем y_1 - y_(N1-2) через предыдущий слой
        for i in range(1, N1 - 1):
            y_values[j][i] = (1 - 2 * gamma) * y_values[j - 1][i] + gamma * (
                    y_values[j - 1][i - 1] + y_values[j - 1][i + 1]) + tau * fi_values[j - 1][i]
        # берем y_(N1-1) из правого граничного условия
        y_values[j][N1 - 1] = mu1_values[j]

    max_delta = fault(y_values, u_values, N1, N2)
    show_graphic(x_values, t_values, y_values, u_values)
    return max_delta


# неявный метод
def implicit_method(h, tau, sigma):
    x_values, t_values, u0_values, mu0_values, mu1_values, y_values, u_values = init_values(h, tau)
    N1 = len(x_values)
    N2 = len(t_values)

    def fi(x, t):
        if sigma == 1 / 2:
            return f(x, t + tau / 2)
        return f(x, t + tau)

    fi_values = np.array([np.array([fi(x, t) for x in x_values]) for t in t_values])

    # заполняю нулевой слой
    for i in range(N1):
        y_values[0][i] = u0_values[i]

    # коэффициент на главной диагонали трехдиагональной матрицы
    coef1 = sigma / (h ** 2)
    # коэффициенты на поддиагонали и наддиагонали
    coef2 = -(1 / tau + 2 * sigma / (h ** 2))

    # для всех слоев j от 1 до N1-1
    for j in range(1, N2):
        # создаю трехдиагональную матрицу, где на главной диагонали стоит coef1,
        # а на поддиагонали и наддиагонали стоят coef2
        # матрица хранится ввиде трех векторов
        #   |coef1 coef2 0    ...  0   0| - строка для вычисления y_1       = b_1
        #   |coef2 coef1 coef2 0 ...   0| - строка для вычисления y_2       = b_2
        #   |0 coef2 coef1 coef2 0 ... 0| - строка для вычисления y_3       = b_3
        #   |          .....            |
        #   |0 ... 0   coef2 coef1 coef2| - строка для вычисления y_(N1-3)  = b_(N1-3)
        #   |0 ... 0    0   coef2 coef1 | - строка для вычисления y_(N1-2)  = b_(N1-2)
        matrix = np.array(
            [np.full(N1 - 3, coef1), np.full(N1 - 2, coef2), np.full(N1 - 3, coef1)]
        )
        # правая часть уравнения
        b = np.zeros(N1 - 2)

        # вычисление y_0 и y_(N1-1)
        y_values[j][0] = mu0_values[j]  # (1)
        y_values[j][N1 - 1] = mu1_values[j]  # (2)

        # вычисляю b_1 как -F_ji - coef1 * y_0
        b[0] = -coef1 * y_values[j][0] - (y_values[j - 1][1] / tau + (1 - sigma) *
                                          (y_values[j - 1][0] - 2 * y_values[j - 1][1] + y_values[j - 1][2]) / (
                                                      h ** 2) +
                                          fi_values[j - 1][1])

        # вычисляю b_2 - b_(N1-3) включительно как -F_ji
        for i in range(1, N1 - 3):
            b[i] = - (y_values[j - 1][i + 1] / tau + (1 - sigma) *
                      (y_values[j - 1][i] - 2 * y_values[j - 1][i + 1] + y_values[j - 1][i + 2]) / (h ** 2) +
                      fi_values[j - 1][i + 1])

        # вычисляю b_(N-2) как -F_ji - coef1 * y_(N1-1)
        b[N1 - 3] = -coef1 * y_values[j][N1 - 1] - \
                    (y_values[j - 1][N1 - 2] / tau + (1 - sigma) *
                     (y_values[j - 1][N1 - 3] - 2 * y_values[j - 1][N1 - 2]
                      + y_values[j - 1][N1 - 1]) / (h ** 2) + fi_values[j - 1][N1 - 2])

        # метод прогонки
        tridiagonal_matrix_algorithm(matrix, b)
        # заполняю y с 1 по (N1-2) индексы включительно
        #   y_0 и y_(N1-2) заполнены в (1) и (2)
        for i in range(1, N1 - 1):
            y_values[j][i] = b[i - 1]

    max_delta = fault(y_values, u_values, N1, N2)
    show_graphic(x_values, t_values, y_values, u_values)
    return max_delta


if __name__ == "__main__":
    # явная разностная схема с tau = h = 0.1
    print(explicit_method(0.1, 0.1))
    # явная разностная схема с h = 0.1 и tau = h^2/2
    print(explicit_method(0.1, 0.005))
    # чисто неявная разностная схема с tau = h = 0.1
    print(implicit_method(0.1, 0.1, 1))
    # разностная схема Кранка-Николсон с tau = h = 0.1
    print(implicit_method(0.1, 0.1, 1 / 2))
