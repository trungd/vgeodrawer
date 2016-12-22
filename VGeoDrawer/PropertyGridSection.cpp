#include "stdafx.h"
#include "PropertyGrid.h"

CPropertyGrid::CSection::~CSection()
{
	for (int i=0;i<m_items.GetSize();i++)
		delete m_items[i];
}

CPropertyGrid::CItem* CPropertyGrid::CSection::FindItem(HITEM hi)
{
	for (int i=0;i<m_items.GetSize();i++)
		if (m_items[i]->m_id==hi) return m_items[i];
	return NULL;
}

int CPropertyGrid::CSection::FindItemIndex(HITEM hi)
{
	for (int i=0;i<m_items.GetSize();i++)
		if (m_items[i]->m_id==hi) return i;
	return -1;
}