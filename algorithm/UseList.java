/* Purpose
 *   This program was written to practice with List.
 * Record of reversions
 *    date       author       description
 * ===========  ==========   ===========================
 * 20080507      jiqing       original version
 * 20080508      jiqing       complete it
 * 20080514      jiqing       reverse list using recursive algorithm
 *                            contact list using recursive algorithm
 */

public class UseList {
  
  public static void main( String s[]) {
    LinkedList l = new LinkedList();

	l.insertTail("John");
	l.insertTail("Tom");
	l.insertHead("Mary");
	l.print();

    // reverse and print
	l.reverse();
	l.print();

    // contact and print
	LinkedList l1 = new LinkedList();
	l1.insertHead("Sam");
	l1.insertHead("White");
	l1.insertHead("Shelly");
	l.contact(l1);
	l.print();
	l.reverse();
	l.print();

    // clone
	LinkedList l2 = l.clone();
	l2.print();
	l2.removeTail();
	l2.removeHead();
	l.print();
	l2.print();
  }
}

class ListNode{
  public String value;
  public ListNode link;
}

class LinkedList{
  public int length;
  public ListNode firstNode;

  public LinkedList(){
    // perhaps below codes are unnecessary
	// because the default construction function will also
	// set length to 0, and firstNode to null
    length = 0;
	firstNode = null;
  }

  public int size(){
    return length;
  }

  public void insertHead( String value){
    ListNode temp = new ListNode();
	temp.value = value;
	temp.link = firstNode;
	firstNode = temp;

	length ++;
  }

  public void insertTail( String value){
    length ++;

    ListNode temp = new ListNode();
	temp.value = value;
	temp.link = null;

	if ( firstNode == null ) {
	  firstNode = temp;
	  return;
	}

	ListNode n = firstNode;
	while( n.link != null ) {
	  n = n.link;
	}
	n.link = temp;
  }

  public void removeHead(){
    if (firstNode == null) return;
    firstNode = firstNode.link;
	length --;
  }

  public void removeTail(){
    // you can't represent this with ' !firstNode'
    if( firstNode == null ) return;
	length --;

	if( firstNode.link == null ){
	  firstNode = null;
	  return;
	}

    ListNode n = firstNode;
	while(n.link.link != null){
	  n = n.link;
	}
	n.link = null;
  }

  public void remove(String value ) {
    ListNode previous, current;

	if( firstNode == null ) return;

	// delete all nodes that have specified value at head of list
	while( value.equals(firstNode.value) ){
	  firstNode = firstNode.link;
	  if( firstNode == null ) return;
	}

	// delete all nodes that have specified value in the list
	previous = firstNode;
	current = previous.link;
	while(current != null){
	  if(value.equals(current.value) ){
	    previous.link = current.link;
	  }
     // move foward
     previous = previous.link;
	 if(previous != null) current = previous.link;
	 else current = null;
	}
  }

  public void reverse() {
    /* ***************normal algorithm***********
	if ( firstNode == null || firstNode.link == null ) return;

    ListNode temp;
	ListNode current, previous;
	previous = firstNode;
	current = previous.link;
	//don't forget to set firstNode's link to null
	//otherwise, there will be a circle.
	firstNode.link = null;

	// reverse
	while( current != null ) {
	  temp = current.link;
	  current.link = previous;
	  previous = current;
	  current = temp;
	}

	firstNode = previous;
	*/

	firstNode = recursiveReverse(firstNode);

  }

  private ListNode recursiveReverse(ListNode l){
    if(l == null)
	  return null;
	else{
	  ListNode head = l;
	  ListNode tail = l.link;
	  head.link = null;
	  return recursiveContact( recursiveReverse(tail), head);
	}
  }

  public void contact( LinkedList l ) {
    /* 
	 * normal algorithm
    if( firstNode == null ){
	  firstNode = l.firstNode;
	  return;
	}

	ListNode n = firstNode;
	while( n.link != null ) {
	  n = n.link;
	}

	n.link = l.firstNode;
	*/

	//recursive algorithm
	length += l.length;
	firstNode = recursiveContact(firstNode, l.firstNode);
  }

  private ListNode recursiveContact(ListNode l1, ListNode l2){
    if(l1 == null)
	  return l2;
	else{
	  l1.link = recursiveContact(l1.link, l2);
	  return l1;
	}
  }

  public LinkedList clone() {
    // something newed isn't local variable
	// it will exist until none refer it.
    LinkedList l = new LinkedList();

	if( firstNode == null ) return l;

	l.firstNode = new ListNode();
	l.firstNode.value = firstNode.value;

	ListNode n = firstNode.link;
	ListNode temp = l.firstNode;
	while( n != null ){
	  temp.link = new ListNode();
	  temp.link.value = n.value;
	  temp.link.link = null;
	  temp = temp.link;
	  n = n.link;
	}

    return l;
  }

  public void print() {

    if( firstNode == null ) return;

	ListNode temp = firstNode;
	while(temp != null ) {
	  System.out.print(temp.value);
	  temp = temp.link;
	  if (temp != null) System.out.print(", ");
	}

	System.out.print("\n");

  }

}
