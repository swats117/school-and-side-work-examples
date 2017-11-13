/*
	AUTHOR: Charles Swarts
	PROMPT: Implement the PA=LU LU decomposition algorithm discussed in CS 357.
	
	The algorithm is recursive.

	The base case is a 1X1 matrix multiplication.
	The recursive case is an NXN matrix. 
	The first step is to implement matrix multiplication.


	BIG NOTE TO SELF. MATRICES ARE INHERENTLY DOUBLE BASED

*/
#include <cstdio>
#include <string.h>
#include <assert.h>
using namespace std;
// SQUARE MATRIX ******
class Matrix{
public:
	double* matrix;
	int length;

	Matrix(int length): length(length){
		printf("making matrix length: %d\n",length);
		assert(length>0);
		// matrix construction makes a copy of the matrix for simplicity.
		// using a flattened array for dynamic allocation purposes.
		matrix = new double[length * length];
		memset(matrix, 0, length*length*sizeof(double));
	}
	Matrix(double* matrix,int length): length(length){
		printf("second constructor length:%d\n",length);
		assert(length>0);
		// matrix construction makes a copy of the matrix for simplicity.
		// using a flattened array for dynamic allocation purposes.
		this->matrix = new double[length * length];

		for(int i=0; i<(length*length); i++){
			this->matrix[i] = matrix[i];
		}
	}

	Matrix(Matrix& old_matrix): length(old_matrix.length){
		
		matrix = new double[length * length];
		for(int i=0; i<(length*length); i++){
			matrix[i] = old_matrix.matrix[i];
		}
	}

	~Matrix(){
		delete [] matrix;
	}
	void printMatrix (){

		for(int i=0; i<length; i++){
			for(int j=0; j<length-1; j++){
				printf("%f, ", matrix[i*length+j]);
			}
			printf("%f\n", matrix[(i+1)*length-1]);
		}
	}

	Matrix* operator * (Matrix& right){
		printf("length: %d\n",length);
		Matrix* output = new Matrix(length);

		for(int i=0; i<length; i++){
			for(int j=0; j<length; j++){
				for(int k=0; k<length; k++){
					// printf("left: %f, right: %f\n",matrix[i*length+k],right.matrix[k*length+j]);
					output->matrix[i*length+j] += matrix[i*length+k]*right.matrix[k*length+j];
				}
				// printf("output: %f\n",output->matrix[i*length+j]);
				// puts("next position");
			}
			// puts("next row");
		}
		return output;
	}
	Matrix* operator + (Matrix& right){
		printf("length: %d\n",length);
		Matrix* output = new Matrix(length);

		for(int i=0; i<length*length; i++){
			output->matrix[i] = matrix[i]+right.matrix[i];
		}
		
		return output;
	}
	Matrix* operator - (Matrix& right){
		printf("length: %d\n",length);
		Matrix* output = new Matrix(length);

		for(int i=0; i<length*length; i++){
			output->matrix[i] = matrix[i]-right.matrix[i];
		}
		
		return output;
	}



};

int int_abs(int num){
	int mask = num>>31;
	return (num^mask)-mask;
}

/* This is the implementation of the PA=LU decomposition basic algorithm*/
void LUDecompose(Matrix A,Matrix** P, Matrix** L, Matrix** U){

	int length = A.length;
	*P = new Matrix(length);
	*L = new Matrix(length);
	*U = new Matrix(length);/*
	 T
	 O*/
	int switch_board[length];
	for(int i=0; i<length; i++) { switch_board[i]=i; }

	/* This for loop goes like	 The head of a Row
									
		   length					
		|-----------|				
		. . . . . . .				. . . . . . .
		. 0 0 0 0 0 0				. O 0 0 0 0 0
		. 0 . . . . .				. O . . . . .
		. 0 . 0 0 0 0				. O . 0 0 0 0
		. 0 . 0 . . .				. O . 0 . . .
		. 0 . 0 . 0 0				. O . 0 . 0 0
		. 0 . 0 . 0 .				. O . 0 . 0 .
								
	*/							
	


	// The base case occurs when i==1.
	for(int sub_len=length; sub_len>1; sub_len--){

		printf("sub_len: %d\n\n", sub_len);
		printf("begin A\n");
		A.printMatrix();
//-------------------- ROW WITH LARGEST HEAD-------------------
		int max = 0;
		int maxrow = length - sub_len;
		for(int j=length-sub_len; j<length; j++){
			printf("j:%d\n",j);
			int cur = A.matrix[length*switch_board[j]+(length-sub_len)];

			if(int_abs(cur)>int_abs(max)){
				max = cur;
				maxrow = j;
			}
		}
		printf("sub_len: %d, maxrow: %d\n", sub_len,maxrow);
		if( max == 0) { printf("not LU decomposable\n"); return; }
//-------------------- ROW WITH LARGEST HEAD-------------------
//-----------SWAP CURRENT ROW WITH ROW WITH LARGEST HEAD-------
		if(length-sub_len != maxrow){
			int temp = switch_board[length-sub_len];
			switch_board[length-sub_len] = switch_board[maxrow];
			switch_board[maxrow] = temp;
		}
		printf("switch_board: ");
		for(int j=0; j<length - 1; j++){
			printf("%d, ",switch_board[j]);
		} printf("%d\n",switch_board[length-1]);
//-----------SWAP CURRENT ROW WITH ROW WITH LARGEST HEAD-------
//-------------------FILL IN ROW IN U and L -------------------
		for(int j=length-sub_len; j<length; j++){
			(*U)->matrix[length*(length-sub_len) + j]=A.matrix[(length*switch_board[length-sub_len]+j)];
			(*L)->matrix[length*switch_board[j] + (length-sub_len)]=A.matrix[(length*switch_board[j]+(length-sub_len))]/A.matrix[length*(switch_board[length-sub_len])+(length-sub_len)];
			// (*L)->matrix[length*switch_board[j] + (length-sub_len)]=A.matrix[(length*switch_board[j]+(length-sub_len))]/A.matrix[length*(switch_board[length-sub_len])+(length-sub_len)];
			// break;
		}
//-------------------FILL IN ROW IN U and L -------------------
//----------------SUBTRACT L21 dot U12 from A22----------------

		puts("before L");
		(*L)->printMatrix();
		puts("before U");
		(*U)->printMatrix();

		for(int j=length-sub_len+1; j<length; j++){
			for(int k=length-sub_len+1; k<length; k++){
				
				
				double l_component = (*L)->matrix[length*(switch_board[j])+(length-sub_len)];
				double u_component = (*U)->matrix[length*(length-sub_len)+(k)];

				printf("L: %f, U: %f\n",l_component, u_component);

				A.matrix[length*(switch_board[j])+k] -= l_component * u_component;
			}
		}
//----------------SUBTRACT L21 dot U12 from A22----------------
		
	}



//--------------------------Base Case--------------------------
	(*U)->matrix[length*length - 1] = A.matrix[length*switch_board[length-1]+length -1];
	(*L)->matrix[length*switch_board[length-1]+length - 1] = 1.0;
//--------------------------Base Case--------------------------

//--------------------Switch the rows in L---------------------
	Matrix L_copy( (**L) );
	int r_switch_board[length];
	for(int i=0; i<length; i++){
		r_switch_board[switch_board[i]]=i;
	}

	for(int i=0; i<length; i++){
		for(int j=0; j<length; j++){
			(*L)->matrix[length*(r_switch_board[i])+j] = L_copy.matrix[length*i+j];		
		}
	}
//--------------------Switch the rows in L---------------------
//------------------Create Permutation Matrix------------------
	for(int i=0; i<length; i++){
		(*P)->matrix[length*i+switch_board[i]] = 1;
	}
//------------------Create Permutation Matrix------------------


}



int main(){
	
	// double ArrayA[9]= {1, 7,
	// 	 			44, 2};
	double ArrayA[16]= {44, 44, 7, 2,
		 			45, 2, 9, 9,
		 			8, 9, 10, 11,
		 			12, 13, 14, 15};
	// double ArrayA[9]= {1, 44, 7,
	// 	 			8, 2, 9,
	// 	 			44, 9, 10};

	// Matrix* A = new Matrix(ArrayA, 2);
	// Matrix* P, *L, *U;
	// LUDecompose((*A),P,L,U);

	// Matrix* PA = (*P) * (*A);
	// Matrix* LU = (*L) * (*U);

	Matrix A(ArrayA, 4);
	Matrix* P, *L, *U;
	LUDecompose(A,&P,&L,&U);

	printf("\n");
	L->printMatrix();
	printf("\n");
	U->printMatrix();

	printf(":)\n");
	// Matrix* PA = (*P) * A;
	// Matrix* LU = (*L) * (*U);


	// (*P * A)->printMatrix();
	(*L * *U)->printMatrix();
	(*P * A)->printMatrix();

	return 0;
}




