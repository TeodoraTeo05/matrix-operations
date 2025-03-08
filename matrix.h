#pragma once
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MODULO 10007
#define DIE(condition) do { \
		if (condition) {    \
			exit(-1);       \
		}                   \
} while (0)

int modulo(int nr);

int **alloc_matrix(int row, int col);

void read(int **matrix, int row, int col);

void free_matrix(int **matrix, int row);

int **create_transpose(int **matrix, int row, int col);

int **multiply(int **matrix_1, int **matrix_2, int row_1, int row_2, int col_2);

int summ(int **matrix, int row, int col);

void swap(int ***matrix, int a, int b);

void swap_numbers(int *a, int *b);

int **redim(int **matrix, int *row, int *col, int index);

int **rise_power(int **matrix, int n, int exp);
