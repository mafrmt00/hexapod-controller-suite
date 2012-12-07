class CHip
{
public:
	CHip(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
			int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
			int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, double dHipTrAngleCalibration,
			double dHeightOffs = 27.d, double dDistanceOffs = 27.d, double dSideOffs = 5.d,
			double dFemurLength = 76.d, double dTibiaLength = 95.d, double dTibiaOffset = 44.d);	

	~CHip(void);
	int SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z);
	int SetPosition_X(double dPosition_X);
	int SetPosition_Y(double dPosition_Y);
	int SetPosition_Z(double dPosition_Z);

	int SetPositionRel_X(double dPositionOffset_X);
	int SetPositionRel_Y(double dPositionOffset_Y);
	int SetPositionRel_Z(double dPositionOffset_Z);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

private:
	CHipSagittal* m_pRestLeg;
	CJoint* m_pTransverseJoint;

	bool m_bCurrentPositionValid;
	double m_bCurrentPosition_X;
	double m_bCurrentPosition_Y;
	double m_bCurrentPosition_Z;

	double m_dSagittalOffset_Height;
	double m_dSagittalOffset_Distance;
	double m_dSagittalOffset_Side;

	int StorePosition(bool bValid = false, double dPosition_X = 0.d, double dPosition_Y = 0.d, double dPosition_Z = 0.d);
	int SetSagittalOffset(double dHeight, double dDistance, double dSide);
	int CalculateParams(double dPosition_X, double dPosition_Y, double dPosition_Z, double& dTransverseAngle, double& dDistance, double& dHeight);

protected:
	eDebugLevel m_DebugLevel;
};
