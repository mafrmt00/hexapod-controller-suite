class CLeg
{
public:
	CLeg(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dAngleCalibration,
			double dFemurLength, double dTibiaLength, double dTibiaOffset);		
	~CLeg(void);

	int SetLength(double dLength);
	int GetResultingLegAngle(double& dResAngle);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	CJoint* m_pKnee;
	eDebugLevel m_DebugLevel;


private:
	double m_FemurLength;
	double m_TibiaLength;
	double m_TibiaOffset;

	double m_TibiDiagonal;
	double m_TibiHelperAngle;

	double m_CurrentLength;

	double m_ResultingLegAngle;

	int CalculateConstants(void);
	int CalculateKneeAngle(double dLength, double& dKneeAngle);
	int CalculateResultingLegAngle(void);
	int SetLegParams(double dFemurLength, double dTibiaLength, double dTibiaOffset);
};
