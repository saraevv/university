import javax.swing.*;
import java.util.ArrayList;
import java.util.Comparator;

public class FirstView extends JPanel {
    private JList<AbstractWorker> list;
    private DefaultListModel<AbstractWorker> listModel;
    private ArrayList<AbstractWorker> arrayList;

    public FirstView(ArrayList<AbstractWorker> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<AbstractWorker>();
        list = new JList<AbstractWorker>(listModel);

        this.add(list);
    }

    public void update(String currentOrganization) {
        listModel.removeAllElements();
        arrayList.stream().filter(x -> x.getOrganization().equals(currentOrganization)).sorted(new Comparator<AbstractWorker>() {
            @Override
            public int compare(AbstractWorker abstractWorker, AbstractWorker t1) {
                return (int)(- abstractWorker.calculateSalary() + t1.calculateSalary());
            }
        }).forEach(x->listModel.addElement(x));
        list.updateUI();
    }
}
