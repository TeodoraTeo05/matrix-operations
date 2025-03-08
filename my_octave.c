#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include "matrix.h"
#include "case.h"

int main(void)
{
	char command;
	//capacity reprezinta cate locuri sunt disponibile pentru matrici
	//size reprezinta locul in care am ajuns cu matricile puse
	int capacity = 1, size = 0;
	int ***matrix_vector, end = 1;
	int *row_vector, *col_vector;

	//aloc dinamic un vector care retine liniile fiecarei matrici
	row_vector = malloc(sizeof(int) * capacity);
	DIE(!row_vector);
	//aloc dinamic un vector care retine coloanele fiecarei matrici
	col_vector = malloc(sizeof(int) * capacity);
	DIE(!col_vector);
	//aloc dinamic un vector de vector pentru matrici
	matrix_vector = (int ***)malloc(sizeof(int **) * capacity);
	DIE(!matrix_vector);
	while (end) {
		command = getchar();
		switch (command) {
		case 'L':
			case_L(&size, &capacity, &matrix_vector, &row_vector, &col_vector);
			break;
		case 'D':
			case_D(size, row_vector, col_vector);
			break;
		case 'P':
			case_P(size, row_vector, col_vector, matrix_vector);
			break;
		case 'T':
			case_T(size, matrix_vector, row_vector, col_vector);
			break;
		case 'M':
			case_M(&size, &row_vector, &col_vector, &matrix_vector, &capacity);
			break;
		case 'F':
			case_F(&size, matrix_vector, col_vector, row_vector);
			break;
		case 'O':
			case_O(size, matrix_vector, row_vector, col_vector);
			break;
		case 'C':
			case_C(size, matrix_vector, col_vector, row_vector);
			break;
		case 'R':
			case_R(size, matrix_vector, row_vector, col_vector);
			break;
		case 'Q':
			case_Q(size, matrix_vector, row_vector, col_vector);
			end = 0;
			break;
		}
		if (check_command(command) == 0)
			printf("Unrecognized command\n");
	}
	return 0;
}
