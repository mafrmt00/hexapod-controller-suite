class CHipSagittal
{
	
public:
	CHipSagittal(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
				int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
				double dFemurLength, double dTibiaLength, double dTibiaOffset);
	~CHipSagittal(void);

	int SetPosition(double dDistance, double dHeight);
	int GetSSC32String(string& sConf);

private:
	CJoint* m_pHipSagitJoint;
	CLeg* m_pLeg;


	int CalculateParams(double dDistance, double dHeight, double& dLegLen, double& dHipAng);

protected:
	eDebugLevel m_DebugLevel;
};
