
#include <stdio.h>
//Input array
int read3d_float_fromfile(char *filename, float*** array, int skip_header, int index_offset);
//Output array
//float
int array2d_float_tostream(FILE *stream, float** array, int nx, int ny);
int array2d_float_tostream2(FILE* stream, float**array, int nx, int ny);
int array3d_float_tostream(FILE* stream, float***array, int nx, int ny, int nz);
int array2d_float_print(float** array, int nx, int ny);
int array2d_float_to_file(char *filename, float** array, int nx, int ny);
int array2d_float_to_file2(char *filename, float** array, int nx, int ny);
int array3d_float_to_file(char *filename, float*** array, int nx, int ny,int nz);
//int
int array2d_int_tostream(FILE *stream, int** array, int nx, int ny);
int array2d_int_tostream2(FILE* stream, int**array, int nx, int ny);
int array3d_int_tostream(FILE* stream, int***array, int nx, int ny, int nz);
int array2d_int_print(int** array, int nx, int ny);
int array2d_int_print2(int** array, int nx, int ny);
int array2d_int_to_file(char *filename, int** array, int nx, int ny);
int array2d_int_to_file2(char *filename, int** array, int nx, int ny);
int array3d_int_to_file(char *filename, int*** array, int nx, int ny,int nz);
//Allocation
int calloc2d_float(float** array, int nx, int ny);
int calloc3d_float(float**** array, int nx, int ny, int nz);
int calloc2d_int(int*** array, int nx, int ny);
int calloc3d_int(int**** array, int nx, int ny, int nz);
//Free
int free2d_float(float** array, int nx, int ny);
int free3d_float(float*** array, int nx, int ny, int nz);
int free2d_int(int** array, int nx, int ny);
int free3d_int(int*** array, int nx, int ny, int nz);
//Copy
int copy3D_float(float*** array1, float*** array2, int nx, int ny, int nz);