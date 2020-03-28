import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class Task2 extends JPanel {
    private JPanel panel;
    private JButton[] buttons;
    private ButtonListener buttonListener;

    Task2(String text) {
        //this.setSize(600, 400);
        this.setLayout(new BorderLayout());
        buttonListener = new ButtonListener();
        panel = new JPanel();
        buttons = new JButton[25];
        this.add(panel, BorderLayout.CENTER);
        this.add(new JLabel(text), BorderLayout.SOUTH);
        Random rand = new Random();
        for (int i = 0; i < 25; ++i) {
            buttons[i] = new JButton(Integer.toString(i + 1));
            float r = rand.nextFloat();
            float g = rand.nextFloat();
            float b = rand.nextFloat();
            Color currentColor = new Color(r, g, b);
            buttons[i].setBackground(currentColor);
            buttons[i].addMouseListener(buttonListener);
        }
        panel.setLayout(new GridLayout(5, 5));
        for (JButton i : buttons) {
            panel.add(i);
        }
    }

    private class ButtonListener extends MouseAdapter {
        private Color currentColor;
        private String currentText;

        @Override
        public void mouseEntered(MouseEvent e) {
            JButton current = (JButton) e.getSource();
            currentText = current.getText();
            currentColor = current.getBackground();
            current.setBackground(Color.GREEN);
        }

        @Override
        public void mouseExited(MouseEvent e) {
            JButton current = (JButton) e.getSource();
            current.setBackground(currentColor);
        }

        @Override
        public void mousePressed(MouseEvent e) {
            JButton current = (JButton) e.getSource();
            currentText = current.getText();
            current.setText("Clicked!");
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            JButton current = (JButton) e.getSource();
            current.setText(currentText);
        }
    }
}


