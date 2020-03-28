import javax.swing.*;
import java.util.ArrayList;
import java.util.Comparator;

public class SecondView extends JPanel {
    private JList<AbstractWorker> list;
    private DefaultListModel<AbstractWorker> listModel;
    private ArrayList<AbstractWorker> arrayList;

    public SecondView(ArrayList<AbstractWorker> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<AbstractWorker>();
        list = new JList<AbstractWorker>(listModel);

        this.add(list);
    }

    public void update() {
        arrayList.stream().sorted(new Comparator<AbstractWorker>() {
            @Override
            public int compare(AbstractWorker abstractWorker, AbstractWorker t1) {
                return (int)(abstractWorker.calculateSalary()/abstractWorker.coefficient - t1.calculateSalary()/t1.coefficient);
            }
        }).forEach(x->listModel.addElement(x));
        list.updateUI();
    }
}