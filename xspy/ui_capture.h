#pragma once
#include "atlmisc.h"
#include "common.h"
#include "utils.h"
#include <set>

// ģ���wtl::CBitmapButtonImpl����Ϊ����ҪSubclassWindow����Attach�ǲ��еģ���Ϊ��BEGIN_MSG_MAP
// ��Ҫ���볭Ϯ��wtl::CZoomScrollImpl��mfcspy
template <class T, class TBase = CStatic, class TWinTraits = ATL::CControlWinTraits>
class ATL_NO_VTABLE ui_capture_t : public ATL::CWindowImpl< T, TBase, TWinTraits>
{
public:
    //// API 
    // ����һ��STATIC�ؼ�Ϊ��׽����
    BOOL SubclassWindow(HWND hWnd);
    // ��ӽ���WM_SPY��Ϣ�Ĵ���
    void AddRecvWnd(HWND hWnd);
    // �Ƴ�����WM_SPY��Ϣ�Ĵ���
    void RemoveRecvWnd(HWND hWnd);
public:
    ui_capture_t();
    ~ui_capture_t();

protected:
    BEGIN_MSG_MAP(ui_capture_t)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
	END_MSG_MAP()

    void Init();
    LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
    VOID FrameWindow(HWND hWnd);
    void DrawFrame(POINT pt);

private:
	HICON m_hIcon;
    bool m_bTracking;
    HWND m_hRecvMsgWnd;
    HWND m_hLastWnd;
    CPen m_pen;
    HCURSOR cursor_sys;
    std::set<HWND> m_recvWnd;
};

#include "ui_capture_impl.h"

class ui_capture : public ui_capture_t<ui_capture>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_BitmapButton"), GetWndClassName())
};