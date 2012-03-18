class CLeg
{
public:
	CLeg(int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir = false, double dFemurLength = 76.d, double dTibiaLength = 95.d, double dTibiaOffset = 44.d);		
	~CLeg(void);

	int SetLength(double dLength);
	int GetResultingLegAngle(double& dResAngle);
	int GetSSC32String(string& sConf);

protected:
	eDebugLevel m_DebugLevel;
	CJoint* m_pKnee;

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