import java.util.Objects;

public class Security extends AbstractWorker {
    protected double area;
    final int BASE = 1000;
    final int CONST1 = 30;
    public Security() {

    }

    public Security(String name, String organization, double coefficient, double area) {
        super(name, organization, coefficient);
        this.area = area;
    }

    @Override
    public String toString() {
        return super.toString() + "Area: " + this.area;
    }

    public double getArea() {
        return area;
    }

    public void setArea(double area) {
        this.area = area;
    }

    @Override
    public double calculateSalary() {
        return round(BASE * this.coefficient * this.area / CONST1);
    }

}
