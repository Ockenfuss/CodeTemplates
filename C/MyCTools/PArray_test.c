
#include "PArray.h"

int main()
{
}

int test_3d_io()
{
    char* filename="Test.inp";
    float*** array;
    calloc3d_float(&array, 10,10,10);
    read3d_float_fromfile(filename, array, 1);
    array2d_float_print(array[2],10,10);
    array3d_float_to_file("Test2.out", array,10,10,10);
}