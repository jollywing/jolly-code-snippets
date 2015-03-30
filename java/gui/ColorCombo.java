/* Purpose:
 *  This program is a exercise for ComboBox.
 *  you can select a color from ComboBox, and this color will
 *  fill the whole window.
 * Record of Reversions:
 *   date     Programer      Description of Change 
 * ========   ==========    =================================
 *  20080403  jiqing         original version
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ColorCombo extends JPanel {

  private JComboBox cb;
  private ComboHandler ch;

  public void init() {
	//set layout manager
	//setLayout( new BorderLayout() );

    //create ComboBox
	String[] s = {"green", "red", "blue", "orange", "white"};
	cb = new JComboBox(s);
	//create ComboBox Listener
	ch = new ComboHandler(this);
	cb.addActionListener(ch);
	//add ComboBox
	add(cb);
  }

  public void updateColor() {
    String colorName = (String) cb.getSelectedItem();
	if (colorName.equals("green") )
	  setBackground( Color.green );
	else if (colorName.equals("blue"))
	  setBackground( Color.blue);
	else if (colorName.equals("red") )
	  setBackground( Color.red);
	else if (colorName.equals("orange") )
	  setBackground( Color.orange);
	else
	  setBackground( Color.white);
  }

  public static void main ( String s[] ) {
    //create a frame to hold the application
	JFrame fr = new JFrame("Color ComboBox");
	fr.setSize(256,256);

    //if there is WindowHandler.class in the same directory
    //you can reference it directly.
    WindowHandler l = new WindowHandler();
    fr.addWindowListener(l);

	//add application
	ColorCombo cc = new ColorCombo();
	cc.init();
	fr.getContentPane().add(cc, BorderLayout.CENTER);

	//show frame
	fr.setVisible(true);
  }
}
 
// this class defines comboBox's Action listener
class ComboHandler implements ActionListener {
  private ColorCombo cc;
  //constructor
  public ComboHandler( ColorCombo c) { cc=c; }

  //execute when an event occurs
  public void actionPerformed( ActionEvent e) {
    cc.updateColor();
  }
}
