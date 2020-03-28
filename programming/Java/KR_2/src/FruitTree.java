import java.util.Objects;

public class FruitTree extends AbstractTree {
    protected double fruitMas;

    public FruitTree(String name, int leavesCount, LeavesType leaves, double fruitMas) {
        super(name, leavesCount, leaves);
        this.fruitMas = fruitMas;
    }

    @Override
    public String toString() {
        return "FruitTree{" +
                " name='" + name + '\'' +
                ", leavesCount=" + leavesCount +
                ", leaves=" + leaves
                + ", fruitMas=" + fruitMas +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        FruitTree fruitTree = (FruitTree) o;
        return Double.compare(fruitTree.fruitMas, fruitMas) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), fruitMas);
    }
}
