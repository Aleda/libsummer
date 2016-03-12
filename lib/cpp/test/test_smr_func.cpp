/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file test_smr_func.cpp
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 12:25:59
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "smr_func.h"

int test_smr_gen_random_id()
{
    long long id = smr_gen_random_id();
    std::cout << "id = " << id << std::endl;
    return 0;
}

int test_smr_progress_bar()
{
    progress_t bar;
    smr_progress_init(&bar, "Aleda", 50, PROGRESS_CHR_STYLE);
    for (int i = 0; i < 100; i++) {
        smr_progress_show(&bar, i / 100.0f);
        sleep(1);
    }
    smr_progress_destroy(&bar);
}

int main(int argc, char* argv[])
{
    test_smr_progress_bar();
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
