//*********************************//
//Sharad Shrestha                  //
//SID: sshrest3                    //
//CMPS 101                         //
//Patrick Tantalo                  //
//Programming Assignment 3         //
//*********************************//

public class List{
    private class Node{
        // Fields
        Object data; //Data associate with node.
        Node next; //Pointer to next node.
        Node previous;//Pointer to previous node.
        
        // Constructor
        Node(Object data){
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
    public Object front(){
        if(length <= 0){
            throw new RuntimeException("List Error: front() called on an Empty List");
        }
        return front.data;
    }
    
    // Returns back element. Pre: length()>0
    public Object back(){
        if(length <= 0){
            throw new RuntimeException("List Error: back() called on an Empty List");
        }
        return back.data;
    }
    
    // Returns cursor element. Pre: length()>0, index()>=0
    public Object get(){
        if(length <= 0){
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
            cursorindex = 0;
            cursor = front;
        }
    }
    
    // If List is non-empty, places the cursor under the back element,
    // otherwise does nothing.
    public void moveBack(){
        if(length > 0){
            cursorindex = length - 1;
            cursor = back;
        }
    }
    
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    public void movePrev(){
        if(cursorindex < length && cursorindex >= 0){
            if(cursorindex != 0){
                cursorindex--;
                cursor = cursor.previous;
            }else{
                cursorindex = -1;
                cursor = null;
            }
        }
    }
    
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing
    public void moveNext(){
        if(cursorindex < length && cursorindex >= 0){
            if(cursorindex != length -1){
                cursor = cursor.next;
                cursorindex++;
            }else{
                cursorindex = -1;
                cursor = null;
            }
        }
    }
    
    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    public void prepend(Object data){
        Node newnode = new Node (data);
        if(front == null){
            front = newnode;
            back = newnode;
        }else{
            newnode.next = front;
            front.previous = newnode;
            front = newnode;
            if (cursorindex >= 0){
                cursorindex++;
            }
        }
        length++;
    }
    
    // Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    public void append(Object data){
        Node newnode = new Node(data);
        if(back == null){
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
    public void insertBefore (Object data){
        if(length < 0){
            throw new RuntimeException ("List Error: insertBefore() called on an Empty List.");
        }else if (index() < 0){
            throw new RuntimeException ("List Error: insertBefore() called on Undefined Index.");
        }
        if(cursor == front){
            prepend(data);
        }else{
            Node newnode = new Node (data);
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
    public void insertAfter(Object data){
        if(length < 0){
            throw new RuntimeException ("List Error: insertAfter() called on an Empty List.");
        }else if (index() < 0){
            throw new RuntimeException ("List Error: insertAfter() called on Undefined Index.");
        }
        if(cursor == back){
            append(data);
        }else{
            Node newnode = new Node (data);
            newnode.previous = cursor;
            newnode.next  = cursor.next;
            cursor.next.previous = newnode;
            cursor.next = newnode;
            length++;
        }
    }

    // Deletes the front element. Pre: length()>0
    public void deleteFront(){
        if(length < 0){
            throw new RuntimeException("List Error: deleteFront called on an Empty List.");
        }else if(length == 1){
            front = null;
        }else{
            front = front.next;
            front.previous = null;
            length--;
            if (cursorindex == 0){ 
                cursor = null;
                cursorindex = -1;
            }else if(cursorindex != -1){
                cursorindex--;
            }
        }
    }

    // Deletes the back element. Pre: length()>0
    public void deleteBack(){
        if(length < 0){
            throw new RuntimeException("List Error: deleteBack called on an Empty List.");
        }else if(cursor == back){
            cursor = null;
            cursorindex = -1;
        }
        if(length() > 1){
            back = back.previous;
        }else{
            back = null;
        }
        length--;
    }

    // Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    public void delete(){
        if (length < 0){
            throw new RuntimeException("List Error: delete() called on an Empty List");
        }else if(cursorindex < 0){
            throw new RuntimeException("List Error: delete() called on Undefined Index");
        }else if(cursor == back){
            deleteBack();
        }else if(cursor == front){
            deleteFront();
        }else{
            cursor.previous.next = cursor.next;
            cursor.next.previous = cursor.previous;
            cursor = null;
            length--;
        }
        cursorindex = -1;
    }


//---------------------------------------Other methods---------------------------------------//


    // Overrides Object's toString method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    public String toString() {
        if (length == 0) return "";
        String str = front.toString(); 
        for (Node A = front.next; A != null; A = A.next) 
            str += " " + A.toString();
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