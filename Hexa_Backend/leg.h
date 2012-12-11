class CLeg
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CLeg(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dAngleCalibration,
			double dFemurLength, double dTibiaLength, double dTibiaOffset);		
	CLeg();
	~CLeg(void);

	int SetLength(double dLength);
	int GetResultingLegAngle(double& dResAngle);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	CJoint* m_pKnee;
	eDebugLevel m_DebugLevel;

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
