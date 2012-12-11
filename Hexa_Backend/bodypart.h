class CBodyPart : public CCoxa
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CBodyPart(	int KneeIOch, eServoType KneeCurrType, double dKneeAngleOffset, bool bKneeInvertDir, double dKneeAngleCalibration,
			int HipSIOch, eServoType HipSCurrType, double dHipSAngleOffset, bool bHipSInvertDir, double dHipAngleCalibration,
			int HipTrIOch, eServoType HipTrCurrType, double dHipTrAngleOffset, bool bHipTrInvertDir, double dHipTrAngleCalibration,
			int PartPositionSide, int PartPositionLineup,
			double dHeightOffs = 27.0, double dDistanceOffs = 27.0, double dSideOffs = 5.0,
			double dFemurLength = 76.0, double dTibiaLength = 95.0, double dTibiaOffset = 44.0);
	CBodyPart();
	~CBodyPart();

	int m_PartPositionSide; //Wich Side of the Body resides the Part (For 2 Sided Body 0 = Left, 1 = Right)
	int m_PartPositionLineup; //Which postionhas the Part on its Side (0 = Front ... n = Back)

private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    	ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CCoxa);
    	ar & BOOST_SERIALIZATION_NVP(m_PartPositionSide);
    	ar & BOOST_SERIALIZATION_NVP(m_PartPositionLineup);
    }
};
