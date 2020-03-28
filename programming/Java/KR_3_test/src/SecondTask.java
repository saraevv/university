import javax.swing.*;
import java.util.ArrayList;
import java.util.Comparator;

public class SecondTask extends JPanel {
    private JList<Drink> list;
    private DefaultListModel<Drink> listModel;
    private ArrayList<Drink> arrayList;

    public SecondTask(ArrayList<Drink> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<Drink>();
        list = new JList<Drink>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        arrayList.stream().sorted(new Comparator<Drink>() {
            @Override
            public int compare(Drink drink, Drink t1) {
                int fComp = -drink.getPrice() + t1.getPrice();
                return fComp == 0 ? drink.getName().compareTo(t1.getName()) : fComp;
            }
        }).forEach(x -> listModel.addElement(x));
        list.updateUI();
    }
}
