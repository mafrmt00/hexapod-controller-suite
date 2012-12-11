#include "hexa_common.h"

CBodyPart::CBodyPart()
: m_PartPositionSide(0xFFFF)
, m_PartPositionLineup(0xFFFF)
{
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CBodyPart empty Object created." << endl;
	}
}

CBodyPart::CBodyPart( int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
		int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
		int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, double dHipTrAngleCalibration,
		int PartPositionSide, int PartPositionLineup,
		double dHeightOffs, double dDistanceOffs, double dSideOffs,
		double dFemurLength, double dTibiaLength, double dTibiaOffset)
: CCoxa( KneeIOch,  KneeCurrType,  dKneeAngleOffset,  bKneeInvertDir,  dKneeAngleCalibration,
		 HipSIOch,  HipSCurrType,  dHipSAngleOffset,  bHipSInvertDir,  dHipAngleCalibration,
		 HipTrIOch,  HipTrCurrType,  dHipTrAngleOffset,  bHipTrInvertDir,  dHipTrAngleCalibration,
		 dHeightOffs,  dDistanceOffs,  dSideOffs,
		 dFemurLength,  dTibiaLength,  dTibiaOffset)
, m_PartPositionSide(PartPositionSide)
, m_PartPositionLineup(PartPositionLineup)
{
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CBodyPart Object created. Position: " << m_PartPositionSide << m_PartPositionLineup << endl;
	}
}

CBodyPart::~CBodyPart()
{
	if (m_DebugLevel >= DebugLevel_all)
	{
		cout << "Info:  CBodyPart Object deleted." << endl;
	}
}
