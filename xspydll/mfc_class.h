/************************************************************************/
/* �鿴MFC�汾����麯���ķ�����
/d1reportAllClassLayout
*/
/************************************************************************/

#pragma once

#include <boost/format.hpp>

#define MAKE_VFN(x) \
    virtual const char* x() \
{ \
    return #x; \
}

#define PRINT_VFN(x) \
    result += boost::str(boost::format("[vtbl+0x%02X]%-24s= %s\r\n") % index % #x % GetCodes((LPVOID)*pStart)); \
    ++pStart; \
    ++index;


struct AFX_MSGMAP_ENTRY
{
    UINT nMessage;   // windows message
    UINT nCode;      // control code or WM_NOTIFY code
    UINT nID;        // control ID (or 0 for windows messages)
    UINT nLastID;    // used for entries specifying a range of control id's
    UINT_PTR nSig;       // signature type (action) or pointer to message #
    //AFX_PMSG pfn;    // routine to call (or special value)
    LPVOID pfn;
};

struct AFX_MSGMAP
{
    LPVOID pfnGetBaseMap;
    //const AFX_MSGMAP* (PASCAL* pfnGetBaseMap)();
    const AFX_MSGMAP_ENTRY* lpEntries;
};

struct CRuntimeClass
{
    // Attributes
    LPCSTR m_lpszClassName;
    int m_nObjectSize;
    UINT m_wSchema; // schema number of the loaded class
    //CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
    LPVOID m_pfnCreateObject;
    //#ifdef _AFXDLL
    CRuntimeClass* (PASCAL* m_pfnGetBaseClass)();
    //#else
    //    CRuntimeClass* m_pBaseClass;
    //#endif
    //
};

class CObject
{
public:
    // �ú������Ի�ȡ���������С
    virtual CRuntimeClass* GetRuntimeClass() const{return 0;};
    MAKE_VFN(dtor);
    MAKE_VFN(Serialize);

    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        index = 0;
        PRINT_VFN(GetRuntimeClass);
        PRINT_VFN(dtor);
        PRINT_VFN(Serialize);
    }
};

class CObject_dbg
{
public:
    virtual CRuntimeClass* GetRuntimeClass() const {return 0;};
    MAKE_VFN(dtor);
    MAKE_VFN(Serialize);
    MAKE_VFN(AssertValid);
    MAKE_VFN(Dump);

    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        index = 0;
        PRINT_VFN(GetRuntimeClass);
        PRINT_VFN(dtor);
        PRINT_VFN(Serialize);
        PRINT_VFN(AssertValid);
        PRINT_VFN(Dump);
    }
};

template<class T>
class CCmdTarget : public T
{
public:
    MAKE_VFN(OnCmdMsg);
    MAKE_VFN(OnFinalRelease);
    MAKE_VFN(IsInvokeAllowed);
    MAKE_VFN(GetDispatchIID);
    MAKE_VFN(GetTypeInfoCount);
    MAKE_VFN(GetTypeLibCache);
    MAKE_VFN(GetTypeLib);
    virtual const AFX_MSGMAP* GetMessageMap(){return 0;}
    MAKE_VFN(GetCommandMap);
    MAKE_VFN(GetDispatchMap);
    MAKE_VFN(GetConnectionMap);
    MAKE_VFN(GetInterfaceMap);
    MAKE_VFN(GetEventSinkMap);
    MAKE_VFN(OnCreateAggregates);
    MAKE_VFN(GetInterfaceHook);
    MAKE_VFN(GetExtraConnectionPoints);
    MAKE_VFN(GetConnectionHook);

    //#define MAKE_MEMBER(x,fmt) sTemp.Format( "[+%02X]" #x "=" fmt "\r\n",(PBYTE)&(x) - (PBYTE)this,x);str += sTemp;
    //    sTemp.Format( "[+%02X]vtbl address=%s\r\n",0,(LPCSTR)GetMods(vtbl));str += sTemp;

    void get_member(PDWORD& pStart, DWORD& index, std::string& result)
    {
        PDWORD pBegin = (PDWORD)pStart;

#define PRINT_MEMBER(x) \
    result += boost::str(boost::format("[+0x%02X]" #x " = 0x%p\r\n") % index % ); \
    ++pStart; \
    ++index;

        PRINT_MEMBER(CCmdTarget::m_dwRef); // 64λ�ֲ���֪����ʲô����
        PRINT_MEMBER(CCmdTarget::m_pOuterUnknown);
        PRINT_MEMBER(CCmdTarget::m_xInnerUnknown);
        PRINT_MEMBER(CCmdTarget::m_xDispatch.m_vtbl);
        //		MAKE_MEMBER(CCmdTarget::m_xDispatch.m_nOffset);
        PRINT_MEMBER(CCmdTarget::m_bResultExpected);
        PRINT_MEMBER(CCmdTarget::m_xConnPtContainer.m_vtbl);
        //		MAKE_MEMBER(CCmdTarget::m_xConnPtContainer.m_nOffset,"%p");
    }

    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        T::get_vfn_string(pStart, index, result);
        PRINT_VFN(OnCmdMsg);
        PRINT_VFN(OnFinalRelease);
        PRINT_VFN(IsInvokeAllowed);
        PRINT_VFN(GetDispatchIID);
        PRINT_VFN(GetTypeInfoCount);
        PRINT_VFN(GetTypeLibCache);
        PRINT_VFN(GetTypeLib);
        PRINT_VFN(GetMessageMap);
        PRINT_VFN(GetCommandMap);
        PRINT_VFN(GetDispatchMap);
        PRINT_VFN(GetConnectionMap);
        PRINT_VFN(GetInterfaceMap);
        PRINT_VFN(GetEventSinkMap);
        PRINT_VFN(OnCreateAggregates);
        PRINT_VFN(GetInterfaceHook);
        PRINT_VFN(GetExtraConnectionPoints);
        PRINT_VFN(GetConnectionHook);
    }

};

// vc60��vs2008��CCmdTarget���麯������һ����vs2008��CWnd���麯����Ͷ�ܶຯ����
template <class dbg>
class CWndX : public CCmdTarget<dbg>
{
public:
};

template<class dbg>
class CWnd42 : public CCmdTarget<dbg>
{
public:
    MAKE_VFN(PreSubclassWindow);
    MAKE_VFN(Create);
    MAKE_VFN(DestroyWindow);
    MAKE_VFN(PreCreateWindow);
    MAKE_VFN(CalcWindowRect);
    MAKE_VFN(OnToolHitTest);
    MAKE_VFN(GetScrollBarCtrl);
    MAKE_VFN(WinHelpA);
    MAKE_VFN(ContinueModal);
    MAKE_VFN(EndModalLoop);
    MAKE_VFN(OnCommand);
    MAKE_VFN(OnNotify);
    MAKE_VFN(GetSuperWndProcAddr);
    MAKE_VFN(DoDataExchange);
    MAKE_VFN(BeginModalState);
    MAKE_VFN(EndModalState);
    MAKE_VFN(PreTranslateMessage);
    MAKE_VFN(OnAmbientProperty);
    MAKE_VFN(WindowProc);
    MAKE_VFN(OnWndMsg);
    MAKE_VFN(DefWindowProcA);
    MAKE_VFN(PostNcDestroy);
    MAKE_VFN(OnChildNotify);
    MAKE_VFN(CheckAutoCenter);
    MAKE_VFN(IsFrameWnd);
    MAKE_VFN(SetOccDialogInfo);
    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        CCmdTarget<dbg>::get_vfn_string(pStart, index, result);
        PRINT_VFN(PreSubclassWindow);
        PRINT_VFN(Create);
        PRINT_VFN(DestroyWindow);
        PRINT_VFN(PreCreateWindow);
        PRINT_VFN(CalcWindowRect);
        PRINT_VFN(OnToolHitTest);
        PRINT_VFN(GetScrollBarCtrl);
        PRINT_VFN(WinHelpA);
        PRINT_VFN(ContinueModal);
        PRINT_VFN(EndModalLoop);
        PRINT_VFN(OnCommand);
        PRINT_VFN(OnNotify);
        PRINT_VFN(GetSuperWndProcAddr);
        PRINT_VFN(DoDataExchange);
        PRINT_VFN(BeginModalState);
        PRINT_VFN(EndModalState);
        PRINT_VFN(PreTranslateMessage);
        PRINT_VFN(OnAmbientProperty);
        PRINT_VFN(WindowProc);
        PRINT_VFN(OnWndMsg);
        PRINT_VFN(DefWindowProcA);
        PRINT_VFN(PostNcDestroy);
        PRINT_VFN(OnChildNotify);
        PRINT_VFN(CheckAutoCenter);
        PRINT_VFN(IsFrameWnd);
        PRINT_VFN(SetOccDialogInfo);
    }
};

template <class dbg>
class CDialog42 : public CWnd42<dbg>
{
public:
    MAKE_VFN(DoModal);
    MAKE_VFN(OnInitDialog);
    MAKE_VFN(OnSetFont);
    MAKE_VFN(OnOK);
    MAKE_VFN(OnCancel);
    MAKE_VFN(PreInitDialog);
    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        CWnd42<dbg>::get_vfn_string(pStart, index, result);
        PRINT_VFN(DoModal);
        PRINT_VFN(OnInitDialog);
        PRINT_VFN(OnSetFont);
        PRINT_VFN(OnOK);
        PRINT_VFN(OnCancel);
        PRINT_VFN(PreInitDialog);
    }
};

template <class dbg>
class CWnd90 : public CCmdTarget<dbg>
{
public:
    MAKE_VFN(PreSubclassWindow);
    MAKE_VFN(Create);
    MAKE_VFN(CreateEx);
    MAKE_VFN(CreateEx1); // �������ֲ�ͬ��Ӱ��
    MAKE_VFN(DestroyWindow);
    MAKE_VFN(PreCreateWindow);
    MAKE_VFN(CalcWindowRect);
    MAKE_VFN(GetMenu);
    MAKE_VFN(SetMenu);
    MAKE_VFN(OnToolHitTest);
    MAKE_VFN(GetScrollBarCtrl);
    MAKE_VFN(WinHelpA);
    MAKE_VFN(HtmlHelpA);
    MAKE_VFN(WinHelpInternal);
    MAKE_VFN(ContinueModal);
    MAKE_VFN(EndModalLoop);
    MAKE_VFN(EnsureStdObj);
    MAKE_VFN(get_accParent);
    MAKE_VFN(get_accChildCount);
    MAKE_VFN(get_accChild);
    MAKE_VFN(get_accName);
    MAKE_VFN(get_accValue);
    MAKE_VFN(get_accDescription);
    MAKE_VFN(get_accRole);
    MAKE_VFN(get_accState);
    MAKE_VFN(get_accHelp);
    MAKE_VFN(get_accHelpTopic);
    MAKE_VFN(get_accKeyboardShortcut);
    MAKE_VFN(get_accFocus);
    MAKE_VFN(get_accSelection);
    MAKE_VFN(get_accDefaultAction);
    MAKE_VFN(accSelect);
    MAKE_VFN(accLocation);
    MAKE_VFN(accNavigate);
    MAKE_VFN(accHitTest);
    MAKE_VFN(accDoDefaultAction);
    MAKE_VFN(put_accName);
    MAKE_VFN(put_accValue);
    MAKE_VFN(SetProxy);
    MAKE_VFN(CreateAccessibleProxy);
    MAKE_VFN(OnCommand);
    MAKE_VFN(OnNotify);
    MAKE_VFN(GetSuperWndProcAddr);
    MAKE_VFN(DoDataExchange);
    MAKE_VFN(BeginModalState);
    MAKE_VFN(EndModalState);
    MAKE_VFN(PreTranslateMessage);
    MAKE_VFN(OnAmbientProperty);
    MAKE_VFN(WindowProc);
    MAKE_VFN(OnWndMsg);
    MAKE_VFN(DefWindowProcA);
    MAKE_VFN(PostNcDestroy);
    MAKE_VFN(OnChildNotify);
    MAKE_VFN(CheckAutoCenter);
    MAKE_VFN(IsFrameWnd);
    MAKE_VFN(CreateControlContainer);
    MAKE_VFN(CreateControlSite);
    MAKE_VFN(SetOccDialogInfo);
    MAKE_VFN(GetOccDialogInfo);
    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        CCmdTarget<dbg>::get_vfn_string(pStart, index, result);
        PRINT_VFN(PreSubclassWindow);
        PRINT_VFN(Create);
        PRINT_VFN(CreateEx);
        PRINT_VFN(CreateEx);
        PRINT_VFN(DestroyWindow);
        PRINT_VFN(PreCreateWindow);
        PRINT_VFN(CalcWindowRect);
        PRINT_VFN(GetMenu);
        PRINT_VFN(SetMenu);
        PRINT_VFN(OnToolHitTest);
        PRINT_VFN(GetScrollBarCtrl);
        PRINT_VFN(WinHelpA);
        PRINT_VFN(HtmlHelpA);
        PRINT_VFN(WinHelpInternal);
        PRINT_VFN(ContinueModal);
        PRINT_VFN(EndModalLoop);
        PRINT_VFN(EnsureStdObj);
        PRINT_VFN(get_accParent);
        PRINT_VFN(get_accChildCount);
        PRINT_VFN(get_accChild);
        PRINT_VFN(get_accName);
        PRINT_VFN(get_accValue);
        PRINT_VFN(get_accDescription);
        PRINT_VFN(get_accRole);
        PRINT_VFN(get_accState);
        PRINT_VFN(get_accHelp);
        PRINT_VFN(get_accHelpTopic);
        PRINT_VFN(get_accKeyboardShortcut);
        PRINT_VFN(get_accFocus);
        PRINT_VFN(get_accSelection);
        PRINT_VFN(get_accDefaultAction);
        PRINT_VFN(accSelect);
        PRINT_VFN(accLocation);
        PRINT_VFN(accNavigate);
        PRINT_VFN(accHitTest);
        PRINT_VFN(accDoDefaultAction);
        PRINT_VFN(put_accName);
        PRINT_VFN(put_accValue);
        PRINT_VFN(SetProxy);
        PRINT_VFN(CreateAccessibleProxy);
        PRINT_VFN(OnCommand);
        PRINT_VFN(OnNotify);
        PRINT_VFN(GetSuperWndProcAddr);
        PRINT_VFN(DoDataExchange);
        PRINT_VFN(BeginModalState);
        PRINT_VFN(EndModalState);
        PRINT_VFN(PreTranslateMessage);
        PRINT_VFN(OnAmbientProperty);
        PRINT_VFN(WindowProc);
        PRINT_VFN(OnWndMsg);
        PRINT_VFN(DefWindowProcA);
        PRINT_VFN(PostNcDestroy);
        PRINT_VFN(OnChildNotify);
        PRINT_VFN(CheckAutoCenter);
        PRINT_VFN(IsFrameWnd);
        PRINT_VFN(CreateControlContainer);
        PRINT_VFN(CreateControlSite);
        PRINT_VFN(SetOccDialogInfo);
        PRINT_VFN(GetOccDialogInfo);
    }
};

template<class dbg>
class CDialog90 : public CWnd90<dbg>
{
public:
    MAKE_VFN(Create);
    MAKE_VFN(Create1); //
    MAKE_VFN(CreateIndirect);
    MAKE_VFN(CreateIndirect1); //
    MAKE_VFN(DoModal);
    MAKE_VFN(OnInitDialog);
    MAKE_VFN(OnSetFont);
    MAKE_VFN(OnOK);
    MAKE_VFN(OnCancel);
    MAKE_VFN(PreInitDialog);
    void get_vfn_string(PDWORD& pStart, DWORD& index, std::string& result)
    {
        CWnd90<dbg>::get_vfn_string(pStart, index, result);
        PRINT_VFN(Create);
        PRINT_VFN(Create);
        PRINT_VFN(CreateIndirect);
        PRINT_VFN(CreateIndirect);
        PRINT_VFN(DoModal);
        PRINT_VFN(OnInitDialog);
        PRINT_VFN(OnSetFont);
        PRINT_VFN(OnOK);
        PRINT_VFN(OnCancel);
        PRINT_VFN(PreInitDialog);
    }
};

template<class T, bool IsDialog>
class CWndOrDialog90 : public CWnd90<T>{};

template<class T>
class CWndOrDialog90<T, true>: public CDialog90<T>{};


template <class dbg>
class CDialogX : public CWndX<dbg>
{
public:
};

// ͨ�ð汾������Ҫ�жϾ������ĸ�MFC�汾���������GetRuntimeClass��ʱ��
typedef CWndX<CObject_dbg> CWndd;
typedef CWndX<CObject> CWnd;

typedef CDialogX<CObject_dbg> CDialogd;
typedef CDialogX<CObject> CDialog;