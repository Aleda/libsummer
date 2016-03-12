 /**
 * @file excel.h
 * @author Aleda(lishuo02@baidu.com || aleda.cn)
 * @date 2015/03/11 15:42:50
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef _EXCEL_H
#define _EXCEL_H

#include <vector>
using namespace std;

#include <xlslib.h>
#include <xlslib/extformat.h>

using namespace xlslib_core;

class Excel
{
public:
    Excel();
    ~Excel();
private:
    Excel(Excel& excel);
    Excel& operator=(Excel& excel);
private:
    workbook m_WorkBook;
    ///Excel工作表，使用之前必须先创建，参见<sheetrec.h>
    worksheet* m_pWorkSheet;
private:

    /*
       注意：
       测试发现Excel最多支持同时使用505种字体；
       workbook::font()的每次调用都会创建并添加一个“字体”到excel文件中，所以
       在这里保存了字体信息，使得每个不同的“字体”只创建并添加一次。

       最多支持4028种不同的单元格格式；
       workbook::xformat()的每次调用都会创建并添加一个“格式”到excel文件中，所以
       在这里保存了格式信息，使得每个不同的“格式”只创建并添加一次。
     */
    ///字体列表
    vector<font_t*> m_FontPtrs;
    ///单元格格式列表
    vector<xf_t*> m_FormatPtrs;
    xf_t* get_xf_t(string& pm_fontName,unsigned16_t pm_fontSize,unsigned16_t pm_fontBoldStyle);
    font_t* get_font_t(string& pm_fontName,unsigned16_t pm_fontSize,unsigned16_t pm_fontBoldStyle);

public:
    /**
     * @brief    创建一张工作表，注意：这个函数必须首先调用
     */
    void CreateWorkSheet(const string& pm_WorkSheetText);

    /**
     * @brief    保存Excel文件
     */
    void SaveExcelFile(const string& pm_FilePath);

    /**
     * @brief    设置单元格的文本d
     */
    void SetCellText(
            unsigned16_t pm_row, 
            unsigned16_t pm_col,
            const string& pm_Text,
            string pm_FontName = "Arial",
            unsigned16_t pm_fontSize = 12,
            bool pm_FontBold = false);

    /**
     * @brief    设置单元格的数字
     */
    void SetCellNumber(
            unsigned16_t pm_row, 
            unsigned16_t pm_col,
            double pm_Number,
            string pm_FontName = "Arial",
            unsigned16_t pm_fontSize = 12 ,
            bool pm_FontBold = false);

    /**
     * @brief    合并单元格
     */
    void MergeCells(
            unsigned16_t pm_first_row, 
            unsigned16_t pm_first_col, 
            unsigned16_t pm_last_row, 
            unsigned16_t pm_last_col);
    /**
     * @brief    设置单元格的宽度，高度
     */
    void SetSize(
            unsigned16_t pm_row, 
            unsigned16_t pm_col,
            unsigned16_t pm_row_height,
            unsigned16_t pm_col_width);

    /**
     * @brief    设置单元格边框为黑色实线
     */
    void SetCellBorder(
            unsigned16_t pm_row, 
            unsigned16_t pm_col);

    /**
     * @brief    设置单元格的对齐方式
     */
    void SetCellAlign(
            unsigned16_t pm_row, 
            unsigned16_t pm_col,
            halign_option_t pm_ha_option,
            valign_option_t pm_va_option);

    /**
     * @brief    设置单元格的背景颜色
     */
    void SetCellBgColor(
            unsigned16_t pm_row, 
            unsigned16_t pm_col,
            color_name_t pm_color);

    /**
     * @brief set the default row height
     *
     * @param [in] height   : unsigned16_t
     * @param [in] hidden   : bool
     * @return  void 
     * @retval   
     * @see 
     * @author Aleda
     * @date 2015/03/11 17:06:46
    **/
    void set_default_rowheight(unsigned16_t height, bool hidden = false);
    /**
     * @brief set the default col width
     *
     * @param [in] width   : unsigned16_t
     * @return  void 
     * @retval   
     * @see 
     * @author Aleda
     * @date 2015/03/11 17:07:20
    **/
    void set_default_colwidth(unsigned16_t width);

};

#endif // Excel_h
/* vim: set ts=4 sw=4 sts=4 tw=100 */
