#include "hexa_common.h"

CJoint::CJoint()
: m_bIvertRotDirection(false),
  m_dAngleCalibration(0.0),
  m_dAngleOffset(0)
{

}

CJoint::CJoint(int IOch, eServoType CurrType, double dAngleOffset, bool bInvertDir, double dAngleCalibration)
: CServo(IOch, CurrType),
m_bIvertRotDirection(false),
m_dAngleCalibration(0.0),
m_dAngleOffset(0)
{
	m_bIvertRotDirection = bInvertDir;
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CJoint new Object generated." << endl;
	}
	
	if (dAngleOffset != 0.d)
	{
		SetAngleOffset	(dAngleOffset);
	}
	
	if (dAngleCalibration != 0.d)
	{
		SetAngleCalibration(dAngleCalibration);
	}
}

CJoint::~CJoint()
{

}

int CJoint::InvertAngle(double dAngleSource, double& dAngleTarget)
{
	if ( dAngleSource <= M_PI)
	{
		dAngleTarget = (2.d * M_PI) - dAngleSource;
	}
	else
	{
		dAngleTarget = M_PI - (dAngleSource - M_PI);
	}

	dAngleTarget = fmod ( dAngleTarget,  M_PI * 2.d);	
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CJoint::InvertAngle Inverted " << (dAngleSource / M_PI) << "*PI" <<  "To:" << (dAngleTarget / M_PI) << "*PI." <<endl;
	}
	
	return 0;
}

int CJoint::RadToPulse(double dAngleSource, int& iPulseWidth)
{
	int iReturnValue = -1;
	double dAngle;
	
	if (m_bIvertRotDirection)
	{
		InvertAngle(dAngleSource, dAngle);
	}
	else
	{
		dAngle = dAngleSource;
	}
	
	if (m_dAngleCalibration != 0.d)
	{
		dAngle += m_dAngleCalibration;
		dAngle = fmod ( dAngle,  M_PI * 2.d);	
	}
		
	if (((dAngle >= 0.d) && (dAngle <= (M_PI / 2.d))) || (( dAngle <= (2.d * M_PI) ) && ( dAngle >= ((3.d * M_PI)  / 2.d))))
	{
		// Lower extended Range
		if (( dAngle >= ((3.d * M_PI) / 2.d))  && (dAngle < ((7.d * M_PI) / 4.d) ))
		{
			iPulseWidth = (int) (500.d + ((400.d / (M_PI/4.d)) * (dAngle - ((3.d * M_PI) / 2.d)) ));
			iReturnValue = 0;
			
			if (m_DebugLevel >= DebugLevel_all)
			{
				cout << "Info:  CJoint::RadToPulse Lower extended Range " << (dAngle / M_PI) << "*PI" << " Converted to:" << iPulseWidth << "Pulsewidth." << endl;
			}			
		}
		
		//Standard Range
		if (((dAngle >= 0.d) && (dAngle <= (M_PI / 4.d))) || (( dAngle <= (2.d * M_PI) ) && ( dAngle >= ((7.d * M_PI)  / 4.d))))
		{
			if ((dAngle >= 0.d)  &&  (dAngle <= (M_PI / 4.d)))
			{
				iPulseWidth = (int) (1500.d + ((1200.d / (M_PI/2.d)) * (dAngle)));
				iReturnValue = 0;
			}
			
			if (( dAngle <= (2.d * M_PI) ) && ( dAngle >= ((7.d * M_PI)  / 4.d)))
			{
				iPulseWidth = (int) (300.d + ((1200.d / (M_PI/2.d)) * (dAngle -  ((3.d * M_PI) / 2.d))));
				iReturnValue = 0;				
			}
			
			if (m_DebugLevel >= DebugLevel_all)
			{
				cout << "Info:  CJoint::RadToPulse Standard Range " << (dAngle / M_PI) << "*PI" << " Converted to:" << iPulseWidth << "Pulsewidth." << endl;
			}				
		}
		
		//Upper extended Range
		if (( dAngle > (M_PI/4.d)) && (dAngle <=  (M_PI/2.d) ))
		{
			iPulseWidth = (int) (2100.d + ((400.d / (M_PI/4.d)) * (dAngle - (M_PI/4.d)) ));
			iReturnValue = 0;
			
			if (m_DebugLevel >= DebugLevel_all)
			{
				cout << "Info:  CJoint::RadToPulse Upper extended Range " << (dAngle / M_PI) << "*PI" << " Converted to:" << iPulseWidth << "Pulsewidth." << endl;
			}				
		}
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CJoint::RadToPulse out of Range:" << (dAngle / M_PI) << "*PI" << endl;
		}
	}
		
	
	return iReturnValue;
}

int CJoint::SetAngleCalibration(double dOffset)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CJoint::SetAngleCalibration new Offset set:" << (dOffset / M_PI) << "*PI."<< endl;
	}	
	
	m_dAngleCalibration = fmod ( dOffset,  M_PI * 2.d);

	return 0;
}

int CJoint::SetAngleOffset(double dOffset)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CJoint::SetAngleOffset new Offset set:" << (dOffset / M_PI) << "*PI."<< endl;
	}	
	
	m_dAngleOffset = fmod ( dOffset,  M_PI * 2.0);

	return 0;
}

int CJoint::SetAngle(double dAngle)
{
	int iNewPulseWidth;
	int iReturnValue;
	
	dAngle += m_dAngleOffset;
	
	while (dAngle < 0)
	{
		dAngle += (2.d * M_PI);
	}
	
	dAngle = fmod ( dAngle,  M_PI * 2.d);
		
	iReturnValue = RadToPulse(dAngle, iNewPulseWidth);
	
	if (iReturnValue >= 0)
	{
		iReturnValue = SetPulseWidth(iNewPulseWidth);
	}
	
	return iReturnValue;
}

int CJoint::SetDebugLevel(eDebugLevel NewDebugLevel)
{
	CServo::SetDebugLevel(NewDebugLevel);
	m_DebugLevel = NewDebugLevel;
	return 0;
}
