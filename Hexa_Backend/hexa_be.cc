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



main()
{
	fstream SerialPort;
	
	SerialPort.open("/dev/ttyO1", ios::out | ios::binary);
	
	if (SerialPort.good() != true)
	{
		cout << "Serial Port open failed." << endl;
	}
	
	cout << "Hexapod Backend started." << endl;

	CLeg* pTestServo = new CLeg(26, ServoType_Normal, -(M_PI / 2.d), true);

	for(int i = 100; i < 180; i += 5)
	{
	
		if (pTestServo->SetLength(i) >= 0)
		{
			//pTestServo->SetAngle(((7.d * M_PI) / 4.d )  + (((M_PI / 2.d) / 10.d) * i ));
	
			string sConfigS;
			string sCRstring;
	
			sCRstring = char(13); 
	
			pTestServo->GetSSC32String(sConfigS);
	
			SerialPort << sConfigS << sCRstring;
		
			SerialPort.flush();
		}
		
		sleep(1);
	}
	
	SerialPort.close();
	delete pTestServo;
}
