package matrix;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DiagonalMatrix {
    private double[][] arr;

    // Конструктор
    DiagonalMatrix(int n, Scanner in) {
        arr = new double[n][];
        for (int i = 0; i < n; ++i) {
            arr[i] = new double[n - i];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i; ++j) {
                arr[i][j] = in.nextDouble();
            }
        }
    }

    // Копирующий коструктор
    DiagonalMatrix(DiagonalMatrix m) {
        this.arr = new double[m.arr.length][];
        for (int i = 0; i < this.arr.length; ++i) {
            arr[i] = new double[this.arr.length - i];
            System.arraycopy(m.arr[i], 0, this.arr[i], 0, this.arr[i].length);
        }
    }

    // Вычисление решения методом Гаусса
    public void dGauss(double[] col) throws ArithmeticException {
        for (int i = arr.length - 1; i > 0; --i) {
            for (int j = 1; j <= i; ++j) {
                if (arr[i][0] == 0)
                    throw new ArithmeticException();
                col[i - j] -= col[i] * arr[i - j][j] / arr[i][0];
                arr[i - j][j] = 0;
            }
        }
        for (int i = 0; i < arr.length; ++i)
            col[i] /= arr[i][0];
    }

    // Умножение матрицы на столбец
    public double[] multiplication(double[] col) {
        double[] ans = new double[arr.length];
        for (int i = 0; i < arr.length; ++i) {
            for (int j = 0; j < arr.length - i; ++j) {
                ans[i] += arr[i][j] * col[j + i];
            }
        }
        return ans;
    }

    // Выврд матрицы
    public void print() {
        System.out.println("Matrix:");
        for (int i = 0; i < arr.length; ++i) {
            for (int j = 0; j < i; ++j) {
                System.out.print(0.0d + " ");
            }
            for (int j = 0; j < arr.length - i; ++j) {
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
    }


}
