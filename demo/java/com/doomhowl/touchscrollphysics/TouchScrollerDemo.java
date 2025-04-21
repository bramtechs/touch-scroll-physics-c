package com.doomhowl.touchscrollphysics;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Java demo for TouchScroller - designed to match the C demo's functionality
 */
public class TouchScrollerDemo extends JPanel implements MouseListener, MouseMotionListener {
    // Match C demo configuration
    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    private static final int TOTAL_CELLS = 25;
    private static final float VIEW_SIZE = WIDTH;
    private static final float CELL_SIZE = HEIGHT / 4.0f;
    private static final float GUTTER_SIZE = WIDTH / 2.0f;
    private static final boolean DIP_TO_CLOSEST_CELL = true;
    private static final float DIP_MAX_SPEED = 10.0f;
    private static final float DIP_SNAPPINESS = 0.1f;
    private static final float MOUSE_SCALE = 5.f; // get mouse position is integer in Swing, so it kinda sucks

    private TouchScroller scroller;
    private Timer timer;
    private boolean mousePressed = false;
    private boolean subjectIsVisible = false;
    private long lastUpdateTime;
    private float fps = 0;
    private int frameCount = 0;
    private long fpsUpdateTime = 0;

    public TouchScrollerDemo() {
        // Initialize TouchScroller - match C demo
        scroller = new TouchScroller(
                TOTAL_CELLS,
                VIEW_SIZE,
                CELL_SIZE,
                GUTTER_SIZE,
                DIP_TO_CLOSEST_CELL,
                DIP_MAX_SPEED,
                DIP_SNAPPINESS);

        // Set up UI
        setPreferredSize(new Dimension(WIDTH, HEIGHT));
        setMaximumSize(getPreferredSize());
        setMinimumSize(getPreferredSize());
        setDoubleBuffered(true); // Enable double buffering for smoother rendering
        addMouseListener(this);
        addMouseMotionListener(this);

        // Initialize last update time
        lastUpdateTime = System.currentTimeMillis();
        fpsUpdateTime = lastUpdateTime;

        // Setup animation timer (target 60 FPS - 1000ms/60 ≈ 16.67ms per frame)
        int targetFPS = 60;
        int delay = 1000 / targetFPS;
        timer = new Timer(delay, e -> {
            // Calculate actual delta time in milliseconds
            long currentTime = System.currentTimeMillis();
            float dt = (float) (currentTime - lastUpdateTime);
            lastUpdateTime = currentTime;

            // Update FPS counter
            frameCount++;
            if (currentTime - fpsUpdateTime >= 1000) {
                fps = frameCount * 1000.0f / (currentTime - fpsUpdateTime);
                frameCount = 0;
                fpsUpdateTime = currentTime;
            }

            scroller.update(dt);
            repaint();
        });
        timer.setCoalesce(false); // Prevent event coalescing which can reduce frame rate
        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        // Enable rendering optimizations
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_OFF);
        g2d.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_SPEED);

        // Match C demo background color (0x3b3b3b)
        g2d.setColor(new Color(59, 59, 59));
        g2d.fillRect(0, 0, getWidth(), getHeight());

        // Get current scroll offset
        float offset = scroller.getOffset();

        // Draw cells - matching the C demo
        for (int i = 0; i < TOTAL_CELLS; i++) {
            float x = i * CELL_SIZE - offset;

            // Only draw visible cells (plus a bit of padding)
            if (x < -CELL_SIZE || x > VIEW_SIZE) {
                continue;
            }

            Color cellColor;
            if (i == 10) {
                // Check visibility of the special "subject" cell #10
                subjectIsVisible = scroller.isVisible(i * CELL_SIZE, (i + 1) * CELL_SIZE);
                cellColor = subjectIsVisible ? Color.GREEN : Color.RED;
            } else {
                // Alternate cell colors to match C demo
                cellColor = (i % 2 == 0) ? new Color(0x7b, 0xb3, 0xd6) : new Color(0xcf, 0xcf, 0xcf);
            }

            g2d.setColor(cellColor);
            g2d.fillRect((int) x, 0, (int) CELL_SIZE, getHeight());
        }

        // Draw FPS counter
        g2d.setColor(Color.WHITE);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString(String.format("FPS: %d", Math.round(fps)), 10, 20);

        // Draw status text - match C demo
        g2d.setColor(Color.BLACK);
        g2d.setFont(new Font("Arial", Font.BOLD, 20));
        g2d.drawString("Subject " + (subjectIsVisible ? "visible" : "invisible"), 10, 50);
    }

    private float processTouchScrollerX(float mouseX) {
        if (mousePressed) {
            scroller.move(mouseX);
        }
        return scroller.getOffset();
    }

    // Mouse event handling for TouchScroller
    @Override
    public void mousePressed(MouseEvent e) {
        mousePressed = true;
        scroller.start(e.getX() * MOUSE_SCALE);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        mousePressed = false;
        scroller.end(e.getX() * MOUSE_SCALE);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        processTouchScrollerX(e.getX() * MOUSE_SCALE);
    }

    // Unused mouse event methods
    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }

    // Cleanup
    public void dispose() {
        timer.stop();
        scroller.dispose();
    }

    // Entry point
    public static void main(String[] args) {
        // Set rendering performance hints
        System.setProperty("sun.java2d.opengl", "true");

        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Touch Scroll Physics - Demo Java");
            TouchScrollerDemo demo = new TouchScrollerDemo();

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(demo);
            frame.pack();
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

            frame.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    demo.dispose();
                }
            });
        });
    }
}