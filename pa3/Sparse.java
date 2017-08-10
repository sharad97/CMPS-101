//*********************************//
//Sharad Shrestha                  //
//SID: sshrest3                    //
//CMPS 101                         //
//Patrick Tantalo                  //
//Programming Assignment 3         //
//*********************************//

import java.io.*;
import java.util.Scanner;

public class Sparse {
    public static void main(String[] args) throws IOException{
        
        Scanner in = null;
        PrintWriter out = null;
		
        // Check command line for correct number of arguments
        if(args.length != 2){
            System.out.println("Usage Error: Sparse <inputFile> <outputFile>");
            System.exit(1);
        }
        
		// Gets input file
        in = new Scanner (new File (args[0]));
        
        int n = in.nextInt();
        int a = in.nextInt();
        int b = in.nextInt();
        
		// Creats matrices A and B with n size
        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);
        
		// Initializes matrix A.
        for (int i=0; i<a; i++){
            int row = in.nextInt();
            int column = in.nextInt();
            double value = in.nextDouble();
            A.changeEntry(row, column, value);
        }
        
		// Initializes matrix B.
        for (int i=0; i<b; i++){
            int row = in.nextInt();
            int column = in.nextInt();
            double value = in.nextDouble();
            B.changeEntry(row, column, value);
        }
        
        in.close();
        
		// Gets output file and creates FileWriter Object
        out = new PrintWriter(new FileWriter(args[1]));
        
        out.println("A has " + a + " non-zero entries:\n" + A);
        out.println("B has " + b + " non-zero entries:\n" + B);
        
        Matrix C = A.scalarMult(1.5);
        out.println("(1.5)*A =\n" + C);

        Matrix D = A.add(B);
        out.println("A+B =\n" + D);

        Matrix E = A.add(A);
        out.println("A+A =\n" + E);

        Matrix F = B.sub(A);
        out.println("B-A =\n" + F);

        Matrix G = A.sub(A);
        out.println("A-A =\n" + G);

        Matrix H = A.transpose();
        out.println("Transpose(A) =\n" + H);

        Matrix I = A.mult(B);
        out.println("A*B =\n" + I);

        Matrix J = B.mult(B);
        out.println("B*B =\n" + J);
        
        out.close();
    }
}