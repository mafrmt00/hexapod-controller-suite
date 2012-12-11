class CHipSagittal
{
	//Boost Serialisation
	friend class boost::serialization::access;
	
public:
	CHipSagittal(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
				int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
				double dFemurLength, double dTibiaLength, double dTibiaOffset);
	CHipSagittal();
	~CHipSagittal();

	int SetPosition(double dDistance, double dHeight, bool bSimulateOnly = false);
	int GetSSC32String(stringstream& sConf);

protected:
	CJoint* m_pHipSagitJoint;
	CLeg* m_pLeg;

	int CalculateParams(double dDistance, double dHeight, double& dLegLen, double& dHipAng);

	eDebugLevel m_DebugLevel;

private:

	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
		bool bHipSagitJointPresent = false;
		bool bLegPresent = false;

		if(NULL != m_pHipSagitJoint)
		{
			bHipSagitJointPresent = true;
		}

		if(NULL != m_pLeg)
		{
			bLegPresent = true;
		}

        ar & BOOST_SERIALIZATION_NVP(m_DebugLevel);

        ar & BOOST_SERIALIZATION_NVP(bHipSagitJointPresent);
        if (bHipSagitJointPresent)
        {
        	ar & BOOST_SERIALIZATION_NVP(m_pHipSagitJoint);
        }

        ar & BOOST_SERIALIZATION_NVP(bLegPresent);
        if (bLegPresent)
        {
        	ar & BOOST_SERIALIZATION_NVP(m_pLeg);
        }
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
		bool bHipSagitJointPresent = false;
		bool bLegPresent = false;

		        ar & BOOST_SERIALIZATION_NVP(m_DebugLevel);

        ar & BOOST_SERIALIZATION_NVP(bHipSagitJointPresent);
        if (bHipSagitJointPresent)
        {
        	m_pHipSagitJoint = new CJoint();
        	ar & BOOST_SERIALIZATION_NVP(m_pHipSagitJoint);
        }

        ar & BOOST_SERIALIZATION_NVP(bLegPresent);
        if (bLegPresent)
        {
        	m_pLeg = new CLeg();
        	ar & BOOST_SERIALIZATION_NVP(m_pLeg);
        }
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};
