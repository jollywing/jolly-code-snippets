
/**
 * AUTHOR: Jolly Wing (jiqingwu@gmail.com)
 * CREATE: 2013-07-16
 * UPDATE: 2013-07-16
 */

import javax.swing.JFrame;
import javax.swing.JPopupMenu;
import javax.swing.JMenuItem;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.awt.Graphics;

public class TestPopupMenu extends JFrame implements MouseListener {
    private JPopupMenu menu;

    public TestPopupMenu() {
        setTitle("Test PopupMenu");
        setSize(250, 244);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addMouseListener(this);

        menu = new JPopupMenu("Popup Menu Sample");
        JMenuItem itemFillRed = new JMenuItem("Fill Red");
        itemFillRed.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    fillColor(Color.red);
                }
            });

        JMenuItem itemFillGreen = new JMenuItem("Fill Green");
        itemFillGreen.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    fillColor(Color.green);
                }
            });

        JMenuItem itemFillBlue = new JMenuItem("Fill Blue");
        itemFillBlue.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    fillColor(Color.blue);
                }
            });

        JMenuItem itemExit = new JMenuItem("Exit");
        itemExit.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    System.exit(0);
                }
            });
        menu.add(itemFillRed);
        menu.add(itemFillGreen);
        menu.add(itemFillBlue);
        menu.add(itemExit);
    }

    private void fillColor(Color color) {
        Graphics g = getGraphics();
        // g.clearRect(0, 0, getWidth(), getHeight());
        g.setColor(color);
        g.fillRect(0, 0, getWidth(), getHeight());
    }

    @Override
    public void mouseClicked(MouseEvent e)
    {
    }

    @Override
    public void mouseEntered(MouseEvent e)
    {
    }

    @Override
    public void mouseExited(MouseEvent e)
    {
    }

    @Override
    public void mousePressed(MouseEvent e)
    {
        // System.out.println("mouse pressed.");
        if (e.getButton() == MouseEvent.BUTTON3)
            {
                // System.out.println("right clicked.");
                menu.show(this, e.getX(), e.getY());
            }
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
    }

    public static void main(String args[]) {
        TestPopupMenu t = new TestPopupMenu();
        t.setVisible(true);
    }
}
