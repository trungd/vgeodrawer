#pragma once
#include "VGObjContainer.h"

// CCommandEdit
class CVGObjContainer;

class CCommandEdit : public CEdit
{
	DECLARE_DYNAMIC(CCommandEdit)

public:
	CCommandEdit();
	virtual ~CCommandEdit();
	CVGObjContainer* m_objArray;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CFont m_Font;
};


