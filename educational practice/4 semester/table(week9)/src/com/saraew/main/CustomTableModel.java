package com.saraew.main;

import com.saraew.stuff.MyDate;

import javax.swing.table.AbstractTableModel;

public class CustomTableModel extends AbstractTableModel {
    private Object[][] data;
    private Controller controller;

    public CustomTableModel(int rows, int cols, Controller controller) {
        this.controller = controller;
        data = new Object[rows + 1][cols + 1];
        data[0][0] = "№";
        for (int i = 1; i <= rows; ++i) {
            data[i][0] = i;
            for (int j = 1; j <= cols; ++j) {
                data[i][j] = new MyDate();
            }
        }
        for (int i = 1; i <= cols; ++i) {
            data[0][i] = (char) ('A' + i - 1);
        }
    }

    public Object[][] getData() {
        return data;
    }

    public void setData(Object[][] data) {
        this.data = data;
    }

    @Override
    public int getRowCount() {
        return data.length;
    }

    @Override
    public int getColumnCount() {
        return data[0].length;
    }

    @Override
    public Object getValueAt(int i, int i1) {
        return data[i][i1];
    }

    @Override
    public boolean isCellEditable(int row, int column) {
        return row != 0 && column != 0;
    }

    @Override
    public Class<?> getColumnClass(int columnIndex) {
        return String.class;
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
        controller.updateCell(rowIndex, columnIndex, aValue.toString());
    }

    public void clear() {
        for (int i = 1; i < data.length; ++i) {
            for (int j = 1; j < data[i].length; ++j) {
                ((MyDate) data[i][j]).setVisible(false);
            }
        }
    }

}
