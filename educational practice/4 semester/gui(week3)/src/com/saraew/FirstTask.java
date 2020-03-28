package com.saraew;

import javax.swing.*;
import java.awt.*;
import java.util.Collections;
import java.util.Map;

public class FirstTask extends JPanel {
    private DefaultListModel<Country> listModel;
    private JList<Country> list;
    private Map<String, Country> countryMap;
    private JScrollPane scrollPane;
    private JLabel output;

    public FirstTask(Map<String, Country> countryMap) {
        this.countryMap = countryMap;
        listModel = new DefaultListModel<>();
        for (Map.Entry<String, Country> entry : countryMap.entrySet()) {
            listModel.addElement(entry.getValue());
        }
        list = new JList<>(listModel);
        list.setCellRenderer(new CountryRenderer());
        scrollPane = new JScrollPane(list);
        scrollPane.setPreferredSize(new Dimension(250, 250));
        this.setLayout(new BorderLayout());
        this.add(scrollPane, BorderLayout.CENTER);
        output = new JLabel();
        output.setHorizontalAlignment(JLabel.CENTER);
        output.setPreferredSize(new Dimension(0, 30));
        this.add(output, BorderLayout.SOUTH);

        //this.add(new JPanel(), BorderLayout.WEST);
        //this.add(new JPanel(), BorderLayout.EAST);
        //this.add(list);
    }

    private class CountryRenderer extends JLabel implements ListCellRenderer<Country> {

        CountryRenderer() {
            this.setOpaque(true);
        }

        @Override
        public Component getListCellRendererComponent(JList<? extends Country> jList, Country country,
                                                      int i, boolean isSelected, boolean cellHasFocus) {
            setIcon(country.getImage());
            setText(country.getName());
            if (isSelected) {
                output.setText(country.getCapital());
                this.setBackground(Color.lightGray);
            } else {
                this.setBackground(Color.white);
            }
            return this;
        }
    }

    public void update() {
        listModel.removeAllElements();
        for (Map.Entry<String, Country> entry : countryMap.entrySet()) {
            listModel.addElement(entry.getValue());
        }
    }

}
