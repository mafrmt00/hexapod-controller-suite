typedef enum ServoType
{
	ServoType_Normal, // Pulse with 0.9ms to 2.1ms
	ServoType_Extended // Pulse width 0.5ms to 2.5ms
}eServoType;

class CServo
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CServo(int IOch, eServoType CurrType);
	CServo(int IOch, eServoType CurrType, int iOffset);
	CServo();
	~CServo();
	
	int SetPulseWidth(int iPwidth, bool bSimulateOnly = false);
	int SetPulseOffset(int iOffset);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

private:
	int m_IOchannel;

	bool m_bBinaryCommands;

	int m_PulseWidth_Current;  //Current pulsewidth
	int m_PulseWidth_Offset;
	int m_PulseWidth_LimitMax;
	int m_PulseWidth_LimitMin;

	int SetServoType(eServoType CurrType);
	int SetIOchannel(int IOch);

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    	ar &  BOOST_SERIALIZATION_NVP(m_IOchannel);
        ar &  BOOST_SERIALIZATION_NVP(m_bBinaryCommands);
        ar &  BOOST_SERIALIZATION_NVP(m_PulseWidth_Current);
        ar &  BOOST_SERIALIZATION_NVP(m_PulseWidth_Offset);
        ar &  BOOST_SERIALIZATION_NVP(m_PulseWidth_LimitMax);
        ar &  BOOST_SERIALIZATION_NVP(m_PulseWidth_LimitMin);
    }

protected:
	eDebugLevel m_DebugLevel;
};
