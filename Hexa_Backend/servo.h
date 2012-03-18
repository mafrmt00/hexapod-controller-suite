typedef enum ServoType
{
	ServoType_Normal, // Pulse with 0.9ms to 2.1ms
	ServoType_Extended // Pulse width 0.5ms to 2.5ms
}eServoType;

class CServo
{
public:
	CServo(int IOch, eServoType CurrType);
	CServo(int IOch, eServoType CurrType, int iOffset);
	~CServo(void);
	
	int SetPulseWidth(int iPwidth);
	int SetPulseOffset(int iOffset);

	int GetSSC32String(string& sConf);
	int FinishSSC32String(string& sConf, int iMoveTime = 0);

	int SetDebugLevel(eDebugLevel NewDebugLevel);

protected:
	eDebugLevel m_DebugLevel;

private:
	int m_IOchannel;

	int m_PulseWidth_Current;  //Current pulsewidth
	int m_PulseWidth_Offset;
	int m_PulseWidth_LimitMax;
	int m_PulseWidth_LimitMin;

	bool m_bBinaryCommands;

	int SetServoType(eServoType CurrType);
	int SetIOchannel(int IOch);
};