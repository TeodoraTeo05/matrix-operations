#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include "matrix.h"

int modulo(int nr)
{
	int result = nr % MODULO;

	if (result < 0)
		result += MODULO;
	return result;
}

int **alloc_matrix(int row, int col)
{
	int **matrix;
	//alocam fiecare linie
	matrix = (int **)malloc(row * sizeof(int *));
	DIE(!matrix);

	//alocam fiecarei linii un rnad de coloane
	for (int i = 0; i < row; i++) {
		matrix[i] = malloc(col * sizeof(int));
		DIE(!matrix[i]);
	}

	return matrix;
}

void read(int **matrix, int row, int col)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			scanf("%d", &matrix[i][j]);
	}
}

//eliberam mai intai liniile din matrice, dupa matricea
void free_matrix(int **matrix, int row)
{
	for (int i = 0; i < row; i++)
		free(matrix[i]);
	free(matrix);
}

int **create_transpose(int **matrix, int row, int col)
{
	int **transpose;
	transpose = alloc_matrix(col, row);

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++)
			transpose[i][j] = matrix[j][i];
	}
	return transpose;
}

int **multiply(int **matrix_1, int **matrix_2, int row_1, int row_2, int col_2)
{
	int **matrix_result;
	int row_result = row_1;
	int col_result = col_2;
	matrix_result = alloc_matrix(row_result, col_result);

	for (int i = 0; i < row_result; i++) {
		for (int j = 0; j < col_result; j++)
			matrix_result[i][j] = 0;
	}

	for (int i = 0; i < row_1; i++) {
		for (int j = 0; j < col_2; j++) {
			for (int k = 0; k < row_2; k++) {
				matrix_result[i][j] += matrix_1[i][k] * matrix_2[k][j];
				//folosim modulo pentru a impiedica overflow-ul
				matrix_result[i][j] = modulo(matrix_result[i][j]);
			}
		}
	}
	return matrix_result;
}

int summ(int **matrix, int row, int col)
{
	int sum = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			sum += matrix[i][j];
			sum = modulo(sum);
		}
	}
	return sum;
}

void swap(int ***matrix, int a, int b)
{
	int **obs = matrix[a];
	matrix[a] = matrix[b];
	matrix[b] = obs;
}

void swap_numbers(int *a, int *b)
{
	int obs = *a;
	*a = *b;
	*b = obs;
}

int **redim(int **matrix, int *row, int *col, int index)
{
	int **new_matrix;
	int nr_l;
	scanf("%d", &nr_l);
	row[index] = nr_l;
	int *lines = malloc(sizeof(int) * nr_l);
	DIE(!lines);

	for (int i = 0; i < nr_l; i++)
		scanf("%d", &lines[i]);

	int nr_c;
	scanf("%d", &nr_c);
	col[index] = nr_c;
	int *cols = malloc(sizeof(int) * nr_c);
	DIE(!col);

	for (int i = 0; i < nr_c; i++)
		scanf("%d", &cols[i]);

	new_matrix = alloc_matrix(nr_l, nr_c);
	for (int i = 0; i < nr_l; i++) {
		for (int j = 0; j < nr_c; j++)
			//ne folosim de vectorii de linii si coloane creato acum
			//pentru a lua elementele exacte din matricea noastra
			new_matrix[i][j] = matrix[lines[i]][cols[j]];
	}

	free(cols);
	free(lines);
	return new_matrix;
}

int **rise_power(int **matrix, int n, int exp)
{
	int **result = alloc_matrix(n, n);
	int **copy = alloc_matrix(n, n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; j++)
			result[i][j] = 0;
		//punem pe diagonala principala 1
		result[i][i] = 1;
	}
	//facem o copie pentru matricea data pentru a nu pierde valorile acesteia
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			copy[i][j] = matrix[i][j];

	while (exp > 0) {
		if (exp % 2 == 1) {
			int **mult_result = multiply(result, copy, n, n, n);
			free_matrix(result, n);
			result = mult_result;
		}
		int **mult_temp = multiply(copy, copy, n, n, n);
		free_matrix(copy, n);
		copy = mult_temp;
		exp /= 2;
	}

	free_matrix(copy, n);
	return result;
}
