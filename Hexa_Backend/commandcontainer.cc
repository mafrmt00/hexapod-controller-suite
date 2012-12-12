#include "hexa_common.h"

CCommandContainer::CCommandContainer()
: m_Command(eCoCo_none)
, m_dParameter01(0)
{

}

CCommandContainer::~CCommandContainer()
{

}

CCommandContainer::CCommandContainer(eComContCommand Command, double dParameter01)
: m_Command(Command)
, m_dParameter01(dParameter01)
{

}

eComContCommand CCommandContainer::GetCommand(void)
{
	return m_Command;
}

double CCommandContainer::GetParam01(void)
{
	return m_dParameter01;
}
