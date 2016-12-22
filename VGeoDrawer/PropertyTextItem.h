#pragma once
#include "customitem.h"
#include "VGObject.h"

class CPropertyTextItem :
	public ICustomItem
{
public:
	CPropertyTextItem(void);
public:
	~CPropertyTextItem(void);
public:
	virtual CPropertyGrid::EEditMode GetEditMode();
	virtual void DrawItem(CDC& dc, CRect rc, bool focused);
	virtual bool OnEditItem();

	CVGText* m_obj;
};
