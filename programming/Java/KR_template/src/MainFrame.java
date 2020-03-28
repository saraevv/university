import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;

public class MainFrame extends JFrame {
    private JTabbedPane tabbedPane;
    private Task task;
    private ArrayList<SomeClass> arrayList;
    private JMenuBar menuBar;
    private JMenu open;
    private JMenuItem openXml;

    public MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setTitle("KR");
        this.setBounds(250, 250, 600, 400);

        arrayList = new ArrayList<SomeClass>();
        tabbedPane = new JTabbedPane();
        task = new Task(arrayList);

        menuBar = new JMenuBar();
        open = new JMenu("Open");
        openXml = new JMenuItem("Open .xml");

        open.add(openXml);
        menuBar.add(open);
        this.setJMenuBar(menuBar);

        tabbedPane.add(task);
        this.add(tabbedPane);

        openXml.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser chooser = new JFileChooser();
                chooser.setCurrentDirectory(new File("./src"));
                chooser.setFileFilter(new FileNameExtensionFilter("xml files (*.xml)", "xml"));
                int res = chooser.showOpenDialog(MainFrame.this);
                if (res == JFileChooser.APPROVE_OPTION) {
                    ReadFromFile.readXml(chooser.getSelectedFile(),arrayList);
                    //updateAll();
                }
            }
        });
    }

    private void updateAll() {
        task.update();
    }
}
