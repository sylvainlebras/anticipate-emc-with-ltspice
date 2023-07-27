#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_SAMPLES 1000

#define DELAY 6000

int main(int argc, char *argv[]) {
	
	int sample = 0;				// total number of samples
	
	// Time domain 
	double transitionTime = 20 ; 				// in nanoSeconds
	double symbolTime = 1000000000/115200 ;  	// in nanoSeconds
	float preEmphasysTime = 0.1 ; 				// in nanoSeconds
	
	// Amplitude domain
	float initialVoltage = 0; 	 				// in Volts
	float voltageHigh = 5.0;					// in Volts
	float voltageLow = 0;						// in Volts
	
	float preEmphasysLowToHighOvershootVoltage = 0.5; // in volts
	float preEmphasysHighToLowOvershootVoltage = 0.5; // in volts
	
	int logicLevel = 0;	// variable for sample
	
	FILE * pFile;
  	pFile = fopen ("testVector.txt","w");
  	
	if (pFile!=NULL)
	{
		// initialize
		fprintf (pFile,"%dn\t0\n",0,initialVoltage);
		fprintf (pFile,"%dn\t0\n",DELAY,initialVoltage );
		
		// loop for every sample
		for (sample = 0 ; sample < NUMBER_OF_SAMPLES ; sample++)
		{
			// Compute a sample
			logicLevel = rand() % 2;
			
			// print sample
			if (logicLevel == 0)
			{
				fprintf (pFile,"%fn\t%5.2f\n",(sample*symbolTime)+DELAY+transitionTime,voltageLow);
				fprintf (pFile,"%fn\t%5.2f\n",((sample+1)*symbolTime)+DELAY-transitionTime,voltageLow);
				printf ("%fn\t%5.2f\n",(sample*symbolTime)+DELAY,voltageLow);
				
			}
			else
			{
				fprintf (pFile,"%fn\t%5.2f\n",(sample*symbolTime)+DELAY+transitionTime,voltageHigh);
				fprintf (pFile,"%fn\t%5.2f\n",((sample+1)*symbolTime)+DELAY-transitionTime,voltageHigh);
				printf ("%fn\t%5.2f\n",(sample*symbolTime)+DELAY,voltageHigh);
			}
		}
		
		printf ("Symbol time : %f ns\n",symbolTime);
		
		fclose (pFile);
	}
	return 0;
		
}
