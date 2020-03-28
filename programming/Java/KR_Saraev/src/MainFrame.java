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
    private FirstView firstView;
    private SecondView secondView;
    private ThirdView thirdView;
    private ArrayList<AbstractWorker> arrayList;
    private JTabbedPane tabbedPane;
    private JMenuBar menuBar;
    private JMenu file;
    private JMenu data;
    private JMenuItem open;
    private JMenuItem valuable;
    private JMenuItem bummer;
    private JMenuItem organizations;
    private JMenuItem search;
    private JMenuItem range;
    private String currentOrganization;

    public MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setTitle("KR Saraev");
        this.setBounds(250, 250, 600, 400);

        arrayList = new ArrayList<AbstractWorker>();
        tabbedPane = new JTabbedPane();

        menuBar = new JMenuBar();
        file = new JMenu("File");
        data = new JMenu("Data");
        open = new JMenuItem("Open");
        valuable = new JMenuItem("Valuable");
        bummer = new JMenuItem("Bummer");
        organizations = new JMenuItem("Organizations");
        search = new JMenuItem("Search");
        range = new JMenuItem("Range");

        file.add(open);
        data.add(valuable);
        data.add(bummer);
        data.add(organizations);
        data.add(search);
        data.add(range);
        menuBar.add(file);
        menuBar.add(data);

        this.setJMenuBar(menuBar);

        firstView = new FirstView(arrayList);
        secondView = new SecondView(arrayList);
        thirdView = new ThirdView(arrayList);

        tabbedPane.add(firstView, "1");
        tabbedPane.add(secondView, "2");
        tabbedPane.add(thirdView, "3");
        this.add(tabbedPane);

        open.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser chooser = new JFileChooser();
                chooser.setCurrentDirectory(new File("./src"));
                chooser.setFileFilter(new FileNameExtensionFilter("xml files (*.xml)", "xml"));
                int res = chooser.showOpenDialog(MainFrame.this);
                if (res == JFileChooser.APPROVE_OPTION) {
                    try {
                        arrayList.clear();
                        ArrayList<AbstractWorker> tm = ReadFromFile.readXml(chooser.getSelectedFile());
                        for (AbstractWorker worker : tm) {
                            arrayList.add(worker);
                        }
                        JOptionPane.showMessageDialog(MainFrame.this, "Count of workers: " + arrayList.size(), "Count of workers", JOptionPane.INFORMATION_MESSAGE);
                    } catch (ParserConfigurationException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (IOException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (SAXException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        valuable.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                currentOrganization = JOptionPane.showInputDialog(MainFrame.this, "Enter organization");
                firstView.update(currentOrganization);
            }
        });

        bummer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                secondView.update();
            }
        });

        organizations.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                thirdView.update();
            }
        });

        search.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (arrayList.isEmpty() || !arrayList.get(0).getClass().getName().equals("Seller")) {
                    JOptionPane.showMessageDialog(MainFrame.this, "There are no sellers");
                } else {
                    double min = arrayList.stream().map(x->(Seller)x).mapToDouble(x->x.getProceeds()).min().getAsDouble();
                    double max = arrayList.stream().map(x->(Seller)x).mapToDouble(x->x.getProceeds()).max().getAsDouble();
                    double mean = (min + max) / 2;
                    AbstractWorker worker = null;
                    for (AbstractWorker elem : arrayList) {
                        Seller seller = (Seller)elem;
                        if (seller.getProceeds() == mean) {
                            worker = elem;
                            break;
                        }
                    }
                    if (worker == null) {
                        JOptionPane.showMessageDialog(MainFrame.this, "There are no mean seller");
                    } else {
                        JOptionPane.showMessageDialog(MainFrame.this, "Mean seller: " + worker.toString());
                    }
                }
            }
        });

    }

}
