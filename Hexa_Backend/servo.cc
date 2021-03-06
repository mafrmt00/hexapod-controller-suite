#include <sstream>
#include "hexa_common.h"

CServo::CServo()
: m_bBinaryCommands (false),
m_PulseWidth_Offset(0),
m_DebugLevel(DebugLevel_none)
{

}

CServo::CServo(int IOch, eServoType CurrType)
: m_bBinaryCommands (false),
m_PulseWidth_Offset(0),
m_DebugLevel(DebugLevel_all)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CServo new Object generated." << endl;
	}
	
	SetIOchannel(IOch);
	SetServoType(CurrType);
}

CServo::CServo(int IOch, eServoType CurrType, int iOffset)
: m_bBinaryCommands (false),
m_PulseWidth_Offset(0),
m_DebugLevel(DebugLevel_errors)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CServo new Object generated." << endl;
	}	
	
	SetIOchannel(IOch);
	SetServoType(CurrType);
	SetPulseOffset(iOffset);
}

CServo::~CServo()
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CServo Object deleted." << endl;
	}
}

int CServo::SetPulseOffset(int iOffset) // Problem with extended range, nonlinear range.
{
	m_PulseWidth_Offset = iOffset;

	return 0;
}

int CServo::SetIOchannel(int IOch)
{
	int iReturnValue = -1;	
	
	//Hardcoded range check
	if ((IOch >= 0) && (IOch <=32))
	{
		if (m_DebugLevel >= DebugLevel_all)
		{	
			cout << "Info:  CServo::SetIOchannel  Channel: " << IOch << endl;
		}
		
		m_IOchannel = IOch;
		iReturnValue = 0;
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error: CServo::SetIOchannel out of Range." << endl;
		}		
		//Invalid
		m_IOchannel = 0xFF;	
	}

	return iReturnValue;	
}

int CServo::SetServoType(eServoType CurrType)
{
	int iReturnValue = 0;
	
	switch(CurrType)
	{
		case ServoType_Normal:
			if (m_DebugLevel >= DebugLevel_all)
			{	
				cout << "Info:  CServo::SetServoType  Type: Normal" << endl;
			}
			
			m_PulseWidth_LimitMax =  2100;
			m_PulseWidth_LimitMin = 900;			
			break;
		
		case ServoType_Extended:
			if (m_DebugLevel >= DebugLevel_all)
			{	
				cout << "Info:  CServo::SetServoType  Type: Extended" << endl;
			}
			
			m_PulseWidth_LimitMax =  2500;
			m_PulseWidth_LimitMin = 500;				
			break;
		
		default:
			
			if (m_DebugLevel >= DebugLevel_errors)
			{
				cout << "Error: CServo::SetServoType out of Range." << endl;
			}
			
			m_PulseWidth_LimitMax =  2100;
			m_PulseWidth_LimitMin = 900;	

			iReturnValue = -1;
			break;
	}
	
	return iReturnValue;
}

int CServo::SetPulseWidth(int iPwidth, bool bSimulateOnly)
{
	int iReturnValue = -1;
	
	iPwidth += m_PulseWidth_Offset;
	
	if ((iPwidth >= m_PulseWidth_LimitMin) && (iPwidth <=m_PulseWidth_LimitMax ))
	{
		//OK Pulsewidth is in Range
		if (false == bSimulateOnly)
		{
			m_PulseWidth_Current = iPwidth;
		}
		iReturnValue = 0;
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			std::cout << "Error: CServo::SetPulseWidth out of Range." << endl;
		}
	}
	
	return iReturnValue;
}

int CServo::GetSSC32String(stringstream& sConf)
{
	stringstream sNewCommandSet;
	
	if (m_bBinaryCommands)
	{
		sNewCommandSet << char(m_IOchannel + 0x80); // Servo Number
		sNewCommandSet << char((m_PulseWidth_Current & 0xFF00) >> 8); // Pulse Width MSB
		sNewCommandSet << char(m_PulseWidth_Current & 0xFF); // Pulse Width LSB
	}	
	else
	{
		sNewCommandSet << "#" << m_IOchannel;
		sNewCommandSet << "P" << m_PulseWidth_Current;

		string sOutDisplay;

		sOutDisplay = sNewCommandSet.str();

		if (m_DebugLevel >= DebugLevel_all)
		{	
			cout << "Info:  CServo::GetSSC32String ASCII Commandstring generated: " << sOutDisplay << endl;
		}		
	}

	sConf << sNewCommandSet.str();
	return 0;
}

int CServo::FinalizeSSC32String(stringstream& sConf, int iMoveTime)
{
	if (m_bBinaryCommands)
	{
		sConf << char(m_IOchannel + 0xA1); // Move Time
		sConf << char((iMoveTime & 0xFF00) >> 8); // Pulse Width MSB
		sConf << char(iMoveTime & 0xFF); // Pulse Width LSB
	}
	else
	{
		sConf << "T" << iMoveTime << char(13);

		string sOutDisplay;

		sOutDisplay = sConf.str();

		if (m_DebugLevel >= DebugLevel_all)
		{	
			cout << "Info:  CServo::FinalizeSSC32String ASCII Commandstring finished : " << sOutDisplay << endl;
		}
	}
	return 0;
}

int CServo::SetDebugLevel(eDebugLevel NewDebugLevel)
{
	m_DebugLevel = NewDebugLevel;
	return 0;
}
