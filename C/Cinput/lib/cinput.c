
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.' && *end != '\\' && *end != '/') {
        --end;
    }
    if ((end > fname && *end == '.') &&
        (*(end - 1) != '\\' && *(end - 1) != '/')) {
        *end = '\0';
    }
}

int replace_extension_log(char *path, char** path_replaced)
{
    strip_ext(path);
    *path_replaced=calloc(strlen(path)+5, sizeof(char));
    strcpy(*path_replaced, path);
    strcat(*path_replaced, ".log\0");
    return 0;
}

int write_log(char* new_log_path, char* old_log_path, char* input_path, const char* program, const char* version)
{
    char* new_log_path_ext;
    replace_extension_log(new_log_path, &new_log_path_ext);

    FILE* new_logfile;
    char ch; 

    if (strcmp(old_log_path,"")==0)//no old logs
    {
        new_logfile=fopen(new_log_path_ext, "w");
    }
    else //there are old logs
    {
        char* old_log_path_ext;
        replace_extension_log(old_log_path, &old_log_path_ext);
        if (strcmp(new_log_path_ext,old_log_path_ext)==0)//old log equals new log: append old log
        {
            new_logfile = fopen(old_log_path_ext, "a");
        }
        else//normal case: copy old log to new log
        {
            new_logfile=fopen(new_log_path_ext, "w");
            FILE* old_logfile = fopen(old_log_path_ext, "r");
            while((ch = fgetc(old_logfile)) != EOF)
            fputc(ch,new_logfile);
            fclose(old_logfile);
        }
        free(old_log_path_ext);
    }
    free(new_log_path_ext);


    fprintf(new_logfile, "\n##########################################################\n");
    time_t t;   // not a primitive datatype
    time(&t);
    fprintf(new_logfile,"#%s\n#", ctime(&t));
    fputs(program, new_logfile);
    fprintf(new_logfile, "\n#VERSION ");
    fputs(version, new_logfile);
    fprintf(new_logfile, "\n#Input File: %s", input_path);

    if (strcmp(input_path,"")!=0)
    {
        FILE* input_file;
        input_file=fopen(input_path, "r");
        fputs("\n#", new_logfile);
        while((ch = fgetc(input_file)) != EOF)
        {
            fputc(ch, new_logfile);
            if(ch=='\n')
            {
                fputc('#', new_logfile);
            }
        }
        fclose(input_file);
    }
    fclose(new_logfile);

    return 0;
}

