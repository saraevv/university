import numpy as np
import matplotlib.pyplot as plot
from math import tan

L = 0
R = 1
epsilon = 10 ** (-10)
u0 = 0


def u(t):
    return tan(t) - t


def f(t, u_t):
    return (u_t + t) ** 2


def der_f(t, u_t):
    return 2 * (u_t + t)


def newton(y_j, t_j1, tau):
    y_k = y_j + 2 * epsilon
    y_k1 = y_j
    while abs(y_k1 - y_k) > epsilon:
        y_k = y_k1
        num = y_k - y_j - tau * f(t_j1, y_k)
        den = 1 - tau * der_f(t_j1, y_k)
        y_k1 = y_k - num / den
    return y_k1


def explicit_mean_rect_method(tau, print):
    dots = np.linspace(L, R, int((R - L) / tau) + 1)
    u_values = [u(i) for i in dots]
    y = np.zeros(len(dots))
    y[0] = u0
    for j in range(1, len(dots)):
        k1 = f(dots[j - 1], y[j - 1])
        k2 = f(dots[j - 1] + tau / 2, y[j - 1] + tau * k1 / 2)
        y[j] = y[j - 1] + tau * k2
    if print:
        out(dots, y, u_values, 1)
    return y


def implicit_Euler_method(tau, print):
    dots = np.linspace(L, R, int((R - L) / tau) + 1)
    u_values = [u(i) for i in dots]
    y = np.zeros(len(dots))
    y[0] = u0
    for j in range(1, len(dots)):
        y[j] = newton(y[j - 1], dots[j], tau)
    if print:
        out(dots, y, u_values, 2)
    return y


def explicit_Runge_Kutta_method_4_order(tau, print):
    dots = np.linspace(L, R, int((R - L) / tau) + 1)
    u_values = [u(i) for i in dots]
    y = np.zeros(len(dots))
    y[0] = u0
    for j in range(1, len(dots)):
        k1 = f(dots[j - 1], y[j - 1])
        k2 = f(dots[j - 1] + tau / 2, y[j - 1] + tau * k1 / 2)
        k3 = f(dots[j - 1] + tau / 2, y[j - 1] + tau * k2 / 2)
        k4 = f(dots[j - 1] + tau, y[j - 1] + tau * k3)
        y[j] = y[j - 1] + tau / 6 * (k1 + 2 * k2 + 2 * k3 + k4)
    if print:
        out(dots, y, u_values, 3)
    return y


def Runge_fault(y_h, y_h_2, p):
    return max([abs(y_h_2[i] - y_h[j])
                for i, j in zip(range(len(y_h_2)), range(0, 2 * len(y_h_2), 2))]) / (2 ** p - 1)


def out(dots, y, u_values, num):
    plot.plot(dots, y, label="Approximation " + str(num))
    plot.plot(dots, u_values, label="Function")
    plot.legend()
    plot.show()
    print("_____________________________________________")
    print("Approximation " + str(num) + " values:")
    print(y)
    delta = [abs(u_values[i] - y[i]) for i in range(0, len(y))]
    print("Max delta: " + str(max(delta)))


# Явный метод средних прямоугольников
y1_h = explicit_mean_rect_method(0.1, True)
y1_h_2 = explicit_mean_rect_method(0.2, False)
print("Runge fault 1: " + str(Runge_fault(y1_h, y1_h_2, 2)))

# Неявный метод Эйлера
y2_h = implicit_Euler_method(0.01, True)
y2_h_2 = implicit_Euler_method(0.02, False)
print("Runge fault 2: " + str(Runge_fault(y2_h, y2_h_2, 1)))

# Явный метод Рунге-Кутта 4-ого порядка
y3_h = explicit_Runge_Kutta_method_4_order(0.1, True)
y3_h_2 = explicit_Runge_Kutta_method_4_order(0.2, False)
print("Runge fault 3: " + str(Runge_fault(y3_h, y3_h_2, 4)))
