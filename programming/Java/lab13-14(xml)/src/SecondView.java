import javax.swing.*;
import java.awt.*;
import java.util.Comparator;

public class SecondView extends JPanel {
    private DefaultListModel<Student> sortedListModel;
    private JList<Student> sortedList;
    private JLabel currentGroupLabel;
    private StudentContainer container;

    SecondView(StudentContainer container) {
        this.container = container;

        sortedListModel = new DefaultListModel<Student>();
        sortedList = new JList<Student>(sortedListModel);
        currentGroupLabel = new JLabel();
        currentGroupLabel.setText("Current group: 0");

        this.setLayout(new BorderLayout());
        this.add(currentGroupLabel, BorderLayout.NORTH);
        this.add(sortedList, BorderLayout.CENTER);
    }

    void update(int currentGroup) {
        sortedListModel.removeAllElements();
        container.stream().filter(x -> x.getGroup() == currentGroup).sorted(new Comparator<Student>() {
            @Override
            public int compare(Student student, Student t1) {
                return student.getNumber() - t1.getNumber();
            }
        }).forEach(x -> sortedListModel.addElement(x));
        sortedList.updateUI();
        currentGroupLabel.setText("Current group: " + currentGroup);
    }
}
