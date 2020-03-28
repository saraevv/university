package com.saraew;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.io.File;

public class AddDialog extends JDialog {
    private JPanel input, name, capital, description, image, price;
    private JLabel lName, lCapital, lDescription, lImage, lPrice;
    private JTextField tName, tCapital, tDescription, tPrice;
    private JButton add, choose;
    private Country country;
    private File imageFile;

    public AddDialog(JFrame owner) {
        this.setAlwaysOnTop(true);
        this.setModal(true);
        this.setResizable(false);
        this.setSize(400, 250);
        this.setTitle("Add a country");

        input = new JPanel();
        name = new JPanel();
        capital = new JPanel();
        description = new JPanel();
        image = new JPanel();
        price = new JPanel();

        lName = new JLabel("Name");
        lName.setHorizontalAlignment(JLabel.CENTER);
        lDescription = new JLabel("Description");
        lDescription.setHorizontalAlignment(JLabel.CENTER);
        lCapital = new JLabel("Capital");
        lCapital.setHorizontalAlignment(JLabel.CENTER);
        lImage = new JLabel("Image");
        lImage.setHorizontalAlignment(JLabel.CENTER);
        lPrice = new JLabel("Price");
        lPrice.setHorizontalAlignment(JLabel.CENTER);

        tName = new JTextField();
        tName.setColumns(15);
        tCapital = new JTextField();
        tCapital.setColumns(15);
        tDescription = new JTextField();
        tDescription.setColumns(15);
        tPrice = new JTextField();
        tPrice.setColumns(15);

        add = new JButton("Add");

        choose = new JButton("Choose");

        name.setLayout(new GridLayout(0, 1));
        name.add(lName);
        name.add(tName);

        capital.setLayout(new GridLayout(0, 1));
        capital.add(lCapital);
        capital.add(tCapital);

        description.setLayout(new GridLayout(0, 1));
        description.add(lDescription);
        description.add(tDescription);

        price.setLayout(new GridLayout(0, 1));
        price.add(lPrice);
        price.add(tPrice);

        image.setLayout(new GridLayout(0, 1));
        image.add(lImage);
        image.add(choose);

        input.setLayout(new FlowLayout());
        input.add(name);
        input.add(capital);
        input.add(description);
        input.add(price);
        input.add(image);

        this.setLayout(new BorderLayout());
        this.add(input, BorderLayout.CENTER);
        this.add(add, BorderLayout.SOUTH);

        this.setLocationRelativeTo(owner);


        choose.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFileChooser fileChooser = new JFileChooser();
                fileChooser.setFileFilter(new FileNameExtensionFilter("PNG image", "png"));
                fileChooser.setCurrentDirectory(new File("."));
                int returnVal = fileChooser.showOpenDialog(AddDialog.this);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    imageFile = fileChooser.getSelectedFile();
                }
            }
        });

        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                String name = tName.getText();
                String capital = tCapital.getText();
                String description = tDescription.getText();
                String price = tPrice.getText();
                if (name.length() == 0 || capital.length() == 0 ||
                        description.length() == 0 || price.length() == 0 || imageFile == null) {
                    JOptionPane.showMessageDialog(AddDialog.this, "Incorrect input!",
                            "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    try {
                        country = new Country(name, capital,
                                imageFile.getPath(), description, Integer.parseInt(price));
                    }
                    catch (NumberFormatException e) {
                        JOptionPane.showMessageDialog(AddDialog.this, "Incorrect input!",
                                "Error", JOptionPane.ERROR_MESSAGE);
                    }
                    AddDialog.this.dispatchEvent(new WindowEvent(AddDialog.this, WindowEvent.WINDOW_CLOSING));
                }
            }
        });
    }

    public boolean isNull() {
        return country == null;
    }

    public Country getCountry() {
        return country;
    }

}
