import javax.swing.*;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) {
        try {
            System.out.println(args[0] + " , " + args[1]);
            System.out.println(Calculation(args[0], Double.parseDouble(args[1])));
        } catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }
    }

    private static double Calculation(String str, double val) throws NumberFormatException {
        StringTokenizer st;
        String current;
        int sign;
        double res = 0, cur;
        if (str.charAt(0) == '-')
            st = new StringTokenizer(str, "+,-", true);
        else
            st = new StringTokenizer("+" + str, "+,-", true);
        while (st.hasMoreTokens()) {
            current = st.nextToken();
            if (current.equals("+"))
                sign = 1;
            else
                sign = -1;
            current = st.nextToken();
            if (current.equals("x"))
                cur = val;
            else
                cur = Double.parseDouble(current);
            res += sign * cur;
        }
        return res;
    }
}
