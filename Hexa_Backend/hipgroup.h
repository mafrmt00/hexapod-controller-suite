typedef list<CHip*> HipList;

class CHipGroup
{
public:
	CHipGroup(void);
	~CHipGroup(void);

	int AddHip(CHip* pHip);

	int SetPosition(double dPosition_X, double dPosition_Y, double dPosition_Z);

	int SetPosition_X(double dPosition_X);
	int SetPosition_Y(double dPosition_Y);
	int SetPosition_Z(double dPosition_Z);

	int SetPositionRel_X(double dPositionOffset_X);
	int SetPositionRel_Y(double dPositionOffset_Y);
	int SetPositionRel_Z(double dPositionOffset_Z);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	HipList* m_pHipList;
	eDebugLevel m_DebugLevel;
};