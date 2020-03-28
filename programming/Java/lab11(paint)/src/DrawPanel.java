import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class DrawPanel extends JPanel {
    DrawPanel(int w, int h) {
        setPreferredSize(new Dimension(w, h));
        buffer = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
    }

    @Override
    public void paintComponent(Graphics g) {
        g.drawImage(buffer, 0, 0, null);
    }

    public BufferedImage getBuffer() {
        return buffer;
    }

    public void loadImage(BufferedImage buf) {
        buffer.createGraphics().setColor(Color.WHITE);
        buffer.createGraphics().fillRect(0, 0, getWidth(), getHeight());
        buffer.createGraphics().drawImage(buf, 0, 0, null);
        repaint();
    }

    private BufferedImage buffer;
}

