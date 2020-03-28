import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.swing.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.Scanner;

public class MainFrame extends JFrame {
    private JTabbedPane tabbedPane;
    private FirstView firstView;
    private SecondView secondView;
    private static StudentContainer container = new StudentContainer();
    private int currentGroup = 0;
    private JMenuBar menuBar;
    private JMenu file;
    private JMenu edit;
    private JMenu open;
    private JMenuItem openTxt;
    private JMenuItem openXml;
    private JMenuItem save;
    private JMenuItem add;
    private JMenuItem editGroup;
    private JFileChooser fileChooser;

    MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setBounds(250, 250, 600, 400);
        this.setTitle("Lab13-14");

        tabbedPane = new JTabbedPane();
        firstView = new FirstView(container);
        secondView = new SecondView(container);

        tabbedPane.add(firstView, "All container");
        tabbedPane.add(secondView, "Sorted list");
        this.add(tabbedPane);

        menuBar = new JMenuBar();
        file = new JMenu("File");
        edit = new JMenu("Edit");
        open = new JMenu("Open");
        add = new JMenuItem("Add");
        save = new JMenuItem("Save");
        openTxt = new JMenuItem("Open .txt");
        openXml = new JMenuItem("Open .xml");
        editGroup = new JMenuItem("Edit current number");

        menuBar.add(file);
        open.add(openTxt);
        open.add(openXml);
        file.add(open);
        file.add(add);
        file.add(save);
        menuBar.add(edit);
        edit.add(editGroup);
        this.setJMenuBar(menuBar);

        try {
            readFromXml(new File("input.xml"));
        } catch (ParserConfigurationException | IOException | SAXException e) {
            JOptionPane.showMessageDialog(MainFrame.this, "Error",
                    "Error", JOptionPane.ERROR_MESSAGE);
        }
        MainFrame.this.updateAll();

        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                AddDialog dialog = new AddDialog(MainFrame.this);
                dialog.setVisible(true);
                if (!dialog.isNull()) {
                    container.add(dialog.getStudent());
                    MainFrame.this.updateAll();
                }
            }
        });

        openTxt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                try {
                    fileChooser = new JFileChooser();
                    int res = fileChooser.showOpenDialog(MainFrame.this);
                    if (res == fileChooser.APPROVE_OPTION) {
                        container.clear();
                        MainFrame.readFromTxt(fileChooser.getSelectedFile());
                        MainFrame.this.updateAll();
                    }
                } catch (FileNotFoundException e) {
                    JOptionPane.showMessageDialog(MainFrame.this, "File not found", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        openXml.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                int res = fileChooser.showOpenDialog(MainFrame.this);
                if (res == fileChooser.APPROVE_OPTION) {
                    try {
                        container.clear();
                        MainFrame.readFromXml(fileChooser.getSelectedFile());
                        MainFrame.this.updateAll();
                    } catch (ParserConfigurationException | IOException | SAXException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Error",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                fileChooser = new JFileChooser();
                int res = fileChooser.showSaveDialog(MainFrame.this);
                if (res == fileChooser.APPROVE_OPTION) {
                    try {
                        MainFrame.writeToXml(fileChooser.getSelectedFile());
                        MainFrame.this.updateAll();
                    } catch (IOException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Error ",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        editGroup.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                CurrentGroupDialog dialog = new CurrentGroupDialog(MainFrame.this);
                dialog.setVisible(true);
                currentGroup = dialog.getNumber();
                MainFrame.this.updateAll();
            }
        });
    }

    private static void readFromTxt(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        while (scanner.hasNext()) {
            container.add(new Student(scanner.next(), Integer.parseInt(scanner.next()),
                    Integer.parseInt(scanner.next()), Integer.parseInt(scanner.next())));
        }
    }

    private static void readFromXml(File file) throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document document = documentBuilder.parse(file);
        NodeList list = document.getElementsByTagName("student");
        for (int i = 0; i < list.getLength(); ++i) {
            Node node = list.item(i);
            Student student = new Student();
            student.setSurname(node.getAttributes().getNamedItem("surname").getNodeValue());
            NodeList childNodes = node.getChildNodes();
            for (int j = 0; j < childNodes.getLength(); ++j) {
                Node current = childNodes.item(j);
                switch (current.getNodeName()) {
                    case "number":
                        student.setNumber(Integer.parseInt(current.getTextContent()));
                        break;
                    case "course":
                        student.setCourse(Integer.parseInt(current.getTextContent()));
                        break;
                    case "group":
                        student.setGroup(Integer.parseInt(current.getTextContent()));
                        break;
                }
            }
            container.add(student);
        }
    }

    private static void writeToXml(File file) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
        writer.write("<root>\n");
        writer.write("\t<students>\n");
        container.stream().forEach(x -> {
            try {
                writer.write("\t\t<student surname=\"" + x.getSurname() + "\">\n\t\t\t<number>" +
                        x.getNumber() + "</number>\n\t\t\t<course>" + x.getCourse() + "</course>\n\t\t\t<group>" +
                        x.getGroup() + "</group>\n\t\t</student>\n");
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        writer.write("\t</students>\n");
        writer.write("</root>\n");
        writer.close();
    }

    private void updateAll() {
        firstView.update();
        secondView.update(currentGroup);
    }
}