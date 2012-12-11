class CLeg
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CLeg(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dAngleCalibration,
			double dFemurLength, double dTibiaLength, double dTibiaOffset);		
	CLeg();
	~CLeg(void);

	int SetLength(double dLength, bool bSimulateOnly = false);
	int GetResultingLegAngle(double& dResAngle);

	int GetSSC32String(stringstream& sConf);
	int FinalizeSSC32String(stringstream& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	CJoint* m_pKnee;

	double m_FemurLength;
	double m_TibiaLength;
	double m_TibiaOffset;

	double m_TibiDiagonal;
	double m_TibiHelperAngle;

	double m_CurrentLength;   //Current State of the Leg
	double m_CurrentLegAngle; //Current State of the Leg

	double m_ResultingLegAngle; //For Computational and Simulation Purposes

	eDebugLevel m_DebugLevel;

	int CalculateConstants(void);
	int CalculateKneeAngle(double dLength, double& dKneeAngle);
	int CalculateResultingLegAngle(double dCurrentLength);
	int SetLegParams(double dFemurLength, double dTibiaLength, double dTibiaOffset);

	int SetKneeParams(int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dAngleCalibration);

private:
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
		bool bKneeIsPresent = false;

		if (NULL!= m_pKnee)
		{
			bKneeIsPresent = true;
		}

    	ar &  BOOST_SERIALIZATION_NVP(m_FemurLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiaLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiaOffset);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiDiagonal);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiHelperAngle);
    	ar &  BOOST_SERIALIZATION_NVP(m_CurrentLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_ResultingLegAngle);

    	ar &  BOOST_SERIALIZATION_NVP(bKneeIsPresent);
       	if (bKneeIsPresent)
    	{
    		ar &  BOOST_SERIALIZATION_NVP(m_pKnee);
    	}

    	ar &  BOOST_SERIALIZATION_NVP(m_DebugLevel);
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
    	bool bKneeIsPresent = false;

    	ar &  BOOST_SERIALIZATION_NVP(m_FemurLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiaLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiaOffset);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiDiagonal);
    	ar &  BOOST_SERIALIZATION_NVP(m_TibiHelperAngle);
    	ar &  BOOST_SERIALIZATION_NVP(m_CurrentLength);
    	ar &  BOOST_SERIALIZATION_NVP(m_ResultingLegAngle);

    	ar &  BOOST_SERIALIZATION_NVP(bKneeIsPresent);
       	if (bKneeIsPresent)
    	{
       		m_pKnee = new CJoint();
    		ar &  BOOST_SERIALIZATION_NVP(m_pKnee);
    	}

    	ar &  BOOST_SERIALIZATION_NVP(m_DebugLevel);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};
