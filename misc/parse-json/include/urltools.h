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


#endif 
