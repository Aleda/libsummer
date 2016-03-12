/**
 * @FUNCTION: parse_json.h
 * @AUTHOR: Aleda(lishuo02@baidu.com)
 * @DATE: 2014/9/19
 * @VERSION: 1.0
 * @FILEIN: TODO
 * @FILEOUT: TODO
*/

#ifndef _PARSE_JSON_H
#define _PARSE_JSON_H

#define BIN_NAME_LENGTH 30

#define DEFAULT_FILE_IN stdin
#define DEFAULT_FILE_OUT stdout
#define MAX_ATTRIBUTE_NUM 20
#define MAX_ATTRIBUTE_LENGTH 100
#define MAX_JSON_DATA 1000000
#define MAX_JSON_ARRAY_SIZE 10000 

typedef struct conf_t
{
	char bin_name[BIN_NAME_LENGTH];
	int attr_num;
	char* attr[MAX_ATTRIBUTE_NUM];
	char json_data[MAX_JSON_DATA];
	FILE* file_in;
	FILE* file_out;
	
}CONF, *PCONF;

int output_usage(char* text);
int init(int argc, char* argv[]);
void output_help();
int parse();
int str2num(const char str_num[], int* num_st, int* num_e);
int read_json();

#endif
