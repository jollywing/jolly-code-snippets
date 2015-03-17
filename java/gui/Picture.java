/* Purpose
 *  This program show some pictures.
 *  compile: javac -encoding gbk Picture.java
 * Record of reversions
 *   date     programer    description
 * =========  =========   =====================
 * 20080409   jiqing      original version
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Picture extends JPanel implements ActionListener {
  
  private JPanel pTop;
  private JLabel lPic;
  private JRadioButton b1, b2, b3;
  private ButtonGroup bg;
  private ImageIcon geyou, xufan, jiqimao;

  public void init() {
    setLayout( new BorderLayout() );

    pTop = new JPanel();
	b1 = new JRadioButton("¸ðÓÅ", true);
	b1.addActionListener(this);
	pTop.add(b1);
	b2 = new JRadioButton("Ðì·«", false);
	b2.addActionListener(this);
	pTop.add(b2);
	b3 = new JRadioButton("»úÆ÷Ã¨", false);
	b3.addActionListener(this);
	pTop.add(b3);

	bg = new ButtonGroup();
	bg.add(b1);
	bg.add(b2);
	bg.add(b3);

	geyou = new ImageIcon("geyou.jpg");
	xufan = new ImageIcon("xufan.jpg");
	jiqimao = new ImageIcon("jiqimao.jpg");
	lPic = new JLabel(geyou);

	add(pTop, BorderLayout.NORTH);
	add(lPic, BorderLayout.CENTER);
  }

  public static void main(String s[]) {
    JFrame fr = new JFrame("show pictures");
	fr.setSize(new Dimension(256, 256) );

	WindowHandler l = new WindowHandler();
	fr.addWindowListener(l);

	Picture p =new Picture();
	p.init();
	fr.getContentPane().add(p, BorderLayout.CENTER);

	fr.setVisible(true);
  }

  public void actionPerformed( ActionEvent e) {
    if(b1.isSelected() )
	  lPic.setIcon(geyou);
	else if (b2.isSelected())
	  lPic.setIcon(xufan);
	else
	  lPic.setIcon(jiqimao);
  }

}
