//一个java编译参数问题
//由于java编译生成的class文件以unicode编码的，
//如果系统默认编码是gbk，并且我们在java文件中使用了中文注释
//java编译时就会报“gbk编码的字符不可映射“的警告错误
//解决这个问题的方法是javac -encoding utf-8 xx.java

import java.awt.*;
import java.awt.event.*;
import javax.swing.*; //JPanel, JFrame, JButton等都是swing包中的类。

//JPanel是一个没有边框和标题栏的简单容器
public class GUI extends JPanel {

  private JLabel label;	//JLabel也可以显示图像
  private JButton pushButton;
  private int count = 0;

  public void init() {
    //BorderLayout是一个布局管理器，
    //将元素布局在一个中心区域和四个环绕边界上。
    //这是JFrame的默认布局管理器。
    //JPanel的默认布局管理器是FlowLayout，从左到右从上到下布局。
    //如果没有下面这条语句，虽然程序不会报错，
    //但JPanel无法使用BorderLayout布局
    setLayout( new BorderLayout() );

    label = new JLabel("push count: 0");
    add( label, BorderLayout.NORTH );
    label.setHorizontalAlignment( label.CENTER);

    pushButton = new JButton( "Test Button" );
    //ButtonHandler会在后面定义，java中使用定义好的类时，不需要提前声明
    pushButton.addActionListener( new ButtonHandler(this) );
    add( pushButton, BorderLayout.SOUTH );
  }

  public void updateLabel() {
    label.setText( "push count: " + (++count) );
  }

  public static void main( String s[]) {
    JFrame fr = new JFrame ("FirstGUI");
    fr.setSize(200,100);

    WindowHandler l = new WindowHandler();
    fr.addWindowListener(l);

    GUI gui = new GUI();
    gui.init();
    //getContentPane相当于得到窗口的客户区
    fr.getContentPane().add(gui, BorderLayout.CENTER);

    //显示frame
    fr.setVisible( true );
  }
}

//只有与文件同名的类才能声明为public
//未加修饰符的类应该默认为package类型，
//即同一个包中的类都可以访问它。
class ButtonHandler implements ActionListener {
  private GUI g;

  public ButtonHandler(GUI g1) {
    g = g1;
  }

  public void actionPerformed( ActionEvent e) {
    g.updateLabel();
  }
}

class WindowHandler extends WindowAdapter {
  public void windowClosing( WindowEvent e) {
    System.exit(0);
  }
}
