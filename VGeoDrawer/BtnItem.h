#pragma once

#define TimerID 1
#define WM_BTNCLICK WM_USER+1
#define WM_BTNMOUSEMOVE WM_USER+3
#define BITMAP_DISTANCE 2

// CBtnItem

class CBtnItem : public CButton
{
	DECLARE_DYNAMIC(CBtnItem)

public:
	CBtnItem();
	virtual ~CBtnItem();
	Bitmap* m_Bitmap;
private:
	BOOL m_bMouseMove;
	BOOL m_bMouseDown;
	BOOL m_bCheck;
	UINT m_nTimer;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetCheck(BOOL bCheck);
	void SetIcon(HICON hIcon);
	int GetIdealWidth();
public:
//	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};