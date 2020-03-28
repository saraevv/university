package matrix;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.NoSuchElementException;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        try {
            // Открытие файла
            File file = new File("input.txt");
            Scanner in = new Scanner(file);
            // Чтение порядка матрицы
            int n = in.nextInt();
            // Создание и чтение матрицы
            DiagonalMatrix matrix = new DiagonalMatrix(n, in);
            // Сохранение матрицы для последующей проверки
            DiagonalMatrix save = new DiagonalMatrix(matrix);
            // Создание и чтение столбца
            double[] col = new double[n];
            for (int i = 0; i < n; ++i)
                col[i] = in.nextDouble();
            // Вывод матрицы и столбца
            System.out.println("Column:");
            for (double x : col)
                System.out.print(x + " ");
            System.out.println();
            matrix.print();
            // Нахождение решения
            matrix.dGauss(col);
            // Вывод решения
            System.out.println("Answer:");
            for (double x : col)
                System.out.print(x + " ");
            System.out.println();
            // Проверка
            // Умножение исходной матрицы на полученный столбец
            double[] test = save.multiplication(col);
            System.out.println("Test:");
            for (double x : test)
                System.out.print(x + " ");
        } catch (FileNotFoundException e) {
            System.err.println("File not found!");
        } catch (NoSuchElementException e) {
            System.err.println("Incorrect input!");
        } catch (ArithmeticException e) {
            System.err.println("Zero on the main diagonal!");
        }

    }
}
