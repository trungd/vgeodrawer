#pragma once
#include "customitem.h"
#include "VGObject.h"
#include "PropertyGrid.h"

class CPropertyGradientPanel :
	public ICustomItem
{
public:
	CPropertyGradientPanel(void);
public:
	~CPropertyGradientPanel(void);
public:
	virtual CPropertyGrid::EEditMode GetEditMode();
	virtual void DrawItem(CDC& dc, CRect rc, bool focused);
	virtual bool OnEditItem();

	CArray<CVGPanel*> m_PanelArr;
};
