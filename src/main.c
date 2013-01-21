/***************************************************************
   Copyright [2011] ODOH KENNETH EMEKA

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***************************************************************/
#include "clock.h"

int main ()
{
	int choice, delay;
    printf("1) Normal Clock \n2) Alarm Clock\n3) Timer\n\nMake your choice ");

    scanf("%d",&choice);   

    switch (choice)
    { 
		case 1:
			showTime();
			break;
		case 2:
			setAlarm();
		    break;  
		case 3:
  			printf ("Enter the time delay in seconds: "); scanf ("%d",&delay);
			timer(delay);
		    break; 
		default:
    		printf("%s\n","You have not made any valid choice");			
		    break;
	}
	
    return 0;
}	 
