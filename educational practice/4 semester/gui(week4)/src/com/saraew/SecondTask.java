package com.saraew;

import javax.swing.*;
import java.awt.*;
import java.util.Timer;
import java.util.TimerTask;

import static java.lang.Integer.min;

public class SecondTask extends JPanel {
    private Image image;
    private double speed = 1;
    private int radius = 200;
    private double corner = 0;
    private boolean isClockwise = true;

    public SecondTask() {
        java.util.Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                //speed = 2 * Math.PI * radius / scrollBar.getValue();
                //speed = (double)scrollBar.getValue() / radius;
                if (isClockwise) {
                    corner += speed / 100;
                } else {
                    corner -= speed / 100;
                }
                corner %= 2 * Math.PI;
                repaint();
            }

        }, 0, 10);
    }

    public void setImage(Image image) {
        this.image = image;
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        if (image != null) {
            int x0 = SecondTask.this.getWidth() / 2;
            int y0 = SecondTask.this.getHeight() / 2;
            radius = min(SecondTask.this.getWidth(), SecondTask.this.getHeight()) / 2;
            g2.setColor(Color.WHITE);
            g2.fillRect(0, 0, 1920, 1080);
            g2.setColor(Color.BLACK);
            double x1 = radius * Math.cos(corner) + x0;
            double y1 = radius * Math.sin(corner) + y0;
            g2.drawOval(x0 - 5, y0 - 5, 10, 10);
            g2.drawImage(image, (int) x1 - 100, (int) y1 - 50, 200, 100, Color.WHITE, null);
        }
    }

    public void setSpeed(double speed) {
        this.speed = speed / radius;
    }

    public void changeDirection() {
        isClockwise = !isClockwise;
    }
}
