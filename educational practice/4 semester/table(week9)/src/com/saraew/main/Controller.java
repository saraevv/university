package com.saraew.main;

import com.saraew.exceptions.CycleException;
import com.saraew.returns.DateConstantReturn;
import com.saraew.returns.LinkConstantReturn;
import com.saraew.returns.MinMaxReturn;
import com.saraew.returns.Return;
import com.saraew.stuff.MyDate;
import com.saraew.stuff.Pair;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.TreeSet;

public class Controller {
    private CustomTableModel tableModel;
    private JTable table;
    private String[][] input;
    private JFrame mainFrame;

    public Controller(int rows, int cols, JTable table, JFrame mainFrame) {
        this.mainFrame = mainFrame;
        this.table = table;
        tableModel = new CustomTableModel(rows, cols, this);
        this.table.setModel(tableModel);
        input = new String[rows][cols];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                input[i][j] = "";
            }
        }
    }

    private String[][] inputCopy() {
        String[][] ans = new String[input.length][input[0].length];
        for (int i = 0; i < input.length; ++i) {
            for (int j = 0; j < input[i].length; ++j) {
                ans[i][j] = input[i][j];
            }
        }
        return ans;
    }

    public void updateCell(int row, int col, String val) {
        String[][] changes = inputCopy();
        if (Parsers.check(val)) {
            changes[row - 1][col - 1] = val;
            try {
                updateValues(changes);
                input = changes;
            } catch (CycleException | IndexOutOfBoundsException | NullPointerException e) {
                String msg;
                if (e instanceof CycleException) {
                    msg = "Cycle!";
                } else if (e instanceof IndexOutOfBoundsException) {
                    msg = "Index out of bounds!";
                } else {
                    msg = "Incorrect link!";
                }
                JOptionPane.showMessageDialog(mainFrame, msg, "Error", JOptionPane.ERROR_MESSAGE);
                try {
                    updateValues(input);
                } catch (CycleException ex) {
                    ex.printStackTrace();
                }
            }
            this.tableModel.fireTableDataChanged();
        } else {
            JOptionPane.showMessageDialog(mainFrame, "Wrong input", "Error", JOptionPane.ERROR_MESSAGE);
        }

    }

    public void updateValues(String[][] changes) throws CycleException {
        this.tableModel.clear();
        for (int i = 0; i < changes.length; ++i) {
            for (int j = 0; j < changes[i].length; ++j) {
                if (changes[i][j].length() != 0) {
                    CalculateValue(i, j, new TreeSet<>(), changes);
                }
            }
        }
    }

    public void CalculateValue(int i, int j, TreeSet<Pair<Integer, Integer>> tree, String[][] changes) throws CycleException {
        MyDate date = (MyDate) this.tableModel.getData()[i + 1][j + 1];
        boolean isEmpty = false;
        if (changes[i][j].length() == 0) {
            throw new NullPointerException();
        }
        if (date.isVisible()) {
            return;
        }
        Pair<Integer, Integer> p = new Pair<>(i, j);
        if (tree.contains(p)) {
            throw new CycleException();
        }
        tree.add(new Pair<>(i, j));
        Return val = Parsers.getValue(changes[i][j]);
        switch (val.getType()) {
            case "empty":
                isEmpty = true;
                date.clear();
                break;
            case "date-constant":
                DateConstantReturn dcr = (DateConstantReturn) val;
                date.setCalendar(dcr.getCalendar());
                date.getCalendar().add(Calendar.DAY_OF_MONTH, dcr.getConstant());
                break;
            case "link-constant":
                LinkConstantReturn lcr = (LinkConstantReturn) val;
                int i1 = lcr.getRow() - 1;
                int i2 = lcr.getCol() - 1;
                CalculateValue(i1, i2, (TreeSet<Pair<Integer, Integer>>) tree.clone(), changes);
                date.setCalendar(((MyDate) this.tableModel.getData()[i1 + 1][i2 + 1]).getCalendar());
                date.getCalendar().add(Calendar.DAY_OF_MONTH, lcr.getConstant());
                break;
            case "minmax":
                MinMaxReturn mmr = (MinMaxReturn) val;
                boolean isMin = mmr.isMin();
                ArrayList<Return> returns = mmr.getValues();
                GregorianCalendar res = null;
                for (Return r : returns) {
                    GregorianCalendar cur;
                    if (r.getType().equals("date-constant")) {
                        cur = ((DateConstantReturn) r).getCalendar();
                    } else {
                        LinkConstantReturn lcr1 = (LinkConstantReturn) r;
                        int i11 = lcr1.getRow() - 1;
                        int i21 = lcr1.getCol() - 1;
                        CalculateValue(i11, i21, (TreeSet<Pair<Integer, Integer>>) tree.clone(), changes);
                        cur = ((MyDate) this.tableModel.getData()[i11 + 1][i21 + 1]).getCalendar();
                    }

                    if (res == null || (isMin && cur.compareTo(res) < 0) || (!isMin && cur.compareTo(res) > 0)) {
                        res = cur;
                    }
                }
                date.setCalendar(res);
                break;
        }
        if (!isEmpty) {
            date.setVisible(true);
        }
    }
}
