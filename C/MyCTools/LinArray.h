#include <stdio.h>





#ifndef LINARRAY_H
#define LINARRAY_H
//=======================Type definitions==================================================================================================================
//3D
//Float
typedef struct arr3d_f{
    float* data;
    size_t nx;
    size_t ny;
    size_t nz;
    size_t stridex;
    size_t stridey;
    size_t stridez;
}arr3d_f;
//Integer
typedef struct arr3d_i{
    int* data;
    size_t nx;
    size_t ny;
    size_t nz;
    size_t stridex;
    size_t stridey;
    size_t stridez;
}arr3d_i;
//4D
//Float
typedef struct arr4d_f{
    float* data;
    size_t na;
    size_t nb;
    size_t nc;
    size_t nd;
    size_t stridea;
    size_t strideb;
    size_t stridec;
    size_t strided;
}arr4d_f;

//=======================Get and set values==================================================================================================================
//3D
//Float
float get3d_f(arr3d_f* arr, size_t x, size_t y, size_t z);
int set3d_f(arr3d_f* arr, size_t x, size_t y, size_t z, float val);
//Integer
int get3d_i(arr3d_i* arr, size_t x, size_t y, size_t z);
int set3d_i(arr3d_i* arr, size_t x, size_t y, size_t z, int val);
//4D
//Float
float get4d_f(arr4d_f* arr, size_t a, size_t b, size_t c, size_t d);
int set4d_f(arr4d_f* arr, size_t a, size_t b, size_t c, size_t d, float val);
//=======================Reading from file==================================================================================================================
//3D
//Float
int read3d_float_fromfile(const char *filename, arr3d_f* array, const int skip_header, const int index_offset);
//=======================Wrtiting and Printing==================================================================================================================
//3D
//Float
int array3d_float_to_file(char *filename, arr3d_f* array);
int array3d_float_tostream(FILE* stream, arr3d_f* array);
//Integer
int array3d_int_to_file(char *filename, arr3d_i* array);
int array3d_int_tostream(FILE* stream, arr3d_i* array);
//=======================Memory managment==================================================================================================================
//3D
//Float
arr3d_f* calloc3d_float(const size_t nx, const size_t ny, const size_t nz);
int free3d_float(arr3d_f* arr);
//Integer
arr3d_i* calloc3d_int(const size_t nx, const size_t ny, const size_t nz);
int free3d_int(arr3d_i* arr);
//4D
//Float
arr4d_f* calloc4d_float(const size_t na, const size_t nb, const size_t nc, const size_t nd);
int free4d_float(arr4d_f* arr);
//=======================Copy Array==================================================================================================================
//3D
//Float
void copy3d_f_metadata(arr3d_f* array1, arr3d_f* array2);
int copy3d_f_data(arr3d_f* array1, arr3d_f* array2);
arr3d_f* copy3d_f(arr3d_f* array1);
void copy3d_f2(arr3d_f* array1, arr3d_f* array2);




#endif /* LINARRAY_H */