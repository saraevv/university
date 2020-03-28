import javax.swing.*;
import java.util.ArrayList;
import java.util.Comparator;

public class ThirdTask extends JPanel {
    private JList<String> list;
    private DefaultListModel<String> listModel;
    private ArrayList<Drink> arrayList;

    public ThirdTask(ArrayList<Drink> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<String>();
        list = new JList<String>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        arrayList.stream().sorted(new Comparator<Drink>() {
            @Override
            public int compare(Drink drink, Drink t1) {
                return drink.getName().compareTo(t1.getName());
            }
        }).forEach(x -> listModel.addElement(x.getName()));
        list.updateUI();
    }
}
