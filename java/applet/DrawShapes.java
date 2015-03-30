/* Purpose
 *  This program can draw rectangle as you drag mouse.
 * Record of reversions
 *   date      author      description
 * =========   ========   ============================
 * 20080423    jiqing     original version: draw rect
 * 20080425    jiqing     extend: draw rect, roundrect, oval
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class DrawShapes extends JApplet 
                      implements MouseListener, MouseMotionListener {
  
  private Vector shapeList;

  // 用choice有问题
  //private Choice shapeChoice;
  //private Choice colorChoice;
  //private Choice fillChoice;
  private JComboBox shapeChoice;
  private JComboBox colorChoice;
  private JComboBox fillChoice;
  private JPanel pTop;

  private Point anchorPoint;
  private Shape s;

  private Dimension offScreenDimension;
  private Image offScreenImage;
  private Graphics offScreenGraphics;

  public void init() {
    
	setLayout( new BorderLayout() );

	pTop = new JPanel();
	getContentPane().add(pTop, BorderLayout.NORTH);

    shapeList = new Vector(10);
	anchorPoint = new Point(0,0);

	// 为choice添加项
	shapeChoice = new JComboBox();
	shapeChoice.addItem( "椭圆");
	shapeChoice.addItem( "矩形");
	shapeChoice.addItem( "圆角矩形");
	// 直接add有问题
	pTop.add(shapeChoice);

	colorChoice = new JComboBox();
	colorChoice.addItem("Red");
	colorChoice.addItem("Yellow");
	colorChoice.addItem("Blue");
	pTop.add(colorChoice);

	fillChoice = new JComboBox();
	fillChoice.addItem("Filled");
	fillChoice.addItem("Hollow");
	pTop.add( fillChoice);

	// 为applet添加鼠标响应事件
    addMouseListener(this);
	addMouseMotionListener(this);
  }
  
  // 鼠标按下的事件
  public void mousePressed(MouseEvent event) {
	
	// choice获得选中的项目。
	String shapeString = (String)shapeChoice.getSelectedItem();
	String colorString = (String)colorChoice.getSelectedItem();
	String fillString = (String)fillChoice.getSelectedItem();

	if(fillString.equals("Hollow") ) {
	  if(shapeString.equals("椭圆") )
	    s = new HollowOval();
	  else if (shapeString.equals("矩形") )
	    s = new HollowRectangle();
	  else
	    s = new HollowRoundRect();
	}
	else {
	  if(shapeString.equals("椭圆") )
	    s = new FilledOval();
	  else if (shapeString.equals("矩形") )
	    s = new FilledRectangle();
	  else
	    s = new FilledRoundRect();
	}

	if( colorString.equals("Red") ) 
	  s.color = Color.red;
	else if (colorString.equals("Yellow") )
	  s.color = Color.yellow;
	else
	  s.color = Color.blue;

	s.boundsBox = new DragRect();

	// vector添加元素
	shapeList.addElement(s);

	// 得到鼠标位置
    anchorPoint.x = event.getX();
	anchorPoint.y = event.getY();
  }

  public void mouseDragged(MouseEvent event) {
	
    // 赋值会得到引用
    DragRect dragRect = s.boundsBox;

    dragRect.setBounds( anchorPoint.x, anchorPoint.y,
	                    event.getX() - anchorPoint.x,
						event.getY() - anchorPoint.y);
	dragRect.normalize();
	repaint();
  }

  public void mouseMoved(MouseEvent event) {}
  public void mouseReleased(MouseEvent event) {}
  public void mouseEntered(MouseEvent event) {}
  public void mouseExited(MouseEvent event) {}
  public void mouseClicked(MouseEvent event) {}

  public void paint(Graphics g) {
	// clear screen
	Dimension d = getSize();

	// 用背景色清屏
	//g.clearRect(0, 0, size.width, size.height);
    //g.drawString("drag mouse to draw a rectangle", 30, 10);
	
	// 当离屏页面还没有创建，或者当前窗口尺寸改变了
	// 重新创建离屏页面。
	if ( (offScreenGraphics == null ) ||
	     ( d.width != offScreenDimension.width ) ||
		 ( d.height != offScreenDimension.height) ) {
	  offScreenDimension = d;
	  offScreenImage = createImage(d.width, d.height);
	  offScreenGraphics = offScreenImage.getGraphics();
	}

	// 清除上一帧图象
	// getBackground() 得到背景色
	offScreenGraphics.setColor( getBackground() );
	offScreenGraphics.fillRect( 0, 0, d.width, d.height);

	// 得到vector的大小
	int shapeCount = shapeList.size();
	for ( int i=0; i < shapeCount; i++ ) {
	  // 得到索引为i的元素
	  s = (Shape) shapeList.elementAt(i);
	  s.draw(offScreenGraphics);
	}

	// 画到前台
	g.drawImage( offScreenImage, 0, 0, this);
	pTop.repaint();
	fillChoice.repaint();
	colorChoice.repaint();
	shapeChoice.repaint();
	
	//g.drawRect(dragRect.x, dragRect.y, dragRect.width, 
	//           dragRect.height);
  }
}

class DragRect extends Rectangle{
  void normalize() {
    if(width < 0) {
	  x += width;
	  width = -width;
	}
	if(height<0 ) {
	  y += height;
	  height = -height;
	}
  }
}

// 抽象类
abstract class Shape{
  public Color color;
  public DragRect boundsBox;

  // 抽象方法
  public abstract void draw(Graphics g);

}

class HollowOval extends Shape {
  public void draw(Graphics g) {
    g.setColor(Color.black);
	g.drawOval(boundsBox.x, boundsBox.y, boundsBox.width,
	           boundsBox.height);
  }
}

class HollowRectangle extends Shape {
  public void draw ( Graphics g ) {
    g.setColor(Color.black);
	g.drawRect( boundsBox.x, boundsBox.y, boundsBox.width,
	            boundsBox.height );
  }
}

class HollowRoundRect extends Shape {
  public void draw ( Graphics g ) {
    g.setColor(Color.black);
	g.drawRoundRect( boundsBox.x, boundsBox.y, boundsBox.width,
	            boundsBox.height, 20, 20 );
  }
}

class FilledOval extends HollowOval {
  public void draw(Graphics g) {
    g.setColor(color);
	g.fillOval( boundsBox.x, boundsBox.y, boundsBox.width,
	            boundsBox.height);
	super.draw(g);
  }
}

class FilledRectangle extends HollowRectangle {
  public void draw(Graphics g) {
    g.setColor(color);
	g.fillRect( boundsBox.x, boundsBox.y, boundsBox.width,
	            boundsBox.height);
	super.draw(g);
  }
}

class FilledRoundRect extends HollowRoundRect {
  public void draw(Graphics g) {
    g.setColor(color);
	g.fillRoundRect( boundsBox.x, boundsBox.y, boundsBox.width,
	            boundsBox.height, 20, 20 );
	super.draw(g);
  }
}
