#include "hexa_common.h"

CLeg::CLeg()
: m_pKnee(NULL)
, m_CurrentLegAngle(0)
, m_DebugLevel(DebugLevel_none)
{

}

CLeg::CLeg(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir,  double dAngleCalibration,
			double dFemurLength, double dTibiaLength, double dTibiaOffset)
: m_pKnee(NULL)
, m_CurrentLegAngle(0)
, m_DebugLevel(DebugLevel_all)
{
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CLeg new Object generated." << endl;
	}
	
	SetLegParams(dFemurLength, dTibiaLength, dTibiaOffset);
	CalculateConstants();
	
	SetKneeParams(KneeIOch, KneeCurrType, dKneeAngleOffset, bKneeInvertDir, dAngleCalibration);
}

CLeg::~CLeg(void)
{
	if (m_pKnee)
	{
		delete m_pKnee;
		m_pKnee = NULL;
	}
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CLeg Object deleted." << endl;
	}	
}

int CLeg::SetKneeParams(int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dAngleCalibration)
{
	if (NULL != m_pKnee)
	{
		delete m_pKnee;
		m_pKnee = NULL;
	}

	m_pKnee = new CJoint(KneeIOch, KneeCurrType, dKneeAngleOffset, bKneeInvertDir, dAngleCalibration);

	return 0;
}


int CLeg::SetLegParams(double dFemurLength, double dTibiaLength, double dTibiaOffset)
{
	m_FemurLength = dFemurLength;
	m_TibiaLength = dTibiaLength;
	m_TibiaOffset = dTibiaOffset;
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CLeg::SetLegParams  Tibia: Length " << m_TibiaLength << "mm, Offset " << m_TibiaOffset << "mm Femur Length: " << m_FemurLength << "mm."<< endl;
	}	
	
	return 0;
}

int CLeg::CalculateConstants(void)
{
	double dSquareLen = 0;
	
	dSquareLen += pow(m_TibiaLength, 2.0);
	dSquareLen += pow(m_TibiaOffset, 2.0);
	
	m_TibiDiagonal = sqrt(dSquareLen);
	
	double dCosineAngle = 0;
	
	dCosineAngle += dSquareLen;
	dCosineAngle += pow(m_TibiaLength, 2.0);
	dCosineAngle -=  pow(m_TibiaOffset, 2.0);
	
	dCosineAngle /= 2 * m_TibiaLength * m_TibiDiagonal;
	
	m_TibiHelperAngle = acos(dCosineAngle);
	
	if (m_DebugLevel >= DebugLevel_all)
	{	
		cout << "Info:  CLeg::CalculateConstants From Tibia: Length " << m_TibiaLength << "mm, Offset " << m_TibiaOffset << "mm Calculated Constants: Diagonal " << m_TibiDiagonal << "mm Angle "<< (m_TibiHelperAngle / M_PI) << "*PI."<< endl;
	}	

	return 0;
}

int CLeg::SetLength(double dLength, bool bSimulateOnly)
{
	int iReturnValue = -1;
	double dKneeAngle;
	
	if (CalculateKneeAngle(dLength, dKneeAngle) >= 0)
	{
		iReturnValue = m_pKnee->SetAngle(dKneeAngle, bSimulateOnly);
		
		if (iReturnValue >= 0)
		{
			if (false == bSimulateOnly)
			{
				//Saved or not, calculate Angle to given Length
				CalculateResultingLegAngle(dLength);

				if (false == bSimulateOnly)
				{
					m_CurrentLength = dLength;
					m_CurrentLegAngle = m_ResultingLegAngle;
				}
			}
		}
	}
	else
	{
		if (m_DebugLevel >= DebugLevel_errors)
		{
			cout << "Error:  CLeg::SetLength out of Range: " << dLength << "mm." << endl;
		}		
	}
	
	return iReturnValue;
}

int CLeg::GetResultingLegAngle(double& dResAngle)
{
	dResAngle = m_ResultingLegAngle;
	return 0;
}

int CLeg::CalculateResultingLegAngle(double dCurrentLength)
{
	double dCosineAngle = 0;
	
	dCosineAngle += pow(dCurrentLength, 2.0);
	dCosineAngle += pow(m_FemurLength, 2.0);
	dCosineAngle -= pow(m_TibiDiagonal, 2.0);
	
	dCosineAngle /= 2 * dCurrentLength * m_FemurLength;

	m_ResultingLegAngle = acos(dCosineAngle);
	
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CLeg::CalculateResultingLegAngle calculated an Angle " << (m_ResultingLegAngle / M_PI) << "*PI." << endl;
	}	

	return 0;	
}

int CLeg::CalculateKneeAngle(double dLength, double& dKneeAngle)
{
	double dCosineAngle = 0;
	
	dCosineAngle += pow(m_FemurLength, 2.0);
	dCosineAngle += pow(m_TibiDiagonal, 2.0);
	dCosineAngle -= pow(dLength, 2.0);
	
	
	dCosineAngle /= 2 * m_FemurLength * m_TibiDiagonal;
	
	dKneeAngle = acos(dCosineAngle);
	
	dKneeAngle -= m_TibiHelperAngle;
	
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CLeg::CalculateKneeAngle From Length: " << dLength << "mm, calculated an Angle " << (dKneeAngle / M_PI) << "*PI." << endl;
	}
	
	return 0;
}

int CLeg::GetSSC32String(stringstream& sConf)
{
	return m_pKnee->GetSSC32String(sConf);
}

int CLeg::FinalizeSSC32String(stringstream& sConf, int iMoveTime)
{
	return m_pKnee->FinalizeSSC32String(sConf, iMoveTime);
}

int CLeg::SetDebugLevel(eDebugLevel NewDebugLevel)
{
	m_pKnee->SetDebugLevel( NewDebugLevel);
	
	m_DebugLevel = NewDebugLevel;
	return 0;
}
