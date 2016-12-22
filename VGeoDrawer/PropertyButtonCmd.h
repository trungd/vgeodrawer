#pragma once
#include "customitem.h"
#include "VGObject.h"
#include "CommandArray.h"

class CPropertyButtonCmdItem :
	public ICustomItem
{
public:
	CPropertyButtonCmdItem(void);
public:
	~CPropertyButtonCmdItem(void);
public:
	virtual CPropertyGrid::EEditMode GetEditMode();
	virtual void DrawItem(CDC& dc, CRect rc, bool focused);
	virtual bool OnEditItem();

	CVGButtonBase* m_obj;
	CCommandArray* m_cmdArray;
};
