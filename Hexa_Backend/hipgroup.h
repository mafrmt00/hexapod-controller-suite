#ifndef HIPGROUPBLOXX
#define HIPGROUPBLOXX

#define WILDCARD_PARTSSIDEFILTER 0xFFFF
#define WILDCARD_POSLINEUPFILTER 0xFFFF

typedef list<CBodyPart*> BodyPartList;

class CBody
{
    friend class boost::serialization::access;

public:
    CBody(const CBody &Origin, int uiPartPositionSideFilter, int uiPartPositionLineupFilter); //Selective Copy Contructor

	CBody(void);
	~CBody(void);

	int AddHip(CBodyPart* pHip);

	int SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z);

	int SetPosition_X(double dPosition_X);
	int SetPosition_Y(double dPosition_Y);
	int SetPosition_Z(double dPosition_Z);

	int SetPositionRel_X(double dPositionOffset_X);
	int SetPositionRel_Y(double dPositionOffset_Y);
	int SetPositionRel_Z(double dPositionOffset_Z);

	int GetSSC32String(stringstream& sConf);
	int FinishSSC32String(stringstream& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	BodyPartList* m_pHipList;
	eDebugLevel m_DebugLevel;

private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
    	ar &  BOOST_SERIALIZATION_NVP(m_pHipList);
    	ar &  BOOST_SERIALIZATION_NVP(m_DebugLevel);
    }
};

#endif //HIPGROUPBLOXX
