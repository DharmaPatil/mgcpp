#include "dt_edit.h"
CEdit::CEdit(CTRLDATA* data,CSkinForm* parent,string typeName):
        CCommCtrl(data,parent,typeName)
{

}
CEdit::CEdit(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName)
{

    CTRLDATA* data = new CTRLDATA();
    char* tmp = new char[strlen(desc->caption) + 1];
    memset(tmp,0,strlen(desc->caption) + 1);

    strcpy(tmp,desc->caption);
    data->caption = tmp;

    tmp = new char[typeName.size() + 1];
    memset(tmp,0,strlen(desc->caption) + 1);
    strcpy(tmp,typeName.c_str());

    data->class_name=tmp;
    data->dwAddData = 0;
    data->dwExStyle = DEF_EDIT_EXSTYLE;
    data->dwStyle   = DEF_EDIT_STYLE;
    data->id        = -1; //auto alloc id
    data->w         = desc->w;
    data->h         = desc->h;
    data->x         = desc->x;
    data->y         = desc->y;

    SetParam(data,parent,typeName);
    _alloc_desc = true;

}
CEdit::~CEdit()
{

}
/*
ES_LEFT
ES_CENTER
ES_RIGHT
*/
void CEdit::SetTextAligned(int aligned)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
    		//可以提供一个类级别的函数，修改该类的所有属性
                 //IncludeWindowStyle();
    		 //ExcludeWindowExStyle
    		 //IncludeWindowExStyle
    		 //GetWindowExStyle
    		 //BOOL GUIAPI ExcludeWindowStyle (HWND hWnd, DWORD dwStyle)
    }
}
std::string  CEdit::GetSelText()
{
	
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
         SendDlgItemMessage (_parent->m_hWnd, _data->id, EM_GETSEL, MAX_TEXT_LENGTH, (LPARAM)_buf);
         return string(_buf);
    }
    return string("");
}
void CEdit::SelectAllText()
{
    SEND_CMD0(EM_SELECTALL); 
}
void CEdit::CopySelectText()
{
    SEND_CMD0(EM_COPYTOCB);
}
void CEdit::CutSelectText()
{
		
}
void CEdit::SetFontSize(int size)
{
    HWND hEdit = GetDlgItem(_parent->m_hWnd,_data->id);


    LOGFONT* font = CreateLogFont("ttf","stxinwei","GB2312-0", FONT_WEIGHT_REGULAR, FONT_SLANT_ROMAN, FONT_SETWIDTH_NORMAL,\
                                  FONT_SPACING_CHARCELL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,size,0);
    fprintf(stderr,"font = %x\n",font);
    SetWindowFont(hEdit,font);
    UpdateWindow(hEdit,TRUE);
}
void CEdit::SetLineHeight(int val)
{
	
}
int  CEdit::GetLineHeight()
{
	
}
void CEdit::SetText(std::string strText)
{
    _parent->SetItemText(_id,strText);
}
std::string CEdit::GetText()
{
     if(_parent)
        return _parent->GetItemText(_id);
     return "";
}
void CEdit::SetLimitLength(int length)
{
    if(_parent)
        SendDlgItemMessage (_parent->m_hWnd, _data->id, EM_LIMITTEXT, length, 0);
}
int  CEdit::GetLimitLength()
{
    if(_parent)
       return SendDlgItemMessage (_parent->m_hWnd, _data->id, EM_GETLIMITTEXT, 0, 0);
    return -1;
}
void CEdit::Redo()
{
	
}
void CEdit::EnableReadOnly(bool yes)
{
    HWND hEdit = GetDlgItem(_parent->m_hWnd,_id);
    if(hEdit == HWND_INVALID)
        return;
    _data->dwStyle = GetWindowStyle(hEdit);

    if(yes){
        _data->dwStyle |= ES_READONLY;
        IncludeWindowStyle(hEdit,ES_READONLY);

    }else{
        _data->dwStyle &= (~ES_READONLY);
        ExcludeWindowStyle(hEdit,ES_READONLY);
    }

    //IncludeWindowStyle(hEdit,_data->dwStyle);
    if(_parent && (_parent->m_hWnd != HWND_INVALID))
        InvalidateRect(hEdit,NULL,TRUE);
}
void CEdit::SetPasswordChar(char ch)
{
	
}
void CEdit::EnablePassword(bool yes)
{
    _data->dwStyle |= ES_PASSWORD;
    /*
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        HWND hwndEdit = _parent->GetItemHwnd(_id);
        IncludeWindowStyle(hwndEdit,ES_PASSWORD);

    }*/
}
void CEdit::EnableDecimal(bool yes)
{
    HWND hEdit = GetDlgItem(_parent->m_hWnd,_id);
    if(hEdit == HWND_INVALID)
        return;
    _data->dwStyle = GetWindowStyle(hEdit);

    if(yes){
        _data->dwStyle |= ES_DECIMAL;
    }else{
        _data->dwStyle &= (~ES_DECIMAL);
    }

    IncludeWindowStyle(hEdit,_data->dwStyle);
    if(_parent && (_parent->m_hWnd != HWND_INVALID))
        InvalidateRect(hEdit,NULL,TRUE);
}
/*
static WNDPROC old_edit_proc;
static int new_edit_proc(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{

    if (message == MSG_CHAR) {
        DWORD my_style = GetWindowStyle(hwnd);
        printf("mystyle = 0x%x char = %c\n",my_style,wParam);
        if ((my_style & ES_DIGIT_ONLY) && (wParam < '0' || wParam > '9'))
        {
                return 0;
        }
        else if((my_style & ES_DECIMAL) && ( (wParam != '.') && (wParam < '0' || wParam > '9')))
        {
                return 0;
        }


    }
    return (*old_edit_proc) (hwnd, message, wParam, lParam);
}
*/
void CEdit::EnableDigtal(bool yes)
{
    HWND hEdit = GetDlgItem(_parent->m_hWnd,_id);
    if(hEdit == HWND_INVALID)
        return;
    _data->dwStyle = GetWindowStyle(hEdit);

    if(yes){
        _data->dwStyle |= ES_DIGIT_ONLY;
    }else{
        _data->dwStyle &= (~ES_DIGIT_ONLY);
    }

    IncludeWindowStyle(hEdit,_data->dwStyle);
    if(_parent && (_parent->m_hWnd != HWND_INVALID))
        InvalidateRect(hEdit,NULL,TRUE);
}
