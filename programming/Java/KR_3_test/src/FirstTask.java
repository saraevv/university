import javax.swing.*;
import java.util.ArrayList;

public class FirstTask extends JPanel {
    private JList<Drink> list;
    private DefaultListModel<Drink> listModel;
    private ArrayList<Drink> arrayList;

    public FirstTask(ArrayList<Drink> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<Drink>();
        list = new JList<Drink>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        for (Drink drink : arrayList) {
            listModel.addElement(drink);
        }
        list.updateUI();
    }
}
