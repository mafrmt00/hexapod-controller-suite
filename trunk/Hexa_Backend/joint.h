class CJoint : public CServo
{
public:
	CJoint(int IOch, eServoType CurrType, double dAngleOffset, bool bInvertDir = false);	

	int SetAngle(double dAngle); //Sets the current Angle, in radians.
	int SetAngleOffset(double dOffset);

private:
	double m_dAngleCurrent;
	double m_dAngleOffset;
	bool m_bIvertRotDirection;

	int RadToPulse(double dAngleSource, int& iPulseWidth);
	int InvertAngle(double dAngleSource, double& dAngleTarget);
};