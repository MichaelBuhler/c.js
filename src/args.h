#ifndef ARGS_H
#define ARGS_H

void args_init(int argc, char** argv);
char args_flag(char* name);
char args_either(char* name, char* otherName);
char* args_value(char* name);
int args_varargs(char** varargs);

#endif