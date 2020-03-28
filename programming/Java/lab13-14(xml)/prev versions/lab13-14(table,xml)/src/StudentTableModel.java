import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;

public class StudentTableModel extends AbstractTableModel {
    ArrayList<Student> arrayList;

    public StudentTableModel() {
        super();
        arrayList = new ArrayList<Student>();
    }

    public void addRow(Student student) {
        arrayList.add(student);
    }

    public ArrayList<Student> getArrayList() {
        return arrayList;
    }

    @Override
    public int getRowCount() {
        return arrayList.size();
    }

    @Override
    public int getColumnCount() {
        return 4;
    }

    @Override
    public Object getValueAt(int i, int j) {
        Student student = arrayList.get(i);
        switch (j) {
            case 0:
                return student.getSurname();
            case 1:
                return student.getNumber();
            case 2:
                return student.getCourse();
            case 3:
                return student.getGroup();
            default:
                return 0;
        }
    }

    public void deleteAll() {
        arrayList.clear();
    }
}
