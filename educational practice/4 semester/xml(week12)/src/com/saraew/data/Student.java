package com.saraew.data;

import java.io.Serializable;

public class Student implements Serializable {
    private String name;
    private int course;
    private int group;
    private boolean isAdmittedToExams;

    public Student(String name, int course, int group, boolean isAdmittedToExams) {
        this.name = name;
        this.course = course;
        this.group = group;
        this.isAdmittedToExams = isAdmittedToExams;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCourse() {
        return course;
    }

    public void setCourse(int course) {
        this.course = course;
    }

    public int getGroup() {
        return group;
    }

    public void setGroup(int group) {
        this.group = group;
    }

    public boolean getIsAdmittedToExams() {
        return isAdmittedToExams;
    }

    public void setAdmittedToExams(boolean admittedToExams) {
        isAdmittedToExams = admittedToExams;
    }
}
