import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;

public class CurrentGroupDialog extends JDialog {
    private JLabel label;
    private JTextField textField;
    private JButton button;
    private int group = -1;

    CurrentGroupDialog(JFrame parent) {
        this.setTitle("Edit group number");
        this.setModal(true);

        label = new JLabel("Enter group number");
        label.setHorizontalAlignment(JLabel.CENTER);
        textField = new JTextField();
        textField.setColumns(5);
        button = new JButton("Set");

        this.setLayout(new GridLayout(0, 1));
        this.add(label);
        this.add(textField);
        this.add(button);
        this.pack();
        this.setLocationRelativeTo(parent);

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                String s = textField.getText();
                if (s.equals(""))
                    group = 0;
                group = Integer.parseInt(s);
                CurrentGroupDialog.this.dispatchEvent(new WindowEvent(CurrentGroupDialog.this, WindowEvent.WINDOW_CLOSING));
            }
        });
    }

    public int getNumber() {
        return group;
    }

}
