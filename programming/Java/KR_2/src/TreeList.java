import org.w3c.dom.ls.LSOutput;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.stream.Collectors;

public class TreeList<T extends AbstractTree> extends ArrayList<T> {

    public void printSort() throws ListIsEmptyException {
        if (this.isEmpty()) {
            throw new ListIsEmptyException("List is empty!");
        }
        this.stream().sorted(new Comparator<AbstractTree>() {
            @Override
            public int compare(AbstractTree abstractTree, AbstractTree t1) {
                return t1.leavesCount - abstractTree.leavesCount;
            }
        }).forEach(AbstractTree::println);
    }

    public int frequency(T tree) throws ListIsEmptyException {
        if (this.isEmpty()) {
            throw new ListIsEmptyException("List is empty!");
        }
        return Collections.frequency(this, tree);
    }

    public T min() throws ListIsEmptyException {
        if (this.isEmpty()) {
            throw new ListIsEmptyException("List is empty!");
        }
        return Collections.min(this);
    }

    public double countOfLeaves(LeavesType leavesType) throws ListIsEmptyException {
        if (this.isEmpty()) {
            throw new ListIsEmptyException("List is empty!");
        }
        return this.stream().filter(x -> x.getLeavesType() == leavesType).mapToInt(x->x.getLeavesCount()).sum();
    }

}
