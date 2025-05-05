#include<iostream>
using namespace std;

class SparseMatrix 
{
	int matrix1[100][100];
	int sparse[100][3];
	int rows, columns;

public:
	void accept_sparsematrix();
	void create_sparsematrix();
	void display_sparsematrix();
	void addition_sparsematrix(SparseMatrix &matrix2);
	void transpose_sparsematrix();
	void fast_transpose_sparsematrix();
	void multiply_sparsematrix(SparseMatrix &matrix2);
};

void SparseMatrix::accept_sparsematrix() 
{
	cout << "\nEnter number of Rows : ";
	cin >> rows;

	cout << "Enter number of Columns : ";
	cin >> columns;

	cout << endl;
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			cout << "Enter Element [" << i << "][" << j << "] : ";
			cin >> matrix1[i][j];
		}
	}
	create_sparsematrix();
}

void SparseMatrix::create_sparsematrix() 
{
	int k = 1;
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			if (matrix1[i][j] != 0) 
			{
				sparse[k][0] = i;
				sparse[k][1] = j;
				sparse[k][2] = matrix1[i][j];
				k++;
			}
		}
	}
	sparse[0][0] = rows;
	sparse[0][1] = columns;
	sparse[0][2] = k - 1;
}

void SparseMatrix::display_sparsematrix() 
{
	cout << "\nSparse Matrix Representation (Row, Column, Value):\n";
	cout << "Row\tCol\tValue\n";

	for (int i = 0; i <= sparse[0][2]; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			cout << sparse[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << endl;
}

void SparseMatrix::addition_sparsematrix(SparseMatrix &matrix2) 
{
	int result[100][3];
	int l1 = sparse[0][2];
	int l2 = matrix2.sparse[0][2];
	int i = 1, j = 1, k = 1;

	result[0][0] = sparse[0][0];
	result[0][1] = sparse[0][1];

	while (i <= l1 && j <= l2) 
	{
		if (sparse[i][0] == matrix2.sparse[j][0] && sparse[i][1] == matrix2.sparse[j][1]) 
		{
			result[k][0] = sparse[i][0];
			result[k][1] = sparse[i][1];
			result[k][2] = sparse[i][2] + matrix2.sparse[j][2];
			i++; j++; k++;
		}
		else if ((sparse[i][0] < matrix2.sparse[j][0]) || (sparse[i][0] == matrix2.sparse[j][0] && sparse[i][1] < matrix2.sparse[j][1])) 
		{
			result[k][0] = sparse[i][0];
			result[k][1] = sparse[i][1];
			result[k][2] = sparse[i][2];
			i++; k++;
		}
		else 
		{
			result[k][0] = matrix2.sparse[j][0];
			result[k][1] = matrix2.sparse[j][1];
			result[k][2] = matrix2.sparse[j][2];
			j++; k++;
		}
	}

	while (i <= l1) 
	{
		result[k][0] = sparse[i][0];
		result[k][1] = sparse[i][1];
		result[k][2] = sparse[i][2];
		i++; k++;
	}

	while (j <= l2) 
	{
		result[k][0] = matrix2.sparse[j][0];
		result[k][1] = matrix2.sparse[j][1];
		result[k][2] = matrix2.sparse[j][2];
		j++; k++;
	}

	result[0][2] = k - 1;

	cout << "\nResultant Sparse Matrix after Addition:\n";
	cout << "Row\tCol\tValue\n";
	for (int t = 0; t < k; t++) {
		cout << result[t][0] << "\t" << result[t][1] << "\t" << result[t][2] << "\n";
	}
	cout << endl;
}

void SparseMatrix::transpose_sparsematrix() 
{
	int trans[100][3];
	trans[0][0] = sparse[0][1];
	trans[0][1] = sparse[0][0];
	trans[0][2] = sparse[0][2];

	int k = 1;
	for (int i = 0; i < sparse[0][1]; i++) 
	{
		for (int j = 1; j <= sparse[0][2]; j++) 
		{
			if (sparse[j][1] == i) 
			{
				trans[k][0] = sparse[j][1];
				trans[k][1] = sparse[j][0];
				trans[k][2] = sparse[j][2];
				k++;
			}
		}
	}

	cout << "\nTranspose of Sparse Matrix:\n";
	cout << "Row\tCol\tValue\n";
	for (int i = 0; i <= sparse[0][2]; i++) 
	{
		cout << trans[i][0] << "\t" << trans[i][1] << "\t" << trans[i][2] << "\n";
	}
	cout << endl;
}

void SparseMatrix::fast_transpose_sparsematrix() 
{
	int rows = sparse[0][0], cols = sparse[0][1], terms = sparse[0][2];
	int result[100][3];
	int total[100] = {0}, index[100];

	result[0][0] = cols;
	result[0][1] = rows;
	result[0][2] = terms;

	for (int i = 1; i <= terms; i++) 
	{
		total[sparse[i][1]]++;
	}

	index[0] = 1;
	for (int i = 1; i < cols; i++) 
	{
		index[i] = index[i - 1] + total[i - 1];
	}

	for (int i = 1; i <= terms; i++) 
	{
		int col = sparse[i][1];
		int pos = index[col]++;
		result[pos][0] = sparse[i][1];
		result[pos][1] = sparse[i][0];
		result[pos][2] = sparse[i][2];
	}

	cout << "\nFast Transpose of Sparse Matrix:\n";
	cout << "Row\tCol\tValue\n";
	for (int i = 0; i <= terms; i++) 
	{
		cout << result[i][0] << "\t" << result[i][1] << "\t" << result[i][2] << "\n";
	}
	cout << endl;
}

void SparseMatrix::multiply_sparsematrix(SparseMatrix &matrix2) 
{
	if (sparse[0][1] != matrix2.sparse[0][0]) 
	{
		cout << "\nMatrix multiplication not possible due to dimension mismatch.\n";
		return;
	}

	int result[100][3], k = 1;
	result[0][0] = sparse[0][0];
	result[0][1] = matrix2.sparse[0][1];

	SparseMatrix transposed;
	transposed = matrix2;
	transposed.transpose_sparsematrix();

	for (int i = 1; i <= sparse[0][2]; i++) 
	{
		for (int j = 1; j <= transposed.sparse[0][2]; j++) 
		{
			if (sparse[i][1] == transposed.sparse[j][1]) 
			{
				int r = sparse[i][0];
				int c = transposed.sparse[j][0];
				int sum = 0;

				for (int x = 1; x <= sparse[0][2]; x++) 
				{
					for (int y = 1; y <= transposed.sparse[0][2]; y++) 
					{
						if (sparse[x][0] == r && transposed.sparse[y][0] == c &&
						    sparse[x][1] == transposed.sparse[y][1]) 
						{
							sum += sparse[x][2] * transposed.sparse[y][2];
						}
					}
				}
				if (sum != 0) 
				{
					result[k][0] = r;
					result[k][1] = c;
					result[k][2] = sum;
					k++;
				}
			}
		}
	}
	result[0][2] = k - 1;

	cout << "\nMultiplication Result:\n";
	cout << "Row\tCol\tValue\n";
	for (int i = 0; i < k; i++) 
	{
		cout << result[i][0] << "\t" << result[i][1] << "\t" << result[i][2] << "\n";
	}
	cout << endl;
}

int main() 
{
	SparseMatrix sm1, sm2;
	int choice;

	do {
		cout << "\n------- Sparse Matrix Menu -------";
		cout << "\n1. Enter First Matrix";
		cout << "\n2. Enter Second Matrix";
		cout << "\n3. Display First Matrix (Sparse)";
		cout << "\n4. Display Second Matrix (Sparse)";
		cout << "\n5. Add Matrices";
		cout << "\n6. Transpose First Matrix";
		cout << "\n7. Fast Transpose First Matrix";
		cout << "\n8. Multiply Matrices";
		cout << "\n0. Exit";
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice) 
		{
			case 1:
				cout << "\nEnter First Matrix:\n";
				sm1.accept_sparsematrix();
				break;

			case 2:
				cout << "\nEnter Second Matrix:\n";
				sm2.accept_sparsematrix();
				break;

			case 3:
				cout << "\nFirst Sparse Matrix:\n";
				sm1.display_sparsematrix();
				break;

			case 4:
				cout << "\nSecond Sparse Matrix:\n";
				sm2.display_sparsematrix();
				break;

			case 5:
				cout << "\nAdding the two matrices...\n";
				sm1.addition_sparsematrix(sm2);
				break;

			case 6:
				sm1.transpose_sparsematrix();
				break;

			case 7:
				sm1.fast_transpose_sparsematrix();
				break;

			case 8:
				sm1.multiply_sparsematrix(sm2);
				break;

			case 0:
				cout << "\nExiting the program.\n";
				break;

			default:
				cout << "\nInvalid choice! Please try again.\n";
		}

	} while (choice != 0);

	return 0;
}
