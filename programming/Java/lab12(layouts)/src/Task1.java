import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Task1 extends JPanel {
    private JPanel left, center, right, l1, r1;
    private JList leftList, rightList;
    private JButton top, bot, button1, button2;
    private JTextField leftField, rightField;
    private ButtonListener buttonListener;
    private DefaultListModel<String> listModel1, listModel2;

    Task1(String text) {
        this.setSize(600, 400);
        listModel1 = new DefaultListModel<>();
        listModel2 = new DefaultListModel<>();
        left = new JPanel();
        right = new JPanel();
        center = new JPanel();
        l1 = new JPanel();
        r1 = new JPanel();
        leftList = new JList(listModel1);
        rightList = new JList(listModel2);
        top = new JButton(">");
        top.setActionCommand("left-right");
        bot = new JButton("<");
        bot.setActionCommand("right-left");
        button1 = new JButton("Add");
        button1.setActionCommand("add to left");
        button2 = new JButton("Add");
        button2.setActionCommand("add to right");
        leftField = new JTextField();
        rightField = new JTextField();

        buttonListener = new ButtonListener();
        top.addActionListener(buttonListener);
        bot.addActionListener(buttonListener);
        button1.addActionListener(buttonListener);
        button2.addActionListener(buttonListener);

        left.setBorder(new BevelBorder(BevelBorder.RAISED));
        left.setPreferredSize(new Dimension(this.getWidth() / 3, this.getHeight()));
        right.setBorder(new BevelBorder(BevelBorder.RAISED));
        right.setPreferredSize(new Dimension(this.getWidth() / 3, this.getHeight()));
        center.setBorder(new BevelBorder(BevelBorder.RAISED));
        center.setPreferredSize(new Dimension(this.getWidth() / 3, this.getHeight()));
        center.setLayout(new BorderLayout());

        top.setPreferredSize(new Dimension(0, 50));
        bot.setPreferredSize(new Dimension(0, 50));

        center.add(top, BorderLayout.NORTH);
        center.add(bot, BorderLayout.SOUTH);

        button1.setHorizontalAlignment(JButton.CENTER);
        button2.setHorizontalAlignment(JButton.CENTER);

        l1.setLayout(new GridLayout(0, 1));
        r1.setLayout(new GridLayout(0, 1));

        leftList.setPreferredSize(new Dimension(0, (this.getHeight() * 4) / 5));
        leftField.setPreferredSize(new Dimension(0, this.getHeight() / 10));
        button1.setPreferredSize(new Dimension(0, this.getHeight() / 10));

        left.setLayout(new BorderLayout());
        left.add(leftList, BorderLayout.CENTER);
        l1.add(button1);
        l1.add(leftField);
        left.add(l1, BorderLayout.SOUTH);
        left.add(new JLabel("Left List"), BorderLayout.NORTH);

        rightList.setPreferredSize(new Dimension(0, (this.getHeight() * 4) / 5));
        rightField.setPreferredSize(new Dimension(0, this.getHeight() / 10));
        button2.setPreferredSize(new Dimension(0, this.getHeight() / 10));

        right.setLayout(new BorderLayout());
        right.add(rightList, BorderLayout.CENTER);
        r1.add(button2);
        r1.add(rightField);
        right.add(r1, BorderLayout.SOUTH);
        right.add(new JLabel("Right List"), BorderLayout.NORTH);

        this.setLayout(new BorderLayout());
        this.add(left, BorderLayout.WEST);
        this.add(center, BorderLayout.CENTER);
        this.add(right, BorderLayout.EAST);
        this.add(new JLabel(text), BorderLayout.SOUTH);
    }

    private class ButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            switch (actionEvent.getActionCommand()) {
                case "add to left":
                    listModel1.addElement(leftField.getText());
                    break;
                case "add to right":
                    listModel2.addElement(rightField.getText());
                    break;
                case "left-right":
                    int[] indices1 = leftList.getSelectedIndices();
                    for (int i = indices1.length - 1; i >= 0; --i) {
                        listModel2.add(0, listModel1.getElementAt(indices1[i]));
                        listModel1.remove(indices1[i]);
                    }
                    break;
                case "right-left":
                    int[] indices2 = rightList.getSelectedIndices();
                    for (int i = indices2.length - 1; i >= 0; --i) {
                        listModel1.add(0, listModel2.getElementAt(indices2[i]));
                        listModel2.remove(indices2[i]);
                    }
                    break;
            }
        }
    }

}
