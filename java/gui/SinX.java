/* Purpose
 *  This program draw sin function:
 *  y(t) = Acos(2*PI*ft + p )
 * Record of reversions
 *   date    programer     description
 * ========  ==========   ========================
 * 20080408  jiqing       original version
 * 20080411  jiqing       add menu
 * 20080413  jiqing       show dialog, read and save
 */
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import java.io.*;	//due to PrintWriter
//import chapman.graphics.JPlot2D; //to draw sin or cos curve

public class SinX extends JPanel implements ActionListener {
  //declare variables
  private Curve a, b, c;
  private Curve currentCurve;
  private double tMin, tMax;
  private JPanel pVert, pHoriz;
  private JLabel lSwing, lFreq, lPhasic, lMinT, lMaxT;
  private JTextField tSwing, tFreq, tPhasic, tMinT, tMaxT;
  private JComboBox funcSelector;
  private PlotSinx plot;
  private JMenuBar menuBar;
  private JMenu fileMenu;
  private JMenuItem load, save, exit;
  private MenuHandler mh;

  //init
  public void init() {

    a = new Curve(100.0, 2.0, 10.);
	b = new Curve(1.0, 1.0, 0.);
	c = new Curve(10.0, 10., 100.);
	currentCurve = a;

	tMin = 0.0;
	tMax = 10 * Math.PI;

	pVert = new JPanel();
	pVert.setLayout(new BoxLayout( pVert, BoxLayout.Y_AXIS) );
	add(pVert);
	
	//add menu
	mh = new MenuHandler(this);
	menuBar = new JMenuBar();
	fileMenu = new JMenu("File");
	load = new JMenuItem("Load");
	load.addActionListener(mh);
	fileMenu.add(load);
	save = new JMenuItem("Save");
	save.addActionListener(mh);
	fileMenu.add(save);
	exit = new JMenuItem("Exit");
	exit.addActionListener(mh);
	fileMenu.add(exit);
	menuBar.add(fileMenu);
	pVert.add(menuBar);

	plot = new PlotSinx(currentCurve.getSwing(), 
	                    currentCurve.getFreq(), 
						currentCurve.getPhasic(),
	                    tMin, tMax);
	plot.setPreferredSize(new Dimension(500, 400) );
	pVert.add(plot);
	
	pHoriz = new JPanel();
	pHoriz.setLayout(new BoxLayout(pHoriz, BoxLayout.X_AXIS) );
	pVert.add(pHoriz);

	lSwing = new JLabel("swing");
	pHoriz.add(lSwing);
	tSwing = new JTextField(3);
	tSwing.setEditable(false);
	pHoriz.add(tSwing);

	lFreq = new JLabel("freq");
	pHoriz.add(lFreq);
	tFreq= new JTextField(3);
	tFreq.setEditable(false);
	pHoriz.add(tFreq);

	lPhasic= new JLabel("phasic");
	pHoriz.add(lPhasic);
	tPhasic = new JTextField(3);
	tPhasic.setEditable(false);
	pHoriz.add(tPhasic);

	funcSelector = new JComboBox();
	funcSelector.addItem("A");
	funcSelector.addItem("B");
	funcSelector.addItem("C");
	funcSelector.addActionListener(this);
	pHoriz.add(funcSelector);
  }

  //save mode
  public void save(String fileName) throws IOException {
    PrintWriter out = new PrintWriter(
	                       new BufferedWriter(
						    new FileWriter(fileName) ) );
	out.println( currentCurve.getSwing() );
	out.println( currentCurve.getFreq() );
	out.println( currentCurve.getPhasic() );
	out.close();
	
  }

  //load mode
  public void load(String fileName) 
    throws FileNotFoundException, IOException {
	String strSwing, strFreq, strPhasic;
    BufferedReader in = new BufferedReader(
	                      new FileReader( fileName ) );
	strSwing = in.readLine();
	strFreq = in.readLine();
	strPhasic= in.readLine();

	plot.set( Double.parseDouble(strSwing),
	          Double.parseDouble(strFreq),
			  Double.parseDouble(strPhasic),
			  tMin, tMax);
	plot.repaint();

  }

  public static void main(String s[]) {
    JFrame fr = new JFrame("y(t) = Acos(2*PI* ft + p)");
	fr.setSize( new Dimension(512, 512) );

	//if there is WindowHandler.class in the same directory
	//you can reference it directly.
	WindowHandler l = new WindowHandler();
	fr.addWindowListener(l);

	//add application
	SinX sinx = new SinX();
	sinx.init();
	fr.getContentPane().add(sinx, BorderLayout.CENTER);

	fr.setVisible(true);
	
  }

  public void actionPerformed( ActionEvent e) {
    String curveName = (String)funcSelector.getSelectedItem();
	if( curveName.equals("A"))
	  currentCurve = a;
	else if( curveName.equals("B"))
	  currentCurve = b;
	else 
	  currentCurve = c;

	tSwing.setText("" + currentCurve.getSwing() );
	tFreq.setText("" + currentCurve.getFreq() );
	tPhasic.setText("" + currentCurve.getPhasic());
	plot.set(currentCurve.getSwing(), 
	         currentCurve.getFreq(), 
			 currentCurve.getPhasic(),
	         tMin, tMax);
	plot.repaint();
  }
}

class MenuHandler implements ActionListener {
  private SinX s;

  //constructor
  public MenuHandler(SinX _s) { s = _s; }

  public void actionPerformed(ActionEvent e) {
    String menu = e.getActionCommand();
	String fileName;
	if(menu.equals("Load") ){
	  fileName = JOptionPane.showInputDialog(null,
	                       "specify the input file...");
	  if(fileName != null){
	    try { s.load(fileName);}
		catch (FileNotFoundException ex) {
		  JOptionPane.showMessageDialog(null, "file not found!",
		            "error", JOptionPane.ERROR_MESSAGE);
		}
		catch( IOException ex) {
		  JOptionPane.showMessageDialog(null, "file read failed!",
		           "error", JOptionPane.ERROR_MESSAGE);
		}
	  }
	}
	else if (menu.equals("Save") ){
	  fileName = JOptionPane.showInputDialog(null,
	                       "save as...");
	  if(fileName != null){
		try{ s.save(fileName);}
		catch (IOException ex) {
		  JOptionPane.showMessageDialog( null,
		            "write file failed!", "error",
					JOptionPane.ERROR_MESSAGE);
	    }
      }
	}
	else
	  System.exit(0);
  }
}

class Curve {
  private double A; //swing
  private double f; //frequency;
  private double p; //phasic

  public Curve( double a, double _f, double _p) {
    A = a;
	f = _f;
	p = _p;
  }

  public void setSwing(double a) { A = a; }
  public void setFreq(double _f) { f = _f; }
  public void setPhasic(double _p) {p = _p; }
  public double getSwing() { return A; }
  public double getFreq() { return f;}
  public double getPhasic() { return p;}
}

class PlotSinx extends JComponent {
  private double A, f, p, tMin, tMax;
  private double [] x;
  private double [] y;
  private final int segmentNum = 64;

  //constructor
  public PlotSinx( double a, double _f, double _p, 
                   double tmin, double tmax) {
    set(a, _f, _p, tmin, tmax);
	x = new double[segmentNum + 1];
	y = new double[segmentNum + 1];
  }

  public void set( double a, double _f, double _p,
                   double tmin, double tmax) {
    A = a;
	f = _f;
	p = _p;
	tMin = tmin;
	tMax = tmax;
  }

  public void paintComponent( Graphics g) {
	//fill background
	Dimension size = getSize();
    Graphics2D g2 = (Graphics2D) g;
	g2.setColor(Color.black);
	g2.fill(new Rectangle2D.Double(0,0, size.width, size.height) );

	double segment = (tMax - tMin)/segmentNum;
	double yMin = 0, yMax = 0;
	for(int i=0; i<= segmentNum; ++i ) {
	  x[i] = tMin + segment * i;
	  y[i] = A * Math.cos( 2 *Math.PI * f * x[i] + p );
	  if( y[i] < yMin)	yMin = y[i];
	  if(y[i] > yMax) yMax = y[i];
	}

	double xScale = size.width/ (tMax-tMin);
	double yScale = size.height / (yMax-yMin);

	//draw line
	double x1, x2, y1, y2;
	g2.setColor(Color.green);
	Line2D line;
	for(int i=0; i < segmentNum; ++i ) {
	  x1 = (x[i]-tMin) * xScale;
	  y1 = (yMax-y[i]) * yScale;
	  x2 = (x[i+1]-tMin) * xScale;
	  y2 = (yMax-y[i+1]) * yScale;
	  line = new Line2D.Double( x1,y1, x2, y2);
	  g2.draw(line);
	}

  }
}
