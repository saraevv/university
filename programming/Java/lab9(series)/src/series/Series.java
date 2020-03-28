package series;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public abstract class Series {
    protected double first;
    protected double coef;

    Series(double first, double coef) {
        this.first = first;
        this.coef = coef;
    }

    public abstract double calculate(int n);

    public String toString(int n) {
        StringBuilder str = new StringBuilder();
        for (int i = 1; i <= n; ++i) {
            str.append(calculate(i));
            if (i != n)
                str.append(" , ");
        }
        return new String(str);
    }

    public double sum(int n) {
        double sum = 0;
        for (int i = 1; i < n; ++i)
            sum += calculate(i);
        return sum;
    }

    public void saveToFile(File f, int n) throws IOException {
        FileWriter writer = new FileWriter(f, false);
        String text = this.toString(n);
        writer.write(text);
        writer.append('\n');
        writer.append(Double.toString(sum(n)));
        writer.append('\n');
        writer.flush();
    }
}


