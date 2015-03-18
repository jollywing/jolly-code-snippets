/* Purpose
 *  This program simulates HanNo tower question.
 * Record of reversions
 *   date       programer       description
 * ==========  ============   ==========================
 * 20080517     jiqing         original version
 */

public class HanNuoTower{
  private long steps;
  private double startTime;

  public void init(){
    steps = 0;
	startTime = System.currentTimeMillis();
  }

  public void moveTower(int n, int start, int finish, int spare){
    steps ++;

    if( n == 1)
	  System.out.println("move a disk from peg " + start 
	                     +" to peg "+ finish);
	else{
	  moveTower(n-1, start, spare, finish);
	  System.out.println("move a disk from peg " + start 
	                     +" to peg "+ finish);
      moveTower(n-1, spare, finish, start);
	}
  }

  public void printResult(){
    double time = System.currentTimeMillis();
	double eTime = (time - startTime) / 1000;
	System.out.println("======================================");
	System.out.println("result stat:");
	System.out.println("total moves " + steps);
	System.out.println("time cost " + eTime +"s.");
	System.out.println("======================================");

  }

  public static void main(String [] args){
    if(args.length < 1){
	  System.out.println("usage: java HanNuoTower disknumber");
	  return;
	}
	else{
	  HanNuoTower h = new HanNuoTower();
	  h.init();
	  h.moveTower(Integer.parseInt(args[0]),
	              1, 3, 2);
	  h.printResult();
	}
  }
  
}
