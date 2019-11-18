#include <stdio.h>
#include <stdlib.h>
#include "LinArray.h"

char* VERSION="1.0.0";



//=======================Reading from file==================================================================================================================
/**
 * @brief File has to be formatted as "x y z value"
 * 
 * @param filename 
 * @param array 
 * @param skip_header number of lines to be skipped in the beginning
 * @param index_offset Number to be added to every index in the file before reading (usually 0 or 1)
 * @return int 
 */
int read3d_float_fromfile(const char *filename, arr3d_f* array, const int skip_header, const int index_offset)
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
        set3d_f(array,i1+index_offset,i2+index_offset,i3+index_offset,f1);
    }
    // fputs(*gptr,stdout);
   }
   fclose(fp);
  return 0;
}
//=======================Get and set values==================================================================================================================
//3D
//Float
float get3d_f(const arr3d_f* arr, const size_t x, const size_t y, const size_t z)
{
    return arr->data[arr->stridex*x+arr->stridey*y+arr->stridez*z];
}
int set3d_f(arr3d_f* arr, const size_t x, const size_t y, const size_t z, const float val)
{
    arr->data[arr->stridex*x+arr->stridey*y+arr->stridez*z]=val;
    return 0;
}
//Integer
int get3d_i(const arr3d_i* arr, const size_t x, const size_t y, const size_t z)
{
    return arr->data[arr->stridex*x+arr->stridey*y+arr->stridez*z];
}
int set3d_i(arr3d_i* arr, const size_t x, const size_t y, const size_t z, const int val)
{
    arr->data[arr->stridex*x+arr->stridey*y+arr->stridez*z]=val;
    return 0;
}

//4D
//Float
float get4d_f(const arr4d_f* arr, const size_t a, const size_t b, const size_t c, const size_t d)
{
    return arr->data[arr->stridea*a+arr->strideb*b+arr->stridec*c+arr->strided*d];
}
int set4d_f(arr4d_f* arr, const size_t a, const size_t b, const size_t c, const size_t d, const float val)
{
    arr->data[arr->stridea*a+arr->strideb*b+arr->stridec*c+arr->strided*d]=val;
    return 0;
}

//=======================Wrtiting and Printing==================================================================================================================
//3D
//Float
int array3d_float_to_file(char *filename, arr3d_f* array)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_float_tostream(fp, array);
    fclose(fp);
    return 0;
}

/**
 * @brief  Write 3d float array to file using one based indices
 * @note   
 * @param  *filename: The file to write in. Will be overwritten if existing.
 * @param  array: the array to write to the specified file
 * @retval 
 */
int array3d_float_to_file1(char *filename, arr3d_f* array)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_float_tostream1(fp, array);
    fclose(fp);
    return 0;
}


int array3d_float_tostream(FILE* stream, arr3d_f* array)
{
    for (int i = 0; i < array->nx; i++)
    {
        for (int j = 0; j < array->ny; j++)
        {
            for (int k = 0; k < array->nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%e\n",i,j,k,get3d_f(array, i,j,k));
            }
        }
    }
    return 0;
}

/**
 * @brief  Write 3d float array to stream with one-based indices
 * @note   
 * @param  stream: IO-stream to write
 * @param  array: the array to write to the stream
 * @retval 0 if success
 */
int array3d_float_tostream1(FILE* stream, arr3d_f* array)
{
    for (int i = 0; i < array->nx; i++)
    {
        for (int j = 0; j < array->ny; j++)
        {
            for (int k = 0; k < array->nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%e\n",i+1,j+1,k+1,get3d_f(array, i,j,k));
            }
        }
    }
    return 0;
}
//Integer
int array3d_int_to_file(char *filename, arr3d_i* array)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_int_tostream(fp, array);
    fclose(fp);
    return 0;
}

/**
 * @brief  Write 3d int array to file using one based indices
 * @note   
 * @param  *filename: The file to write in. Will be overwritten if existing.
 * @param  array: the array to write to the specified file
 * @retval 
 */
int array3d_int_to_file1(char *filename, arr3d_i* array)
{
    FILE *fp;
    if ( (fp = fopen(filename,"w")) == NULL) {
        fprintf(stderr, "Could not open %s!\n", filename);
        return -1;
    }
    array3d_int_tostream1(fp, array);
    fclose(fp);
    return 0;
}

int array3d_int_tostream(FILE* stream, arr3d_i* array)
{
    for (int i = 0; i < array->nx; i++)
    {
        for (int j = 0; j < array->ny; j++)
        {
            for (int k = 0; k < array->nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%d\n",i,j,k,get3d_i(array, i,j,k));
            }
        }
    }
    return 0;
}
/**
 * @brief  Write 3d int array to stream with one-based indices
 * @note   
 * @param  stream: IO-stream to write
 * @param  array: the array to write to the stream
 * @retval 0 if success
 */
int array3d_int_tostream1(FILE* stream, arr3d_i* array)
{
    for (int i = 0; i < array->nx; i++)
    {
        for (int j = 0; j < array->ny; j++)
        {
            for (int k = 0; k < array->nz; k++)
            {
                fprintf(stream, "%d\t%d\t%d\t%d\n",i+1,j+1,k+1,get3d_i(array, i,j,k));
            }
        }
    }
    return 0;
}

//=======================Memory managment==================================================================================================================
//3D
//Float
arr3d_f* calloc3d_float(const size_t nx, const size_t ny, const size_t nz)
{
    arr3d_f* arr;
    arr=malloc(sizeof(arr3d_f));
    arr->nx=nx;
    arr->ny=ny;
    arr->nz=nz;
    arr->data=(float*)calloc(nx*ny*nz, sizeof(float));
    arr->stridez=1;
    arr->stridey=arr->stridez*nz;
    arr->stridex=arr->stridey*ny;
    return arr;
}

int free3d_float(arr3d_f* arr)
{
    return 0;
    free(arr->data);
}
//Integer
arr3d_i* calloc3d_int(const size_t nx, const size_t ny, const size_t nz)
{
    arr3d_i* arr;
    arr=malloc(sizeof(arr3d_i));
    arr->nx=nx;
    arr->ny=ny;
    arr->nz=nz;
    arr->data=(int*)calloc(nx*ny*nz, sizeof(int));
    arr->stridez=1;
    arr->stridey=arr->stridez*nz;
    arr->stridex=arr->stridey*ny;
    return arr;
}

int free3d_int(arr3d_i* arr)
{
    return 0;
    free(arr->data);
}
//4D
//Float
arr4d_f* calloc4d_float(const size_t na, const size_t nb, const size_t nc, const size_t nd)
{
    arr4d_f* arr;
    arr=malloc(sizeof(arr4d_f));
    arr->na=na;
    arr->nb=nb;
    arr->nc=nc;
    arr->nd=nd;
    arr->data=(float*)calloc(na*nb*nc*nd, sizeof(float));
    arr->strided=1;
    arr->stridec=arr->strided*nd;
    arr->strideb=arr->stridec*nc;
    arr->stridea=arr->strideb*nb;
    return arr;
}

int free4d_float(arr4d_f* arr)
{
    return 0;
    free(arr->data);
}

//=======================Copy Array==================================================================================================================
//3D
//Float
void copy3d_f_metadata(arr3d_f* array1, arr3d_f* array2)
{
    array2->nx=array1->nx;
    array2->ny=array1->ny;
    array2->nz=array1->nz;
    array2->stridex=array1->stridex;
    array2->stridey=array1->stridey;
    array2->stridez=array1->stridez;
}
int copy3d_f_data(arr3d_f* array1, arr3d_f* array2)
{
    int size=(array1->nx)*(array1->ny)*(array1->nz);
    int count=0;
    while(count<size)
    {
        array2->data[count]=array1->data[count];
        count++;
    }
    return 0;
}

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
arr3d_f* copy3d_f(arr3d_f* array1)
{
    arr3d_f* array2=calloc3d_float(array1->nx, array1->ny, array1->nz);
    copy3d_f_metadata(array1, array2);
    copy3d_f_data(array1, array2);
    return array2;
}
void copy3d_f2(arr3d_f* array1, arr3d_f* array2)
{
    copy3d_f_metadata(array1, array2);
    copy3d_f_data(array1, array2);
}
