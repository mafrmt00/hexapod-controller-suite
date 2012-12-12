#ifndef COCOBLOXX
#define COCOBLOXX

typedef enum ComContCommand
{
	eCoCo_none = 0x00,
	eCoCo_SetPosition_X = 0x01,
	eCoCo_SetPosition_Y = 0x02,
	eCoCo_SetPosition_Z = 0x03,
}eComContCommand;

class CCommandContainer
{
	//Boost Serialisation
	friend class boost::serialization::access;

public:
	CCommandContainer();
	~CCommandContainer();

	CCommandContainer(eComContCommand Command, double dParameter01);

	eComContCommand GetCommand(void);
	double GetParam01(void);

protected:
	eComContCommand m_Command;
	double m_dParameter01;

private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    	ar & BOOST_SERIALIZATION_NVP(m_Command);
    	ar & BOOST_SERIALIZATION_NVP(m_dParameter01);
    }
};
#endif // COCOBLOXX
