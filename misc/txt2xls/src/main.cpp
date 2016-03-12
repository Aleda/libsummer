/**
 * @file main.cpp
 * @author Aleda(lishuo02@baidu.com || aleda.cn)
 * @date 2015/03/11 14:14:28
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <signal.h> 
#include <unistd.h> 
#include <getopt.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "excel.h"
#include "smr_lib.h"
#include "xlslib.h"


const std::string ___VERSION___ = "1.0.0";
const std::string AUTHOR  = "Aleda(lishuo02@baidu.com | aleda.cn)";


std::string g_delimeter = "\t";
std::string g_filename  = "";

struct option opts[] = {
    {"delimeter", required_argument, NULL, 'd'},
    {"help",      no_argument,       NULL, 'h'},
    {"version",   no_argument,       NULL, 'v'},
    {"output",    no_argument,       NULL, 'o'}
};

void show_version()
{
    std::cout << "\t\ttxt2xls v" << ___VERSION___ << std::endl;
    std::cout << "\t\t\t" << AUTHOR << "\n" << std::endl;
    exit(0);
} 

void show_usage()
{
    std::cout << "\t\t\ttxt2xls v" << ___VERSION___ << "\n" << std::endl;
    std::cout << "\t\t\t\t" << AUTHOR << "\n" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t[-d | --delimeter]\tthe delimeter of the txt for split, default: tab" << std::endl;
    std::cout << "\t[-o | --output   ]\tthe output file name, default: timestamp" << std::endl;
    std::cout << "\t[-v | --version  ]\tshow the version" << std::endl;
    std::cout << "\t[-h | --help     ]\tshow the help\n" << std::endl;
    std::cout << "\t[NOTICE:] stdin must be utf-8\n" << std::endl;
    std::cout << "\tAny Question Please Contact Aleda(lishuo02@baidu.com | aleda.cn)\n" << std::endl;
    exit(0);
}

void covert_opt(int argc, char* argv[])
{
    char opt;
    while ((opt=getopt_long(argc, argv, "d:o:hv", opts, NULL)) != -1) {
        switch (opt) {
        case 'd':
            if (strlen(optarg) > 0) {
                g_delimeter = optarg;
            }
            break;
        case 'o':
            if (strlen(optarg) > 0) {
                g_filename = optarg;
            }
            break;
        case 'h':
            show_usage();
            break;
        case 'v':
            show_version();
            break;
        default:
            break;
        }
    }
}

void gen_file_name()
{
    if (g_filename.compare("") == 0) {
        long long random_id = smr_gen_random_id();
        std::stringstream str_s;
        str_s << random_id << ".xls";
        str_s >> g_filename;
    }
}

int main(int argc, char* argv[])
{
    covert_opt(argc, argv);
    gen_file_name();
    Excel excel;
    // 创建一个worksheet
    excel.CreateWorkSheet("sheet1");
    // 设置默认的行高和列宽
    //excel.set_default_rowheight(15);
    //excel.set_default_colwidth(18);

    std::string line;
    int num_row = 0;
    int speed = 0;
    std::cerr << "[INFO]begin generate the excel" << std::endl;
    // 加上进度条显示
    progress_t bar;
    smr_progress_init(&bar, "", 100, PROGRESS_CHR_STYLE);
    int progress_num = 1;
    while (std::getline(std::cin, line).good())
    {
        vector<std::string> str_arr_des;
        int n = smr_split(line, str_arr_des, g_delimeter);
        for (int i = 0; i < n; i++) {
            excel.SetCellText(num_row, i, str_arr_des[i]);
            if (i % 2 == 0) {
                excel.SetCellBgColor(num_row, i, CLR_TEAL);
                excel.SetCellBorder(num_row, i);
            } 
        }
        str_arr_des.clear();
        num_row++;
        if (num_row % 1000 == 0 && progress_num < 90) {
            smr_progress_show(&bar, progress_num++ / 100.0f);
        }
    }
    smr_progress_show(&bar, 1);
    std::cout << std::endl;
    smr_progress_destroy(&bar);
    excel.SaveExcelFile(g_filename);
    std::cerr << "[INFO]the excel: " << g_filename << " generate successful" << std::endl;
    return 0;

}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
