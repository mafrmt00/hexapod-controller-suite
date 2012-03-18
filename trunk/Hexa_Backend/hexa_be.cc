#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <unistd.h>

using namespace std;

#include "my_types.h"
#include "servo.h"
#include "joint.h"
#include "leg.h"
#include "hip_sagit.h"
#include "hip.h"



main()
{
	fstream SerialPort;
	
	SerialPort.open("/dev/ttyO1", ios::out | ios::binary);
	
	if (SerialPort.good() != true)
	{
		cout << "Serial Port open failed." << endl;
	}
	
	cout << "Hexapod Backend started." << endl;

	CHip* pTestServo = new CHip(26, ServoType_Normal, -(M_PI / 2.d), true,    25, ServoType_Normal, 0, true,    24, ServoType_Normal, -(M_PI / 4.d), false);
	//CHipSagittal* pTestServo = new CHipSagittal(26, ServoType_Normal, -(M_PI / 2.d), true,    25, ServoType_Normal, 0, true);
	//CLeg* pTestServo = new CLeg(26, ServoType_Normal, -(M_PI / 2.d), true);

	for(int i = 110; i < 180; i += 5)
	{
		if (pTestServo->SetPosition(i, 70, 70) >= 0)
		//if (pTestServo->SetLength(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	
			string sConfigS;
			string sCRstring = "T1000";
	
			sCRstring += char(13); 
	
			pTestServo->GetSSC32String(sConfigS);
	
			SerialPort << sConfigS << sCRstring;
		
			SerialPort.flush();
		}
		
		sleep(1);
	}
	
	SerialPort.close();
	delete pTestServo;
}
