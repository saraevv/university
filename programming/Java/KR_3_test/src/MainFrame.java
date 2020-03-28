import org.xml.sax.SAXException;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.ParserConfigurationException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class MainFrame extends JFrame {
    private ArrayList<Drink> arrayList;
    private FirstTask firstTask;
    private SecondTask secondTask;
    private ThirdTask thirdTask;
    private FourthTask fourthTask;
    private JTabbedPane tabbedPane;
    private JMenuBar menuBar;
    private JMenu open;
    private JMenuItem openXml;

    public MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setTitle("KR test");
        this.setBounds(250, 250, 600, 400);

        arrayList = new ArrayList<Drink>();
        tabbedPane = new JTabbedPane();
        firstTask = new FirstTask(arrayList);
        secondTask = new SecondTask(arrayList);
        thirdTask = new ThirdTask(arrayList);
        fourthTask = new FourthTask(arrayList);

        menuBar = new JMenuBar();
        open = new JMenu("Open");
        openXml = new JMenuItem("Open .xml");
        open.add(openXml);
        menuBar.add(open);
        this.setJMenuBar(menuBar);

        tabbedPane.add(firstTask, "1");
        tabbedPane.add(secondTask, "2");
        tabbedPane.add(thirdTask, "3");
        tabbedPane.add(fourthTask, "4");

        this.add(tabbedPane);

        openXml.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser chooser = new JFileChooser();
                chooser.setCurrentDirectory(new File("./src"));
                chooser.setFileFilter(new FileNameExtensionFilter("xml files (*.xml)", "xml"));
                int res = chooser.showOpenDialog(MainFrame.this);
                if (res == JFileChooser.APPROVE_OPTION) {
                    try {
                        ReadArrayListFromXml.read(chooser.getSelectedFile(), arrayList);
                        MainFrame.this.updateAll();
                    } catch (ParserConfigurationException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    } catch (SAXException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
    }

    private void updateAll() {
        firstTask.update();
        secondTask.update();
        thirdTask.update();
        fourthTask.update();
    }
}
