import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;

public class AddDialog extends JDialog {
    private JPanel mainPanel;
    private JPanel buttonPanel;
    private JPanel surnamePanel;
    private JPanel numberPanel;
    private JPanel coursePanel;
    private JPanel groupPanel;
    private JTextField surnameField;
    private JTextField numberField;
    private JTextField courseField;
    private JTextField groupField;
    private JButton addButton;
    private DefaultTableModel students;

    AddDialog(JFrame owner, DefaultTableModel students) {
        this.setAlwaysOnTop(true);
        this.setModal(true);
        this.setResizable(false);
        this.setSize(400, 150);
        this.setTitle("Add a student");

        this.students = students;
        mainPanel = new JPanel();
        buttonPanel = new JPanel();
        surnamePanel = new JPanel();
        numberPanel = new JPanel();
        coursePanel = new JPanel();
        groupPanel = new JPanel();
        surnameField = new JTextField();
        numberField = new JTextField();
        courseField = new JTextField();
        groupField = new JTextField();
        addButton = new JButton("Add");

        surnameField.setColumns(15);
        numberField.setColumns(15);
        courseField.setColumns(15);
        groupField.setColumns(15);

        this.setLayout(new BorderLayout());
        this.add(mainPanel, BorderLayout.CENTER);
        this.add(buttonPanel, BorderLayout.SOUTH);

        mainPanel.setLayout(new FlowLayout());
        mainPanel.add(surnamePanel);
        mainPanel.add(numberPanel);
        mainPanel.add(coursePanel);
        mainPanel.add(groupPanel);

        surnamePanel.setLayout(new BorderLayout());
        surnamePanel.add(new JLabel("Surname"), BorderLayout.NORTH);
        surnamePanel.add(surnameField, BorderLayout.SOUTH);

        numberPanel.setLayout(new BorderLayout());
        numberPanel.add(new JLabel("Number"), BorderLayout.NORTH);
        numberPanel.add(numberField, BorderLayout.SOUTH);

        coursePanel.setLayout(new BorderLayout());
        coursePanel.add(new JLabel("Course"), BorderLayout.NORTH);
        coursePanel.add(courseField, BorderLayout.SOUTH);

        groupPanel.setLayout(new BorderLayout());
        groupPanel.add(new JLabel("Group"), BorderLayout.NORTH);
        groupPanel.add(groupField, BorderLayout.SOUTH);

        buttonPanel.setLayout(new BorderLayout());
        buttonPanel.add(new JPanel(), BorderLayout.WEST);
        buttonPanel.add(new JPanel(), BorderLayout.EAST);
        buttonPanel.add(addButton, BorderLayout.CENTER);

        EnterListener enterListener = new EnterListener();
        surnameField.addKeyListener(enterListener);
        numberField.addKeyListener(enterListener);
        courseField.addKeyListener(enterListener);
        groupField.addKeyListener(enterListener);


        addButton.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                String surname = surnameField.getText();
                String number = numberField.getText();
                String course = courseField.getText();
                String group = groupField.getText();
                if (surname.length() == 0 || number.length() == 0 ||
                        course.length() == 0 || group.length() == 0) {
                    JOptionPane.showMessageDialog(AddDialog.this, "Incorrect input!",
                            "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    Object[] row = {surname, Integer.parseInt(number),
                            Integer.parseInt(course), Integer.parseInt(group)};
                    students.addRow(row);
                    Window.updateList();
                    AddDialog.this.dispatchEvent(new WindowEvent(AddDialog.this, WindowEvent.WINDOW_CLOSING));
                }
            }
        });
        this.setLocationRelativeTo(owner);

    }

    private class EnterListener extends KeyAdapter {
        @Override
        public void keyTyped(KeyEvent e) {
            if(e.getKeyChar() == KeyEvent.VK_ENTER) {
                 for(ActionListener actionListener: addButton.getActionListeners()){
                     actionListener.actionPerformed(new ActionEvent(this,0,null));
                 }
            }
        }
    }

}
