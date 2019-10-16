
#include <stdio.h>
int array2d_float_tostream(FILE *stream, float** array, int nx, int ny);
int array2d_float_print(float** array, int nx, int ny);
int array2d_float_to_file(char *filename, float** array, int nx, int ny);
int array2d_int_tostream(FILE *stream, int** array, int nx, int ny);
int array2d_int_print(int** array, int nx, int ny);
int array2d_int_to_file(char *filename, int** array, int nx, int ny);
//Allocation
int calloc2d_float(float** array, int nx, int ny);
int calloc3d_float(float**** array, int nx, int ny, int nz);
int calloc2d_int(int*** array, int nx, int ny);
int calloc3d_int(int**** array, int nx, int ny, int nz);
//Free
int free2d_float(float** array, int nx);
int free3d_float(float*** array, int nx, int ny);
int free2d_int(int** array, int nx);
int free3d_int(int*** array, int nx, int ny);
