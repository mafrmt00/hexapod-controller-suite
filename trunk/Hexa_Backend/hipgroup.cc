#include <iostream>
#include <list>

using namespace std;

#include "my_types.h"
#include "servo.h"
#include "joint.h"
#include "leg.h"
#include "hip_sagit.h"
#include "hip.h"
#include "hipgroup.h"

CHipGroup::CHipGroup(void)
: m_pHipList(NULL)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHipGroup new Object generated." << endl;
	}
	
	m_pHipList = new HipList();
}

CHipGroup::~CHipGroup(void)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHipGroup  Object deleted." << endl;
	}
	
	if (m_pHipList != NULL)
	{
		delete m_pHipList;
		m_pHipList = NULL;
	}
}

int CHipGroup::AddHip(CHip* pHip)
{
	m_pHipList->push_back(pHip);
	
	return 0;
}

int CHipGroup::SetDebugLevel(eDebugLevel NewDebugLevel)
{
	m_DebugLevel = NewDebugLevel;
	return 0;
}

int CHipGroup::SetPosition_X(double dPosition_X)
{
	int iReturnValue = 0;
	HipList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_X(dPosition_X) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CHipGroup::SetPosition_Y(double dPosition_Y)
{
	int iReturnValue = 0;
	HipList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_Y(dPosition_Y) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CHipGroup::SetPosition_Z(double dPosition_Z)
{
	int iReturnValue = 0;
	HipList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_Z(dPosition_Z) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CHipGroup::SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z)
{
	int iReturnValue = 0;
	HipList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition(dPosition_X, dPosition_Y, dPosition_Z) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CHipGroup::GetSSC32String(string& sConf)
{
	int iReturnValue = 0;
	HipList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->GetSSC32String(sConf) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;	
}

int CHipGroup::FinishSSC32String(string& sConf, int iMoveTime)
{
	return (m_pHipList->back())->FinishSSC32String(sConf, iMoveTime);
}