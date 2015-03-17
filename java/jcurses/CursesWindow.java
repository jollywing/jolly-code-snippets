/**
 * Jcurses Home: http://sourceforge.net/projects/javacurses
 * AUTHOR: jolly wing
 * CREATE: 2013-07-03
 **/

import jcurses.widgets.Window;
import jcurses.event.WindowListener;
import jcurses.event.WindowEvent;
import jcurses.system.InputChar;
import jcurses.system.CharColor;

public class CursesWindow extends Window implements WindowListener{
    public CursesWindow(int width, int height, String name) {
        super(width, height, true, name);
        this.addListener(this);
        this.setTitleColors(new CharColor(CharColor.BLACK,
                                          CharColor.REVERSE));
    }

    public static void main(String args[]) {
        CursesWindow w = new CursesWindow(30, 20, "JCurses Window");
        w.show();
    }

    /**
     * WindowListener implementation.
     * By Default, pressing Escape will close the window
     * you can call Window.setClosingChar to replace 'Escape'.
     */
    public void windowChanged( WindowEvent event ) {
        if( event.getType() == WindowEvent.CLOSING ) {
            event.getSourceWindow().close();
        }
    }

    protected void handleInput( InputChar ch ) {
        super.handleInput(ch);
        if (ch.getCharacter() == '\n' || ch.getCharacter() == '\r') {
            this.close();
        }
    }

}
