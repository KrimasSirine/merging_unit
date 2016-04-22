/*#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval tv;
 
int main(int argc, char** argv)
{
	gettimeofday(&tv, NULL);

	unsigned  long long millisecondsSinceEpoch =
			(unsigned  long long)(tv.tv_sec) * 1000 +
			(unsigned  long long)(tv.tv_usec) / 1000;

	printf("%llu\n", millisecondsSinceEpoch);
	unsigned long int a = (unsigned long int)millisecondsSinceEpoch;
	printf("%lu\n", a); 
	return 0;  
}*/
/*#include <time.h>
#include <stdio.h>


int main(void)
{
  struct tm *local;
  time_t t;

  t = time(NULL);
  local = localtime(&t);
  printf("Local time and date: %s\n", asctime(local));
  local = gmtime(&t);
  printf("UTC time and date: %s\n", asctime(local));
  return 0;
}*/
/*#include <stdio.h>
#include <time.h>

int main(void)
{
    printf("%f\n", (double) clock());
    return 0;
}*/
#include <stdio.h>
#include <time.h>
int i;
int main(void) {
    printf("Timestamp: %d\n",(int)time(NULL));
    i=sizeof(int);
    printf("%d",i);
    return 0;
}
