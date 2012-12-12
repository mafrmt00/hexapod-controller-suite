#include "hexa_common.h"

CBody::CBody(const CBody &Origin, int uiPartPositionSideFilter, int uiPartPositionLineupFilter) //Selective Copy Contructor
: m_pHipList(NULL)
{
	if (Origin.m_pHipList != NULL)
	{
		int uiCount = 0;

		m_pHipList = new BodyPartList();

		BodyPartList::iterator i;

		for(i = Origin.m_pHipList->begin(); i != Origin.m_pHipList->end(); ++i)
		{
			if ((uiPartPositionSideFilter == WILDCARD_PARTSSIDEFILTER) || (uiPartPositionSideFilter == (*i)->m_PartPositionSide))
			{
				if ((uiPartPositionLineupFilter == WILDCARD_POSLINEUPFILTER) || (uiPartPositionLineupFilter == (*i)->m_PartPositionLineup))
				{
					AddHip(*i);
					uiCount++;
				}
			}
		}

		if (m_DebugLevel >= DebugLevel_all)
		{
			cout << "Info:  CHipGroup new Object generated. And copied " << uiCount << " Entries." << endl;
		}

	}
}

CBody::CBody(void)
: m_pHipList(NULL)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHipGroup new Object generated." << endl;
	}
	
	m_pHipList = new BodyPartList();
}

CBody::~CBody(void)
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

int CBody::AddHip(CBodyPart* pHip)
{
	m_pHipList->push_back(pHip);
	
	return 0;
}

int CBody::SetDebugLevel(eDebugLevel NewDebugLevel)
{
	m_DebugLevel = NewDebugLevel;
	return 0;
}

int CBody::SetPositionRel_X(double dPositionOffset_X)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPositionRel_X(dPositionOffset_X) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}


int CBody::SetPositionRel_Y(double dPositionOffset_Y)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPositionRel_Y(dPositionOffset_Y) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::SetPositionRel_Z(double dPositionOffset_Z)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPositionRel_Z(dPositionOffset_Z) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::SetPosition_X(double dPosition_X)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_X(dPosition_X) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::SetPosition_Y(double dPosition_Y)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_Y(dPosition_Y) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::SetPosition_Z(double dPosition_Z)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition_Z(dPosition_Z) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->SetPosition(dPosition_X, dPosition_Y, dPosition_Z) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;
}

int CBody::ExecuteCommand(CCommandContainer &Command)
{
	int iReturnValue = 0;

	switch(Command.GetCommand())
	{
		case eCoCo_SetPosition_X:
			SetPosition_X(Command.GetParam01());
			break;

		case eCoCo_SetPosition_Y:
			SetPosition_Y(Command.GetParam01());
			break;

		case eCoCo_SetPosition_Z:
			SetPosition_Z(Command.GetParam01());
			break;

		default:
			break;
	}

	return iReturnValue;
}

int CBody::GetSSC32String(stringstream& sConf)
{
	int iReturnValue = 0;
	BodyPartList::iterator i;
	
	for( i = m_pHipList->begin(); i != m_pHipList->end(); ++i ) 
	{
		if ((*i)->GetSSC32String(sConf) < 0)
		{
			iReturnValue = -1;
		}
	}
	
	return iReturnValue;	
}

int CBody::FinishSSC32String(stringstream& sConf, int iMoveTime)
{
	return (m_pHipList->back())->FinalizeSSC32String(sConf, iMoveTime);
}
