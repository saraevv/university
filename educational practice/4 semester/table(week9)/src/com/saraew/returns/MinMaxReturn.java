package com.saraew.returns;

import java.util.ArrayList;

public class MinMaxReturn extends Return {
    protected boolean isMin;
    protected ArrayList<Return> values;

    public MinMaxReturn(boolean isMin) {
        super("minmax");
        this.isMin = isMin;
        values = new ArrayList<>();
    }

    public void append(Return r) {
        values.add(r);
    }

    public boolean isMin() {
        return isMin;
    }

    public void setMin(boolean min) {
        isMin = min;
    }

    public ArrayList<Return> getValues() {
        return values;
    }

    public void setValues(ArrayList<Return> values) {
        this.values = values;
    }
}
