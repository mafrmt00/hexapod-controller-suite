class CHipSagittal
{
	
public:
	CHipSagittal(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, 
				int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, 
				double dFemurLength, double dTibiaLength, double dTibiaOffset);
	~CHipSagittal(void);

	int SetPosition(double dDistance, double dHeight);
	int GetSSC32String(string& sConf);

protected:
	eDebugLevel m_DebugLevel;

private:
	CLeg* m_pLeg;
	CJoint* m_pHipSagitJoint;

	int CalculateParams(double dDistance, double dHeight, double& dLegLen, double& dHipAng);
	
};