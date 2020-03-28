import javax.swing.*;
import java.awt.*;

public class FirstView extends JPanel {
    private DefaultListModel<Student> listModel;
    private JList<Student> list;
    private StudentContainer container;

    FirstView(StudentContainer container) {
        this.container = container;

        listModel = new DefaultListModel<Student>();
        list = new JList<Student>(listModel);

        this.setLayout(new BorderLayout());
        this.add(list, BorderLayout.CENTER);
    }

    void update() {
        listModel.removeAllElements();
        container.stream().forEach(x -> listModel.addElement(x));
        list.updateUI();
    }
}
