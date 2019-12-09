#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief Read a float array from a given string
 * 
 * @param str The string
 * @param delim String containing all delimiter characters
 * @param val Float array
 * @param n_val Number of floats to read
 * @return int 
 */
int readstring_f(char* str, char* delim, float* val, const size_t n_val)
{
    int length=strlen(str)+1;//strlen does not count \0!
    char* str_cp=malloc(length*sizeof(char));
    strcpy(str_cp, str);
    // char *token = NULL;

    int count=0;
    for (char* token = strtok(str_cp, delim); token != NULL; token = strtok(NULL, delim))
    {
        char *unconverted;
        val[count] = strtof(token, &unconverted);
        // if (!isspace(*unconverted) && *unconverted != 0)
        // {
        //     return -1;
        // }
        count++;
    }
    free(str_cp);
    return 0;
}

char* readline_file(const char *filename, int line_number)
{
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Could not open %s!\n", filename);
        return NULL;
    }
    int nRet;
    int line_count = 0;
    size_t t = 0;
    char *gptr = NULL;
    while ((nRet = getline(&gptr, &t, fp)) > 0)
    {
        line_count++;
        if (line_count == line_number)
        {
            return gptr;
        }
    }
    fclose(fp);
    return NULL;
}
