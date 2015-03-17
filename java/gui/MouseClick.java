/* Purpose
 *  When you click mouse on canvas, This program will draw a circle
 *  around where you clicked.
 * Record of reversions
 *    date   programer    description
 * ========  ==========  ============================
 * 20080414  jiqing      original version
 * 20080415  jiqing      add class DrawCircle
 * 20080417  jiqing      draw circle & mouse click& popup menu
 */
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;  //draw circle
import javax.swing.*;

public class MouseClick extends JPanel {
  private JMenuBar bar;
  private JMenu menu;
  private JMenuItem clear, exit;
  private JMenuItem popupClear;
  private MouseDrawCircle dc; 
  private MouseHandler mh;
  private MenuHandler me;
  private JPopupMenu popup;         //popup menu
  

  //init
  public void init(){
    setLayout( new BorderLayout());
	mh = new MouseHandler(this);
	me = new MenuHandler(this);

	bar = new JMenuBar();

	menu = new JMenu("File");
	menu.setMnemonic('f');

	clear = new JMenuItem("Clear");
	clear.setMnemonic('c');
	clear.addActionListener(me);
	menu.add( clear );

	menu.addSeparator();

	exit = new JMenuItem("Exit");
	exit.setMnemonic('e');
	exit.addActionListener(me);
    menu.add( exit);

	bar.add(menu);

	add(bar, BorderLayout.NORTH);

	dc = new MouseDrawCircle();

	//create popup menu and add to DrawCircle canvas
	popup = new JPopupMenu();
	//add clear and exit to popup menu
	popupClear = new JMenuItem("Clear");
	popupClear .setMnemonic('c');
	popupClear .addActionListener(me);
	popup.add( popupClear );
	
	// notice!!!!! a menu item can only be add to one menu
	//popup.add(clear);
	//popup.add(exit);
	dc.add(popup);

	dc.addMouseListener(mh);
	add(dc, BorderLayout.CENTER);

  }

  //application entry
  public static void main( String s[]) {
    JFrame fr = new JFrame(" mouse click, draw circle.");
	fr.setSize(new Dimension(512, 512));
	
	//if there is WindowHandler.class in the same directory
	//you can reference it directly.
	WindowHandler l = new WindowHandler();
	fr.addWindowListener(l);

	MouseClick mc = new MouseClick();
	mc.init();
	fr.getContentPane().add(mc, BorderLayout.CENTER);

	fr.setVisible(true);
  }

  public void updateOnClick( double x, double y) {
	double rand = Math.random() * 100;
	Circle c1 = new Circle(x, y, rand);
    dc.addCircle(c1);
	dc.repaint();
  }

  public void clearCanvas() {
    dc.clear();
	dc.repaint();
  }

  public void showPopupMenu( Component c,  int x, int y) {
    popup.show( c, x, y); 
  }

}

class MouseHandler extends MouseAdapter{

  private MouseClick mc;

  public MouseHandler(MouseClick m){
    mc = m;
  }

  // implements MouseListener interface
  // notice: mouseClicked can't be a popup trigger.
  public void mousePressed( MouseEvent e) {
    if(e.isPopupTrigger() )
	  mc.showPopupMenu(e.getComponent(), e.getX(), e.getY());
	else
      mc.updateOnClick(e.getX(), e.getY() );
  }
  
}

class MenuHandler implements ActionListener {
  private MouseClick mc;

  public MenuHandler(MouseClick m) {
    mc = m;
  }

  public void actionPerformed(ActionEvent e){
    String menu = e.getActionCommand();
	if(menu.equals("Exit"))
	  System.exit(0);
	else 
	  mc.clearCanvas();
  }
}

class Circle {
  private double x;
  private double y;
  private double r;

  public Circle(double _x, double _y, double _r) {
    x = _x;
	y = _y;
	r = _r;
  }

  public double getX() { return x;}
  public double getY() { return y;}
  public double getR() { return r;}
}

class MouseDrawCircle extends JComponent {
  private Circle [] c;
  private int count;

  public MouseDrawCircle() {
    c = new Circle[10];
	count = 0;
  }

  public void paintComponent( Graphics g ) {
    Graphics2D g2 = (Graphics2D)g;

	//set background color
	Dimension size = getSize();
	g2.setColor(Color.white);
	g2.fill( new Rectangle2D.Double(0,0, size.width, size.height) );

	//draw circles
	g.setColor(Color.red);
	for(int i=0; i<count; i++){
	  Ellipse2D ell = new Ellipse2D.Double( c[i].getX() - c[i].getR(),
	                   c[i].getY() - c[i].getR(),
					   2*c[i].getR(), 2*c[i].getR());
	  g2.draw(ell);
	}
  }

  public void addCircle (Circle _c) {
    if(count < 10){
	  count++;
	  c[count-1] = _c;
	}
  }

  public void clear(){
    count = 0;
  }
}
