/* Purpose
 *  This program reverse array with 
 *  several different recursive method.
 * Record of reversions
 *   data       programer     description
 * ==========  ==========   ====================
 * 20080515     jiqing       original version
 */

public class Recursive{
  private int [] a;
  private final static int LENGTH = 10;

  public void init(){
    a = new int[LENGTH];
	for( int i=0; i< LENGTH; ++i){
	  a[i] = i;
	}
  }

  public void print(){
    for(int i=0; i< LENGTH; ++i){
	  System.out.print(a[i] +" ");
	}
	System.out.print("\n\n");
  }

  // n is the upbound of array
  public void reverse1( int n){
    if(n > 1){
	  int temp = a[0];
      //forward a[1, n]
	  for(int i = 1; i < n; i++){
	    a[i-1] = a[i];
	  }
	  //move a[0] to the tail
	  a[n-1] = temp;
	  //reverse a[m, n-1]
	  reverse1(n-1);
	}
  }

  // n is the lowbound of array to handle
  public void reverse2(int n){
    if(n < LENGTH - 1){
	  int temp = a[LENGTH-1];

	  // backward a[n,LENGTH -2]
	  // !!!!!!!!!This is not correct
	  //for(int i = n; i < LENGTH -1; i++)
	  //  a[i+1] = a[i];
	  // !!!!!! This is right
	  for ( int i = LENGTH -1; i >n; i--)
	    a[i] = a[i-1];

	  // move a[LENGTH-1] to a[n]
	  a[n] = temp;

	  // reverse a[n, LENGTH-1]
	  reverse2(n+1);
	}
  }

  // m is lowbound, n is upbound
  public void reverse3(int m, int n){
    if(m < n){
	  int temp = a[m];
	  a[m] = a[n];
	  a[n] = temp;
	  reverse3(m+1, n-1);
	}
  }

  public static void main(String s[]){
    // new a array of integer
	Recursive r = new Recursive();
	r.init();
	r.print();
	// reverse it with three diffrent method.
	r.reverse1(LENGTH); 
	r.print();

	r.reverse2(0);
	r.print();

	r.reverse3(0, LENGTH -1);
	r.print();
  }
}
