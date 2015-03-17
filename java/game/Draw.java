/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-18
 **/

import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

class Draw extends Frame
{
    public Draw(String title) {
        super(title);
        setSize(400, 500);
        addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    System.exit(0);
                }
            });
    }

    public static void main(String [] args) {
        Draw win = new Draw("Game Window");
        win.setVisible(true);
    }
}
