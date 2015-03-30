/* Purpose
 *  这是一个计时程序。
 * Record of reversions
 *    date       programer       description
 * ===========  ===========    ==========================
 * 20080422      jiqing        original code
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ElapsedTimeApplet extends JApplet implements ActionListener {

  private JTextField textTime, textState;
  private JButton btStart, btTime, btStop;
  private Timer timer;

  public void init() {
    getContentPane().setLayout( new BorderLayout() );

	textTime = new JTextField("0.000 s");
	textTime.setEditable(false);
	getContentPane().add( textTime, BorderLayout.NORTH );

	btStart = new JButton("start");
	btStart.setHorizontalAlignment( JButton.CENTER );
	btStart.addActionListener(this);
	getContentPane().add( btStart, BorderLayout.WEST );

	btTime= new JButton("elapsed time");
	btTime.setHorizontalAlignment( JButton.CENTER );
	btTime.addActionListener(this);
	getContentPane().add( btTime, BorderLayout.CENTER);

	btStop = new JButton("stop");
	btStop.setHorizontalAlignment( JButton.CENTER );
	btStop.addActionListener(this);
	getContentPane().add( btStop, BorderLayout.EAST );

	textState = new JTextField("ready");
	textState.setEditable(false);
	getContentPane().add( textState, BorderLayout.SOUTH );

	timer = new Timer();

  }

  public void actionPerformed( ActionEvent e) {
    String buttonName = e.getActionCommand();

	if (buttonName.equals("start")) {
	  timer.startTimer();
	  textTime.setText(timer.elapsedTime() +" s");
	  textState.setText("running ...");
	}
	else if( buttonName.equals("elapsed time") ) {
	  textTime.setText(timer.elapsedTime() +" s");
	}
	else {
	  timer.stopTimer();
	  textTime.setText(timer.elapsedTime() +" s");
	  textState.setText("stopped");
	}
  }
}

class Timer {
  private double time;
  private double eTime;
  private boolean running;

  public Timer() {
    //以毫秒为单位返回系统时间
    time = System.currentTimeMillis();
	running = false;
  }

  public void startTimer() {
    time = System.currentTimeMillis();
	eTime = 0;
	running = true;
  }

  //以秒为单位返回流逝的时间
  public double elapsedTime(){
    if(running == true){
      eTime = (System.currentTimeMillis() - time) / 1000;
	}
	return eTime;
  }

  public void stopTimer() {
    eTime = (System.currentTimeMillis() - time) / 1000;
    running = false;
  }
}
