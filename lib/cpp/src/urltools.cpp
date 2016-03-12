/**
 * @FILE: urltools.cpp
 * @BRIEF: urltools
 * @VERSION: 1.0
 * @AUTHOR: Aleda(lishuo02@baidu.com)
 * @date: 2014/8/28
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/types.h>

#include "urltools.h"

int urltools_Split(const char str[], char* str_arr[], char separator)
{
	int len_str = strlen(str);
	char buf[MAX_LENGTH];
	int cnt = 0;
	int pos = 0;
	for (int i = 0; i < len_str; i++)
	{
		if (str[i] == separator)
		{
			buf[pos++] = '\0';
			if (pos > MAX_LENGTH)
			{
				return -2;
			}
			str_arr[cnt] = (char*)malloc(sizeof(char) * pos);
			strcpy(str_arr[cnt++], buf);
			pos = 0;
		}
		else
		{
			buf[pos++] = str[i];
		}
	}
	buf[pos++] = '\0';
	if (pos > MAX_LENGTH)
	{
		return -2;
	}
	str_arr[cnt] = (char*)malloc(sizeof(char) * pos);
	strcpy(str_arr[cnt++], buf);
	if (cnt == 0)
	{
		return -1;
	}
	return cnt;
}

int urltools_Urlencode(const char* str, char* result, int resultSize)
{
	int i;
	int j = 0;//for result index
	char ch;
	int strSize = strlen(str);
	if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0))
	{
		return 0;
	}
	for ( i=0; (i<strSize)&&(j<resultSize); ++i)
	{
		ch = str[i];
		if (((ch>='A') && (ch<'Z')) ||
			((ch>='a') && (ch<'z')) ||
			((ch>='0') && (ch<'9'))) 
		{
			result[j++] = ch;
		} 
		else if (ch == ' ') 
		{
			result[j++] = '+';
		} 
		else if (ch == '.' || ch == '-' || ch == '_' || 
				ch == '*' || ch == ':' || ch == '/')
		{
			result[j++] = ch;
		}
		else
		{
			if (j+3 < resultSize)
			{
				sprintf(result+j, "%%%02X", (unsigned char)ch);
				j += 3;
			}
			else
			{
				return 0;
			}
		}
	}
	result[j] = '\0';
	printf("result = %s\n", result);
	return j;
}

int urltools_Urldecode(const char* str, char *result, int resultSize)
{
	char ch,ch1,ch2;
	int i;
	int j = 0;//record result index
	
	int strSize = strlen(str);
	
	if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0))
	{
		return 0;
	}

	for ( i=0; (i<strSize) && (j<resultSize); ++i)
	{
		ch = str[i];
		switch (ch)
		{
			case '+':
				result[j++] = ' ';
				break;
			case '%':
				if (i+2<strSize)
				{
					ch1 = hex2num(str[i+1]);//高4位
					ch2 = hex2num(str[i+2]);//低4位
					if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
						result[j++] = (char)((ch1<<4) | ch2);
					i += 2;
					break;
				}
				else 
				{
					break;
				}
			default:
				result[j++] = ch;
				break;
		}
	}
	
	result[j] = 0;
	return j;
}

int hex2num(char c)
{
	if (c>='0' && c<='9') return c - '0';
	if (c>='a' && c<='z') return c - 'a' + 10;//这里+10的原因是:比如16进制的a值为10
	if (c>='A' && c<='Z') return c - 'A' + 10;

	//printf("unexpected char: %c", c);
	return NON_NUM;
}

int urltools_Find(const char str[], char item)
{
	if (str == NULL)
	{
		return -1;
	}
	int str_len = strlen(str);
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] == item)
		{
			return i;
		}
	}
	return -1;
}

int urltools_Substr(const char str[], char substr[], char item)
{
	if (str == NULL)
	{
		return -1;
	}
	int str_len = strlen(str);
	char* tmp = (char*)malloc(str_len + 1);
	int cnt = 0;
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] == item)
		{
			break;
		}
		tmp[cnt++] = str[i];
	}
	tmp[cnt] = '\0';
	if (cnt == 0)
	{
		return -1;
	}
	strncpy(substr, tmp, str_len + 1);
	free(tmp);
	return cnt;
}

int urltools_Cutstr(const char str[], int begin, int end, char* cutstr)
{
	if (str == NULL || begin > end)
	{
		return -1;
	}
	int cnt = 0;
	for (int i = begin; i <= end; i++)
	{
		cutstr[cnt++] = str[i];
	}
	cutstr[cnt] = '\0';
	return cnt;
}

int urltools_Isnummber(const char str[])
{
	int str_len = strlen(str);
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return 0;
		}
	}
	return 1;
}

long long urltools_GenId()
{
	time_t tm_t = time(NULL);
	struct tm *local = localtime(&tm_t);
	char str_md[35];
	snprintf(str_md, 35, "%d%02d%02d%02d%02d%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	srand(tm_t);
	int rand_id = rand() % 1000;
	char str_id[50];
	snprintf(str_id, 50, "%s%d", str_md, rand_id);
	long long ll_id = atol(str_id);
	return ll_id;
}

int urltools_Strncpy(char* str_dest, const char* str_src, unsigned int len)
{
	if (str_dest == NULL || str_src == NULL)
	{
		return -1;
	}
	int len_src = strlen(str_src);
	len = len_src < len ? len_src : len;
	urltools_Memcpy((void*)str_dest, (void*)str_src, len + 1);
	return 1;
}

int urltools_Memcpy(void* mem_dest, const void* mem_src, unsigned int size)
{
	if (mem_dest == NULL || mem_src == NULL)
	{
		return -1;
	}
	if (mem_dest < mem_src || (char*)mem_dest < (char*)mem_src + size)
	{
		while (size--)
		{
			*(char*)mem_dest = *(char*)mem_src;
			mem_dest = (char*)mem_dest + 1;
			mem_src = (char*)mem_src + 1;
		}
	}
	else
	{
		mem_dest = (char*)mem_dest + size - 1;
		mem_src = (char*)mem_src + size - 1;
		while (size--)
		{
			*(char*)mem_dest = *(char*)mem_src;
			mem_dest = (char*)mem_dest - 1;
			mem_src = (char*)mem_src - 1;
		}
	}
}

size_t callback_get_data(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct memory_t *mem = (struct memory_t *)userp;
	
	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL)
	{
		/* out of memory! */ 
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

int urltools_CurlUrl(const char* url, char** page)
{
	struct memory_t chunk;
	
	// chunk initialization
	chunk.memory = (char*)malloc(1);
	chunk.size = 0;

	CURL* curl = curl_easy_init();
	CURLcode res = CURLE_OK;
	
	if (curl != NULL)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); /**设置多线程的*/
		
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if (res == CURLE_OK)
	{
		*page = (char*)chunk.memory;
		return 1;
	}
	return -1;
}

int urltools_GetTimeNow(char** str_time)
{
	time_t t_time;
	time(&t_time);
	char* _time = (char*)malloc(128);
	memset(_time, 0, sizeof(_time));
	strftime(_time, 128, "%Y/%m/%d %H:%M:%S", localtime(&t_time));
	printf("_time = %s\n", _time);
	*str_time = _time;
}


