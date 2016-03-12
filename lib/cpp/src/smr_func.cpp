/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file smr_func.cpp
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 12:21:33
 * @version $Revision$ 
 * @brief 
 *  
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "smr_func.h"

long long smr_gen_random_id()
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

int smr_hex2num(char c)
{
	if (c>='0' && c<='9') return c - '0';
	if (c>='a' && c<='z') return c - 'a' + 10;//这里+10的原因是:比如16进制的a值为10
	if (c>='A' && c<='Z') return c - 'A' + 10;

	return '0';
}

void smr_progress_init(progress_t *bar, char *title, int max, int style)
{
    bar->chr = '#';
    bar->title = title;
    bar->style = style;
    bar->max = max;
    bar->offset = 100 / (float)max;
    bar->pro = (char *) malloc(max+1);
    if ( style == PROGRESS_BGC_STYLE )
        memset(bar->pro, 0x00, max+1);
    else {
        memset(bar->pro, 32, max);
        memset(bar->pro+max, 0x00, 1);
    }
}

void smr_progress_show(progress_t *bar, float bit)
{
    int val = (int)(bit * bar->max);
    switch ( bar->style ) 
    {
        case PROGRESS_NUM_STYLE:
            printf("\033[?25l\033[31m\033[1m%s%d%%\033[?25h\033[0m\r",
                    bar->title, (int)(bar->offset * val));
            fflush(stdout);
            break;
        case PROGRESS_CHR_STYLE:
            memset(bar->pro, '#', val);
            printf("\033[?25l\033[31m\033[1m%s[%-s] %d%%\033[?25h\033[0m\r", 
                    bar->title, bar->pro, (int)(bar->offset * val));
            fflush(stdout);
            break;
        case PROGRESS_BGC_STYLE:
            memset(bar->pro, 32, val);
            printf("\033[?25l\033[31m\033[1m%s\033[41m %d%% %s\033[?25h\033[0m\r", 
                    bar->title, (int)(bar->offset * val), bar->pro);
            fflush(stdout);
            break;
    }
}

void smr_progress_destroy(progress_t *bar)
{
    free(bar->pro);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
