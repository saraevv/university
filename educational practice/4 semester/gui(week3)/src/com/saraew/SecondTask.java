package com.saraew;

import javax.swing.*;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.Map;

public class SecondTask extends JPanel {
    private DefaultTableModel tableModel;
    private JTable table;
    private Map<String, Country> countryMap;
    private JScrollPane scrollPane;
    private JPanel info;
    private JLabel text;
    private JLabel price;

    public SecondTask(Map<String, Country> countryMap) {
        this.countryMap = countryMap;
        tableModel = new DefaultTableModel() {
            public Class getColumnClass(int column) {
                switch (column) {
                    case 0:
                        return ImageIcon.class;
                    case 1:
                        return String.class;
                    case 2:
                    case 4:
                        return Integer.class;
                    case 3:
                        return Boolean.class;
                    default:
                        return Object.class;
                }
            }

            public boolean isCellEditable(int row, int column) {
                return column != 0;
            }
        };
        tableModel.setColumnIdentifiers(new Object[]{"Country", "Description", "Price", "Selected"});
        for (Map.Entry<String, Country> entry : countryMap.entrySet()) {
            tableModel.addRow(new Object[]{entry.getValue().getImage(), entry.getValue().getDescription(),
                    entry.getValue().getPrice(), Boolean.FALSE});
        }
        table = new JTable(tableModel);
        DefaultTableCellRenderer centerRenderer = new DefaultTableCellRenderer();
        centerRenderer.setHorizontalAlignment(JLabel.CENTER);
        table.getColumnModel().getColumn(2).setCellRenderer(centerRenderer);
        table.setRowHeight(40);
        scrollPane = new JScrollPane(table);
        this.setLayout(new BorderLayout());
        this.add(scrollPane, BorderLayout.CENTER);

        text = new JLabel("Total price:");
        text.setHorizontalAlignment(JLabel.CENTER);
        price = new JLabel("0");
        price.setHorizontalAlignment(JLabel.CENTER);
        info = new JPanel();
        info.setLayout(new BorderLayout());
        info.add(text, BorderLayout.WEST);
        info.add(price, BorderLayout.EAST);
        info.setPreferredSize(new Dimension(0, 50));
        text.setFont(new Font("Arial", Font.BOLD, 15));
        price.setFont(new Font("Arial", Font.BOLD, 15));
        this.add(info, BorderLayout.SOUTH);

        tableModel.addTableModelListener(new TableModelListener() {
            @Override
            public void tableChanged(TableModelEvent tableModelEvent) {
                if (tableModelEvent.getColumn() == 3 || tableModelEvent.getColumn() == 2) {
                    int count = 0;
                    for (int i = 0; i < tableModel.getRowCount(); ++i) {
                        if ((boolean) tableModel.getValueAt(i, 3)) {
                            count += (int) tableModel.getValueAt(i, 2);
                        }
                    }
                    price.setText(Integer.toString(count));
                }
            }
        });
    }

    public void update() {
        for (int i = 0; i < tableModel.getRowCount(); ++i) {
            tableModel.removeRow(0);
        }
        tableModel.setColumnIdentifiers(new Object[]{"Country", "Description", "Price", "Selected"});
        for (Map.Entry<String, Country> entry : countryMap.entrySet()) {
            tableModel.addRow(new Object[]{entry.getValue().getImage(), entry.getValue().getDescription(),
                    entry.getValue().getPrice(), Boolean.FALSE});
        }
    }

}
