package series;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Window w = new Window();
        w.setVisible(true);
    }

    static class Window extends JFrame {

        private JPanel buttons, radiobuttons, textfields, labels;
        private JButton calculateElem, calculateSum, save;
        private JRadioButton liner, exponential;
        private JTextField first, coef, num, output;
        private JLabel lfirst, lcoef, lnum;
        private Series s;

        Window() {
            setBounds(200, 200, 350, 350);
            setVisible(true);
            setTitle("Series");

            radiobuttons = new JPanel();
            radiobuttons.setLayout(new FlowLayout());
            liner = new JRadioButton("Liner");
            radiobuttons.add(liner);
            exponential = new JRadioButton("Exponential");
            radiobuttons.add(exponential);
            ButtonGroup bg = new ButtonGroup();
            bg.add(liner);
            bg.add(exponential);
            liner.doClick();

            buttons = new JPanel();
            buttons.setLayout(new FlowLayout());
            calculateElem = new JButton("Calculate Elem");
            calculateElem.setActionCommand("Calculate Elem");
            calculateElem.addActionListener(new ButtonListener());
            buttons.add(calculateElem);
            calculateSum = new JButton("Calculate Sum");
            calculateSum.setActionCommand("Calculate Sum");
            calculateSum.addActionListener(new ButtonListener());
            buttons.add(calculateSum);
            save = new JButton("Save as File");
            save.setActionCommand("Save as File");
            save.addActionListener(new ButtonListener());
            buttons.add(save);

            labels = new JPanel();
            labels.setLayout(new FlowLayout());
            lfirst = new JLabel("First Element");
            labels.add(lfirst);
            lcoef = new JLabel("Coefficient");
            labels.add(lcoef);
            lnum = new JLabel("Number");
            labels.add(lnum);

            textfields = new JPanel();
            textfields.setLayout(new FlowLayout());
            first = new JTextField();
            first.setColumns(7);
            textfields.add(first);
            coef = new JTextField();
            coef.setColumns(7);
            textfields.add(coef);
            num = new JTextField();
            num.setColumns(7);
            textfields.add(num);

            Container container = this.getContentPane();
            container.setLayout(new GridLayout(0, 1));
            container.add(radiobuttons);
            container.add(labels);
            container.add(textfields);
            container.add(buttons);
            output = new JTextField();
            output.setEditable(false);
            container.add(output);

        }

        private class ButtonListener implements ActionListener {

            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    boolean IsLiner = liner.isSelected();
                    String str;
                    str = first.getText();
                    double f = Double.parseDouble(str);
                    str = coef.getText();
                    double c = Double.parseDouble(str);
                    str = num.getText();
                    int n = Integer.parseInt(str);
                    if (IsLiner)
                        s = new Liner(f, c);
                    else
                        s = new Exponential(f, c);
                    double res;
                    switch (actionEvent.getActionCommand()) {
                        case "Calculate Elem":
                            res = s.calculate(n);
                            output.setText(Double.toString(res));
                            break;
                        case "Calculate Sum":
                            res = s.sum(n);
                            output.setText(Double.toString(res));
                            break;
                        case "Save as File":
                            try {
                                JFileChooser fileChooser = new JFileChooser();
                                fileChooser.showSaveDialog(null);
                                s.saveToFile(fileChooser.getSelectedFile(), n);
                            }
                            catch (IOException e) {
                                output.setText("Incorrect file");
                            }
                            break;
                    }
                } catch (Exception ex) {
                    output.setText("Incorrect input");
                }
            }
        }
    }
}
