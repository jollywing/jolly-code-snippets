/* Purpose
 *  This program list all Looks in system.
 * Record of reversions
 *    date      programer   description
 * ==========  ==========  =================================
 * 20080417     jiqing      create this file
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*; //due to ListSelectionListener


public class Looks extends JPanel implements ActionListener {

  private JLabel title; //all installed look and feels
  private JList  looks; //list all looks
  private JButton setLook; //set selected look
  private ListHandler lh;
  private UIManager.LookAndFeelInfo[] ls ;

  public void init(){
    setLayout( new BorderLayout());
	lh = new ListHandler(this);

	title = new JLabel("all installed look and feels");
	add(title, BorderLayout.NORTH);

    //structure UIManager.LookAndFeelInfo
    ls = UIManager.getInstalledLookAndFeels();
	String [] ss = new String[ls.length];
	for(int i=0; i<ls.length; i++){
	  ss[i] = ls[i].getName();
	}
	looks = new JList(ss );

	//looks.setPreferredSize( new Dimension(200,180));
	looks.addListSelectionListener(lh);
	add(looks, BorderLayout.CENTER);

	setLook = new JButton("set current look");
	setLook.addActionListener(this);
	add(setLook, BorderLayout.SOUTH);
  }
  
  public void updateLook(){
	try {
      UIManager.setLookAndFeel(
	          ls[ looks.getSelectedIndex()].getClassName()); 
	}
	catch( Exception e) {
	  JOptionPane.showMessageDialog(null, "set looks failed!", "Error",
	                                JOptionPane.ERROR_MESSAGE);
	}
  }

  public void actionPerformed( ActionEvent e) {
    JOptionPane.showMessageDialog(null, "This button is useless",
	                         "information", 
							 JOptionPane.INFORMATION_MESSAGE);
  }

  public static void main(String s[]){
    JFrame fr = new JFrame("Look and Feel Manager");
	fr.setSize( new Dimension(512,256) );

	WindowHandler l = new WindowHandler();
	fr.addWindowListener(l);

	Looks look = new Looks();
	look.init();
	fr.getContentPane().add(look, BorderLayout.CENTER);

	fr.setVisible(true);
  }
}

class ListHandler implements ListSelectionListener {
  private Looks l;

  public ListHandler(Looks _l){ l = _l;}

  public void valueChanged( ListSelectionEvent e) {
    l.updateLook();
  }

}
