/*
 * purpose:
 *   This GUI-based program converts temperature in
 *   degree Fahrenheit to degree Celsius, and vice versa.
 * Record of revisions:
 *   Date       Programer      Description of change
 *  =======    ============   ======================
 *  20080402    jiqing         original code
 *  20080421    jiqing         改写成小应用程序(applet)
 *  20080422    jiqing         通过html文件传递参数
 * Notes
 *  1 applet不允许访问宿主计算机的资源，不允许读写磁盘文件。
 *  2 applet是那些扩展了javax.swing.JApplet类的类。
 *  3 applet程序有五个关键的方法: init, start, stop, destroy
 *    和paintComponent。简单的applet仅须重写init和
 *    paintComponent方法。
 *  4 JApplet继承自JPanel，因此默认的布局是FlowLayout。
 *  5 applet程序与java应用程序的不同之处在于，使用JApplet替代了
 *    JPanel，使用Html文件代替了JFrame。
 *  6 可以通过html向applet程序传递参数，在<applet>和</applet>间，
 *    <param name="xxx" value="yyy">。 applet程序中通过
 *    String getParameter(paramName)获取参数值。
 *  7 在程序中加入传递参数的代码后，就不能再作为java应用程序执行了。
 */

import java.awt.*;					//abstract window toolkit
import java.awt.event.*;			//window listener
import javax.swing.*;				//JPanel, JFrame, etc.
import java.awt.geom.*;				//drawing
import java.text.DecimalFormat; 	//to format temperature

//一个既可以作为applet又可以作为应用程序的程序，要继承JApplet类
public class TempConversion extends JApplet {

	private JPanel pLeft;
	private TempIndicator ti;
	private JLabel l1, l2;
	private JTextField t1, t2;
	private DegCHandler cHnd;	//degC textField's listener
	private DegFHandler fHnd;
	private int precision =  1;   //用于控制小数点后的位数

	// init方法，将由浏览器调用
    public void init() {

	  //从html文件中获取参数
	  //precision = Integer.parseInt( getParameter("precision") );

	  getContentPane().setLayout( new BorderLayout() );

      cHnd = new DegCHandler(this);
	  fHnd = new DegFHandler(this);

	  //labels and texts
	  // JLabel( String s, int HerizonAlignment)
	  l1 = new JLabel("摄氏温度：", JLabel.LEFT);
	  l2 = new JLabel("华氏温度：", JLabel.LEFT);
	  // JTextField( String s, int cols)
	  t1 = new JTextField("0.0", 8);
	  t1.addActionListener( cHnd);
	  t2 = new JTextField("32.0", 8);
	  t2.addActionListener( fHnd);

      // left panel
	  pLeft = new JPanel();
	  pLeft.setLayout( new BoxLayout( pLeft, BoxLayout.Y_AXIS) );
	  pLeft.add(l1);
	  pLeft.add(t1);
	  //create rigid distance between two components
	  //Dimension defines horizon distance and vertical distance.
	  pLeft.add( Box.createRigidArea( new Dimension(0,30)) );
	  pLeft.add(l2);
	  pLeft.add(t2);
	  // create a virtual component,
	  // it will occupy all remained vertical space
	  pLeft.add( Box.createVerticalGlue() );
	  getContentPane().add ( pLeft, BorderLayout.WEST );

	  ti = new TempIndicator(10, 20, 15, 200, 0);
	  // you must set this area
	  ti.setPreferredSize( new Dimension(96, 256) );
	  getContentPane().add ( ti, BorderLayout.EAST );
	}

	//update temperature
	public void updateTemperature( float t) {
	  ti.setTemperature(t);
	  ti.repaint();
	}

	//convert deg F to deg C
	public void toC( float degF) {
	  DecimalFormat df;
	  if(precision == 2)
	    df = new DecimalFormat("###.00");
      else
	    df = new DecimalFormat("###.0");

	  //float constant follows by 'f', double constant needn't
	  float degC = (5.f /9.f ) * (degF-32);
	  t1.setText( df.format(degC) );
	  t2.setText( df.format(degF) );
	  updateTemperature( degC );
	}

	//convert deg C to deg F
	public void toF(float degC) {
	  DecimalFormat df;
	  if(precision == 2)
	    df = new DecimalFormat("###.00");
      else
	    df = new DecimalFormat("###.0");

	  float degF = (9.f / 5.f) * degC + 32;
	  t1.setText( df.format(degC) );
	  t2.setText( df.format(degF) );
	  updateTemperature( degC );
	}

	public static void main(String s[]) {
		//create a frame to hold application
		JFrame fr = new JFrame("Temperature Convertor");
		fr.setSize(256, 256);

		//if there is WindowHandler.class in the same directory
		//you can reference it directly.
		//WindowHandler l = new WindowHandler();
		//fr.addWindowListener(l);

		//add application
		TempConversion tc = new TempConversion();
		tc.init();
		tc.start(); //继承自JApplet的方法。

		//使用适合applet的窗口事件处理器
		AppletWindowHandler l = new AppletWindowHandler(tc);
		fr.addWindowListener(l);

		fr.getContentPane().add(tc, BorderLayout.CENTER);

		fr.setVisible(true);
	}
}

// degC listener
class DegCHandler implements ActionListener {
	private TempConversion tc;

	//constructor
	public DegCHandler( TempConversion t) { tc=t;}

	//execute when an event occurs
	public void actionPerformed( ActionEvent e) {
	  String input = e.getActionCommand();
	  Float degC = Float.parseFloat(input);
	  tc.toF(degC);
	}
}

// degF listener
class DegFHandler implements ActionListener {
	private TempConversion tc;

	//constructor
	public DegFHandler( TempConversion t) { tc=t;}

	//execute when an event occurs
	public void actionPerformed( ActionEvent e) {
	  String input = e.getActionCommand();
	  Float degF = Float.parseFloat(input);
	  tc.toC(degF);
	}
}

// this class draw temperature indicator
class TempIndicator extends JComponent {
	private float temperature;
	private float left;
	private float top;
	private float height;
	private float width;

	//constructor
	public TempIndicator( float _left, float _top, 
	                      float w, float h, float t ) {
	  this.left = _left;
	  this.top = _top;
	  this.height = h;
	  this.width = w;
	  this.temperature = t;
	}

	public void paintComponent(Graphics g) {
	  // cast the graphics object to Graph2D
	  Graphics2D g2 = (Graphics2D) g;
	  //set background color
	  Dimension size = getSize();
	  g2.setColor( Color.white);
	  g2.fill( new Rectangle2D.Double( 0, 0, size.width, size.height) );

	  //draw temperature indicator shape -- a rectangle
	  RoundRectangle2D rect = new RoundRectangle2D.Float( left, 
	                                top, width, height, 10, 10);
	  g2.setColor( Color.black );
	  g2.draw(rect);

	  //draw temperature column
	  RoundRectangle2D rectT = new RoundRectangle2D.Float(left, 
	                      top + height *(100-temperature)/100, width,
						  height * temperature/100, 10, 10);
	  g2.setColor( Color.red);
	  g2.fill(rectT);
	}

	public void setTemperature( float t) {
	  temperature = t;
	}
}

//**********************************************
// 适合applet的窗口事件处理器
//**********************************************
class AppletWindowHandler extends WindowHandler {
  JApplet ap;

  public AppletWindowHandler (JApplet a) {ap =a;}

  public void windowClosing(WindowEvent e) {
    ap.stop();
	ap.destroy();
	System.exit(0);
  }
}
