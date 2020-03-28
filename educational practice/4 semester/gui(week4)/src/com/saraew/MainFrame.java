package com.saraew;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class MainFrame extends JFrame {
    private JTabbedPane tabbedPane;
    private FirstTask firstTask;
    private SecondTask secondTask;
    private ThirdTask thirdTask;
    private JPanel secondTaskEditor;
    private JMenuBar menuBar;
    private JMenu menu;
    private JMenuItem chooseImage;
    private JMenuItem chooseInput;
    private String imagePath;
    private JScrollBar scrollBar;
    private JButton changeDirection;

    public MainFrame() {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setBounds(250, 150, 800, 600);
        this.setTitle("GUI");
        init();
    }

    private void init() {
        tabbedPane = new JTabbedPane();
        firstTask = new FirstTask();

        thirdTask = new ThirdTask();

        JPanel secondPanel = new JPanel();
        secondPanel.setLayout(new BorderLayout());
        secondTaskEditor = new JPanel();
        changeDirection = new JButton("Change direction");
        scrollBar = new JScrollBar(JScrollBar.HORIZONTAL, 500, 50, 150, 2000);
        secondTaskEditor.setLayout(new BorderLayout());
        secondTaskEditor.add(scrollBar, BorderLayout.NORTH);
        secondTaskEditor.add(changeDirection, BorderLayout.SOUTH);
        secondPanel.add(secondTaskEditor, BorderLayout.SOUTH);
        secondTask = new SecondTask();
        secondPanel.add(secondTask, BorderLayout.CENTER);
        tabbedPane.add(firstTask, "First Task");
        tabbedPane.add(secondPanel, "Second Task");

        tabbedPane.add(thirdTask, "Third Task");
        this.add(tabbedPane);
        menuBar = new JMenuBar();
        menu = new JMenu("File");
        chooseImage = new JMenuItem("Choose image");
        chooseInput = new JMenuItem("Choose input file");
        menu.add(chooseImage);
        menu.add(chooseInput);
        menuBar.add(menu);
        this.setJMenuBar(menuBar);
        chooseImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File("."));
                fileChooser.setFileFilter(new FileNameExtensionFilter("JPG and PNG", "JPG", "PNG"));
                int status = fileChooser.showOpenDialog(MainFrame.this);
                if (status == JFileChooser.APPROVE_OPTION) {
                    try {
                        secondTask.setImage(ImageIO.read(fileChooser.getSelectedFile()));
                    } catch (IOException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Wrong input", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        chooseInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setCurrentDirectory(new File("."));
                fileChooser.setFileFilter(new FileNameExtensionFilter("JSON", "JSON"));
                int status = fileChooser.showOpenDialog(MainFrame.this);
                if (status == JFileChooser.APPROVE_OPTION) {
                    try {
                        thirdTask.setDataList(JsonDataParser.parse(fileChooser.getSelectedFile().getPath()));
                    } catch (FileNotFoundException e) {
                        JOptionPane.showMessageDialog(MainFrame.this, "Wrong input", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        scrollBar.addAdjustmentListener(new AdjustmentListener() {
            @Override
            public void adjustmentValueChanged(AdjustmentEvent adjustmentEvent) {
                secondTask.setSpeed(adjustmentEvent.getValue());
            }
        });
        
        changeDirection.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                secondTask.changeDirection();
            }
        });
    }
}
