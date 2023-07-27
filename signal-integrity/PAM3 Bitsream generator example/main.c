#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_SAMPLES 1000
// Max consecutive identical symbol (for droop)
#define MAX_CONSECUTIVE_0	7
#define MAX_CONSECUTIVE_1	10
					//mmmµµµnnn
#define M_G_RISE	0.00000005
#define M_G_FALL	0.00000005
#define M_G_PERIOD  (1.0/7500000)

// Droop in volt per second
#define M_G_DROOP	100
#define M_G_LOW		-1.2
#define M_G_HIGH	1.2

// Pre emphasis definition (not used in this example)
#define P_E_RISE		0.00000015
#define P_E_FALL		0.00000015
#define P_E_DURATION	0.00000010
#define P_E_LOW			-0.50
#define P_E_HIGH		0.50

// Ringing definition (not used in this example)
#define RINGING_DECAY	0.9
#define RINGING_FREQ	10000000

#define DELAY 100

int main(int argc, char *argv[]) {
	
	int sample = 0;			

	// variable for sample
	int previousLogicLevel = 1 ;
	int logicLevel = 1;	
	int consecutiveHigh = 0;
	int consecutiveLow = 0;
	
	int transition = 0;
	
	float busvoltage[3] = { M_G_LOW, 0.0, M_G_HIGH };	//-1, 0 and +1 levels in volt
	
	FILE * pfile;

  	pfile = fopen ("SPE-Testvector.txt","w");
  	
	if (pfile!=NULL)
	{
		// initialize
		fprintf (pfile,"%E\t%5.2f\n",0,busvoltage[1]);
		fprintf (pfile,"%E\t%5.2f\n",(DELAY-1)*M_G_PERIOD,busvoltage[1] );
		
		// loop for every sample
		for (sample = DELAY ; sample < (NUMBER_OF_SAMPLES+DELAY) ; sample++)
		{
			// Compute a sample
			previousLogicLevel = logicLevel;
			logicLevel = (rand() % 3) ;
			transition = abs((previousLogicLevel - logicLevel));
			
			switch (transition)
			{
				case 2  : // +1 to -1 transition or +1 to -1 transition
					fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD),busvoltage[previousLogicLevel]);
					fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD)+(M_G_RISE),busvoltage[logicLevel]);				
				break;
				
				case 1 : // transition to nearby state ( -1 <-> 0 <-> 1 )
					fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD)+((1.0*M_G_RISE)/4.0),busvoltage[previousLogicLevel]);
					fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD)+((3.0*M_G_RISE)/4.0),busvoltage[logicLevel]);
				break;	
					
				case 0 : // no change in value
					fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD),busvoltage[logicLevel]);
				break;
				
				default : 
				break;
			
			}
		}
		fprintf (pfile,"%E\t%5.2f\n",(sample*M_G_PERIOD),busvoltage[logicLevel]);
		fprintf (pfile,"%E\t%5.2f\n",(++sample*M_G_PERIOD),busvoltage[1]);
		

		printf ("Symbol time : %f s\n",M_G_PERIOD);
		
		fclose (pfile);
	}
	return 0;
		
}
