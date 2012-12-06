#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>

#include <unistd.h>

using namespace std;

#include "my_types.h"
#include "servo.h"
#include "joint.h"
#include "leg.h"
#include "hip_sagit.h"
#include "hip.h"
#include "hipgroup.h"

#define CALIBRATION_SERVO_24 (0.022817 * M_PI)
#define CALIBRATION_SERVO_25 (1.97135 * M_PI)
#define CALIBRATION_SERVO_26 (1.9427 * M_PI)

#define CALIBRATION_SERVO_20 (0.0 * M_PI)
#define CALIBRATION_SERVO_21 (1.95862 * M_PI)
#define CALIBRATION_SERVO_22 (1.97454 * M_PI)

#define CALIBRATION_SERVO_16 (1.95862 * M_PI)
#define CALIBRATION_SERVO_17 (1.97135 * M_PI)
#define CALIBRATION_SERVO_18 (1.97454 * M_PI)

#define CALIBRATION_SERVO_08 (1.9618 * M_PI)
#define CALIBRATION_SERVO_09 (0.0031831 * M_PI)
#define CALIBRATION_SERVO_10 (1.99363 * M_PI)

#define CALIBRATION_SERVO_04 (0.0063662 * M_PI)
#define CALIBRATION_SERVO_05 (0.0159155 * M_PI)
#define CALIBRATION_SERVO_06 (1.99363 * M_PI)

#define CALIBRATION_SERVO_00 (1.99682 * M_PI)
#define CALIBRATION_SERVO_01 (1.9809 * M_PI)
#define CALIBRATION_SERVO_02 (1.99682 * M_PI)

#define SERVO_MOVE_TIME 300

void testbench(void)
{
	fstream SerialPort;
	
	SerialPort.open("/dev/ttyO1", ios::out | ios::binary);
	
	if (SerialPort.good() != true)
	{
		cout << "Serial Port open failed." << endl;
	}
	
	cout << "Hexapod Backend started." << endl;
	
	CHipGroup* pLeftBugSide = new CHipGroup;
	CHipGroup* pRightBugSide = new CHipGroup;
	CHipGroup* pFrontBugSide = new CHipGroup;
	CHipGroup* pRearBugSide = new CHipGroup;
	CHipGroup* pWholeBug = new CHipGroup;

	CHip* pLegLeft01 = new CHip(	26, ServoType_Normal, -(M_PI / 2.0), 	true, CALIBRATION_SERVO_26,
								25, ServoType_Normal, 0, 			true, CALIBRATION_SERVO_25,
								24, ServoType_Normal, -(0.25 * M_PI), 	false, CALIBRATION_SERVO_24);
	
	CHip* pLegLeft02 = new CHip(	22, ServoType_Normal, -(M_PI / 2.0), 	true, CALIBRATION_SERVO_22,
								21, ServoType_Normal, 0, 			true, CALIBRATION_SERVO_21,
								20, ServoType_Normal, -(0.5 * M_PI),	false, CALIBRATION_SERVO_20);
	
	CHip* pLegLeft03 = new CHip(	18, ServoType_Normal, -(M_PI / 0), 	true, CALIBRATION_SERVO_18,
								17, ServoType_Normal, 0, 			true, CALIBRATION_SERVO_17,
								16, ServoType_Normal, -(0.75 * M_PI), 	false, CALIBRATION_SERVO_16);
	
	
	
	CHip* pLegRight01 = new CHip(	10, ServoType_Normal, -(M_PI / 2.0), 	false, CALIBRATION_SERVO_10,
								9,  ServoType_Normal, 0, 			false, CALIBRATION_SERVO_09,
								8,  ServoType_Normal, -(0.25 * M_PI), 	true, CALIBRATION_SERVO_08);
								
	CHip* pLegRight02 = new CHip(	6, ServoType_Normal, -(M_PI / 2.0), 		false, CALIBRATION_SERVO_06,
								5,  ServoType_Normal, 0, 			false, CALIBRATION_SERVO_05,
								4,  ServoType_Normal, -(0.5 * M_PI),	true, CALIBRATION_SERVO_04);

	CHip* pLegRight03 = new CHip(	2, ServoType_Normal, -(M_PI / 2.0), 		false, CALIBRATION_SERVO_02,
								1,  ServoType_Normal, 0, 			false, CALIBRATION_SERVO_01,
								0,  ServoType_Normal, -(0.75 * M_PI), 	true, CALIBRATION_SERVO_00);
	
	//CHipSagittal* pTestServo = new CHipSagittal(26, ServoType_Normal, -(M_PI / 2.d), true,    25, ServoType_Normal, 0, true);
	//CLeg* pTestServo = new CLeg(26, ServoType_Normal, -(M_PI / 2.d), true);

	pLeftBugSide->AddHip(pLegLeft01);
	pLeftBugSide->AddHip(pLegLeft02);
	pLeftBugSide->AddHip(pLegLeft03);
	
	pRightBugSide->AddHip(pLegRight01);
	pRightBugSide->AddHip(pLegRight02);
	pRightBugSide->AddHip(pLegRight03);
	
	pFrontBugSide->AddHip(pLegLeft01);
	pFrontBugSide->AddHip(pLegRight01);
	
	pRearBugSide->AddHip(pLegLeft03);
	pRearBugSide->AddHip(pLegRight03);	
	
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
	
	string sConfigS = "";
	
	pLegLeft01->SetPosition(100, 100, 100) ;
	pLegLeft02->SetPosition(1, 150, 100) ;
	pLegLeft03->SetPosition(-100, 100, 100) ;
	
	pLegRight01->SetPosition(100, -100, 100) ;
	pLegRight02->SetPosition(1, -150, 100) ;
	pLegRight03->SetPosition(-100, -100, 100) ;
	
	pWholeBug->AddHip(pLegLeft01);	
	pWholeBug->AddHip(pLegLeft02);
	pWholeBug->AddHip(pLegLeft03);
	
	pWholeBug->AddHip(pLegRight01);
	pWholeBug->AddHip(pLegRight02);
	pWholeBug->AddHip(pLegRight03);
	
	for(int i = 100; i < 150; i += 5)
	{
		if (pWholeBug->SetPosition_Z(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	
			sConfigS = "";

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);
	
			SerialPort << sConfigS;
		
			SerialPort.flush();
		}
		
		sleep(1);
	}
	
	for(int i = 150; i > 100; i -= 5)
	{
		if (pWholeBug->SetPosition_Z(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	
			sConfigS = "";

			pWholeBug->GetSSC32String(sConfigS);
			pWholeBug->FinishSSC32String(sConfigS, SERVO_MOVE_TIME);
	
			SerialPort << sConfigS;
		
			SerialPort.flush();
		}
		
		sleep(1);
	}	
	
	SerialPort.close();

	delete pLeftBugSide;
	delete pRightBugSide;
	delete pFrontBugSide;
	delete pRearBugSide;
	delete pWholeBug;
	
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
		
		string sConfigS;
		string sCRstring = "T1000";

		sCRstring += char(13); 

		pServo->GetSSC32String(sConfigS);

		SerialPort << sConfigS << sCRstring;
	
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
	int c;
	bool cflag = false;
	bool tflag = false;
	
	while ((c = getopt (argc, argv, "ct")) != -1)	
	{
		switch (c)
		{
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
