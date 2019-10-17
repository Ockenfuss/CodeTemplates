




#include <stdio.h>
#include <stdlib.h>

char* VERSION="1.0.0";
//=====================================================================Input===============================================================
//Read array from file

/**
 * @brief File has to be formatted as "x y z value"
 * 
 * @param filename 
 * @param array 
 * @param skip_header 
 * @return int 
 */
int read3d_float_fromfile(char *filename, float*** array, int skip_header)
{
    FILE *fp;
   if ( (fp = fopen(filename,"r")) == NULL) {
      fprintf(stderr, "Could not open %s!\n", filename);
      return -1;
   }
   int nRet;
   int line_count=0;
   size_t *t = malloc(0);

   char **gptr = malloc(sizeof(char*));
   *gptr = NULL;

    int i1, i2, i3;
    float f1;
   while( (nRet=getline(gptr, t, fp)) > 0)
   {
    line_count++;
    if(line_count>skip_header)
    {
        sscanf(*gptr, "%d %d %d %e", &i1, &i2, &i3, &f1);
        array[i1][i2][i3]=f1;
    }
    // fputs(*gptr,stdout);
   }
  return 0;
}

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

int array3d_float_tostream(FILE* stream, float***array, int nx, int ny, int nz)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%e\n",i,j,k,array[i][j][k]);
            }
        }
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

int array3d_float_to_file(char *filename, float*** array, int nx, int ny,int nz)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_float_tostream(fp, array, nx, ny,nz);
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

int array2d_int_tostream2(FILE* stream, int**array, int nx, int ny)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            fprintf(stream, "%d\t%d\t%d\n",i,j,array[i][j]);
        }
    }
    return 0;
}


int array3d_int_tostream(FILE* stream, int***array, int nx, int ny, int nz)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%d\n",i,j,k,array[i][j][k]);
            }
        }
    }
    return 0;
}

int array2d_int_print(int** array, int nx, int ny)
{
    array2d_int_tostream(stdout, array, nx, ny);
    return 0;
}
int array2d_int_print2(int** array, int nx, int ny)
{
    array2d_int_tostream2(stdout, array, nx, ny);
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
int array2d_int_to_file2(char *filename, int** array, int nx, int ny)
{
    FILE *fp;
    fp=fopen(filename, "w+");  // "a+": append, "w+": delete old file
    array2d_int_tostream2(fp, array, nx, ny);
    fclose(fp);
    return 0;
}

int array3d_int_to_file(char *filename, int*** array, int nx, int ny,int nz)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_int_tostream(fp, array, nx, ny,nz);
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

// Attempt to construct a generic function.
// int calloc_nd(void* array, int dim, int* size, int sizeof_type)
// {
//     if(dim>1)
//     {
//         array=malloc(size[dim-1]*sizeof(void*));
//         for (int i = 0; i < size[dim-1]; i++)
//         {
//             calloc_nd((void*)*array, dim-1, size, sizeof_type);
//         }
//     }
//     else if(dim==1)
//     {
//         array=malloc(size[0]*sizeof_type);
//     }
//     else
//     {
//         return -1;
//     }
    
//     return 0;
// }

//Free functions
int free2d_float(float** array, int nx, int ny)
{
    for (int i = 0; i < nx; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}
int free3d_float(float*** array, int nx, int ny, int nz)
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
int free2d_int(int** array, int nx, int ny)
{
    for (int i = 0; i < nx; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}
int free3d_int(int*** array, int nx, int ny, int nz)
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

//=================================================Copy array==============================================================================
/**
 * @brief Copy array1 to array2
 * 
 * @param array1 
 * @param array2 
 * @param nx 
 * @param ny 
 * @param nz 
 * @return int 
 */
int copy3D_float(float*** array1, float*** array2, int nx, int ny, int nz)
{
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                array2[i][j][k]=array1[i][j][k];
            }
            
        }
    }
    return 0;
}