/*

 * @FILE: urltools.h
 * @BRIEF: urltools
 * @VERSION: 1.0
 * @AUTHOR: Aleda(lishuo02@baidu.com)
 * @date: 2014/8/28
 */
#pragma once

#ifndef _URLTOOLS_H
#define _URLTOOLS_H

#define MAX_LENGTH 500
#define MAX_URLENCODE_LENGTH 500
#define NON_NUM '0'

/**
 * @return -1:don't have; -2:OOM >0:number
 * @param 
 * @must do: free str_arr when finished;
 */
int urltools_Split(const char str[], char* str_arr[], char separator);
int urltools_Urlencode(const char str_src[], char* str_res, int resultSize);
int urltools_Urldecode(const char str_src[], char* str_res, int resultSize);
int urltools_Find(const char str[], char item);
int urltools_Substr(const char str[], char sub_str[], char item);
int urltools_Cutstr(const char str[], int begin, int end, char* cutstr);
int hex2num(char c);
int urltools_Isnummber(const char str[]);

/**
 * @brief: generate a task_id, rely on time
 * 
 * @param: NULL
 *
 * @retval: ID(long long)
 */
long long urltools_GenId();


/**
 * @brief: safe strnpy 
 *
 * @param: str_dest: omitting
 *         str_src: omitting
 *
 * @retval: -1: error
 *           1: true
 */
int urltools_Strncpy(char* str_dest, const char* str_src, unsigned int len);
int urltools_Memcpy(void* mem_dest, const void* mem_src, unsigned int len);


struct memory_t
{
	char* memory;
	size_t size;
};

/**
 *
 * @brief: curl url
 *
 * @param: 1) url: the url that you want to be curl(to ensure legality)
 *         2) page: the page caught back
 *
 * @retval: 1) -1: error
 *          2)  1: true
 */
int urltools_CurlUrl(const char* url, char** page);
size_t callback_get_data(void *ptr, size_t size, size_t nmemb, void *userp);

/**
 *
 * @breif: get time by format: 2014/09/28 15:50:21
 *
 * @param: 1) the variable that storage time
 *
 * @retval: 1) -1: error
 *          2)  1: true
 */
int urltools_GetTimeNow(char** str_time);

#endif 
