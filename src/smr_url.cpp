/***************************************************************************
 * 
 *                            Aleda All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file smr_url.cpp
 * @author Aleda(lishuo02@baidu.com | aleda.cn)
 * @date 2015/03/13 16:12:12
 * @version $Revision$ 
 * @brief 
 *  
 **/
#include <stdio.h>
#include <string.h>

#include "smr_func.h"
#include "smr_url.h"

int smr_url_encode(const char* str, char* result, int resultSize)
{
	int i;
	int j = 0;//for result index
	char ch;
	int strSize = strlen(str);
	if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0))
	{
		return 0;
	}
	for ( i=0; (i<strSize)&&(j<resultSize); ++i)
	{
		ch = str[i];
		if (((ch>='A') && (ch<'Z')) ||
			((ch>='a') && (ch<'z')) ||
			((ch>='0') && (ch<'9'))) 
		{
			result[j++] = ch;
		} 
		else if (ch == ' ') 
		{
			result[j++] = '+';
		} 
		else if (ch == '.' || ch == '-' || ch == '_' || 
				ch == '*' || ch == ':' || ch == '/')
		{
			result[j++] = ch;
		}
		else
		{
			if (j+3 < resultSize)
			{
				sprintf(result+j, "%%%02X", (unsigned char)ch);
				j += 3;
			}
			else
			{
				return 0;
			}
		}
	}
	result[j] = '\0';
	return j;
}

int smr_url_decode(const char* str, char *result, int resultSize)
{
	char ch,ch1,ch2;
	int i;
	int j = 0;//record result index
	
	int strSize = strlen(str);
	
	if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0))
	{
		return 0;
	}

	for ( i=0; (i<strSize) && (j<resultSize); ++i)
	{
		ch = str[i];
		switch (ch)
		{
			case '+':
				result[j++] = ' ';
				break;
			case '%':
				if (i+2<strSize)
				{
					ch1 = smr_hex2num(str[i+1]);//高4位
					ch2 = smr_hex2num(str[i+2]);//低4位
					if ((ch1!='0') && (ch2!='0'))
						result[j++] = (char)((ch1<<4) | ch2);
					i += 2;
					break;
				}
				else 
				{
					break;
				}
			default:
				result[j++] = ch;
				break;
		}
	}
	
	result[j] = 0;
	return j;
}



/* vim: set ts=4 sw=4 sts=4 tw=100 */
