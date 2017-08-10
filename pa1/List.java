//*********************************//
// Sharad Shrestha                 //
// SID: 1439935                    //
// CMPS 101                        //
// Patrick Tantalo                 //
// Programming Assignment 1        //
//*********************************//

public class List{
    private class Node{
        // Fields
        int data; //Data associate with node.
        Node next; //Pointer to next node.
        Node previous;//Pointer to previous node.
        
        // Constructor
        Node(int data){
            this.data = data;
            next = null;
            previous = null;
        }
		
        // "toString" overrides object's toString method.
        // It returns the data of the node object as a String.
        public String toString(){
            return String.valueOf(data);
        }
    }
    
    // Fields
    private Node front;//pointer to first element
    private Node back; //pointer to last element
    private Node cursor; //points to current element being used
    private int length; //number of element in list
    private int cursorindex; //index of element 
	

//------------------------------Constructor-----------------------------------//
    
    // Creates new empty list
    public List(){
        front = null;
        back = null;
        cursor = null;
        length = 0;
        cursorindex = -1;
    }

	
//-------------------------------Access Functions------------------------------//
    
    // returns the number of elements in this list
    public int length(){
        return length;
    }
    
    // returns the index of the cursor element when cursor is defined
    // returns -1 if cursor is not defined
    public int index(){
        return cursorindex;
    }
    
    // Returns front element. Pre: length()>0
    public int front(){
        if(length == 0){
            throw new RuntimeException("List Error: front() called on an Empty List");
        }
        return front.data;
    }
    
    // Returns back element. Pre: length()>0
    public int back(){
        if(length == 0){
            throw new RuntimeException("List Error: back() called on an Empty List");
        }
        return back.data;
    }
    
    // Returns cursor element. Pre: length()>0, index()>=0
    public int get(){
        if(length < 0){
            throw new RuntimeException("List Error: get() called on an Empty List.");
        }else if(index() < 0){
            throw new RuntimeException("List Error: get() called  on Undefined Index.");
        }else{
            return cursor.data;
        }
    }
    
    // Returns true if this List and L are the same integer
    // sequence. The cursor is ignored in both lists.
    public boolean equals(List L){
        boolean check = true;
        Node A = front;
        Node B = L.front;
        if(length == L.length){
            while(check && A != null){
                check = (A.data == B.data);
                A = A.next;
                B = B.next;
            }
            return check;
        }else{
            return false;
        }
    }

	
//------------------------------Manipulation procedures----------------------------//
    
    // Resets this List to its original empty state.
    public void clear(){
        front = null;
        back = null;
        cursor = null;
        length = 0;
        cursorindex = -1;
    }
    
    // If List is non-empty, places the cursor under the front element,
    // otherwise does nothing.
    public void moveFront(){
        if(length > 0){
            cursor = front;
            cursorindex = 0;
        }
    }
    
    // If List is non-empty, places the cursor under the back element,
    // otherwise does nothing.
    public void moveBack(){
        if(length > 0){
            cursor = back;
            cursorindex = length - 1;
        }
    }
    
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    public void movePrev(){
        if(cursor == front){
            cursor = null;
            cursorindex = -1;
        }else{
            cursor = cursor.previous;
            cursorindex--;
        }
    }
    
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing
    public void moveNext(){
        if(cursor == back){
            cursor = null;
            cursorindex = -1;
        }else{
            cursor = cursor.next;
            cursorindex++;
        }
    }
    
    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    public void prepend(int data){
        Node newnode = new Node (data);
        if(length == 0){
            front = newnode;
            back = newnode;
        }else{
            newnode.next = front;
            front.previous = newnode;
            front = newnode;
            cursorindex++;
        }
        length++;
    }
	
    // Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    public void append(int data){
        Node newnode = new Node(data);
        if(length == 0){
            front = newnode;
            back = newnode;
        }else{
            newnode.previous = back;
            back.next = newnode;
            back = newnode;
        }
        length++;
    }
	
    // Insert new element before cursor.
    // Pre: length()>0, index()>=0
    public void insertBefore (int data){
        if(length < 0){
            throw new RuntimeException ("List Error: insertBefore() called on an Empty List.");
        }else if (index() < 0){
            throw new RuntimeException ("List Error: insertBefore() called on Undefined Index.");
        }
        Node newnode = new Node (data);
        if(cursorindex == 0){
            prepend(data);
        }else{
            newnode.next = cursor;
            newnode.previous = cursor.previous;
            cursor.previous.next = newnode;
            cursor.previous = newnode;
            cursorindex++;
            length++;
        }
    }
	
    // Inserts new element after cursor.
    // Pre: length()>0, index()>=0
    public void insertAfter(int data){
        if(length < 0){
            throw new RuntimeException ("List Error: insertAfter() called on an Empty List.");
        }else if (index() < 0){
            throw new RuntimeException ("List Error: insertAfter() called on Undefined Index.");
        }
        Node newnode = new Node (data);
        if(cursorindex == length()-1){
            append(data);
        }else{
			newnode.previous = cursor;
            newnode.next  = cursor.next;
            cursor.next = newnode;
            cursorindex++;
            length++;
        }
    }
	
    // Deletes the front element. Pre: length()>0
    public void deleteFront(){
        if(length < 0){
            throw new RuntimeException("List Error: deleteFront called on an Empty List.");
        }else{
            front = front.next;
            cursorindex--;
            length--;
        }
    }
	
    // Deletes the back element. Pre: length()>0
    public void deleteBack(){
        if(length < 0){
            throw new RuntimeException("List Error: deleteBack called on an Empty List.");
        }else{
            back = back.previous;
            length--;
        }
    }

    // Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    public void delete(){
        if (length < 0){
            throw new RuntimeException("List Error: delete() called on an Empty List");
        }else if(index() < 0){
            throw new RuntimeException("List Error: delete() called on Undefined Index");
        }else if(cursor == front){
            deleteFront();
        }else if(cursor == back){
            deleteBack();
        }else{
            cursor.previous.next = cursor.next;
            cursor.next.previous = cursor.previous;
            length--;
        }
    }
	
	
//---------------------------------------Other methods---------------------------------------//


    // Overrides Object's toString method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    public String toString(){
        String str = new String("");
		Node A = front;
        while(A != null){
            str += A.toString() + " ";
			A = A.next;
        }
        return str;
    }
	
    // Returns a new List representing the same integer sequence as this
    // List. The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    public List copy(){
        List copy = new List();
        Node A = front;
        while(A != null){
            copy.append(A.data);
            A = A.next;
        }
        return copy;
    }
    
    // Returns a new List which is the concatenation of
    // this list followed by L. The cursor in the new List
    // is undefined, regardless of the states of the cursors
    // in this List and L. The states of this List and L are
    // unchanged
    public List concat(List L){
        List concat = copy();
        Node A = L.front;
        while(A != null){
            concat.append(A.data);
            A = A.next;
        }
        return concat;
    }
} 