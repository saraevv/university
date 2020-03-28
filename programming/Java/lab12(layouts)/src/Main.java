import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        Window w = new Window();
        w.setVisible(true);
    }

    static class Window extends JFrame {
        private Task1 task1;
        private Task2 task2;
        private Task3 task3;
        private JTabbedPane tabbedPane;
        private String text;

        Window() {
            this.setDefaultCloseOperation(EXIT_ON_CLOSE);
            this.setTitle("lab12");
            this.setBounds(250, 250, 700, 500);
            text = "Saraev V. M., 2 cours, 3 group";
            task1 = new Task1(text);
            task2 = new Task2(text);
            task3 = new Task3(text);
            tabbedPane = new JTabbedPane();
            this.add(tabbedPane);
            tabbedPane.add(task1, "Task 1");
            tabbedPane.add(task2, "Task 2");
            tabbedPane.add(task3, "Task 3");
        }
    }
}
