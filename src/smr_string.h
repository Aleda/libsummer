 /**
 * @file smr_string.h
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/11 19:58:41
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef SMR_STRING_H
#define SMR_STRING_H

#include <string>

#define MAX_SPLIT_LEN   500
/**
 * @brief 对字符串以separator进行分割
 *              一般不要使用这个函数，因为这个函数对于单个分割串的长度有限制，
 *              即：不能超过MAX_SPLIT_LEN
 * @notice 默认的每个被分割的字符串不超高MAX_SPLIT_LEN
 *
 * @param [in] str_src       : const char[]  
 * @param [in] str_arr_des   : char* []         这里需要注意，传的是指针数组
 * @param [in] separator     : char             单个字符
 * @return  int 
 * @retval  >=0: split_num; -1: NULL pointor; -2: 分割的字符串>MAX_SPLIT_LEN
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/11 20:06:58
**/
int smr_split(const char str_src[], char* str_arr_des[], const char separator);

/**
 * @brief 对字符串以字符串separators进行分割，需要注意的是，传入的是指针数组
 *
 * @param [in] str_src   : const char[]
 * @param [in] str_arr_des   : char* []
 * @param [in] separator_arr   : const char[]
 * @return  int 
 * @retval   >=0: split_num; -1: OOM; 
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 11:14:26
**/
int smr_split(const char str_src[], char* str_arr_des[], const char separator_arr[]);

/**
 * @brief 支持C++方向的对string类型的split，这个不涉及内存的分配，较稳定
 *
 * @param [in] str_src       : std::string
 * @param [in] str_des_vec   : std::vector<std::string>&
 * @param [in] delim         : const std::string
 * @return  int 
 * @retval  >=0: split_num;
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/12 12:10:59
**/
int smr_split(std::string str_src, std::vector<std::string>& str_des_vec, const std::string delim);


#endif  // SMR_STRING_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
