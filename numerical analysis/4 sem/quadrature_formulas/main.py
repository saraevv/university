from math import sin, cos, e

L = -1
R = 1
EXACT = 0.436547
A = [0.00775384, 0.0761026, 0.231437, 0.331254, 0.251019, 0.0995173, 0.0178684, 0.000920897]
X = [-0.866595, -0.69679, -0.482143, -0.235601, 0.0275523, 0.291019, 0.538768, 0.757123]


def f(t):
    return sin(1 - cos(e ** (t ** 5)))


def ro(t):
    return ((1 - t) ** 5) * ((1 + t) ** 3)


def quadrature_formula(n):
    x = L
    h = abs(L - R) / (n - 1)
    Q = f(x) / 2
    for k in range(0, n - 1):
        x += h
        Q += f(x) * ro(x)
    x += h
    Q += f(x) / 2
    Q *= h
    return Q


faults = [10 ** (-4), 10 ** (-6), 10 ** (-8)]
for fault in faults:
    n = 3
    answers = [quadrature_formula(n)]
    n *= 2
    current_fault = 1
    while current_fault > fault:
        answers.append(quadrature_formula(n))
        current_fault = 1 / 3 * abs(answers[len(answers) - 1] - answers[len(answers) - 2])
        n *= 2
    print("answer = " + str(answers[len(answers) - 1]) + " - " + "num = " + str(len(answers)) + " - " + str(
        abs(answers[len(answers) - 1] - EXACT)))

res = 0
for i in range(8):
    res += A[i] * f(X[i])
print("answer = " + str(res) + " - " + str(abs(res - EXACT)))