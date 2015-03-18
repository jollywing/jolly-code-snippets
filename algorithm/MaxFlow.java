/* Purpose
 *  ����������������·���㷨(ShortestAugmentingPath)����������⡣
 * Record of reversions
 *   date      programmer      description
 * ========== ============    ========================
 * 20080713    jiqing          create
 */

import java.io.*;

public class MaxFlow{

  // java�еĶ�ά���飬ÿһ�п����в�ͬ��Ԫ�ظ���
  private double network[][];
  private int vertexNumber;

  public void readNetwork(String fileName)
    throws FileNotFoundException, IOException {

	String strLine;
    // open file
    BufferedReader in = new BufferedReader(
	                      new FileReader( fileName ) );
	// ignore empty line and comments
	strLine = in.readLine();
    //����ʹ��strLine[0]����Ϊ�ַ��������ַ�����
	while( strLine.charAt(0) == '\n' || strLine.charAt(0) == '#' 
	      || strLine.charAt(0) == ' ') 
	  strLine = in.readLine();
	// read number of vertexes
	vertexNumber = Integer.parseInt(strLine);
	// new network matrix
	network = new double[vertexNumber][];
	for(int i=0; i < vertexNumber; ++i)
	  network[i] = new double[vertexNumber];
	// read weights
	for(int i=0; i < vertexNumber; ++i){
	  strLine = in.readLine();
	  String [] weights = strLine.split("\t");
	  for(int j=0; j< vertexNumber; ++j)
	    network[i][j] = Double.parseDouble(weights[j]);
	}
    return;
  }
  public void printNetwork(){
	System.out.println("G has "+ vertexNumber + " vertexes.");
	for(int i=0; i< vertexNumber; ++i){
	  for(int j=0; j< vertexNumber; ++j){
	    System.out.print(""+ network[i][j]);
		if(j < vertexNumber -1) System.out.print("\t");
	  }
	  System.out.print("\n");
	}
    return;
  }

  public double ShortestAugmentingPath(){
    return 0;
  }

  public static void main(String [] args)
    throws FileNotFoundException, IOException {
    String netFile;
	double maxFlow;
    // check parameters
	// get file name
	// create MaxFlow object
	MaxFlow m = new MaxFlow();
    // read data of network
	m.readNetwork("graph");
	
    // caculate the max flow
	maxFlow = m.ShortestAugmentingPath();

    // output 
	System.out.println("your inputed graph:");
	m.printNetwork();
	System.out.println("The max flow is " + maxFlow +".");
  }
}
