import javax.swing.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;

public class ThirdView extends JPanel {
    private JList<String> list;
    private DefaultListModel<String> listModel;
    private ArrayList<AbstractWorker> arrayList;

    public ThirdView(ArrayList<AbstractWorker> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<String>();
        list = new JList<String>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        Set<String> set = new TreeSet<String>();
        for (AbstractWorker elem : arrayList) {
            set.add(elem.getOrganization());
        }
        set.forEach(x->listModel.addElement(x));
        list.updateUI();
    }
}