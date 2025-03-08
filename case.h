#pragma once
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

void case_L(int *size, int *capacity, int ****matrix, int **row, int **col);

void case_D(int size, int *row, int *col);

void case_P(int size, int *row, int *col, int ***matrix);

void case_T(int size, int ***matrix, int *row, int *col);

void case_M(int *size, int **row, int **col, int ****matrix, int *capacity);

void case_F(int *size, int ***matrix, int *col, int *row);

void case_O(int size, int ***matrix, int *row, int *col);

void case_C(int size, int ***matrix, int *col, int *row);

void case_R(int size, int ***matrix, int *row, int *col);

void case_Q(int size, int ***matrix, int *row, int *col);

int check_command(char command);

