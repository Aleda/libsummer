/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file smr_url.h
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:10:10
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef SMR_URL_H
#define SMR_URL_H

/**
 * @brief string transfer to URLCODE
 *
 * @param [in] str_src       : const char[] src_string
 * @param [in] str_res       : char*        url_encoded_string
 * @param [in] result_size   : int          encoded_size
 * @return  int 
 * @retval   
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:29:25
**/
int smr_url_encode(const char str_src[], char* str_res, int result_size);

/**
 * @brief URLENCODE transfer to string
 *
 * @param [in] str_src   : const char*
 * @param [in] str_res   : char*
 * @param [in] result_sise   : int
 * @return  int 
 * @retval   
 * @see 
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:30:31
**/
int smr_url_decode(const char *str_src, char* str_res, int result_sise);

#endif  // SMR_URL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
