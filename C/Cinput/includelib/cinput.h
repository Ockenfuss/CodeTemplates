
void strip_ext(char *fname);
int replace_extension_log(char *path, char** path_replaced);
int write_log(char* new_log_path, char* old_log_path, char* input_path, const char* program, const char* version);