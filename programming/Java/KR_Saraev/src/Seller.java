import java.util.Objects;

public class Seller extends AbstractWorker {
    protected double proceeds;
    private double CONST = 40;

    public Seller() {
    }

    public Seller(String name, String organization, double coefficient, double proceeds) {
        super(name, organization, coefficient);
        this.proceeds = proceeds;
    }

    @Override
    public String toString() {
        return super.toString() + "Proceeds: " + this.proceeds;
    }

    public double getProceeds() {
        return proceeds;
    }

    public void setProceeds(double proceeds) {
        this.proceeds = proceeds;
    }

    @Override
    public double calculateSalary() {
        return round(this.coefficient * this.proceeds * CONST/100);
    }

}
