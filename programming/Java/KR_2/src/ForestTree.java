import java.util.Objects;

public class ForestTree extends AbstractTree {
    protected double woodCount;

    public ForestTree(String name, int leavesCount, LeavesType leaves, double woodCount) {
        super(name, leavesCount, leaves);
        this.woodCount = woodCount;
    }

    @Override
    public String toString() {
        return "ForestTree{" +
                " name='" + name + '\'' +
                ", leavesCount=" + leavesCount +
                ", leaves=" + leaves +
                ", woodCount=" + woodCount +
                " }";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        ForestTree that = (ForestTree) o;
        return Double.compare(that.woodCount, woodCount) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), woodCount);
    }
}
