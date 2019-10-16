




#include <stdio.h>
#include <stdlib.h>

char* VERSION="1.0.0";
//=========================================================================================================================================
//Printing and saving of arrays
//float
int array2d_float_tostream(FILE *stream, float** array, int nx, int ny)
{
    for(int i=0; i<nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            fprintf(stream, "%.6f\t",array[i][j]);
        }
        fprintf(stream, "\n");
    }
    return 0;
}

int array2d_float_print(float** array, int nx, int ny)
{
    array2d_float_tostream(stdout, array, nx, ny);
    return 0;
}


int array2d_float_to_file(char *filename, float** array, int nx, int ny)
{
    FILE *fp;
    fp=fopen(filename, "w+");  // "a+": append, "w+": delete old file
    array2d_float_tostream(fp, array, nx, ny);
    fclose(fp);
    return 0;
}

//integer
int array2d_int_tostream(FILE *stream, int** array, int nx, int ny)
{
    for(int i=0; i<nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            fprintf(stream, "%d\t",array[i][j]);
        }
        fprintf(stream, "\n");
    }
    return 0;
}

int array2d_int_print(int** array, int nx, int ny)
{
    array2d_int_tostream(stdout, array, nx, ny);
    return 0;
}


int array2d_int_to_file(char *filename, int** array, int nx, int ny)
{
    FILE *fp;
    fp=fopen(filename, "w+");  // "a+": append, "w+": delete old file
    array2d_int_tostream(fp, array, nx, ny);
    fclose(fp);
    return 0;
}




//=========================================================================================================================================
//Allocation functions
int calloc2d_float(float*** array, int nx, int ny)
{
    (*array)=calloc(nx, sizeof(float*));
    for (int i = 0; i < nx; i++)
    {
        (*array)[i]=calloc(ny, sizeof(float));
    }
    return 0;
}

int calloc3d_float(float**** array, int nx, int ny, int nz)
{
    *array=calloc(nx, sizeof(float**));
    for (int i = 0; i < nx; i++)
    {
        (*array)[i]=calloc(ny, sizeof(float*));
        for (int j = 0; j < ny; j++)
        {
            (*array)[i][j]=calloc(nz, sizeof(float));
        }
    }
    return 0;
}
int calloc2d_int(int*** array, int nx, int ny)
{
    (*array)=calloc(nx, sizeof(int*));
    for (int i = 0; i < nx; i++)
    {
        (*array)[i]=calloc(ny, sizeof(int));
    }
    return 0;
}

int calloc3d_int(int**** array, int nx, int ny, int nz)
{
    *array=calloc(nx, sizeof(int**));
    for (int i = 0; i < nx; i++)
    {
        (*array)[i]=calloc(ny, sizeof(int*));
        for (int j = 0; j < ny; j++)
        {
            (*array)[i][j]=calloc(nz, sizeof(int));
        }
    }
    return 0;
}

//Free functions
int free2d_float(float** array, int nx)
{
    for (int i = 0; i < nx; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}
int free3d_float(float*** array, int nx, int ny)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
    return 0;
}
int free2d_int(int** array, int nx)
{
    for (int i = 0; i < nx; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}
int free3d_int(int*** array, int nx, int ny)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
    return 0;
}