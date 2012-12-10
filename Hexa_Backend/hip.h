class CHip
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CHip(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
			int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
			int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, double dHipTrAngleCalibration,
			double dHeightOffs = 27.0, double dDistanceOffs = 27.0, double dSideOffs = 5.0,
			double dFemurLength = 76.0, double dTibiaLength = 95.0, double dTibiaOffset = 44.0);

	CHip();
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

protected:
	CHipSagittal* m_pRestLeg;
	CJoint* m_pTransverseJoint;

	bool m_bCurrentPositionValid;
	double m_bCurrentPosition_X;
	double m_bCurrentPosition_Y;
	double m_bCurrentPosition_Z;

	double m_dSagittalOffset_Height;
	double m_dSagittalOffset_Distance;
	double m_dSagittalOffset_Side;

	int StorePosition(bool bValid = false, double dPosition_X = 0.0, double dPosition_Y = 0.0, double dPosition_Z = 0.0);
	int SetSagittalOffset(double dHeight, double dDistance, double dSide);
	int CalculateParams(double dPosition_X, double dPosition_Y, double dPosition_Z, double& dTransverseAngle, double& dDistance, double& dHeight);

	eDebugLevel m_DebugLevel;

private:
	template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
		bool bTransverseJointPresent = false;

		if(NULL != m_pTransverseJoint)
		{
			bTransverseJointPresent = true;
		}

    	ar & BOOST_SERIALIZATION_NVP(m_bCurrentPositionValid);

        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_X);
        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_Y);
        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_Z);

        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Height);
        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Distance);
        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Side);

        ar & BOOST_SERIALIZATION_NVP(m_DebugLevel);

        ar & BOOST_SERIALIZATION_NVP(bTransverseJointPresent);
        if (bTransverseJointPresent)
        {
        	ar & BOOST_SERIALIZATION_NVP(m_pTransverseJoint);
        }
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
    	bool bTransverseJointPresent = false;

    	ar & BOOST_SERIALIZATION_NVP(m_bCurrentPositionValid);

        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_X);
        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_Y);
        ar &  BOOST_SERIALIZATION_NVP(m_bCurrentPosition_Z);

        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Height);
        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Distance);
        ar &  BOOST_SERIALIZATION_NVP(m_dSagittalOffset_Side);

        ar & BOOST_SERIALIZATION_NVP(m_DebugLevel);

        ar & BOOST_SERIALIZATION_NVP(bTransverseJointPresent);
        if (bTransverseJointPresent)
        {
        	m_pTransverseJoint = new CJoint();
        	ar & BOOST_SERIALIZATION_NVP(m_pTransverseJoint);
        }
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};
