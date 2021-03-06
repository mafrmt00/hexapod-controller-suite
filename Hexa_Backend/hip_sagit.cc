#include "hexa_common.h"

CHipSagittal::CHipSagittal()
: m_pHipSagitJoint(NULL),
m_pLeg(NULL),
m_DebugLevel(DebugLevel_none)
{

}

CHipSagittal::CHipSagittal(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
						int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir,  double dHipAngleCalibration,
						double dFemurLength, double dTibiaLength, double dTibiaOffset)
: m_pHipSagitJoint(NULL),
m_pLeg(NULL),
m_DebugLevel(DebugLevel_all)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHipSagittal new Object generated." << endl;
	}
	
	m_pHipSagitJoint = new CJoint( HipSIOch, HipSCurrType, dHipSAngleOffset,  bHipSInvertDir, dHipAngleCalibration);
	m_pLeg = new CLeg( KneeIOch, KneeCurrType, dKneeAngleOffset, bKneeInvertDir, dKneeAngleCalibration, dFemurLength, dTibiaLength, dTibiaOffset);
}

CHipSagittal::~CHipSagittal(void)
{	
	if(m_pHipSagitJoint != NULL)
	{
		delete m_pHipSagitJoint;
		m_pHipSagitJoint = NULL;
	}
	
	if (m_pLeg != NULL)
	{
		delete m_pLeg;
		m_pLeg = NULL;
	}
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHipSagittal Object deleted." << endl;
	}	
}

int CHipSagittal::SetPosition(double dDistance, double dHeight, bool bSimulateOnly)
{
	int iReturnValue = -1;
	
	double dLegLen;
	double dHipAng;
	
	if (CalculateParams(dDistance, dHeight, dLegLen, dHipAng) >= 0)
	{
		if( m_pLeg->SetLength(dLegLen, bSimulateOnly) >= 0)
		{
			double dResLegAng;
			
			if (m_pLeg->GetResultingLegAngle(dResLegAng) >= 0)
			{
				if (m_pHipSagitJoint->SetAngle(dHipAng - dResLegAng, bSimulateOnly) >= 0)
				{
					iReturnValue = 0;
				}
				else
				{
					if (m_DebugLevel >= DebugLevel_errors)
					{
						cout << "Error:  CHipSagittal::SetPosition Angle out of Range: " << (dHipAng / M_PI) << "*PI." << endl;
					}			
				}			
			}
		}
		else
		{
			if (m_DebugLevel >= DebugLevel_errors)
			{
				cout << "Error:  CHipSagittal::SetPosition Length out of Range: " << dLegLen << "mm." << endl;
			}	
		}		
		
		

	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CHipSagittal::SetPosition Calculation failed From Distance " << dDistance << "mm, Height" << dHeight << "mm" << endl;
		}
	}
	
	return iReturnValue;
}

int CHipSagittal::CalculateParams(double dDistance, double dHeight, double& dLegLen, double& dHipAng)
{
	int iReturnValue = 0;
	
	double dLegLenSquare = 0;
	
	dLegLenSquare += pow(dDistance, 2);
	dLegLenSquare += pow(dHeight, 2);
	
	dLegLen = sqrt(dLegLenSquare);
	
	double dHipAngSin = 0;
	
	dHipAngSin = dHeight / dLegLen;
	
	dHipAng = asin(dHipAngSin);
	
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CHipSagittal::CalculateParams From Distance " << dDistance << "mm, Height" << dHeight << "mm, Calculated: Leg Length" << dLegLen << "mm, Sagittal Angle " << (dHipAng/M_PI) << "*PI." << endl;
	}	
	
	return iReturnValue;
}

int CHipSagittal::GetSSC32String(stringstream& sConf)
{
	int iReturnValue = 0;
	
	if (m_pHipSagitJoint->GetSSC32String(sConf) < 0)
	{
		iReturnValue = -1;
	}
	
	if (m_pLeg->GetSSC32String(sConf) < 0)
	{
		iReturnValue = -1;
	}	
	
	if (iReturnValue < 0)
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CHipSagittal::GetSSC32String failed" << endl;
		}	
	}
	
	return iReturnValue;
}
