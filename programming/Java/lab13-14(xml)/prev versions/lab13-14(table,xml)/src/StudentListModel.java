import javax.swing.*;
import java.util.ArrayList;

public class StudentListModel extends AbstractListModel<String> {
    ArrayList<String> arrayList;

    public StudentListModel() {
        super();
        arrayList = new ArrayList<String>();
    }

    public ArrayList<String> getArrayList() {
        return arrayList;
    }

    public void add (String string) {
        arrayList.add(string);
    }

    public void deleteAll() {
        arrayList.clear();
    }

    @Override
    public int getSize() {
        return arrayList.size();
    }

    @Override
    public String getElementAt(int i) {
        return arrayList.get(i);
    }

    public void pushBack(String student) {
        arrayList.add(student);
    }
}
