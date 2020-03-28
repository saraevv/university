import java.util.Objects;

public abstract class AbstractWorker {
    protected String name;
    protected String organization;
    protected double coefficient;

    public AbstractWorker() {

    }

    public AbstractWorker(String name, String organization, double coefficient) {
        this.name = name;
        this.organization = organization;
        this.coefficient = coefficient;
    }

    abstract public double calculateSalary();

    @Override
    public String toString() {
        return "Name: " + this.name + "; Organization: " + organization + "; Coefficient: " + coefficient + "; ";
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getOrganization() {
        return organization;
    }

    public void setOrganization(String organization) {
        this.organization = organization;
    }

    public double getCoefficient() {
        return coefficient;
    }

    public void setCoefficient(double coefficient) {
        this.coefficient = coefficient;
    }

    protected double round(double x) {
        int ix = (int) (x * 100);
        return ix / 100;
    }
}
