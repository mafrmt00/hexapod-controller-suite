#include <iostream>
#include <cmath>

using namespace std;

#include "my_types.h"
#include "servo.h"
#include "joint.h"
#include "leg.h"
#include "hip_sagit.h"
#include "hip.h"

CHip::CHip(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, 
			int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, 
			int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, 
			double dHeightOffs, double dDistanceOffs, double dSideOffs,
			double dFemurLength, double dTibiaLength, double dTibiaOffset)
: m_pRestLeg(NULL),
m_pTransverseJoint(NULL),
m_DebugLevel(DebugLevel_all)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHip Object created." << endl;
	}
	
	m_pRestLeg = new CHipSagittal(KneeIOch, KneeCurrType, dKneeAngleOffset, bKneeInvertDir,  HipSIOch, HipSCurrType, dHipSAngleOffset, bHipSInvertDir, dFemurLength, dTibiaLength, dTibiaOffset);
	m_pTransverseJoint = new CJoint(HipTrIOch, HipTrCurrType, dHipTrAngleOffset, bHipTrInvertDir);
	SetSagittalOffset(dHeightOffs, dDistanceOffs, dSideOffs);
}

CHip::~CHip(void)
{
	if (m_pRestLeg != NULL)
	{
		delete m_pRestLeg;
		m_pRestLeg = NULL;
	}
	
	if (m_pTransverseJoint != NULL)
	{
		delete m_pTransverseJoint;
		m_pTransverseJoint = NULL;
	}	
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHip Object deleted." << endl;
	}		
}

int CHip::SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z)
{
	int iReturnValue = -1;
	
	double dTransverseAngle;
	double dDistance;
	double dHeight;
	
	if (CalculateParams(dPosition_X, dPosition_Y, dPosition_Z, dTransverseAngle, dDistance, dHeight) >= 0)
	{
		if(m_pRestLeg->SetPosition(dDistance, dHeight) >= 0)
		{
			if (m_pTransverseJoint->SetAngle(dTransverseAngle) >= 0)
			{
				iReturnValue = 0;
			}
			else
			{
				if (m_DebugLevel >= DebugLevel_errors)
				{
					cout << "Error:  CHip::SetPosition Angle out of Range." << endl;
				}
			}
		}
		else
		{
			if (m_DebugLevel >= DebugLevel_errors)
			{
				cout << "Error:  CHip::SetPosition Leg Parameter out of Range." << endl;
			}
		}
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CHip::SetPosition Parameter Calculation failed." << endl;
		}		
	}
}

int CHip::SetSagittalOffset(double dHeight, double dDistance, double dSide)
{
	m_dSagittalOffset_Height = dHeight;
	m_dSagittalOffset_Distance = dDistance;
	m_dSagittalOffset_Side = dSide;
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CHip::SetSagittalOffset New Values: Height " << m_dSagittalOffset_Height << "mm, Distance "<< m_dSagittalOffset_Distance << "mm, Side " << m_dSagittalOffset_Side << "mm." << endl;
	}	
	
	return 0;
}

int CHip::CalculateParams(double dPosition_X, double dPosition_Y, double dPosition_Z, double& dTransverseAngle, double& dDistance, double& dHeight)
{
	double dD1Square = 0;
	double dD1 = 0;
	
	dD1Square += pow(dPosition_X, 2);
	dD1Square += pow(dPosition_Y, 2);
	
	dD1 = sqrt(dD1Square) ;
	

	double dLSquare = 0;
	double dL = 0;

	dLSquare += dD1Square;
	dLSquare -= pow(m_dSagittalOffset_Side, 2);
	
	dL = sqrt(dLSquare);
	
	
	double dD2Square = 0;
	double dD2 = 0;	
	
	dD2Square += dLSquare;
	dD2Square -= pow(m_dSagittalOffset_Side, 2);
	
	dD2 = sqrt(dD2Square);
	
		
	double dL2Square = 0;
	double dL2 = 0;
	
	dL2Square += dD2Square;
	dD2Square -= pow(m_dSagittalOffset_Side, 2);
	
	dL2 = sqrt(dL2Square);
	
	
	double dTravAngCos = 0;
	
	dTravAngCos =  dPosition_X / dL2;
	
	dTransverseAngle = acos(dTravAngCos);
	dHeight = dPosition_Z - m_dSagittalOffset_Height;
	dDistance = dL - m_dSagittalOffset_Distance;
	
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CHip::CalculateParams from X,Y,Z " << dPosition_X << ", " << dPosition_Y << ", " << dPosition_Z <<". " << dHeight << "mm  Height, " << dDistance << "mm Distance, " << (dTransverseAngle/M_PI) << "*PI Traversal Angle " << endl;
	}
	
	return 0;
}

int CHip::GetSSC32String(string& sConf)
{
	int iReturnValue = 0;
	
	if (m_pTransverseJoint->GetSSC32String(sConf) < 0)
	{
		iReturnValue = -1;
	}
	
	if (m_pRestLeg->GetSSC32String(sConf) < 0)
	{
		iReturnValue = -1;
	}	
	
	if (iReturnValue < 0)
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CHip::GetSSC32String failed" << endl;
		}	
	}
	
	return iReturnValue;
}