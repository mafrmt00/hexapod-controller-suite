#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "my_types.h"
#include "servo.h"


CServo::CServo(int IOch, eServoType CurrType)
: m_bBinaryCommands (false),
m_DebugLevel(DebugLevel_all),
m_PulseWidth_Offset(0)
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
m_DebugLevel(DebugLevel_errors),
m_PulseWidth_Offset(0)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CServo new Object generated." << endl;
	}	
	
	SetIOchannel(IOch);
	SetServoType(CurrType);
	SetPulseOffset(iOffset);
}

int CServo::SetPulseOffset(int iOffset) // Problem with extended range, nonlinear range.
{
	m_PulseWidth_Offset = iOffset;
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

int CServo::SetPulseWidth(int iPwidth)
{
	int iReturnValue = -1;
	
	iPwidth += m_PulseWidth_Offset;
	
	if ((iPwidth >= m_PulseWidth_LimitMin) && (iPwidth <=m_PulseWidth_LimitMax ))
	{
		m_PulseWidth_Current = iPwidth;
		iReturnValue = 0;
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error: CServo::SetPulseWidth out of Range." << endl;
		}
	}
	
	return iReturnValue;
}

int CServo::GetSSC32String(string& sConf)
{
	string sNewCommandSet = "";
	
	if (m_bBinaryCommands)
	{
		string sNewCommand;
		
		sNewCommand = char(m_IOchannel + 0x80); // Servo Number
		sNewCommandSet += sNewCommand;
		
		sNewCommand = char((m_PulseWidth_Current & 0xFF00) >> 8); // Pulse Width MSB
		sNewCommandSet += sNewCommand;
		
		sNewCommand = char(m_PulseWidth_Current & 0xFF); // Pulse Width LSB
		sNewCommandSet += sNewCommand;
		
	}	
	else
	{
		sNewCommandSet += "#";
		ostringstream tmpStream00;
		tmpStream00 << m_IOchannel;
		sNewCommandSet+= tmpStream00.str();
		
		sNewCommandSet += "P";
		ostringstream tmpStream01;
		tmpStream01 << m_PulseWidth_Current;
		sNewCommandSet+= tmpStream01.str();		
		
		if (m_DebugLevel >= DebugLevel_all)
		{	
			cout << "Info:  CServo::GetSSC32String ASCII Commandstring generated: " << sNewCommandSet << endl;
		}		
	}
	
	sConf += sNewCommandSet;
	
	return 0;
}