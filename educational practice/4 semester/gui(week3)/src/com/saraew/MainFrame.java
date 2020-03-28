package com.saraew;

import org.xml.sax.SAXException;

import javax.swing.*;
import javax.xml.parsers.ParserConfigurationException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class MainFrame extends JFrame {
    private JTabbedPane tabbedPane;
    private FirstTask firstTask;
    private SecondTask secondTask;
    private static Map<String, Country> countryMap = new TreeMap<>();
    private JMenuBar menuBar;
    private JMenu edit;
    private JMenuItem add;

    public MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setBounds(250, 150, 800, 600);
        this.setTitle("GUI");
        init();
    }

    private void init() {
        try {
            CountryParser.parseFromXML("E:\\university\\educational practice\\4 semester\\gui(week3)\\input.xml",
                    countryMap);
        } catch (ParserConfigurationException | IOException | SAXException e) {
            e.printStackTrace();
        }
        tabbedPane = new JTabbedPane();
        firstTask = new FirstTask(countryMap);
        secondTask = new SecondTask(countryMap);
        tabbedPane.add(firstTask, "First Task");
        tabbedPane.add(secondTask, "Second Task");
        this.add(tabbedPane);

        menuBar = new JMenuBar();
        edit = new JMenu("Edit");
        add = new JMenuItem("Add");
        menuBar.add(edit);
        edit.add(add);
        this.setJMenuBar(menuBar);

        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                AddDialog dialog = new AddDialog(MainFrame.this);
                dialog.setVisible(true);
                if (!dialog.isNull()) {
                    Country country = dialog.getCountry();
                    countryMap.put(country.getName(), country);
                    MainFrame.this.updateAll();
                }
            }
        });
    }

    public void updateAll() {
        firstTask.update();
        secondTask.update();
    }

}
