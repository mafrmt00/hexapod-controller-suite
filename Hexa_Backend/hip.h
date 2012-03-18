class CHip
{
public:
	CHip(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, 
			int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, 
			int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, 
			double dHeightOffs = 27.d, double dDistanceOffs = 27.d, double dSideOffs = 5.d,
			double dFemurLength = 76.d, double dTibiaLength = 95.d, double dTibiaOffset = 44.d);	
	~CHip(void);
	int SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z);
	int GetSSC32String(string& sConf);

protected:
	eDebugLevel m_DebugLevel;

private:
	CJoint* m_pTransverseJoint;
	CHipSagittal* m_pRestLeg;

	double m_dSagittalOffset_Height;
	double m_dSagittalOffset_Distance;
	double m_dSagittalOffset_Side;

	int SetSagittalOffset(double dHeight, double dDistance, double dSide);
	int CalculateParams(double dPosition_X, double dPosition_Y, double dPosition_Z, double& dTransverseAngle, double& dDistance, double& dHeight);
};