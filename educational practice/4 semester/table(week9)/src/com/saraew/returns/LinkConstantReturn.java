package com.saraew.returns;

public class LinkConstantReturn extends Return {
    protected int row, col, constant;

    public LinkConstantReturn(int row, int col, int constant) {
        super("link-constant");
        this.row = row;
        this.col = col;
        this.constant = constant;
    }

    public int getRow() {
        return row;
    }

    public void setRow(int row) {
        this.row = row;
    }

    public int getCol() {
        return col;
    }

    public void setCol(int col) {
        this.col = col;
    }

    public int getConstant() {
        return constant;
    }

    public void setConstant(int constant) {
        this.constant = constant;
    }
}
