package com.saraew.main;

import javax.swing.*;

public class MainWindow extends JFrame {
    private static final int CELL_HEIGHT = 20;

    public MainWindow(int rows, int cols) {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setBounds(300, 300, 600, CELL_HEIGHT * (rows + 1) + 40);
        this.setResizable(false);
        JTable table = new JTable();
        table.setRowHeight(CELL_HEIGHT);
        Controller controller = new Controller(rows, cols, table, this);

        this.add(table);
    }
}
