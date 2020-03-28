package com.company;

import java.awt.*;

public class Main {

    public static void main(String[] args) {
        try {
            if (args.length != 2) {
                throw new IllegalArgumentException();
            }
            double x = Double.parseDouble(args[0]);
            double accuracy = Double.parseDouble(args[1]);
            System.out.println(calculate(x, accuracy));
        } catch (NumberFormatException e) {
            System.out.println("Wrong arguments!");
        } catch (IllegalArgumentException e) {
            System.out.println("Wrong number of arguments!");
        }
    }

    public static double calculate(double x, double e) {
        double sum = 0, k = 1, a = 1;
        while (true) {
            if (Math.abs(a) <= e) {
                break;
            }
            a = (a * x * x) / (2 * k);
            ++k;
            sum += a;
        }
        return sum;
    }
}
