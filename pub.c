#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "hal_thread.h"
#include "sv_publisher.h"

static bool running = true;

void sigint_handler(int signalId)
{
    running = 0;
    printf("BIG PROBLEM HERE\n");
}
    //SV_ASDU tasdu[8];
    //SV_ASDU asdu;
    int test, i, ui, uj, uii, uiii, uij, uil;
	//char cTemp[8][10];
    //int dataIndex[8][8];
    int dataIndex[8];
    float data[8];
    FILE *ReadInput[8];
    int retval[8];
    //int iRet = 0;
    //float fTempData;
    //int LineIdx;
    //unsigned char FileIdx = 0;
   const char path[8][200] = {
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseA.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseB.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseC.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/Neutral_Current.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseA.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseB.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/voltage_phaseC.txt",
		"/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/Neutral_To_Ground_Voltage.txt" 
	};
	char phase[4] = {'A','B','C','N'};
int
main(int argc, char** argv)
{
	SampledValuesPublisher svPublisher = SampledValuesPublisher_create("eth0");

    SV_ASDU asdu = SampledValuesPublisher_addASDU(svPublisher, "svpub1", NULL, 1);
/* 
	// ASDU declaration, Index declaration and data initialisation		                 
    for(ui = 0; ui < 8; ui++)
    {
		memset(cTemp[ui],0,sizeof(cTemp[ui]));
		sprintf(cTemp[ui],"svpub%d",ui);
		tasdu[ui] = SampledValuesPublisher_addASDU(svPublisher, cTemp[ui], NULL, 1);
		for(uj = 0; uj < 8; uj++)
		{
			dataIndex[ui][uj] = SV_ASDU_addFLOAT(tasdu[ui]);
			data[ui]= 0.f ;
		}
	}
*/
	
		for(uj = 0; uj < 8; uj++)
		{
			dataIndex[uj] = SV_ASDU_addFLOAT(asdu);
			data[uj]= 0.f ;
		}

	SampledValuesPublisher_setupComplete(svPublisher);
	
		// Open 8 files
    for (i = 0; i < 8; uj++)
		{
			ReadInput[i] = fopen(path[i], "r");
			if (ReadInput[i] == NULL)
			{
				break;
			}
		}	
		
	
	 while (running)
	 {
		test = 1;
		for (ui=0; ui<8; ui++)
		{
			retval[ui] = fscanf(ReadInput[ui], "%f", &data[ui]);
			test = test & (retval[ui] != EOF);
		}
		
		while (test)
		{
			printf("----------------------------********-----------------------------\n");
			for (uii=0; uii<4; uii++)
			{
				printf("current%c value : %f\n", phase[uii], data[uii]);
				SV_ASDU_setFLOAT(asdu, dataIndex[uii], data[uii]);
				retval[uii] = fscanf(ReadInput[uii], "%f", &data[uii]);
				test = test & (retval[uii] != EOF);
			}
			for (uiii=4; uiii<8; uiii++)
			{
				printf("voltage%c value : %f\n", phase[uiii-4], data[uiii]);
				SV_ASDU_setFLOAT(asdu, dataIndex[uii], data[uii]);
				retval[uiii] = fscanf(ReadInput[uiii-4], "%f", &data[uiii]);
				test = test & (retval[uiii] != EOF);
			}
		SV_ASDU_increaseSmpCnt(asdu);
		}
		SampledValuesPublisher_publish(svPublisher);
		Thread_sleep(2);
		//usleep(250);
    }
	//close all files
	for (uil=0; uil<8; uil++)
	{
		fclose(ReadInput[uil]) ;   
	}
     
    SampledValuesPublisher_destroy(svPublisher);
}
/*		
		test = 1;
		uii = 0;
		do	
		{
		   //printf("asdu number %d\n", uii);
			uij = 0;
			LineIdx += FileIdx;
			FileIdx = 0;
			while  ((uij < 8) & (ir != 0) )
			//printf("reading from Line %d\n", LineIdx);
			for(FileIdx=0;FileIdx<8;FileIdx++) 
			{
				//printf("reading from File %d\n", FileIdx);
				//iretval[uij] = fscanf(ReadInput[uij],"%f",&data[uii][uij]);
				for(a=0;a<LineIdx+1;a++)
					iRet = fscanf(ReadInput[FileIdx],"%f",&fTempData);
				//printf("value %f \n", fTempData);
				//ir = ir & iretval[uij];
				ir = ir & iRet;
				if  (iRet != EOF)
				{
					//SV_ASDU_setFLOAT(tasdu[uii], dataIndex[uii][uij], data[uii][uij]);
					SV_ASDU_setFLOAT(tasdu[uii], dataIndex[uii][uij], fTempData);
				}
				uij++;
			}
			SV_ASDU_increaseSmpCnt(tasdu[uii]);
			uii++;
		}
		while ( (uii < 8) );
*/	
	
