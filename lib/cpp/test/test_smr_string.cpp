/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file test_smr_string.cpp
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/11 23:25:54
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

#include "smr_string.h"

int main(int argc, char* argv[])
{
    char str_src[] = "w,s,s,s,s,s,,,,qweasdasda,a,,,asd,./asd./asdsadas./asdasd";
    char* str_arr[100];
    char sep = ',';
    char sep_arr[10] = "./";
    int n = smr_split((const char*)str_src, str_arr, sep);
    std::cout << "n = " << n << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << str_arr[i] << std::endl;
        if (str_arr[i] != NULL)
            free(str_arr[i]);
    }
    memset(str_arr, 0, sizeof(str_arr));
    int m = smr_split((const char*)str_src, str_arr, (const char*)sep_arr);
    std::cout << "m = " << m << std::endl;
    for (int i = 0; i < m; i++) {
        std::cout << str_arr[i] << std::endl;
        if (str_arr[i] != NULL)
            free(str_arr[i]);
    }
    std::string str_src_ = "wasd,/.asd,/.asd,/.asd,asd,asd";
    std::string delim = ",/.";
    std::vector<std::string> str_arr_des_;
    int c = smr_split(str_src_, str_arr_des_, delim);
    std::cout << "c = " << c << std::endl;
    for (int i = 0; i < c; i++) {
        std::cout << str_arr_des_[i] << std::endl;
    }
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
