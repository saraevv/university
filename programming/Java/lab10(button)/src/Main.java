import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class Main {
    public static void main(String[] args) {
        Window w = new Window();
        w.setVisible(true);
    }

    static class Window extends JFrame {

        private static JPanel center;
        private static JLabel statusBar;
        private static JButton button;

        Window() {
            this.setBounds(300, 300, 600, 400);
            this.setTitle("Button");
            Container container = this.getContentPane();

            center = new JPanel();
            button = new JButton();
            button.setPreferredSize(new Dimension(200, 50));
            center.add(button);

            statusBar = new JLabel();
            statusBar.setText("0;0");
            statusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));
            statusBar.setPreferredSize(new Dimension(0, 20));


            container.setLayout(new BorderLayout());
            container.add(statusBar, BorderLayout.SOUTH);
            container.add(center, BorderLayout.CENTER);
            MyListener ml = new MyListener();
            addMouseListener(ml);
            addMouseMotionListener(ml);
        }
    }

    private static class MyListener implements MouseListener, MouseMotionListener {

        @Override
        public void mouseClicked(MouseEvent mouseEvent) {
            Window.button.setLocation(new Point(
                    MouseInfo.getPointerInfo().getLocation().x - 100, MouseInfo.getPointerInfo().getLocation().y - 25
            ));
        }

        @Override
        public void mousePressed(MouseEvent mouseEvent) {

        }

        @Override
        public void mouseReleased(MouseEvent mouseEvent) {

        }

        @Override
        public void mouseEntered(MouseEvent mouseEvent) {

        }

        @Override
        public void mouseExited(MouseEvent mouseEvent) {

        }

        @Override
        public void mouseDragged(MouseEvent mouseEvent) {

        }

        @Override
        public void mouseMoved(MouseEvent mouseEvent) {

        }
    }
}