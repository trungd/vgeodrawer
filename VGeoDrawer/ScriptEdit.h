#pragma once


// CScriptEdit

class CScriptEdit : public CEdit
{
	DECLARE_DYNAMIC(CScriptEdit)

public:
	CScriptEdit();
	virtual ~CScriptEdit();
	
	CFont m_Font;

	void InitCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


