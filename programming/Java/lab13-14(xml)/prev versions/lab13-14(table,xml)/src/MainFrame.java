import org.w3c.dom.*;
import org.xml.sax.SAXException;

import javax.swing.*;
import javax.swing.border.Border;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.*;
import java.util.Comparator;
import java.util.Scanner;

public class MainFrame extends JFrame {
    private JPanel southPanel;
    private static StudentListModel listModel = new StudentListModel();
    private static StudentTableModel tableModel = new StudentTableModel();
    private static JList list = new JList(listModel);
    private static JTable table = new JTable(tableModel);
    private JButton setCurrentGroup;
    private JLabel currentGroupLabel;
    private JTextField currentGroupField;
    private static int currentGroup = -1;
    private Font font;
    private JMenuBar menuBar;
    private JMenu file;
    private JMenu open;
    private JMenuItem openTxt;
    private JMenuItem openXml;
    private JMenuItem save;
    private JMenuItem add;
    private JFileChooser fileChooser;
    private JLabel nameLabel;
    private JLabel numberLabel;
    private JLabel courseLabel;
    private JLabel groupLabel;
    private JLabel listLabel;

    public MainFrame() {
        super("Lab 13-14");
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setBounds(450, 250, 600, 400);
        this.setResizable(false);

        init();

        menuBar.add(file);
        open.add(openTxt);
        open.add(openXml);
        file.add(open);
        file.add(add);
        file.add(save);
        this.setJMenuBar(menuBar);

        openTxt.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    fileChooser = new JFileChooser();
                    int res = fileChooser.showOpenDialog(MainFrame.this);
                    if (res == fileChooser.APPROVE_OPTION) {
                        MainFrame.readFromTxtFile(fileChooser.getSelectedFile());
                    }
                } catch (FileNotFoundException e) {
                    JOptionPane.showMessageDialog(MainFrame.this, "File not found", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        openXml.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                int res = fileChooser.showOpenDialog(MainFrame.this);
                if (res == fileChooser.APPROVE_OPTION) {
                    try {
                        MainFrame.readFromXmlFile(fileChooser.getSelectedFile());
                    } catch (ParserConfigurationException | IOException | SAXException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Error",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        add.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                AddDialog addDialog = new AddDialog(MainFrame.this, tableModel, table);
                addDialog.setVisible(true);
            }
        });

        save.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                int res = fileChooser.showSaveDialog(MainFrame.this);
                if (res == fileChooser.APPROVE_OPTION) {
                    try {
                        MainFrame.writeToXml(fileChooser.getSelectedFile());
                    } catch (IOException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Error ",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        table.setBorder(BorderFactory.createLineBorder(Color.black));
        list.setBorder(BorderFactory.createLineBorder(Color.black));

        table.setRowHeight(35);
        table.getColumnModel().getColumn(0).setPreferredWidth(this.getWidth() / 6);
        table.getColumnModel().getColumn(1).setPreferredWidth(this.getWidth() / 6);
        table.getColumnModel().getColumn(2).setPreferredWidth(this.getWidth() / 24);
        table.getColumnModel().getColumn(3).setPreferredWidth(this.getWidth() / 24);
        table.setFont(font);
        list.setFont(font);

        currentGroupLabel.setHorizontalAlignment(JLabel.CENTER);
        currentGroupLabel.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        currentGroupField.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        setCurrentGroup.setPreferredSize(new Dimension(this.getWidth() / 3, 20));
        setCurrentGroup.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                try {
                    currentGroup = Integer.parseInt(currentGroupField.getText());
                    MainFrame.updateListModel();
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(MainFrame.this, "Incorrect number",
                            "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        currentGroupField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                if(e.getKeyChar() == KeyEvent.VK_ENTER) {
                    for(ActionListener actionListener: setCurrentGroup.getActionListeners()){
                        actionListener.actionPerformed(new ActionEvent(this,0,null));
                    }
                }
            }
        });

        southPanel.setLayout(new BorderLayout());
        southPanel.add(setCurrentGroup, BorderLayout.EAST);
        southPanel.add(currentGroupField, BorderLayout.CENTER);
        southPanel.add(currentGroupLabel, BorderLayout.WEST);

        this.setLayout(new BorderLayout());
        this.add(southPanel, BorderLayout.SOUTH);
        this.add(table, BorderLayout.WEST);
        this.add(list, BorderLayout.CENTER);

        try {
            readFromTxtFile(new File("input.txt"));
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(MainFrame.this, "File not found",
                    "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void init() {
        southPanel = new JPanel();
        setCurrentGroup = new JButton("Set");
        currentGroupLabel = new JLabel("Current group");
        currentGroupField = new JTextField();
        font = new Font("Arial", Font.BOLD, 15);
        menuBar = new JMenuBar();
        file = new JMenu("File");
        open = new JMenu("Open");
        add = new JMenuItem("Add");
        save = new JMenuItem("Save");
        openTxt = new JMenuItem("Open .txt");
        openXml = new JMenuItem("Open .xml");
        nameLabel = new JLabel("Name");
        numberLabel = new JLabel("Number");
        courseLabel = new JLabel("Course");
        groupLabel = new JLabel("Group");
        listLabel = new JLabel("List");
    }

    private static void readFromTxtFile(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        tableModel.deleteAll();
        while (scanner.hasNext()) {
            tableModel.addRow(Student.readStudent(scanner));
        }
        table.updateUI();
        MainFrame.updateListModel();
    }

    private static void readFromXmlFile(File file) throws ParserConfigurationException, IOException, SAXException {
        tableModel.deleteAll();
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(file);

        NodeList nodeList = document.getElementsByTagName("student");
        for (int i = 0; i < nodeList.getLength(); ++i) {
            NamedNodeMap attributes = nodeList.item(i).getAttributes();
            Student student = new Student();
            for (int j = 0; j < attributes.getLength(); ++j) {
                switch (attributes.item(j).getNodeName()) {
                    case "surname":
                        student.setSurname(attributes.item(j).getNodeValue());
                        break;
                    case "number":
                        student.setNumber(Integer.parseInt(attributes.item(j).getNodeValue()));
                        break;
                    case "course":
                        student.setCourse(Integer.parseInt(attributes.item(j).getNodeValue()));
                        break;
                    case "group":
                        student.setGroup(Integer.parseInt(attributes.item(j).getNodeValue()));
                        break;
                }
            }
            tableModel.addRow(student);
        }
        table.updateUI();
        MainFrame.updateListModel();
    }

    static void updateListModel() {
        if (currentGroup != -1) {
            listModel.deleteAll();
            tableModel.getArrayList().stream().filter(x -> x.getGroup() == currentGroup).
                    sorted(new Comparator<Student>() {
                        @Override
                        public int compare(Student student, Student t1) {
                            return student.getNumber() - t1.getNumber();
                        }
                    }).forEach(x -> listModel.add(x.getSurname()));
            list.updateUI();
        }

    }

    private static void writeToXml(File file) throws IOException {
//        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
//        Document document = documentBuilder.newDocument();
//
//        Element root = document.createElement("root");
//        Element students = document.createElement("students");
//
//        document.appendChild(root);
//        root.appendChild(students);
//
//        tableModel.getArrayList().stream().forEach(x -> {
//            Element student = document.createElement("student");
//            Element surname = document.createElement("surname");
//            surname.setTextContent(x.getSurname());
//            Element number = document.createElement("number");
//            number.setTextContent(Integer.toString(x.getNumber()));
//            Element course = document.createElement("coure");
//            course.setTextContent(Integer.toString(x.getCourse()));
//            Element group = document.createElement("group");
//            group.setTextContent(Integer.toString(x.getGroup()));
//
//            student.appendChild(surname);
//            student.appendChild(number);
//            student.appendChild(course);
//            student.appendChild(group);
//            students.appendChild(student);
//        });
//
//        Transformer transformer = TransformerFactory.newInstance().newTransformer();
//        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
//        transformer.transform(new DOMSource(document), new StreamResult(new FileOutputStream(file)));
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
        writer.write("<root>\n");
        writer.write("\t<students>\n");
        tableModel.getArrayList().forEach(x -> {
            try {
                writer.write("\t\t<student surname=\"" + x.getSurname() + "\" number=\"" + x.getNumber() + "\" course=\"" +
                        x.getCourse() + "\" group=\"" + x.getGroup() + "\" />\n");
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        writer.write("\t</students>\n");
        writer.write("</root>\n");
        writer.close();
        table.updateUI();
    }

}
