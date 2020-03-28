import javax.swing.*;
import java.util.ArrayList;

public class Task extends JPanel {
    private JList<SomeClass> list;
    private DefaultListModel<SomeClass> listModel;
    private ArrayList<SomeClass> arrayList;

    public Task(ArrayList<SomeClass> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<SomeClass>();
        list = new JList<SomeClass>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        for (SomeClass i : arrayList) {
            listModel.addElement(i);
        }
        list.updateUI();
    }
}
