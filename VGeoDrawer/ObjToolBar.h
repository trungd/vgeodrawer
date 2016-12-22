#pragma once
#include "VGeoDrawerDoc.h"
#include "ObjBtnDlg.h"
#include "ButtonPopup.h"
#include "BCMenu.h"

#define BUTTON_SIZE 40
#define BUTTON_DISTANCE 2

#define TOOL_MENU_START 5345

class CVGeoDrawerDoc;
class CObjToolBar : public CSizingControlBar
{
	DECLARE_DYNAMIC(CObjToolBar)

public:
	CObjToolBar();
	virtual ~CObjToolBar();
	CVGeoDrawerDoc* pDoc;
	CArray<CStringArray*,CStringArray*> m_btnTextArray;
	CArray<CBtnItem*,CBtnItem*> m_btnArray;
	int m_nSelection;
	void SetSelection(int nSelection);
	void LoadButtons();
	void RemoveAll();
	void ReArangeButton();
	BCMenu* m_Menu;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
private:
	BOOL m_bSelecting;
	CButtonPopup* popup;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnBtnClk(WPARAM wParam, LPARAM lParam);
	LRESULT OnMenuClk(WPARAM wParam, LPARAM lParam);
	LRESULT OnBtnMouseMove(WPARAM wParam, LPARAM lParam);
	BOOL m_bHorz;
protected:
	CSize CalcDynamicLayout(int nLength, DWORD dwMode);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnCommand(UINT nIndex);
	void PopupMenu(int index, bool bAnimate=true);
	void OnUpdateCommand(UINT nIndex, CCmdUI* pCmdUI);
};


