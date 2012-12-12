#include "hexa_common.h"


#define CALIBRATION_SERVO_24 (0.022817 	* M_PI)
#define CALIBRATION_SERVO_25 (1.97135 	* M_PI)
#define CALIBRATION_SERVO_26 (1.9427 	* M_PI)

#define CALIBRATION_SERVO_20 (0.0		* M_PI)
#define CALIBRATION_SERVO_21 (1.97454 	* M_PI)
#define CALIBRATION_SERVO_22 (1.97454 	* M_PI)

#define CALIBRATION_SERVO_16 (1.95862 	* M_PI)
#define CALIBRATION_SERVO_17 (1.97135 	* M_PI)
#define CALIBRATION_SERVO_18 (1.97454 	* M_PI)

#define CALIBRATION_SERVO_08 (1.9618 	* M_PI)
#define CALIBRATION_SERVO_09 (0.0031831 * M_PI)
#define CALIBRATION_SERVO_10 (1.99363 	* M_PI)

#define CALIBRATION_SERVO_04 (0.0127324 * M_PI)
#define CALIBRATION_SERVO_05 (0.0127324 * M_PI)
#define CALIBRATION_SERVO_06 (1.98727 	* M_PI)

#define CALIBRATION_SERVO_00 (1.99682 	* M_PI)
#define CALIBRATION_SERVO_01 (1.9809 	* M_PI)
#define CALIBRATION_SERVO_02 (1.99682 	* M_PI)

#define SERVO_MOVE_TIME 1000


void save_BodyPart(const CBodyPart &s, const char * filename)
{
#if 0
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::text_oarchive oa(ofs);
    oa << s;
#endif
#if 1
    // make an XML archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
#endif
}

void load_BodyPart(CBodyPart &s, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore from archive
    ia >> BOOST_SERIALIZATION_NVP(s);
}

void save_hipgroup(const CBody &s, const char * filename)
{
    // make an archive
    std::ofstream ofs(filename);
    assert(ofs.good());
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(s);
}


void testbench(void)
{
	fstream SerialPort;
	
	SerialPort.open("/dev/ttyO1", ios::out | ios::binary);
	
	if (SerialPort.good() != true)
	{
		cout << "Serial Port open failed." << endl;
	}
	
	cout << "Hexapod Backend started." << endl;
	

	CBodyPart* pLegLeft01 = new CBodyPart(
									26, ServoType_Normal, -(M_PI / 2.0), 	true, 	CALIBRATION_SERVO_26,
									25, ServoType_Normal, 0, 				true, 	CALIBRATION_SERVO_25,
									24, ServoType_Normal, -(0.25 * M_PI), 	false, 	CALIBRATION_SERVO_24,
									0, 0);
	
	CBodyPart* pLegLeft02 = new CBodyPart(
									22, ServoType_Normal, -(M_PI / 2.0), 	true, 	CALIBRATION_SERVO_22,
									21, ServoType_Normal, 0, 				true, 	CALIBRATION_SERVO_21,
									20, ServoType_Normal, -(0.5 * M_PI),	false, 	CALIBRATION_SERVO_20,
									0, 1);
	
	CBodyPart* pLegLeft03 = new CBodyPart(
									18, ServoType_Normal, -(M_PI / 2.0), 	true, 	CALIBRATION_SERVO_18,
									17, ServoType_Normal, 0, 				true, 	CALIBRATION_SERVO_17,
									16, ServoType_Normal, -(0.75 * M_PI), 	false, 	CALIBRATION_SERVO_16,
									0, 2);
	
	
	
	CBodyPart* pLegRight01 = new CBodyPart(
									10, ServoType_Normal, -(M_PI / 2.0), 	false, 	CALIBRATION_SERVO_10,
									9,  ServoType_Normal, 0.0, 				false, 	CALIBRATION_SERVO_09,
									8,  ServoType_Normal, -(0.25 * M_PI), 	true, 	CALIBRATION_SERVO_08,
									1, 0);
								
	CBodyPart* pLegRight02 = new CBodyPart(
									6, ServoType_Normal, -(M_PI / 2.0), 	false, 	CALIBRATION_SERVO_06,
									5,  ServoType_Normal, 0.0, 				false, 	CALIBRATION_SERVO_05,
									4,  ServoType_Normal, -(0.5 * M_PI),	true, 	CALIBRATION_SERVO_04,
									1, 1);

	CBodyPart* pLegRight03 = new CBodyPart(
									2, ServoType_Normal, -(M_PI / 2.0), 	false, 	CALIBRATION_SERVO_02,
									1,  ServoType_Normal, 0.0, 				false, 	CALIBRATION_SERVO_01,
									0,  ServoType_Normal, -(0.75 * M_PI), 	true, 	CALIBRATION_SERVO_00,
									1, 2);


	//Serialization test
    std::string filename("./LegLeft01.xml");
	save_BodyPart(*pLegLeft01, filename.c_str());
	
	CBodyPart* pRestoredLeg = new CBodyPart();
	load_BodyPart(*pRestoredLeg, filename.c_str());

	std::string filename02("./LegLeft01out.xml");
	save_BodyPart(*pRestoredLeg, filename02.c_str());

	//CHipSagittal* pTestServo = new CHipSagittal(26, ServoType_Normal, -(M_PI / 2.d), true,    25, ServoType_Normal, 0, true);
	//CLeg* pTestServo = new CLeg(26, ServoType_Normal, -(M_PI / 2.d), true);


	//Contruct the Bug
	CBody* pWholeBug = new CBody();

	pWholeBug->AddHip(pLegLeft01);
	pWholeBug->AddHip(pLegLeft02);
	pWholeBug->AddHip(pLegLeft03);

	pWholeBug->AddHip(pLegRight01);
	pWholeBug->AddHip(pLegRight02);
	pWholeBug->AddHip(pLegRight03);

	//Left Side
	CBody* pLeftBugSide = new CBody(*pWholeBug, 0, WILDCARD_POSLINEUPFILTER);

	//Right Side
	CBody* pRightBugSide = new CBody(*pWholeBug, 1, WILDCARD_POSLINEUPFILTER);

	//Front
	CBody* pFrontBugSide = new CBody(*pWholeBug, WILDCARD_PARTSSIDEFILTER, 0);
	
	//Rear
	CBody* pRearBugSide  = new CBody(*pWholeBug, WILDCARD_PARTSSIDEFILTER, 2);

	//Tripods
	CBody* pTripod01 = new CBody();
	CBody* pTripod02 = new CBody();

	pTripod01->AddHip(pLegLeft01);
	pTripod01->AddHip(pLegRight02);
	pTripod01->AddHip(pLegLeft03);	
	
	pTripod02->AddHip(pLegRight01);
	pTripod02->AddHip(pLegLeft02);
	pTripod02->AddHip(pLegRight03);		


    std::string filename01("./LeftBugSide.xml");
	save_hipgroup(*pLeftBugSide, filename01.c_str());
	
	#if 0	
	pWholeBug->AddHip(pLegLeft01);
	pWholeBug->AddHip(pLegLeft02);
	pWholeBug->AddHip(pLegLeft03);	
	pWholeBug->AddHip(pLegRight01);
	pWholeBug->AddHip(pLegRight02);
	pWholeBug->AddHip(pLegRight03);
	

	pWholeBug->SetPosition(1, 50, 50) ;
	pFrontBugSide->SetPosition_Y(1);
	pFrontBugSide->SetPosition_X(50);
	pRearBugSide->SetPosition_Y(1);
	pRearBugSide->SetPosition_X(50);
#endif
	
	stringstream sConfigS;
	
	pLegLeft01->SetPosition(100, 100, 100) ;
	pLegLeft02->SetPosition(1, 150, 100) ;
	pLegLeft03->SetPosition(-100, 100, 100) ;
	
	pLegRight01->SetPosition(100, -100, 100) ;
	pLegRight02->SetPosition(1, -150, 100) ;
	pLegRight03->SetPosition(-100, -100, 100) ;
	

	
	sConfigS.str("");
	

	pLegLeft01->GetSSC32String(sConfigS);
	pLegLeft01->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);
	
	sConfigS.str("");

	pLegLeft02->GetSSC32String(sConfigS);
	pLegLeft02->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);
	
	sConfigS.str("");

	pLegLeft03->GetSSC32String(sConfigS);
	pLegLeft03->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);

	sConfigS.str("");

	pLegRight01->GetSSC32String(sConfigS);
	pLegRight01->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);
	
	sConfigS.str("");

	pLegRight02->GetSSC32String(sConfigS);
	pLegRight02->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);

	sConfigS.str("");

	pLegRight03->GetSSC32String(sConfigS);
	pLegRight03->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	SerialPort << sConfigS.str();
	SerialPort.flush();
	sleep(1);
	sConfigS.str("");
	
	if (pWholeBug->SetPositionRel_Z(25.0) >= 0)
	{
		//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));

		pWholeBug->GetSSC32String(sConfigS);
		pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

		SerialPort << sConfigS.str();
	
		SerialPort.flush();
		sConfigS.str("");
	}
	
	sleep(SERVO_MOVE_TIME / 1000);
	
	for (int i = 0 ; i < 5 ; i++)
	{
		if (pWholeBug->SetPositionRel_X(20.0) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));


			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
		sleep(SERVO_MOVE_TIME / 1000);		
		
		
		if ((pTripod01->SetPositionRel_Z(-25.d) >= 0) && (pTripod01->SetPositionRel_X(-20.d) >= 0))
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
	


		
		sleep(SERVO_MOVE_TIME / 1000);
		
		if (pTripod01->SetPositionRel_Z(25.d) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
		sleep(SERVO_MOVE_TIME / 1000);		

		if ((pTripod02->SetPositionRel_Z(-25.d) >= 0) && (pTripod02->SetPositionRel_X(-20.d) >= 0))
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		

		
		sleep(SERVO_MOVE_TIME / 1000);	
		
		if (pTripod02->SetPositionRel_Z(25.d) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
		sleep(SERVO_MOVE_TIME / 1000);
		
	
		

	}

	if (pWholeBug->SetPositionRel_Z(-25.0) >= 0)
	{
		//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));


		pWholeBug->GetSSC32String(sConfigS);
		pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);

		SerialPort << sConfigS.str();
	
		SerialPort.flush();
		sConfigS.str("");
	}
	
	sleep(SERVO_MOVE_TIME / 1000);	
	#if 0
	for(int i = 100; i < 160; i += 5)
	{
		if (pWholeBug->SetPosition_Z(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	
			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
		sleep(1);
	}
	
	for(int i = 160; i > 100; i -= 5)
	{
		if (pWholeBug->SetPosition_Z(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinalizeSSC32String(sConfigS, SERVO_MOVE_TIME);
	
			SerialPort << sConfigS.str();
		
			SerialPort.flush();
			sConfigS.str("");
		}
		
		sleep(1);
	}	
	#endif
	
	SerialPort.close();

	delete pLeftBugSide;
	delete pRightBugSide;
	delete pFrontBugSide;
	delete pRearBugSide;
	delete pWholeBug;
	delete pTripod01;
	delete pTripod02;
	
	delete pLegLeft01;	
	delete pLegLeft02;	
	delete pLegLeft03;
	delete pLegRight01;
	delete pLegRight02;
	delete pLegRight03;	
}

void calibration(void)
{
	fstream SerialPort;
	SerialPort.open("/dev/ttyO1", ios::out | ios::binary);
	
	int iServoNumber;
	CJoint* pServo = NULL;
	
	cout << "Interactive Servo calibration." << endl;
	
	cout << "Enter Servo Number:";
	cin >> iServoNumber;
	cout<< endl;
	
	if (pServo != NULL)
	{
		delete pServo;
		pServo = NULL;
	}
	
	pServo = new CJoint(iServoNumber);
	
	string scommand;
	double dServoAngle = 0;
	
	do
	{
		cout << "Enter Servo Command:";
		cin >> scommand;
		cout<< endl;
		
		if (scommand == "p")
		{
			dServoAngle += 0.01;
			
			if (pServo != NULL)
			{
				pServo->SetAngle(dServoAngle);
			}
			
		}
		
		if (scommand == "m")
		{
			dServoAngle -= 0.01;
			
			if (pServo != NULL)
			{
				pServo->SetAngle(dServoAngle);
			}
			
		}		
		
		if (scommand == "c")
		{
			dServoAngle = 0.0;
			
			if (pServo != NULL)
			{
				pServo->SetAngle(dServoAngle);
			}
			
		}		
		
		stringstream sConfigS;

		pServo->GetSSC32String(sConfigS);

		SerialPort << sConfigS << "T1000" << char(13);
	
		SerialPort.flush();		
		
	}
	while(scommand != "e");
		
	if (pServo != NULL)
	{
		delete pServo;
		pServo = NULL;
	}

	SerialPort.close();	
}

int main (int argc, char **argv)
{
    extern char *optarg;
    extern int optind, optopt;

	int c;
	bool cflag = false;
	bool tflag = false;
	
	char *cSerialPort = NULL;

	while ((c = getopt (argc, argv, "s:ct")) != -1)
	{
		switch (c)
		{
			//Set Serial Port to be used
			case 's':
				cSerialPort = optarg;

				if(cSerialPort == NULL)
				{
					cout << "Error: Option -s needs a parameter /dev/tty0 for example." << endl;
				}
				else
				{
					cout << "Using serial port " << cSerialPort << endl;
				}
				break;

			case 'c':
				cflag = true;
				break;
			
			case 't':
				tflag = true;
				break;	

			default:
				abort ();
				break;
		}
	}
	
	if (tflag)
	{
		testbench();
		return 1;
	}
	
	if (cflag)
	{
		calibration();
		return 1;
	}	
	
	return 0;
}
