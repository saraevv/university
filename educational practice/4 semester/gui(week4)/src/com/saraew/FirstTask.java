package com.saraew;

import javax.swing.*;
import java.awt.*;
import java.util.Timer;
import java.util.TimerTask;

public class FirstTask extends JPanel {
    private double corner = -90;

    public FirstTask() {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                corner += 6;
                repaint();
            }

    },0,1000);

}

    protected void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D)g;
        int x0 = FirstTask.this.getWidth() / 2;
        int y0 = FirstTask.this.getHeight() / 2;
        g2.setStroke(new BasicStroke(10.0f));
        g2.setColor(Color.WHITE);
        g2.fillRect(0, 0, 1920, 1080);
        g2.setColor(Color.BLACK);
        int radius = 200;
        g2.drawOval(x0 - radius, y0 - radius, radius * 2, radius * 2);
        double endx, endy;
        endx = radius * Math.cos(corner * Math.PI / 180) + x0;
        endy = radius * Math.sin(corner * Math.PI / 180) + y0;
        g2.drawLine(x0, y0, (int) endx, (int) endy);
    }


}
