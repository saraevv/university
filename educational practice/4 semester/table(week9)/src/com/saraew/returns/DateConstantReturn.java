package com.saraew.returns;

import java.util.GregorianCalendar;

public class DateConstantReturn extends Return {
    protected GregorianCalendar calendar;
    protected int constant;

    public DateConstantReturn(GregorianCalendar calendar, int constant) {
        super("date-constant");
        this.calendar = calendar;
        this.constant = constant;
    }

    public GregorianCalendar getCalendar() {
        return calendar;
    }

    public void setCalendar(GregorianCalendar calendar) {
        this.calendar = calendar;
    }

    public int getConstant() {
        return constant;
    }

    public void setConstant(int constant) {
        this.constant = constant;
    }
}
