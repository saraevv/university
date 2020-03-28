import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
import java.util.TreeSet;

public class Window extends JFrame {
    private JPanel bottom;
    private JList list;
    private static DefaultListModel<String> listModel = new DefaultListModel<>();
    private JTable table;
    private static DefaultTableModel tableModel = new DefaultTableModel();
    private Object[] columns = {"Surname", "Number", "Course", "Group"};
    private JMenuBar menuBar;
    private JMenu file;
    private JMenuItem open;
    private JMenuItem add;
    private static int currentGroup = -1;
    private JLabel currentGroupLabel;
    private JTextField currentGroupField;
    private JButton setCurrentGroup;
    private JFileChooser fileChooser;

    Window() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setTitle("Lab 13");
        this.setBounds(250, 250, 600, 400);

        bottom = new JPanel();

        list = new JList(listModel);

        tableModel.setColumnCount(4);
        tableModel.setColumnIdentifiers(columns);
        table = new JTable(tableModel);

        menuBar = new JMenuBar();
        file = new JMenu("File");
        menuBar.add(file);
        open = new JMenuItem("Open");
        add = new JMenuItem("Add");
        file.add(open);
        file.add(add);

        table.setBorder(BorderFactory.createLineBorder(Color.black));
        list.setBorder(BorderFactory.createLineBorder(Color.black));

        add.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                AddDialog addDialog = new AddDialog(Window.this, tableModel);
                addDialog.setVisible(true);
            }
        });

        open.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                fileChooser.showSaveDialog(Window.this);
                try {
                    Window.readFromFile(fileChooser.getSelectedFile());
                } catch (FileNotFoundException e) {
                    JOptionPane.showMessageDialog(Window.this, "File not found", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        setCurrentGroup = new JButton("Set");
        currentGroupField = new JTextField();
        currentGroupLabel = new JLabel("Current group");
        currentGroupLabel.setHorizontalAlignment(JLabel.CENTER);

        currentGroupLabel.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        currentGroupField.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        setCurrentGroup.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        setCurrentGroup.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (currentGroupField.getText().length() != 0) {
                    currentGroup = Integer.parseInt(currentGroupField.getText());
                    updateList();
                }
            }
        });

        bottom.setLayout(new BorderLayout());
        bottom.add(currentGroupLabel, BorderLayout.WEST);
        bottom.add(currentGroupField, BorderLayout.CENTER);
        bottom.add(setCurrentGroup, BorderLayout.EAST);

        this.setLayout(new BorderLayout());
        this.add(table, BorderLayout.WEST);
        this.add(list, BorderLayout.CENTER);
        this.add(bottom, BorderLayout.SOUTH);
        this.setJMenuBar(menuBar);

        try {
            this.readFromFile(new File("input.txt"));
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(Window.this, "File not found", "Error", JOptionPane.ERROR_MESSAGE);
        }
        this.setVisible(true);
    }

    private static void readFromFile(File file) throws FileNotFoundException {
        tableModel.setRowCount(0);
        Scanner scanner = new Scanner(file);
        while (scanner.hasNext()) {
            Object[] row = {scanner.next(), scanner.nextInt(), scanner.nextInt(), scanner.nextInt()};
            tableModel.addRow(row);
            updateList();
        }
    }

    static void updateList() {
        if (currentGroup != -1) {
            listModel.removeAllElements();
            ArrayList<Student> arrayList = new ArrayList<>();
            for (int i = 0; i < tableModel.getRowCount(); ++i) {
                arrayList.add(new Student((String) tableModel.getValueAt(i, 0), (int) tableModel.getValueAt(i, 1),
                        (int) tableModel.getValueAt(i, 2), (int) tableModel.getValueAt(i, 3)));
            }
            //TreeSet<Student> treeSet = new TreeSet<Student>(arrayList.stream().filter(x -> x.getGroup() == currentGroup).
            //    collect(Collectors.toSet()));
            TreeSet<Student> treeSet = new TreeSet<Student>(new Comparator<Student>() {
                @Override
                public int compare(Student student, Student t1) {
                    return student.getNumber() - t1.getNumber();
                }
            });
            for(Student student: arrayList) {
                treeSet.add(student);
            }
            for(Student student:treeSet) {
                listModel.addElement(student.getSurname());
            }
        }
    }
}