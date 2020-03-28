package series;

public class Liner extends Series {

    Liner(double first, double coef) {
        super(first, coef);
    }

    public double calculate(int n) {
        if (n <= 1)
            return first;
        else {
            double res = first;
            for (int i = 2; i <= n; ++i)
                res += coef;
            return res;
        }
    }
}
