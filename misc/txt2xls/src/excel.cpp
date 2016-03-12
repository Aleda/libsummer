 /**
 * @file excel.cpp
 * @author Aleda(lishuo02@baidu.com || aleda.cn)
 * @date 2015/03/11 14:48:45
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "excel.h"

//font.cpp line 47
const unsigned16_t BOLD_OPTION_TABLE[] = {
    FONT_BOLDNESS_BOLD,
    FONT_BOLDNESS_HALF,
    FONT_BOLDNESS_NORMAL,
    FONT_BOLDNESS_DOUBLE 
};

Excel::Excel()
{
    m_pWorkSheet=NULL;
}


Excel::~Excel()
{
}

void Excel::CreateWorkSheet( const string& pm_WorkSheetText )
{
    //限制只建一个WorkSheet
    if(m_pWorkSheet!=NULL)
        return;

    m_pWorkSheet = m_WorkBook.sheet(pm_WorkSheetText);
    m_pWorkSheet->MakeActive();
}

void Excel::SaveExcelFile( const string& pm_FilePath )
{
    assert(m_pWorkSheet!=NULL);
    m_WorkBook.Dump(pm_FilePath);
}


void Excel::SetCellNumber(
        unsigned16_t pm_row,
        unsigned16_t pm_col,
        double pm_Number,
        string pm_FontName /*= "Arial"*/,
        unsigned16_t pm_fontSize /*= 12 */,
        bool pm_FontBold /*= false*/)
{
    xf_t* p_xf_t=get_xf_t(pm_FontName,pm_fontSize*20,pm_FontBold?BOLDNESS_BOLD:BOLDNESS_NORMAL);
    m_pWorkSheet->number(pm_row,pm_col,pm_Number,p_xf_t);
    //m_pWorkSheet->rowheight(pm_row,15);
}


void Excel::SetCellText(unsigned16_t pm_row,
        unsigned16_t pm_col,
        const string& pm_Text,
        string pm_FontName /*= "Arial"*/,
        unsigned16_t pm_fontSize /*= 12 */,
        bool pm_FontBold /*= false*/)
{
    xf_t* p_xf_t=get_xf_t(pm_FontName, pm_fontSize*20, pm_FontBold?BOLDNESS_BOLD:BOLDNESS_NORMAL);
    m_pWorkSheet->label(pm_row, pm_col, pm_Text, p_xf_t);
    //m_pWorkSheet->rowheight(pm_row,15);
}

void Excel::MergeCells( unsigned16_t pm_first_row, unsigned16_t pm_first_col,
        unsigned16_t pm_last_row, unsigned16_t pm_last_col )
{
    m_pWorkSheet->merge(pm_first_row,pm_first_col,pm_last_row,pm_last_col);
}

void Excel::SetSize(
        unsigned16_t pm_row,
        unsigned16_t pm_col,
        unsigned16_t pm_row_height,
        unsigned16_t pm_col_width )
{
    if(pm_row_height!=0)
    {
        m_pWorkSheet->rowheight(pm_row,pm_row_height);
    }

    if (pm_col_width!=0)
    {
        m_pWorkSheet->colwidth(pm_col,pm_col_width);
    }
}

void Excel::SetCellAlign(unsigned16_t pm_row, unsigned16_t pm_col,
        halign_option_t pm_ha_option,
        valign_option_t pm_va_option)
{
    cell_t* pCell=m_pWorkSheet->FindCellOrMakeBlank(pm_row,pm_col);
    pCell->halign(pm_ha_option);
    pCell->valign(pm_va_option);
}

void Excel::SetCellBorder(unsigned16_t pm_row, unsigned16_t pm_col)
{
    cell_t* pCell=m_pWorkSheet->FindCellOrMakeBlank(pm_row,pm_col);
    pCell->borderstyle(BORDER_LEFT,BORDER_THIN);
    pCell->borderstyle(BORDER_RIGHT,BORDER_THIN);
    pCell->borderstyle(BORDER_TOP,BORDER_THIN);
    pCell->borderstyle(BORDER_BOTTOM,BORDER_THIN);
}

void Excel::SetCellBgColor(unsigned16_t pm_row, unsigned16_t pm_col,color_name_t pm_color)
{
    cell_t* pCell=m_pWorkSheet->FindCellOrMakeBlank(pm_row,pm_col);
    pCell->fillstyle(FILL_SOLID);
    pCell->fillbgcolor(pm_color);
    pCell->fillfgcolor(pm_color);
}

xf_t* Excel::get_xf_t(string& pm_fontName,unsigned16_t pm_fontSize,unsigned16_t pm_fontBoldStyle)
{
    xf_t* p_xf_t=NULL;

    vector<xf_t*>::iterator ptr_xf_t=m_FormatPtrs.begin();
    for (;ptr_xf_t!=m_FormatPtrs.end();ptr_xf_t++)
    {
        xf_t* _p_xf_t=*ptr_xf_t;
        font_t* pfont=_p_xf_t->GetFont();

        //string fontName=*pfont->GetName();
        string fontName=pfont->GetName();
        unsigned16_t fontBoldStyle=pfont->GetBoldStyle();
        unsigned16_t fontSize=pfont->GetHeight();

        if ( fontName==pm_fontName && 
                fontSize==pm_fontSize &&
                fontBoldStyle==BOLD_OPTION_TABLE[pm_fontBoldStyle])
        {
            p_xf_t=_p_xf_t;
            return p_xf_t;
        }
    }

    font_t* pfont=get_font_t(pm_fontName,pm_fontSize,pm_fontBoldStyle);
    p_xf_t=m_WorkBook.xformat();
    p_xf_t->SetFont(pfont);
    m_FormatPtrs.push_back(p_xf_t);

    return p_xf_t;
}

font_t* Excel::get_font_t(string& pm_fontName,unsigned16_t pm_fontSize,unsigned16_t pm_fontBoldStyle)
{
    font_t* pfont=NULL;
    vector<font_t*>::iterator itpFont=m_FontPtrs.begin();
    for (;itpFont!=m_FontPtrs.end();itpFont++)
    {
        font_t* _pfont=*itpFont;

        string fontName=_pfont->GetName();
        unsigned16_t fontBoldStyle=_pfont->GetBoldStyle();
        unsigned16_t fontSize=_pfont->GetHeight();

        if ( fontName==pm_fontName && 
                fontSize==pm_fontSize &&
                fontBoldStyle==BOLD_OPTION_TABLE[pm_fontBoldStyle])
        {
            pfont=_pfont;
            break;
        }
    }

    if (pfont==NULL)
    {
        pfont=m_WorkBook.font(pm_fontName);
        pfont->SetHeight(pm_fontSize);
        pfont->SetBoldStyle((boldness_option_t)pm_fontBoldStyle);

        m_FontPtrs.push_back(pfont);
    }

    return pfont;
}

void Excel::set_default_rowheight(unsigned16_t height, bool hidden)
{
    if (height > 0) {
        m_pWorkSheet->defaultRowHeight(height, hidden);       
    } else {
        //TODO test
        m_pWorkSheet->defaultRowHeight(256, hidden);       
    }
}

void Excel::set_default_colwidth(unsigned16_t width)
{
    if (width > 0) {
        m_pWorkSheet->defaultColwidth(width);       
    } else {
        //TODO test
        m_pWorkSheet->defaultColwidth(256);       
    }
}


/* vim: set ts=4 sw=4 sts=4 tw=100 */
