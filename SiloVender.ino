


const int RotateClockwiseInputPin = 2;
const int RotateConterClockwiseInputPin = 3;

const int RotateClockWiseOutputPin = 13;
const int RotateConterClockwiseIOutputPin = 11;
const unsigned long RunTime = 10; //Seconds
const unsigned long DelayTime = 2; //Seconds

unsigned long time, timeZ1, timeZ2, RotateClockwiseSetTime, RotateConterClockwiseSetTime;
bool RotateClockwiseCmd = false;
bool RotateConterClockwiseCmd = false;

bool RotateClockwiseSet, RotateClockwiseSet_Z = false;
bool RotateConterClockwiseSet, RotateConterClockwiseSet_Z = false;

bool RotateClockwiseOut;
bool RotateConterClockwiseOut;

String SendString = "";

void setup()
{

	Serial.begin(9600);
	
	timeZ1 = millis();
	timeZ2 = timeZ1;

	pinMode(RotateClockwiseInputPin, INPUT_PULLUP);
	pinMode(RotateConterClockwiseInputPin, INPUT_PULLUP);

	pinMode(RotateClockWiseOutputPin, OUTPUT);
	pinMode(RotateConterClockwiseIOutputPin, OUTPUT);
}

void loop()
{
	// Reading input
	time = millis();
	RotateClockwiseCmd = !digitalRead(RotateClockwiseInputPin);
	RotateConterClockwiseCmd = !digitalRead(RotateConterClockwiseInputPin);

	//Resetting Outputs
	RotateClockwiseSet = false;
	RotateConterClockwiseSet = false;
	RotateClockwiseOut = false;
	RotateConterClockwiseOut = false;


	if (RotateClockwiseCmd && !RotateConterClockwiseCmd)
	{
		RotateClockwiseSet = true;
	}

	else if (!RotateClockwiseCmd && RotateConterClockwiseCmd)
	{
		RotateConterClockwiseSet = true;
	}

	else if (!RotateClockwiseCmd && !RotateConterClockwiseCmd)
	{
		if ((time-timeZ1)>RunTime)
		{

			timeZ1 = time;
		}
	}

	if (RotateClockwiseSet_Z && !RotateClockwiseSet)
	{
		RotateClockwiseSetTime = time;
	}

	if (RotateConterClockwiseSet_Z && !RotateConterClockwiseSet)
	{
		RotateConterClockwiseSetTime = time;
	}

	if ((time - RotateClockwiseSetTime)>(DelayTime * 1000) && RotateConterClockwiseSet)
	{
		
		RotateConterClockwiseOut = true;
	}

	if ((time - RotateConterClockwiseSetTime)>(DelayTime * 1000) && RotateClockwiseSet )
	{
		RotateClockwiseOut = true;
	}

	if (RotateClockwiseOut && RotateConterClockwiseOut)
	{
		digitalWrite(RotateClockWiseOutputPin, false);
		digitalWrite(RotateConterClockwiseIOutputPin, false);
	}
	else
	{
		digitalWrite(RotateClockWiseOutputPin, RotateClockwiseOut);
		digitalWrite(RotateConterClockwiseIOutputPin, RotateConterClockwiseOut);
	}


	RotateClockwiseSet_Z = RotateClockwiseSet;
	RotateConterClockwiseSet_Z = RotateConterClockwiseSet;

	SendString = String(RotateClockwiseSet) + "\n" + String(RotateClockwiseOut);
	Serial.println(SendString);

	delay(5);
}
