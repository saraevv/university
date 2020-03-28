import java.util.Objects;

public abstract class AbstractTree implements Comparable<AbstractTree> {
    protected String name;
    protected int leavesCount;
    protected LeavesType leaves;

    public AbstractTree(String name, int leavesCount, LeavesType leaves) {
        this.name = name;
        this.leavesCount = leavesCount;
        this.leaves = leaves;
    }

    @Override
    public String toString() {
        return "AbstractTree{" +
                "name='" + name + '\'' +
                ", leavesCount=" + leavesCount +
                ", leaves=" + leaves +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AbstractTree that = (AbstractTree) o;
        return leavesCount == that.leavesCount &&
                Objects.equals(name, that.name) &&
                leaves == that.leaves;
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, leavesCount, leaves);
    }

    @Override
    public int compareTo(AbstractTree abstractTree) {
        if (this.leavesCount == abstractTree.leavesCount) {
            return -this.name.compareTo(abstractTree.name);
        } else {
            return this.leavesCount - abstractTree.leavesCount;
        }
    }

    public LeavesType getLeavesType() {
        return leaves;
    }

    public void println() {
        System.out.println(this);
    }

    public int getLeavesCount() {
        return leavesCount;
    }
}
