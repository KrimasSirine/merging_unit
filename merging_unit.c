#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "hal_thread.h"
#include "sv_publisher.h"

static bool running = true;

void sigint_handler(int signalId)
{
    running = 0;
}

int test, retval[8];
int  uj, i, ui, uii, uiii, uk, l;
int ind[8];
float data[8];
FILE *transducerFile[8];
const char path[8][200] = 
{
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseA.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseB.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseC.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/neutral_current.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseA.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseB.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseC.txt",
	"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/neutral_to_ground_voltage.txt" 
};
	
int
main(int argc, char** argv)
{	
	
//create publisher connected with eth0	
	SampledValuesPublisher svPublisher = SampledValuesPublisher_create("eth0");
	 
	
//declaration of 8 ASDUs 	
	SV_ASDU asdu = SampledValuesPublisher_addASDU(svPublisher, "svpub1", NULL, 1);
	
		for(uj = 0; uj < 8; uj++)
		{
			data[uj] = 0 ;
			ind[uj] = SV_ASDU_addFLOAT(asdu);
		}
	
    SampledValuesPublisher_setupComplete(svPublisher);
	

	
    while (running)  
	{ 
//open 8 transducerFiles 
		for (i=0; i<8; i++)
		{
			transducerFile[i] = fopen(path[i], "r");
			if (transducerFile[i] == NULL)
			{
				printf("empty file");
				break;
			}
		}
		
		test = 1;
//read the first value of each 8 files. 
		for (ui=0; ui<8; ui++)
		{
			retval[ui] = fscanf(transducerFile[ui], "%f", &data[ui]);
			test = test & (retval[ui] != EOF);
		}
			
		/*for (l=0; l<1000; l++)
		{*/
		
		l = 1;	
// allocate 8 values from 8 files to each tasdu
			while ((test) & (l))
			{   
				uii=0;
				
				while (uii<8)
				{
					//printf("data[%d] : %f\n", uii, data[uii]);
					SV_ASDU_setFLOAT(asdu, ind[uii], data[uii]);
					printf("data[%d] : %f\n", uii, data[uii]);
					retval[uii] = fscanf(transducerFile[uii], "%f", &data[uii]);
					test = test & (retval[uii] != EOF);
					uii++;
				}
		
		//printf("-------------*******************-----------------------\n");
		SV_ASDU_increaseSmpCnt(asdu);
		SampledValuesPublisher_publish(svPublisher);
		usleep(250);
			}
		//}	
	}
	
// close the 8 transducerFiles
	for (uiii=0; uiii<8; uiii++)
	{
		fclose(transducerFile[uiii]);
	}
	
//destroy publisher
    SampledValuesPublisher_destroy(svPublisher);
}
