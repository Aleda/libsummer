/***************************************************************************
 * 
 *                      Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file smr_string.cpp
 * @author Alead(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/11 20:08:18
 * @version $Revision$ 
 * @brief 
 *  
 **/
#include <string.h>
#include <malloc.h>
#include <string>
#include <vector>
#include "smr_string.h"

int smr_split(const char str[], char* str_arr[], char separator)
{
    if (str == NULL || str_arr == NULL) {
        return -1;
    }
	int len_str = strlen(str);
	char buf[MAX_SPLIT_LEN];
	int cnt = 0;
	int pos = 0;
	for (int i = 0; i < len_str; i++)
	{
		if (str[i] == separator)
		{
			buf[pos++] = '\0';
			if (pos > MAX_SPLIT_LEN)
			{
				return -2;
			}
			str_arr[cnt] = (char*)malloc(sizeof(char) * (pos + 5));
            if (str_arr[cnt] == NULL) {
                return -1;
            }
			strncpy(str_arr[cnt++], buf, pos + 5);
			pos = 0;
		}
		else
		{
			buf[pos++] = str[i];
		}
	}
	buf[pos++] = '\0';
	if (pos > MAX_SPLIT_LEN)
	{
		return -2;
	}
	str_arr[cnt] = (char*)malloc(sizeof(char) * (pos + 5));
    if (str_arr[cnt] == NULL) {
        return -1;
    }
	strncpy(str_arr[cnt++], buf, pos + 5);
	if (cnt == 0)
	{
		return -1;
	}
	return cnt;
}

int smr_split(const char str_src[], char* str_arr_des[], const char separator_arr[])
{
    if (str_src == NULL || str_arr_des == NULL
            || separator_arr == NULL) {
        return -1;
    }
    char *p;
    p = strtok((char*)str_src, separator_arr);
    int num_count = 0;
    while (p) {
        int str_len = strlen(p);
        str_arr_des[num_count] = (char*)malloc(sizeof(char) * (str_len + 5));
        if (str_arr_des[num_count] == NULL) {
            return -1;
        }
        strncpy(str_arr_des[num_count++], p, str_len + 5);
        p = strtok(NULL, separator_arr);
    }
    return num_count;
}

int smr_split(std::string str_src, std::vector<std::string>& str_des_vec, const std::string delim)
{
    size_t pos = 0;
    int num_count = 0;
    while ((pos = str_src.find(delim)) != std::string::npos) {
        str_des_vec.push_back(str_src.substr(0, pos));
        str_src.erase(0, pos + delim.length());
        num_count++;
    }
    str_des_vec.push_back(str_src.substr(0, pos));
    num_count++;
    return num_count;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
