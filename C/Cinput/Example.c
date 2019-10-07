/**
 * @file Example.c
 * @author Paul Ockenfuß
 * @brief Example on how to parse an input file and create logs.
 * @version 1.0.0
 * @date 2019-10-06
 * This example program parses a simple input file and uses it to read data from
 * another file (Data1.dat) and write results to another file (Data2.dat).
 * Alongside, the process is logged by creating a logfile (Data2.log).
 * @copyright Copyright (c) 2019
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includelib/ini.h"
#include "includelib/cinput.h"
#include "includelib/ascii.h"

const char* version="1.0.0";

typedef struct
{
    int option2;
    const char* option1;
    char* data;
    char* save;
} configuration;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("default", "option2")) {
        pconfig->option2 = atoi(value);
    } else if (MATCH("default", "option1")) {
        pconfig->option1 = strdup(value);
    } else if (MATCH("default", "data")) {
        pconfig->data = strdup(value);
    } else if (MATCH("default", "save")) {
        pconfig->save = strdup(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    configuration config;

    if (ini_parse("Example.ini", handler, &config) < 0) {
        printf("Can't load 'Example.ini'\n");
        return 1;
    }
    printf("Config loaded from 'Example.ini': version=%d, name=%s, email=%s\n",
        config.option2, config.data, config.save);
    double* data;
    int length;
    read_1c_file(config.data,&data, &length);
    FILE* result;
    result=fopen(config.save, "w");
    for (int i=0; i<length; i++)
    {
        data[i]=data[i]+(double)config.option2;
        fprintf(result, "%.4f\n",data[i]);
    }
    fclose(result);

    write_log(config.save, config.data, "Example.ini", "Example.c", version);
    
    return 0;
}
