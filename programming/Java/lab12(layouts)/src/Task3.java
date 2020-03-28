import javax.swing.*;
import java.awt.*;

public class Task3 extends JPanel {
    private JPanel panel;
    private JRadioButton[] buttons;
    private ImageIcon selected, disable, entered, pressed;

    Task3(String text) {
        this.setSize(600, 400);
        panel = new JPanel();
        buttons = new JRadioButton[4];
        selected = new ImageIcon("1.png");
        disable = new ImageIcon("2.png");
        entered = new ImageIcon("3.png");
        pressed = new ImageIcon("4.png");
        panel.setLayout(null);
        for (int i = 0; i < 4; ++i) {
            buttons[i] = new JRadioButton();
            buttons[i].setSelected(false);
            buttons[i].setRolloverEnabled(true);
            buttons[i].setIcon(disable);
            buttons[i].setPressedIcon(pressed);
            buttons[i].setRolloverIcon(entered);
            buttons[i].setSelectedIcon(selected);
            buttons[i].setDisabledIcon(disable);
            buttons[i].setDisabledSelectedIcon(disable);
            buttons[i].setRolloverSelectedIcon(entered);
            panel.add(buttons[i]);
        }
        buttons[0].setBounds(0, 0, 300, 200);
        buttons[1].setBounds(300, 0, 300, 200);
        buttons[2].setBounds(0, 200, 300, 200);
        buttons[3].setBounds(300, 200, 300, 200);
        buttons[0].setText("First");
        buttons[1].setText("Second");
        buttons[2].setText("Third");
        buttons[3].setText("Fourth");
        this.setLayout(new BorderLayout());
        this.add(panel, BorderLayout.CENTER);
        this.add(new JLabel(text), BorderLayout.SOUTH);
    }
}
