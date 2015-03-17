/* Purpose
 *  This program plot curve correspond to y = ax^2 + bx + c
 * Record of reversions
 *   date      programer     description of change
 * ========   ==========    =======================
 * 20080405    jiqing        original version
 * 20080406    jiqing        add code to draw Frame
 * 20080407    jiqing        add code to draw function
 */

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class PlotFunc extends JPanel {
  private DrawFunc df;
  private JLabel lA, lB, lC, lMinX, lMaxX;
  private JTextField tA, tB, tC, tMinX, tMaxX;
  private TextHandler h;

  public void init() {
    //add DrawFunc
	df = new DrawFunc(0., 100., 1., 1., 1.);
	df.setPreferredSize(new Dimension(500, 400) );
	add(df);

	h = new TextHandler( this );

	//add label for a
	lA = new JLabel("a:", JLabel.RIGHT);
	add(lA);
	//add Textfield for a
	tA = new JTextField("1", 10);
	tA.addActionListener(h);
	add(tA);
	//add label for b
	lB = new JLabel("b:", JLabel.RIGHT);
	add(lB);
	//add textfield for b
	tB = new JTextField("1", 10);
	tB.addActionListener(h);
	add(tB);
	//add label for c
	lC = new JLabel("c:", JLabel.RIGHT);
	add(lC);
	//add textfield for c
	tC = new JTextField("1", 10);
	tC.addActionListener(h);
	add(tC);
	//add label for min x
	lMinX = new JLabel("min x:", JLabel.RIGHT);
	add(lMinX);
	//add textfield for min x
	tMinX = new JTextField("0", 10);
	tMinX.addActionListener(h);
	add(tMinX);
	//add label for max x
	lMaxX = new JLabel("max x:", JLabel.RIGHT);
	add(lMaxX);
	//add textfield for max x
	tMaxX = new JTextField("100", 10);
	tMaxX.addActionListener(h);
	add(tMaxX);
  }

  public void updateFuncPlot() {
    double a = Double.parseDouble( tA.getText());
	double b = Double.parseDouble( tB.getText());
	double c = Double.parseDouble( tC.getText());
	double minX = Double.parseDouble( tMinX.getText());
	double maxX = Double.parseDouble( tMaxX.getText());
	df.change(minX, maxX, a, b, c);
	df.repaint();
  }

  public static void main( String s[] ) {
    JFrame fr = new JFrame("Plot Function");
	fr.setSize(512, 512);

    //if there is WindowHandler.class in the same directory
    //you can reference it directly.
    WindowHandler l = new WindowHandler();
    fr.addWindowListener(l);

	//add application
	PlotFunc pf = new PlotFunc();
	pf.init();
	fr.getContentPane().add(pf, BorderLayout.CENTER);

	fr.setVisible(true);
  }
}

class DrawFunc extends JComponent {
  private double[] x;
  private double[] y;
  private double minX, maxX;
  private double minY, maxY;
  private double a, b, c;
  private String title;
  //private String xLabel = "x轴";
  //private String yLabel = "y轴";
  private final int segmentNum = 32;

  //constructor
  public DrawFunc(double minx, double maxx, 
                  double _a, double _b, double _c) {
    change(minx, maxx, _a, _b, _c);
  }

  // change param
  public void change(double minx, double maxx, 
                double _a, double _b, double _c) {
    minX = minx;
	maxX = maxx;
	a = _a;
	b = _b;
	c = _c;
  }

  public void paintComponent( Graphics g) {
	// basic stroke can control line style
	BasicStroke bs;
	Line2D line;

	double x1, x2;  //starting and ending x-value of segment
	double y1, y2;  //starting and ending y-value of segment

	final double xLeftMargin = 0.125;
	final double xRightMargin = 0.045;
	final double yTopMargin = 0.075;
	final double yBottomMargin = 0.075;

	double normalWidth, normalHeight;
	double normalStartX, normalStartY;
	double normalEndX, normalEndY;

	//calculate frame
	normalWidth = 1.0 - xLeftMargin - xRightMargin;
	normalHeight = 1.0 -yTopMargin - yBottomMargin;
	normalStartX = xLeftMargin;
	normalStartY = yTopMargin;
	normalEndX = normalStartX + normalWidth;
	normalEndY = normalStartY + normalHeight;
	
	//int plotWidth, plotHeight, plotStartX, plotStartY;
	
    //create data to display
	x = new double[segmentNum + 1];
	y = new double[segmentNum + 1];

	double segment = (maxX - minX)/segmentNum;
	minY = maxY = 0.0;
	for(int i=0; i <= segmentNum; i++ ) {
	  x[i] = minX + segment * i;
	  y[i] = a * x[i] * x[i] + b* x[i] + c;
	  if ( y[i] > maxY)
	    maxY = y[i];
      if (y[i] < minY )
	    minY = y[i];
	}

	double xScale = normalWidth /(maxX - minX);
	double yScale = normalHeight /(maxY - minY);
	

    //fill background
	Graphics2D g2 = (Graphics2D) g;
	Dimension size = getSize();
	g2.setColor(Color.yellow);
	g2.fill(new Rectangle2D.Double(0,0, size.width, size.height) );

	//draw frame

	// if object is double, Math.round return long.
	// so convert them to integers.
	//plotWidth = (int)Math.round(size.width * normalWidth);
	//plotHeight = (int)Math.round(size.height * normalHeight);
	//plotStartX = (int)Math.round(size.width * normalStartX);
	//plotStartY = (int)Math.round(size.height * normalStartY);
	
	g2.setColor(Color.black);
	float[] solid = {12.0f, 0.0f};	//solid line style
	bs = new BasicStroke( 1.0f, BasicStroke.CAP_SQUARE,
	                      BasicStroke.JOIN_MITER,
						  6.0f, solid, 0.0f);
	g2.setStroke(bs);

	line = new Line2D.Double( size.width * normalStartX,
	                          size.height * normalStartY,
							  size.width * normalEndX,
							  size.height * normalStartY);
	g2.draw(line);
	line = new Line2D.Double( size.width * normalEndX,
	                          size.height * normalStartY,
							  size.width * normalEndX,
							  size.height * normalEndY);
	g2.draw(line);
	line = new Line2D.Double( size.width * normalEndX,
	                          size.height * normalEndY,
							  size.width * normalStartX,
							  size.height * normalEndY);
	g2.draw(line);
	line = new Line2D.Double( size.width * normalStartX,
	                          size.height * normalEndY,
							  size.width * normalStartX,
							  size.height * normalStartY);
	g2.draw(line);

	/* -----------------------------
	 * draw function
	 * ----------------------------*/
		//set color
	g2.setColor( Color.red);

	//set line style
	bs = new BasicStroke(4.0f, BasicStroke.CAP_SQUARE, 
	                     BasicStroke.JOIN_MITER, 1.0f, solid, 0.0f);
	g2.setStroke(bs);

	// draw line
	// i is only valid in for loop
	for(int i=0; i < segmentNum; i++ ) {
	  x1 = (x[i] - minX) * xScale + normalStartX;
	  x2 = (x[i+1] - minX) * xScale + normalStartX;
	  y1 = normalStartY + (maxY- y[i]) * yScale;
	  y2 = normalStartY + (maxY - y[i+1]) * yScale;
	  line = new Line2D.Double ( size.width * x1,
	                             size.height * y1,
								 size.width * x2,
								 size.height * y2);
	  g2.draw(line);
	}

	//draw title
	title = a + "x^2 + " + b + "x + " + c;
	g2.setColor(Color.blue);
	Font font = new Font("Helvetica", Font.BOLD, 14);
	g2.setFont(font);
	FontMetrics fm = g2.getFontMetrics();
	/*double normalStringWidth = (double) fm.stringWidth(title)
	                           /size.width;
	double normalStringHeight = (double) fm.getHeight()
	                           /size.width;
	*/
	double normalStringX = normalStartX; 
	double normalStringY = normalStartY/2;
	g2.drawString( title,
	               (int) Math.round(size.width * normalStringX ),
				   (int) Math.round(size.height * normalStringY) );

  }
}

class TextHandler implements ActionListener {
  private PlotFunc pf;
  public TextHandler( PlotFunc p) {
    pf = p;
  }
  public void actionPerformed( ActionEvent e) {
    pf.updateFuncPlot();
  }
}

