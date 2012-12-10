class CJoint : public CServo
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CJoint(	int IOch, eServoType CurrType = ServoType_Normal, 
			double dAngleOffset = 0, bool bInvertDir = false, double dAngleCalibration = 0);
	CJoint();
	~CJoint();

	int SetAngle(double dAngle); //Sets the current Angle, in radians.
	int SetAngleOffset(double dOffset);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	double m_dAngleCurrent;
	bool m_bIvertRotDirection;
	double m_dAngleCalibration; //Offset for zero-position calibration, is not influenced by Inversion-Flag;
	double m_dAngleOffset; // Offset for Mounting and calculation purpose.

	int SetAngleCalibration(double dOffset);
	int RadToPulse(double dAngleSource, int& iPulseWidth);
	int InvertAngle(double dAngleSource, double& dAngleTarget);

private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    	ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CServo);
       	ar & BOOST_SERIALIZATION_NVP(m_dAngleCurrent);
        ar & BOOST_SERIALIZATION_NVP(m_bIvertRotDirection);
        ar & BOOST_SERIALIZATION_NVP(m_dAngleCalibration);
        ar & BOOST_SERIALIZATION_NVP(m_dAngleOffset);
    }

};
