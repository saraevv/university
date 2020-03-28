import java.util.Scanner;

public class Student {
    private String surname;
    private int number;
    private int course;
    private int group;

    public Student() {
    }

    public Student(String surname, int number, int course, int group) {
        this.surname = surname;
        this.number = number;
        this.course = course;
        this.group = group;
    }

    @Override
    public String toString() {
        return this.surname + " " + this.number + " " +
                this.course + " " + this.group;
    }

    public static Student readStudent(Scanner scanner) {
        return new Student(scanner.next(), Integer.parseInt(scanner.next()),
                Integer.parseInt(scanner.next()), Integer.parseInt(scanner.next()));
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
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
}
