class CJoint : public CServo
{
public:
	CJoint(	int IOch, eServoType CurrType = ServoType_Normal, 
			double dAngleOffset = 0, bool bInvertDir = false, double dAngleCalibration = 0);	

	int SetAngle(double dAngle); //Sets the current Angle, in radians.
	int SetAngleOffset(double dOffset);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

private:
	double m_dAngleCurrent;
	double m_dAngleOffset; // Offset for Mounting and calculation purpose.
	double m_dAngleCalibration; //Offset for zero-position calibration, is not influenced by Inversion-Flag;
	bool m_bIvertRotDirection;

	int SetAngleCalibration(double dOffset);
	int RadToPulse(double dAngleSource, int& iPulseWidth);
	int InvertAngle(double dAngleSource, double& dAngleTarget);
};