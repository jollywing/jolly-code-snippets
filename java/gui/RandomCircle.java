/* Purpose
 *  This program show a random circle, and caculate its radius, 
 *  diameter, area and perimeter.
 *  click the button, a new circle will be created.
 * Record of versions
 *   date      programer      description
 * ========   ============   ==========================
 * 20080404    jiqing         original code
 */
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;    //draw circle
import javax.swing.*;
import java.text.DecimalFormat; 	//to format temperature

//FlowLayout is JPanel's default layout
//from left to right, from top to bottom.
public class RandomCircle extends JPanel implements ActionListener {

  private DrawCircle dc;
  private JLabel lRadius, lDiameter, lArea, lPerimeter;
  private JTextField tRadius, tDiameter, tArea, tPerimeter;
  private JButton bGenerate;
  private double radius = 100.; // circle's radius

  public void init() {
    
	//create drawing area
	dc = new DrawCircle(radius);
	dc.setPreferredSize( new Dimension(512,400) );
    add( dc );

	lRadius = new JLabel("Radius:", JLabel.RIGHT);
	add(lRadius);
	tRadius = new JTextField("100", 14);
	tRadius.setEditable(false);
	add( tRadius );
	
	lDiameter= new JLabel("Diameter:", JLabel.RIGHT);
	add(lDiameter);
	tDiameter= new JTextField("200", 14);
	tDiameter.setEditable(false);
	add( tDiameter);

	lArea= new JLabel("Area:", JLabel.RIGHT);
	add(lArea);
	tArea= new JTextField("31415", 14);
	tArea.setEditable(false);
	add( tArea);

	lPerimeter= new JLabel("Perimeter:", JLabel.RIGHT);
	add(lPerimeter);
	tPerimeter= new JTextField("628", 14);
	tPerimeter.setEditable(false);
	add( tPerimeter);

	bGenerate = new JButton("Generate");
	bGenerate.addActionListener(this);
	bGenerate.setToolTipText("generate a random circle.");
	add(bGenerate);
  }

  public static void main(String s[]) {
    JFrame fr = new JFrame("Random circle");
	fr.setSize(512, 512);

	WindowHandler wh = new WindowHandler();
	fr.addWindowListener(wh);

	//add application
	RandomCircle rc = new RandomCircle();
	rc.init();
	fr.getContentPane().add(rc, BorderLayout.CENTER);

	fr.setVisible(true);
  }

  //update canvas
  public void updateCanvas() {
    //Math.random() return a random value between 0 and 1.
    double r = Math.random() * 200;
	dc.setRadius(r);
	dc.repaint();
	
	DecimalFormat df = new DecimalFormat("###.##");
	tRadius.setText( df.format( dc.getRadius()) );
	tDiameter.setText( df.format(dc.getDiameter()) );
	tArea.setText( df.format(dc.getArea()) );
	tPerimeter.setText( df.format( dc.getPerimeter()) );
  }

  //implements actionlistener
  public void actionPerformed(ActionEvent e) {
    String button = e.getActionCommand();
	if(button.equals("Generate") )
	  updateCanvas();
  }

}

// this class extends JComponent and draws a circle
class DrawCircle extends JComponent {
  private double radius;

  // constructor
  public DrawCircle( double r ){
    radius = r;
  }

  //repaint
  public void paintComponent( Graphics g) {
    Graphics2D g2 = (Graphics2D) g;

	//set randering hints to improve display quality
	g2.setRenderingHint( RenderingHints.KEY_ANTIALIASING,
	                     RenderingHints.VALUE_ANTIALIAS_ON );
	
	//draw circle
	// new Ellipse2D.Double( left, top, width, height)
	Ellipse2D circle = new Ellipse2D.Double(20., 30., 
	                  radius*2, radius*2 );
    g2.setColor( Color.green);
	g2.fill(circle);
	g2.setColor( Color.red);
	g2.draw(circle);
  }

  public void setRadius( double r) {
    radius = r;
  }

  public double getRadius() { return radius; }
  public double getDiameter() { return radius * 2; }
  public double getArea() { return Math.PI * radius * radius; }
  public double getPerimeter() { return Math.PI * radius *2; }

}
