/* Purpose
 *  这个程序解决了二分图匹配问题。
 *  由于源程序中使用了gbk编码的中文字符，
 *  编译时请使用：javac -encoding gbk BiMatch.java
 * Record of reversions
 *   date       programmer      description
 * =========   ==========   ========================
 *  20080714    jiqing       create this document
 *  20080719    jiqing       O(n^3)的算法
 */

import java.io.*;
import java.util.Vector;

public class BiMatch{
  private int biGraph[][];
  private int vertexNumber;
  private Node [] nodes;
  private Vector<Match> matches;
  private Vector<Node> queue;
  private Vector nodesInV;

  public void readBiGraph(String fileName)
    throws FileNotFoundException, IOException {
  	String strLine;
    // open file
    BufferedReader in = new BufferedReader(
	                      new FileReader( fileName ) );
	// ignore empty line and comments
	strLine = in.readLine();
    //不能使用strLine[0]，因为字符串不是字符数组
	while( strLine.charAt(0) == '\n' || strLine.charAt(0) == '#' 
	      || strLine.charAt(0) == ' ') 
	  strLine = in.readLine();
	// read number of vertexes
	vertexNumber = Integer.parseInt(strLine);
	// read nodes in V
	nodesInV = new Vector(10);
	nodesInV.clear();
	strLine = in.readLine();
	String vNodes[] = strLine.split("\t");
	for(int i=0; i < vNodes.length; ++i)
	  nodesInV.addElement(Integer.parseInt(vNodes[i]) );

	// new biGraph matrix
	biGraph = new int[vertexNumber][];
	for(int i=0; i < vertexNumber; ++i)
	  biGraph[i] = new int[vertexNumber];
	// read weights
	for(int i=0; i < vertexNumber; ++i){
	  strLine = in.readLine();
	  String [] weights = strLine.split("\t");
	  for(int j=0; j< vertexNumber; ++j)
	    biGraph[i][j] = Integer.parseInt(weights[j]);
	}

	// init nodes
	initNodes();

    return;
  }

  public void printBiGraph(){
    System.out.println("This bipartite graph has "+ 
	  vertexNumber + " vertexes.");
	// output vertex in V
	for( int i=0; i < nodesInV.size(); ++i) {
	  System.out.print(nodesInV.elementAt(i) );
	  if (i < nodesInV.size() -1) System.out.print("\t");
	}
	System.out.print("\n");
	
	// for each vertex
	for(int i=0; i< vertexNumber; ++i){
	  // print connectivity with other vertexes
	  for(int j=0; j < vertexNumber; ++j){
	    System.out.print(biGraph[i][j]);
		if(j < vertexNumber -1)
		  System.out.print("\t");
	  }
	  System.out.print("\n");
	}
	return;
  }

  private void initNodes(){
    nodes = new Node[vertexNumber];
	for(int i=0; i< vertexNumber; ++i){
	  nodes[i] = new Node();
	  nodes[i].vertex = i;
	  if(nodesInV.indexOf(i) != -1)
	    nodes[i].isInV = true;
	}
  }

  // 用V中的自由结点重新初始化队列
  private void initQueueFromV(){
    // clear queue
	queue.clear();
	// for each node in V
	for(int i=0; i< nodesInV.size(); ++i){
	  // if this node is not matched
	  if( nodes[ (Integer)nodesInV.get(i) ].matched == false ) 
	    // push it into queue
		queue.addElement(nodes[ (Integer)nodesInV.get(i) ]);
	}
  }

  // 给定一个结点，查询它的对偶是谁
  private int whoMatch( int v ){
    for(int i=0; i< matches.size(); ++i){
	  if( matches.get(i).first == v )  return matches.get(i).second;
	  if( matches.get(i).second == v)  return matches.get(i).first;
	}
	return -1;
  }

  // 检查两个结点的连边是否在M中
  private int inMatch( int vertex1, int vertex2) {
	for( int i=0; i< matches.size(); i++){
	  if( (matches.get(i).first == vertex1 && 
	       matches.get(i).second == vertex2)
	    ||(matches.get(i).first == vertex2 && 
		   matches.get(i).second == vertex1) 
		)
	    return i;
	}

	return -1;
  }

  // 增加match
  private void addMatch( int vertex1, int vertex2 ){
    // if this match exists in match array, return
	if ( inMatch(vertex1, vertex2) != -1)
	  return;
	// set two vertexes matched
	nodes[vertex1].matched = true;
	nodes[vertex2].matched = true;
	// add this match into match array
	Match m = new Match(vertex1, vertex2);
	matches.addElement(m);
	return;
  }

  // 移除match
  private void removeMatch( int vertex1, int vertex2) {
    // find the match
    int index = inMatch(vertex1, vertex2);

	if (index != -1){
	  // remove the match
	  matches.remove(index);
	  // set two vertexes unmatched
	  nodes[vertex1].matched = false;
	  nodes[vertex2].matched = false;
	}
  }

  public void printMatches(){
    System.out.println("The max match is found:");

    for(int i=0; i< matches.size(); ++i)
	  System.out.println( "( "+ matches.get(i).first + ", "
	    + matches.get(i).second + " )" );
	
	System.out.println("");
	return;
  }

  // 时间复杂度为n^3的宽度优先搜索算法
  public void n3BfsMatch(){
    //init matches
	matches = new Vector(10);
	matches.clear();
	//init queue
	queue = new Vector(10);
	queue.clear();
	initQueueFromV();

	//while queue is not empty
	while( queue.isEmpty() == false ){
      // popup the first element w
	  Node w = queue.remove(0);
	  // if w in V
	  if (w.isInV == true){
	    // for each vertex u connected to w
		for( int i=0; i< vertexNumber; ++i){
		  if( biGraph[w.vertex][i] == 1 ){
		    // if u is free
			if(nodes[i].matched == false){
		      // add (w,u) into matches
			  addMatch(w.vertex, i);
			  // get new matches from augmenting path
			  Node v= w;
			  Node u;
			  while(v.label != -1){
			    u = nodes[v.label];
				removeMatch(v.vertex, u.vertex);
				v = nodes[u.label];
				addMatch(u.vertex, v.vertex);
			  }
			  //clear labels of all nodes
			  for(int j=0; j < vertexNumber; ++j)
			    nodes[j].label = -1;
			  // reinit queue
			  initQueueFromV();

			  // jumpout from for
			  break;
			}
		    // if u is matched
			else{
		      // if(w,u) is not in matches and u is not labeled
			  if ( inMatch(nodes[i].vertex, w.vertex) == -1
			       && nodes[i].label == -1){
			    // label u with w
				nodes[i].label = w.vertex;
			    // add u into queue
				queue.addElement(nodes[i]);
			  }

			} // end if u is matched
		  } // end if u is connected to w
		} //end for each node
	  } // end if w is in set V

	  // if w in U
	  else{
	    // label u who is matched by w with w
		Node u = nodes[ whoMatch(w.vertex) ];
		u.label = w.vertex;
		// add u into queue
		queue.addElement(u);
	  } // end if w in set U

	} //end while queue is not empty
	return;
  }

  // 时间复杂度为n^2.5的宽度优先搜索算法
  // 该算法由Hopcroft和Karp提出
  public void n25BfsMatch(){
    //clear matches
	// while not maximum
	  // init queue
	  // subset of U
	  // set of edges that connect from V to U
	  // label all vertexes in V and U
	  //  while ...
	    // ...
	  //if L is empty
	    //...
	  //else
	    //...
	return;
  }

  public static void main(String [] args)
    throws FileNotFoundException, IOException{
	// check parameters
    if(args.length < 1){
	  System.out.println("usage: java BiMatch filename");
	  return;
	}
	// create BiMatch Object
	BiMatch bm = new BiMatch();
    // read bipartite graph
	bm.readBiGraph(args[0]);
	// caculate max match
	bm.n3BfsMatch();
	// output
	bm.printBiGraph();
	bm.printMatches();
  }
}

class Match{
  int first;
  int second;

  public Match(int num1, int num2){
    first = num1;
	second = num2;
  }
}

class Node{
  int vertex;		// number of vertex
  int label;		// label on vertex
  boolean matched;	// is vertex matched?
  boolean isInV; 	// is vertex is Set V

  public Node(){
    vertex = -1;
	label = -1;
	matched = false;
	isInV = false;
  }
}

