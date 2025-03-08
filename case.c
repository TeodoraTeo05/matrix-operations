#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include "case.h"
#include "matrix.h"

void case_L(int *size, int *capacity, int ****matrix, int **row, int **col)
{
	//daca am atins capacitatea maxima, o dublam
	if ((*size) == (*capacity)) {
		(*capacity) *= 2;
		*matrix = (int ***)realloc((*matrix), sizeof(int **) * (*capacity));
		DIE(!matrix);

		*row = realloc((*row), sizeof(int) * (*capacity));
		DIE(!row);

		*col = realloc((*col), sizeof(int) * (*capacity));
		DIE(!col);
	}

	int row_new, col_new;
	scanf("%d%d", &row_new, &col_new);

	//alocam in urmatorul loc matricea, liniile si coloanele acesteia
	(*matrix)[(*size)] = alloc_matrix(row_new, col_new);
	(*row)[(*size)] = row_new;
	(*col)[(*size)] = col_new;

	read((*matrix)[(*size)], row_new, col_new);
	(*size)++;
}

void case_D(int size, int *row, int *col)
{
	int index;
	scanf("%d", &index);

	if (0 <= index && index < size)
		printf("%d %d\n", row[index], col[index]);
	else
		printf("No matrix with the given index\n");
}

void case_P(int size, int *row, int *col, int ***matrix)
{
	int index;
	scanf("%d", &index);

	if (0 <= index && index < size) {
		for (int i = 0; i < row[index]; i++) {
			for (int j = 0; j < col[index]; ++j)
				printf("%d ", matrix[index][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void case_T(int size, int ***matrix, int *row, int *col)
{
	int index;
	scanf("%d", &index);

	if (0 <= index && index < size) {
		int **transpose;
		transpose = create_transpose(matrix[index], row[index], col[index]);
		//eliberam matricea de la inceput si o inlocuim cu transpusa ei
		free_matrix(matrix[index], row[index]);
		matrix[index] = transpose;

		//inversam numarul de linii si de coloane pentru a corespunde
		//cu noua matrice
		int obs = row[index];
		row[index] = col[index];
		col[index] = obs;
	} else {
		printf("No matrix with the given index\n");
	}
}

void case_M(int *size, int **row, int **col, int ****matrix, int *capacity)
{
	int index, index1;
	scanf("%d %d", &index, &index1);

	//verificam conditiile
	if ((0 > index || index >= (*size)) || (0 > index1 || index1 >= (*size))) {
		printf("No matrix with the given index\n");
	} else if ((*col)[index] != (*row)[index1]) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		int **multiply_matrix;
		multiply_matrix = multiply((*matrix)[index], (*matrix)[index1],
								   (*row)[index], (*row)[index1],
								   (*col)[index1]);
		//verificam cazul in care am ajuns la capacitatea maxima,
		//deoarece schimbarea nu se face in-place, iar matricea calculata
		//se va adauga la sfarsitul vectorului de matrici
		if ((*size) == (*capacity)) {
			*capacity = (*capacity) * 2;
			*matrix = realloc((*matrix), sizeof(int **) * (*capacity));
			*row = realloc((*row), sizeof(int) * (*capacity));
			*col = realloc((*col), sizeof(int) * (*capacity));
		}
		(*matrix)[(*size)] = multiply_matrix;
		(*row)[(*size)] = (*row)[index];
		(*col)[(*size)] = (*col)[index1];
		(*size)++;
	}
}

void case_F(int *size, int ***matrix, int *col, int *row)
{
	int index;
	scanf("%d", &index);

	if (0 <= index && index < (*size)) {
		//se elibereaza matricea dorita
		free_matrix(matrix[index], row[index]);

		//se muta toate valorile liniilor si coloanelor cu o pozitie la stanga
		for (int i = index; i < (*size) - 1; i++)
			row[i] = row[i + 1];

		for (int i = index; i < (*size) - 1; i++)
			col[i] = col[i + 1];

		//se inverseaza matricile una cate una pana la final si se scade
		//size-ul lor cu 1
		for (int i = index; i < (*size) - 1; i++)
			swap(matrix, i, i + 1);

		(*size)--;
	} else {
		printf("No matrix with the given index\n");
	}
}

void case_O(int size, int ***matrix, int *row, int *col)
{
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			//se aplica functia summ pentru a compara suma
			if (summ(matrix[i], row[i], col[i])
					> summ(matrix[j], row[j], col[j])) {
				//se inverseaza matricele care respecta conditiile, la fel
				//si liniile si coloanele
				swap(matrix, i, j);
				swap_numbers(&row[i], &row[j]);
				swap_numbers(&col[i], &col[j]);
			}
		}
	}
}

void case_C(int size, int ***matrix, int *col, int *row)
{
	int index, aux;
	scanf("%d", &index);

	if (0 <= index && index < size) {
		//se face o copie a valorii liniei, pentru a nu pierde valoarea
		aux = row[index];
		int **matrix_redim = redim(matrix[index], row, col, index);
		free_matrix(matrix[index], aux);
		matrix[index] = matrix_redim;
	} else {
		printf("No matrix with the given index\n");
	}
}

void case_R(int size, int ***matrix, int *row, int *col)
{
	int index, exp;
	scanf("%d%d", &index, &exp);

	//se verifica conditiile
	if (0 <= index && index < size) {
		if (exp < 0) {
			printf("Power should be positive\n");

		} else if (row[index] != col[index]) {
			printf("Cannot perform matrix multiplication\n");

		} else {
			int **log_matrix = rise_power(matrix[index], row[index], exp);
			free_matrix(matrix[index], row[index]);
			matrix[index] = log_matrix;
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void case_Q(int size, int ***matrix, int *row, int *col)
{
	for (int i = size - 1; i >= 0; i--)
		free_matrix(matrix[i], row[i]);

	free(matrix);
	free(col);
	free(row);
}

int check_command(char command)
{
	char commands[] = "LDPTMFOCRQ";
	int nr_comenzi = strlen(commands);

	for (int i = 0; i < nr_comenzi; i++) {
		if (command == commands[i])
			return 1;
	}
	//pentru cazurile in care caracterele primite sunt cifre sau spatii
	if (command >= 'A' && command <= 'Z')
		return 0;
	else
		return 1;
}
