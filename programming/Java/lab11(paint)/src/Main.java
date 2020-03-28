import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Window w = new Window();
        w.setVisible(true);
    }

    private static class Window extends JFrame {
        private static JPanel edit;
        private static JButton red, green, blue, save, load;
        private static DrawPanel mainp;
        private static JScrollPane scrollPane;
        private static JFileChooser fileChooser;
        private static Color color = Color.red;
        private static int prevX, prevY;

        private Window() {
            this.setTitle("Paint");
            this.setDefaultCloseOperation(EXIT_ON_CLOSE);
            this.setBounds(250, 250, 600, 400);

            Container container = this.getContentPane();
            container.setLayout(new BorderLayout());

            edit = new JPanel();
            mainp = new DrawPanel(Toolkit.getDefaultToolkit().getScreenSize().width, Toolkit.getDefaultToolkit().getScreenSize().height);
            scrollPane = new JScrollPane(mainp);
            ButtonListener bl = new ButtonListener();
            red = new JButton();
            red.setActionCommand("red");
            red.addActionListener(bl);
            green = new JButton();
            green.setActionCommand("green");
            green.addActionListener(bl);
            blue = new JButton();
            blue.setActionCommand("blue");
            blue.addActionListener(bl);
            save = new JButton();
            save.setActionCommand("save");
            save.addActionListener(bl);
            load = new JButton();
            load.setActionCommand("load");
            load.addActionListener(bl);

            red.setBackground(Color.red);
            green.setBackground(Color.green);
            blue.setBackground(Color.blue);
            save.setText("Save");
            load.setText("Load");
            edit.setLayout(new FlowLayout());
            edit.add(red);
            edit.add(green);
            edit.add(blue);
            edit.add(save);
            edit.add(load);

            container.add(scrollPane, BorderLayout.CENTER);
            container.add(edit, BorderLayout.SOUTH);

            mainp.addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent mouseEvent) {
                    Graphics2D g = (Graphics2D) (mainp.getGraphics());
                    Graphics2D gbuf = (Graphics2D) (mainp.getBuffer().getGraphics());
                    g.setColor(color);
                    gbuf.setColor(color);
                    g.fillOval(mouseEvent.getX(), mouseEvent.getY(), 5, 5);
                    gbuf.fillOval(mouseEvent.getX(), mouseEvent.getY(), 5, 5);
                }

                @Override
                public void mousePressed(MouseEvent mouseEvent) {
                    prevX = mouseEvent.getX();
                    prevY = mouseEvent.getY();
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
            });

            mainp.addMouseMotionListener(new MouseAdapter() {
                @Override
                public void mouseDragged(MouseEvent e) {
                    Graphics2D g = (Graphics2D) (mainp.getGraphics());
                    Graphics2D gbuf = (Graphics2D) (mainp.getBuffer().getGraphics());
                    g.setStroke(new BasicStroke(5f));
                    gbuf.setStroke(new BasicStroke(5f));
                    g.setColor(color);
                    gbuf.setColor(color);
                    g.drawLine(prevX, prevY, e.getX(), e.getY());
                    gbuf.drawLine(prevX, prevY, e.getX(), e.getY());
                    prevX = e.getX();
                    prevY = e.getY();
                }
            });
        }



        private class ButtonListener implements ActionListener {

            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                String s = actionEvent.getActionCommand();
                switch (s) {
                    case "red":
                        color = Color.red;
                        break;
                    case "green":
                        color = Color.green;
                        break;
                    case "blue":
                        color = Color.blue;
                        break;
                    case "save":
                        fileChooser = new JFileChooser();
                        fileChooser.setCurrentDirectory(new File("."));
                        if (fileChooser.showDialog(Window.this, "Save") == JFileChooser.APPROVE_OPTION) {
                            try {
                                ImageIO.write(mainp.getBuffer(), "png", fileChooser.getSelectedFile());
                            } catch (IOException exc) {
                                JOptionPane.showMessageDialog(Window.this, "File doesn't exist", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                        break;
                    case "load":
                        fileChooser = new JFileChooser(".");
                        if (fileChooser.showDialog(Window.this, "Load") == JFileChooser.APPROVE_OPTION) {
                            try {
                                mainp.loadImage(ImageIO.read(fileChooser.getSelectedFile()));
                            } catch (IOException exc) {
                                JOptionPane.showMessageDialog(Window.this, "File doesn't exist", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                        break;
                }
            }
        }

    }
}
