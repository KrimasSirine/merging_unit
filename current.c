#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>


int main()

{
	int i=0;
	float fVal1;
    FILE  *ReadInput;
    int iretval;

    ReadInput = fopen("/home/sirine/Desktop/IEC 61850 lib/libiec61850-0.9.0.2/examples/merging_unit/current_phaseA.txt","r") ;
    iretval = fscanf(ReadInput,"%f",&fVal1);
    while(iretval != EOF)
    {
		printf("%f\n",fVal1);
		iretval = fscanf(ReadInput,"%f",&fVal1);
		i++;
		}
		
    return 0;
}
