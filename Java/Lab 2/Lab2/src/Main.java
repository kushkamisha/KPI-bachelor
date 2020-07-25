/**
 * Java labs - Lab2
 * @version 1.0 2018-02-26
 * @author Misha Kushka
*/

class Matrix {
	private final char[][] matr;
	private final int n;
	private final int m;
	
	Matrix(char[][] newMatr) {
		matr = newMatr;
		n = matr.length;
		m = matr[0].length;
	}
	
	void printMatrix() {
		System.out.print('\t');
		for (int i = 0; i < this.n; ++i) {
			for (int j = 0; j < this.m; ++j) {
				System.out.print(this.matr[i][j] + "  ");
			}
			System.out.print("\n\t");
		}
		System.out.println();
	}
	
	char[][] transpose() {
		char[][] outputMatrix = new char[this.m][this.n];
		
		for (int i = 0; i < this.n; ++i) {
			for (int j = 0; j < this.m; ++j) {
				outputMatrix[j][i] = this.matr[i][j];
			}
		}
		
		return outputMatrix;
	}
	
	char minElementsColumnSum() {
		int minSum = 0;
		char columnMinElement;
		
		for (int i = 0; i < this.n; ++i) {
			columnMinElement = Character.MAX_VALUE;
			for (int j = 0; j < this.m; ++j) {
				if (matr[i][j] < columnMinElement) {
					columnMinElement = matr[i][j]; 
				}
			}
			
			// Overflow check
			if (i == this.n-1 && minSum + (int)columnMinElement > Character.MAX_VALUE) {
				System.err.println("Overflow char type!");
			}
				
			minSum += (int)columnMinElement;
		}
		
		return (char)minSum;
	}
}

public class Main {

	public static void main(String[] args) {
		
		char[][] matr = {
				{'a', 'b', 'c', 'd'}, // {Character.MAX_VALUE-3, Character.MAX_VALUE-2, Character.MAX_VALUE-1, Character.MAX_VALUE},
				{'e', 'f', 'g', 'h'},
				{'i', 'j', 'k', 'l'}
		};
		
		Matrix matrix = new Matrix(matr);
		
		// Input matrix
		System.out.println("Input matrix:");
		matrix.printMatrix();
		
		// Transposed matrix
		System.out.println("Transposed matrix:");
		Matrix transpMatr = new Matrix(matrix.transpose());
		transpMatr.printMatrix();
		
		// Sum of the smallest elements from matrix columns
		System.out.print("Sum of the smallest elements from matrix columns -> ");
		char result = matrix.minElementsColumnSum();
		System.out.println(result);

	}

}
