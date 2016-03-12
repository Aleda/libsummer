/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file smr_func.h
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 12:21:46
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef SMR_FUNC_H
#define SMR_FUNC_H

/**
 * @brief generate a random longlong num
 *
 * @return  long long 
 * @retval   
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 12:23:49
**/
long long smr_gen_random_id();

/**
 * @brief transfer a hex(16) num to decimal(10) 
 *
 * @param [in] c   : char
 * @return  int 
 * @retval   num(10)
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:26:24
**/
int smr_hex2num(char c);

//=========================process_bar_begin=================================//
/**
 * @brief process_t 进度条
 */
enum PROGRESS {
    PROGRESS_NUM_STYLE = 0,
    PROGRESS_CHR_STYLE = 1,
    PROGRESS_BGC_STYLE = 2
};

typedef struct {
    char  chr;       /*tip char*/
    char  *title;    /*tip string*/
    int   style;      /*progress style*/
    int   max;        /*maximum value*/
    float offset;
    char  *pro;
} progress_t;

/**
 * @brief process_bar init
 *
 * @param [in] bar     : process_t* process_t*
 * @param [in] title   : char*      title
 * @param [in] max     : int        max_end_value
 * @param [in] style   : int        show_style
 * @return  int 
 * @retval  NULL
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:59:49
**/
void smr_progress_init(progress_t *bar, char* title, int max, int style);

/**
 * @brief process_show
 *
 * @param [in] bar   : progress_t*
 * @param [in] bit   : float
 * @return  void 
 * @retval  void
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 17:02:49
**/
void smr_progress_show(progress_t *bar, float bit);

/**
 * @brief process_destory
 *
 * @param [in] bar   : progress_t*
 * @return  void 
 * @retval  void
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 17:11:31
**/
void smr_progress_destroy(progress_t *bar);  

//========================process_bar_end=================================//
#endif  // SMR_FUNC_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
