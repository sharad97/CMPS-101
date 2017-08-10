//*********************************//
//Sharad Shrestha                  //
//SID: sshrest3                    //
//CMPS 101                         //
//Patrick Tantalo                  //
//Programming Assignment 3         //
//*********************************//

class Matrix{
    private class Entry{
		// Entry Field
        int column;
        double value;
        
        Entry(int column, double value){
            this.column = column;
            this.value = value;
        }
        
        public String toString(){ 
            String str = "";
            str = ("("+ column + ", " + value +")"); 
            return str;
        }
        
        public boolean equals(Entry e){
            if(column == e.column && value == e.value){ 
                return true;
            }else{
                return false;
            }
        }
    }
    
	// Matrix Field
    private int size;
    private int nnz;
    private List[] row;

    
//---------------------Constructor-----------------------------//

    
// Makes a new n x n zero Matrix. pre: n>=1
    Matrix(int n){
        if(n<=0){
            throw new RuntimeException("Matrix Error: Invalid size of matrix(n should be >= to 1");
        }else{
            size = n;
            row = new List[n+1];
            for(int i=0; i<n+1; i++){
                row[i] = new List();
            }
        }
    }

    
//-------------------Access functions-------------------------//

    
// Returns n, the number of rows and columns of this Matrix
    int getSize(){
        return size;
    }

// Returns the number of non-zero entries in this Matrix
    int getNNZ(){
        return nnz;
    }
   
// Overrides Object's equals() method
    public boolean equals(Object O){ 
        Matrix eq = (Matrix)O;
        if(this == eq){
            return true;
        }
        if(size != eq.getSize()){
            return false;
        }
        for(int i=0; i<size; ++i){
            List x = row[i];
            List y = eq.row[i];
            if(x.length() != y.length()){
                return false;
            }
			x.moveFront();
			y.moveFront();
            for(int j=0; x.index() >= j && y.index() >= j; j++){
                Entry a = (Entry)x.get();
                Entry b = (Entry)y.get();
                if(!a.equals(b)){ 
                    return false;
                }
				x.moveNext(); 
				y.moveNext();
            }
        }
        return true;
    }
  

//-----------------Manipulation procedures---------------------//


// Sets this Matrix to the zero state
    void makeZero(){
        for(int i=0; i<=size; i++){
            row[i].clear();
        }
        nnz=0;
    }

// Returns a new Matrix having the same entries as this Matrix
    Matrix copy(){
        Matrix copy = new Matrix(this.size);
        for(int i=1; i<this.size; i++){
            row[i].moveFront();
            for(int j=1; j<=row[i].length() ; j++){
                Entry entry = (Entry)row[i].get();
                copy.changeEntry(i, entry.column, entry.value);
                row[i].moveNext();
            }
        }
        return copy;
    }
   
// Changes ith row, jth column of this Matrix to x
// Pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x){
        if(i < 1 || i > this.size){
            throw new RuntimeException("Matrix Error: changeEntry() called on invalid parameter of row");
        }
        if(j < 1 || j > this.size){
           throw new RuntimeException("Matrix Error: changeEntry() called on invalid parameter of column");
        }
		Entry entry = new Entry(j,x);
		Entry a;
		List r = row[i];
		if(x==0){
            if(r.length()>0){
				r.moveFront();
                for(int k=0; r.index()>=k; k++ ){
                    a = (Entry)r.get();
                    if(a.column==j && (int)a.value != 0) {
                        r.delete();
                        nnz--;
                        break;
                    }
					r.moveNext();
                }
            }
        }else if(x!=0){
			if(r.length() == 0){
				r.append(entry);
				nnz++;
			}else if(r.length()>0){
				r.moveFront();
                for(int k=0; r.index()>=k; k++){
                    a = (Entry)r.get();
                    if(a.column == j) {
                        r.delete();
                        nnz--;
                        break;
                    }
					r.moveNext();
                }
				r.moveFront();
                for(int k=0; r.index()>=k; k++){
                    a = (Entry)r.get();
                    if (j < a.column){
                        r.insertBefore(entry);
                        nnz++;
                        break;
                    }
					r.moveNext();
                }
				if(r.index() == -1 && x !=0){
					r.append(entry);
					nnz++; 
                }
            }
        }
    }

// Returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x){
        Matrix scalarmult = new Matrix(this.size);
        for(int i = 1; i <= this.size; i++){
            row[i].moveFront();
            for(int j = 1; j<=row[i].length(); j++){
                Entry entry = (Entry)row[i].get();
                scalarmult.changeEntry(i,entry.column, (entry.value)*x);
                row[i].moveNext();
            }
        }
        scalarmult.nnz = nnz;
        return scalarmult;
    }

// Returns a new Matrix that is the sum of this Matrix with M
// Pre: getSize()==M.getSize()
    Matrix add(Matrix M){
        if(this.size != M.size){
            throw new RuntimeException("Matrix Error: add() called on Matrices of different size");
        }
        Matrix add = new Matrix(this.size);
        List x, y;
        Entry a, b;
        for(int i = 1; i <= this.size; i++){
            x = this.row[i];
            y = M.row[i];
            x.moveFront();
            y.moveFront();
            if (this.equals(M)) {
                return this.scalarMult(2.0);
            }else{
                while(x.index() >= 0 || y.index() >= 0){
                    if(x.index() >= 0 && y.index() >= 0){
                        a = (Entry)x.get();
                        b = (Entry)y.get();
                        if(a.column < b.column){
                            add.changeEntry(i, a.column, a.value);
                            x.moveNext();
                        }else if(a.column > b.column){
                            add.changeEntry(i, b.column, b.value);
                            y.moveNext();
                        }else{
                            add.changeEntry(i, a.column, a.value + b.value);
                            x.moveNext();
                            y.moveNext();
                        }
                    }else if(x.index() >= 0){
                        a = (Entry)x.get();
                        add.changeEntry(i, a.column, a.value);
                        x.moveNext();
                    }else if(y.index() >= 0){
                        b = (Entry)y.get();
                        add.changeEntry(i, b.column, b.value);
                        y.moveNext();
                    }
                }
            }
        }
        return add;
    }

// Returns a new Matrix that is the difference of this Matrix with M
// Pre: getSize() == M.getSize()
    Matrix sub(Matrix M){
        if(this.size != M.size){
            throw new RuntimeException("Matrix Error: sub() called on Matrices of different size");
        }
        Matrix sub = new Matrix(this.size);
        Matrix s = M.scalarMult(-1);
        sub = this.add(s);
        return sub;
    }

// Returns a new Matrix that is the transpose of this Matrix
    Matrix transpose(){
        Matrix transpose= new Matrix(this.size);
        for(int i=1; i<=this.size; i++){
            row[i].moveFront();
            for(int j=1; j<=row[i].length() ; j++){
                Entry x = (Entry)row[i].get();
                transpose.changeEntry(x.column, i , x.value);
                row[i].moveNext();
            }
        }
        transpose.nnz = nnz;
        return transpose;
    }

// Returns a new Matrix that is the product of this Matrix with M
// Pre: getSize()==M.getSize()
    Matrix mult(Matrix M){
        if (this.size != M.size){
            throw new RuntimeException("Matrix Error: mult() called on Matrices of different size");
        }
        Matrix mult = new Matrix(this.size);
        M = M.transpose();
        for(int i = 1; i <= this.size; i++){
            for (int j = 1; j <= size; j++){
                mult.changeEntry(i, j, dot(row[i], M.row[j]));
            }
        }
        return mult;
    }

    
//---------------------Other functions-----------------------------------//

    
// Overrides Object's toString() method
    public String toString(){
        String str =  new String("");
        for (int i=1; i<=this.size; i++){
            if(row[i].length() > 0){
                str = str +i+": "+ this.row[i] + '\n';
            }
        }
        return str;
    }
   
// Helper Functions
    private static double dot(List A, List B){
        double product = 0.0;
		Entry x, y;
        if(A.length()==0 || B.length()==0){
            return 0;
        }
        A.moveFront();
        B.moveFront();
        while(A.index() >= 0 && B.index() >= 0){
            x = (Entry)A.get();
            y = (Entry)B.get();
            if(x.column < y.column){
                A.moveNext();
            }else if(x.column > y.column){
                B.moveNext();
            }else if(x.column == y.column){
                product += (x.value*y.value);
                A.moveNext();
                B.moveNext();
            }
        }
        return product;
    }
}   