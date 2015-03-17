/**
 * AUTHOR: Jolly Wing
 * CREATE: 2013-07-03
 * UPDATE: 2013-07-03
 * COMPILE: javac -encoding GBK -cp lib/jcurses.jar CursesTextarea.java
 */

import jcurses.widgets.Window;
import jcurses.widgets.TextArea;
import jcurses.widgets.LayoutManager;
import jcurses.widgets.DefaultLayoutManager;
import jcurses.widgets.WidgetsConstants;
import jcurses.system.Toolkit;

public class CursesTextarea extends Window {
    public CursesTextarea(int width, int height, String name) {
        // no border
        super(width, height, false, name);
    }

    public static void main(String [] args) {
        Toolkit.setEncoding("GBK");
        CursesTextarea textareaWindow = new CursesTextarea(30, 15, "JCurses Text");
        TextArea textBox = new TextArea(28, 15, "中文可以吗？");
        DefaultLayoutManager manager = new DefaultLayoutManager();
        textareaWindow.getRootPanel().setLayoutManager(manager);
        manager.addWidget(textBox, 0, 0, 29, 15,
                      WidgetsConstants.ALIGNMENT_TOP, WidgetsConstants.ALIGNMENT_LEFT );
        textareaWindow.show();
    }
}
