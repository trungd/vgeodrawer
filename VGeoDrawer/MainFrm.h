// MainFrm.h : interface of the CMainFrame class
//


#include "VGeoDrawer.h"
#include "CommandCtrlBar.h"
#include "PropertiesBar.h"
#include "ObjListBar.h"
#include "BCMenu.h"
#include "ObjToolBar.h"
#include "CustomizeToolboxDlg.h"
#include "AddToolDlg.h"
#include "ConstructionStepsBar.h"
#include "PageViewBar.h"
#include "WatchBar.h"
//#include "CommandPromptBar.h"

#define IDR_PROPERTIES 100
#define IDR_COMMAND 101
#define IDR_OBJLIST 102
#define IDR_CONSTRUCTIONSTEPS 103
#define IDR_OBJTOOLBAR 104
#define IDR_MOTION 105
#define IDR_TBAR_PAGE 106
#define IDR_TBAR_PAGE_LIST 107
#define IDR_PAGE_VIEW 108
#define IDR_WATCH_BAR 109

#define IDC_CBPAGE 8237

class CPropertiesBar;
class CVGObjContainer;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar m_wndStatusBar;
	CToolBar m_wndToolBar;
	CToolBar m_wndMotionController;
	CToolBar m_wndPageTBar;
	CObjToolBar m_wndObjToolBar;
	CComboBox m_cbPage;
	CFont m_Font;
	//CCommandPromptBar m_wndCommandPromptBar;

	CVGeoDrawerDoc* pDoc;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	CCommandCtrlBar m_wndCommand;
	CConstructionStepsBar m_wndConstructionSteps;
	CPropertiesBar m_wndProperties;
	CObjListBar m_wndList;
	CPageViewBar m_wndPageViewBar;
	CWatchBar m_wndWatchBar;
	BOOL m_bFullScreen;
	BOOL m_bFullScreenShowMode;
	
	CVGeoDrawerDoc* GetDocument();
public:
	afx_msg void OnViewInputWindow();
public:
	afx_msg void OnUpdateViewInputWindow(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateViewFullscreen(CCmdUI *pCmdUI);
public:
	afx_msg void OnViewFullscreen();
	HMENU NewMenu();
	BCMenu m_menu;
	//BCMenu m_ToolMenu;
	CArray<CStringArray*,CStringArray*>m_toolBarArray;

private:
	void LoadObjToolbar();

private:
	CRect rectFull;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnUpdateViewPropertieswindow(CCmdUI *pCmdUI);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewPropertieswindow();
	void SaveState(void);
	void LoadState(void);
	afx_msg void OnViewPropertiesWindow();
	afx_msg void OnUpdateViewPropertiesWindow(CCmdUI *pCmdUI);
	afx_msg void OnViewCommandInput();
	afx_msg void OnUpdateViewCommandInput(CCmdUI *pCmdUI);
	afx_msg void OnViewGeoobjWindow();
	afx_msg void OnUpdateViewGeoobjWindow(CCmdUI *pCmdUI);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI *pCmdUI);
	afx_msg void OnOptionsCustomizeToolbox();
	afx_msg void OnOptionsNewTool();
	afx_msg void OnOptionsEquationeditor();
	afx_msg void OnObjectsProperties();
	afx_msg void OnViewMotionController();
	afx_msg void OnUpdateViewMotionController(CCmdUI *pCmdUI);
	afx_msg void OnEditAnimateStart();
	afx_msg void OnViewShowmode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateViewShowmode(CCmdUI *pCmdUI);
	afx_msg void OnExitFullMode();
public:
	afx_msg void OnViewPageViewBar();
public:
	afx_msg void OnUpdateViewPageViewBar(CCmdUI *pCmdUI);
public:
	afx_msg void OnViewWatch();
public:
	afx_msg void OnUpdateViewWatch(CCmdUI *pCmdUI);
	afx_msg void OnToolCommand(UINT nIndex);
	afx_msg void OnUpdateToolCommand(CCmdUI* pCmdUI);
	afx_msg void OnSelChangePage();
};