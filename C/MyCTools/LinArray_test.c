#include <LinArray.h>

int test_3darr_f();

int main()
{
    test_3darr_f();
}

int test_3darr_f()
{
    arr3d_f test;
    calloc_3darr_f(&test, 3,3,3);
    set3d_f(&test, 1,1,1,0.1);
    printf("%.4f\n", get3d_f(&test, 1,1,1));
}