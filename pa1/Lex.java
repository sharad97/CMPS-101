//*********************************//
//Sharad Shrestha                  //
//SID: 1439935                     //
//CMPS 101                         //
//Patrick Tantalo                  //
//Programming Assignment 1         //
//*********************************//

import java.io.*;
import java.util.Scanner;

public class Lex{
    
    public static void main(String[] args) throws IOException {
        Scanner in = null;
        PrintWriter out = null;
        String line = null;
        int lineNumber = 0;
        int A, B;
        
        if( args.length!=2 ){
            System.err.println("Lex Usage: Lex <input file> <output file>");
            System.exit(1);
        }
        
        // Gets input file
        in = new Scanner(new File(args[0]));
        
        // Gets output file and creates FileWriter Object
        out = new PrintWriter(new FileWriter(args[1]));
        
        // Counts how many lines are in file
        while(in.hasNextLine()){
            lineNumber++;
            // Add extra space so split works right
            line = in.nextLine()+" ";
        }
        
        String[] stringArray = new String[lineNumber];
        in = new Scanner(new File(args[0]));
        for(int i = 0; i<lineNumber; i++){
            stringArray[i] = in.nextLine();
        }
        
        // Sorts a string array 
        List L = new List();
        int n = stringArray.length;
        L.append(0);
        
        for(A=1; A<n; A++){
            L.moveFront();
            while( L.index()!=-1 && stringArray[A].compareTo(stringArray[L.get()])>0 ){
                L.moveNext();
            }if( L.index()==-1 ){
                L.append(A);
            }else
            L.insertBefore(A);
        }

        // Loop through the list and prints out sorted string array 
        L.moveFront();
        for(B=0; B<n; B++){
            out.println(stringArray[L.get()]);
            L.moveNext();
        }
        
        in.close();
        out.close();
    }
}