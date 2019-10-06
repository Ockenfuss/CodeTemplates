
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int write_log(const char* new_log_path, const char* old_log_path, const char* input_path, const char* program, const char* version)
{
    FILE* new_logfile;
    char ch; 

    if (strcmp(old_log_path,"")==0)
    {
        new_logfile=fopen(new_log_path, "w");
    }
    else if (strcmp(new_log_path,old_log_path)==0)
    {
        new_logfile = fopen(old_log_path, "a");
    }
    else
    {
        new_logfile=fopen(new_log_path, "w");
        FILE* old_logfile = fopen(old_log_path, "r");
        while((ch = fgetc(old_logfile)) != EOF)
        fputc(ch,new_logfile);
        fclose(old_logfile);
    }

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

