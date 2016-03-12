/**
 * @FUNCTION: TODO
 * @AUTHOR: Aleda(aledalee@foxmail.com)
 * @DATE: 2014/9/19
 * @VERSION: 1.0
 * @FILEIN: TODO
 * @FILEOUT: TODO
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

#include "parse_json.h"
#include "urltools.h"
#include "cJSON.h"

using namespace std;

PCONF g_pconf;

int output_usage(char* text)
{
    fprintf(stderr, "\t\tparse-json\tversion:1.0.0\n\n");
	fprintf(stderr, "\t\t\t\tDesign By Aleda(aledalee@foxmail.com | aleda.cn)\n");
	fprintf(stderr, "Usage:\n\techo \'{\"hometown\": {\"country\": \"China\", \"province\": \"Hebei\"}\'} | ./parse_json hometown/country\n");
	fprintf(stderr, "\tcat json.list | ./parse_json name\n\n");
	fprintf(stderr, "more detail for \'-h\'\n");
	if (text != NULL)
	{
		fprintf(stderr, "Error:\n");
		fprintf(stderr, "\t %s\n", text);
	}
	return -1;
}

void output_help()
{
	fprintf(stderr, "\t\t%%%HELP%%%%   Vsersion: 1.0\n\n");
	fprintf(stderr, "Please make sure that the input data is only one json data\n\n");
	fprintf(stderr, "examples:\n");
	fprintf(stderr, "\t1. echo \'{\"hometown\": {\"country\": \"China\", \"province\": \"Hebei\"}}\' | ./parse_json hometown/country\n");
	fprintf(stderr, "\t\t\"China\"\n");
	fprintf(stderr, "\t2. echo \'{\"people_id\": [1, 2, 3, 4, 5]}\' | ./parse_json people_id[2]\n");
	fprintf(stderr, "\t\t3\n");
	fprintf(stderr, "\t3. echo \'{\"peoples\": [{\"name\": \"Aleda\", \"age\": 21}]}\' | ./parse_json peoples\n");
	fprintf(stderr, "\t\t[{\"name\": \"Aleda\", \"age\": 21}]\n");
	fprintf(stderr, "\t4. echo \'{\"peoples\": [{\"name\": \"Aleda\", \"age\": 21}]}\' | ./parse_json peoples[0]\n");
	fprintf(stderr, "\t\t\"Aleda\"\n\n\n");
	fprintf(stderr, "\t\t\tAny question, please email to lishuo02@baidu.com\n");
}

int init_opt(int argc, char* argv[])
{
	char opt;
	g_pconf->file_in = DEFAULT_FILE_IN;
	g_pconf->file_out = DEFAULT_FILE_OUT;
	while ((opt = getopt(argc, argv, "h")) != -1)
	{
		switch (opt)
		{
			case 'h':
				output_help();
				break;
			default:
				break;
		}
	}
	return 1;
}

int read_json()
{
	char ch;
	int cnt = 0;
	while ((ch = fgetc(g_pconf->file_in)) != EOF)
	{
		if (cnt > MAX_JSON_DATA)
		{
			return output_usage("json_data is too long");
		}
		g_pconf->json_data[cnt++] = ch;
	}
	g_pconf->json_data[cnt] = '\0';
	return 1;
}

int init(int argc, char* argv[])
{
	if (argc == 1)
	{
		return output_usage("Please enter attributes");
	}
	init_opt(argc, argv);
	if (argv[1][0] == '-')
	{
		return 0;
	}
	g_pconf->attr_num = urltools_Split(argv[1], g_pconf->attr, '/');
	if (g_pconf->attr_num <= 0)
	{
		return output_usage("have no attr!");
	}
	if (read_json() < 0)
	{
		return 0;
	}
	return 1;
}

int str2num(const char str_num[], int* num_st, int* num_e)
{
	int str_len = strlen(str_num);
	char* str_st = (char*)malloc(str_len);
	char* str_e = (char*)malloc(str_len);
	int ind = urltools_Find(str_num, '-');
	if (ind == -1)
	{
		if (urltools_Isnummber(str_num))
		{
			*num_st = atoi(str_num);
			*num_e = *num_st;
			free(str_st);
			free(str_e);
			return 1;
		}
		else
		{
			*num_st = -1;
			*num_e = -1;
			free(str_st);
			free(str_e);
			return 0;
		}
	}
	else
	{
		if (ind == str_len)
		{
			*num_st = -1;
			*num_e = -1;
			free(str_st);
			free(str_e);
			return 0;
		}
		int _ind = urltools_Substr(str_num, str_st, '-');
		urltools_Cutstr(str_num, _ind + 1, str_len, str_e);
		if (urltools_Isnummber(str_st))
		{
			*num_st = atoi(str_st);
		}
		if (urltools_Isnummber(str_e))
		{
			*num_e = atoi(str_e);
		}
		if (num_st < num_e)
		{
			free(str_st);
			free(str_e);
			return 1;
		}
		else
		{
			*num_st = -1;
			*num_e = -1;
			free(str_st);
			free(str_e);
			return 0;
		}
	}
}

int parse()
{
	int attr_num = g_pconf->attr_num;
	queue<cJSON*> Q;
	while (!Q.empty())
	{
		Q.pop();
	}
	cJSON* obj = cJSON_Parse(g_pconf->json_data);
	if (obj == NULL)
	{
		return output_usage("json_data format is wrong!");
	}
	Q.push(obj);
	for (int i = 0; i < attr_num; i++)
	{
		int left_bracket = urltools_Find(g_pconf->attr[i], '[');
		int right_bracket = urltools_Find(g_pconf->attr[i], ']');
		int str_len = strlen(g_pconf->attr[i]);
		char* substr = (char*)malloc(str_len + 1);
		char* str_num = (char*)malloc(str_len + 1);
		//int arr_st = -1;
		//int arr_e = -1;
		int num_st;
		int num_e;
		int flag_arr = 0;
		if (left_bracket < right_bracket && left_bracket != 0)
		{
			urltools_Substr(g_pconf->attr[i], substr, '[');
			urltools_Cutstr(g_pconf->attr[i], left_bracket + 1, right_bracket - 1, str_num);
			if (str2num(str_num, &num_st, &num_e) < 0)
			{
				return output_usage("arr_num is not true!");
			}
			flag_arr = 1;
		}
		else
		{
			strncpy(substr, g_pconf->attr[i], str_len + 1);
		}
		vector<cJSON*> v_json;
		v_json.clear();
		while (!Q.empty())
		{
			cJSON* pre_json = Q.front();
			Q.pop();
			if (pre_json == NULL)
			{
				char _output[100];
				snprintf(_output, 100, "not have such attr: %s", substr);
				return output_usage(_output);
			}
			v_json.push_back(pre_json);
		}
		vector<cJSON*>::iterator it;
		for (it = v_json.begin(); it != v_json.end(); it++)
		{
			cJSON* attr_data = cJSON_GetObjectItem(*it, substr);
			if (attr_data == NULL)
			{
				return output_usage("attr is wrong!");
			}
			if (flag_arr)
			{
				for (int i = num_st; i <= num_e; i++)
				{
					cJSON* arr_item = cJSON_GetArrayItem(attr_data, i);
					if (arr_item == NULL)
					{
						return output_usage("attr nummber is wrong!");
					}
					Q.push(arr_item);
				}
			}
			else
			{
				Q.push(attr_data);
			}
			free(*it);
		}
		free(substr);
		free(str_num);
	}
	while (!Q.empty())
	{
		cJSON* json_data = Q.front();
		Q.pop();
		fprintf(g_pconf->file_out, "%s", cJSON_PrintUnformatted(json_data));
		fflush(g_pconf->file_out);
		free(json_data);
	}
	fprintf(g_pconf->file_out, "\n");
	fflush(g_pconf->file_out);
	return 1;
}

int main(int argc, char* argv[])
{
	g_pconf = (PCONF)malloc(sizeof(CONF));
	memset(g_pconf, 0, sizeof(g_pconf));
	if (init(argc, argv) > 0)
	{
		parse();
	}
	free(g_pconf);
	return 0;
}
