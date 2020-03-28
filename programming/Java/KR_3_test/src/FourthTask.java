import javax.swing.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.DoubleStream;

public class FourthTask extends JPanel {
    private JList<String> list;
    private DefaultListModel<String> listModel;
    private ArrayList<Drink> arrayList;

    public FourthTask(ArrayList<Drink> arrayList) {
        this.arrayList = arrayList;
        listModel = new DefaultListModel<String>();
        list = new JList<String>(listModel);

        this.add(list);
    }

    public void update() {
        listModel.removeAllElements();
        double mean;
        if (arrayList.get(0) instanceof Coffee) {
            Map<CoffeeType, Double> map = new HashMap<>();

            mean = arrayList.stream().map(x -> (Coffee) x).filter(x -> x.getCoffeeType() == CoffeeType.GRAIN).
                    mapToDouble(Coffee::getCaffeineCount).sum() / arrayList.stream().map(x -> (Coffee) x).filter(x -> x.getCoffeeType() == CoffeeType.GRAIN).
                    mapToDouble(Coffee::getCaffeineCount).count();
            map.put(CoffeeType.GRAIN, mean);

            mean = arrayList.stream().map(x -> (Coffee) x).filter(x -> x.getCoffeeType() == CoffeeType.MILLED).
                    mapToDouble(Coffee::getCaffeineCount).sum() / arrayList.stream().map(x -> (Coffee) x).filter(x -> x.getCoffeeType() == CoffeeType.MILLED).
                    mapToDouble(Coffee::getCaffeineCount).count();
            map.put(CoffeeType.MILLED, mean);

            for(Map.Entry i: map.entrySet()) {
                listModel.addElement("Key: " + i.getKey() +"; Value: " + i.getValue());
            }
        } else {
            Map<TeaType, Double> map = new HashMap<>();

            mean = arrayList.stream().map(x ->(Tea)x).filter(x->x.getTeaType()==TeaType.BLACK).
                    mapToDouble(Tea::getCaffeineCount).sum()/arrayList.stream().map(x ->(Tea)x).filter(x->x.getTeaType()==TeaType.BLACK).
                    mapToDouble(Tea::getCaffeineCount).count();
            map.put(TeaType.BLACK, mean);

            mean = arrayList.stream().map(x ->(Tea)x).filter(x->x.getTeaType()==TeaType.GREEN).
                    mapToDouble(Tea::getCaffeineCount).sum()/arrayList.stream().map(x ->(Tea)x).filter(x->x.getTeaType()==TeaType.GREEN).
                    mapToDouble(Tea::getCaffeineCount).count();
            map.put(TeaType.GREEN, mean);

            for(Map.Entry i: map.entrySet()) {
                listModel.addElement("Key: " + i.getKey() +"; Value: " + i.getValue());
            }
        }
        list.updateUI();
    }
}
