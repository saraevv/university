package com.saraew.stuff;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class MyDate {
    private GregorianCalendar calendar = null;
    private boolean isVisible = false;

    @Override
    public String toString() {
        if (!isVisible) {
            return "";
        }
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH) + 1;
        int day = calendar.get(Calendar.DAY_OF_MONTH);
        return day + "." + month + "." + year;
    }

    public GregorianCalendar getCalendar() {
        return calendar;
    }

    public void setCalendar(GregorianCalendar calendar) {
        if (this.calendar == null) {
            this.calendar = new GregorianCalendar();
        }
        this.calendar.set(Calendar.YEAR, calendar.get(Calendar.YEAR));
        this.calendar.set(Calendar.MONTH, calendar.get(Calendar.MONTH));
        this.calendar.set(Calendar.DAY_OF_MONTH, calendar.get(Calendar.DAY_OF_MONTH));
    }

    public boolean isVisible() {
        return isVisible;
    }

    public void setVisible(boolean visible) {
        isVisible = visible;
    }

    public void clear() {
        this.calendar = null;
        this.isVisible = false;
    }
}
