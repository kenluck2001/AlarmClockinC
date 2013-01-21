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

int getDayValue(char * str, char *day[7])
{
	int count;
	int index;
 	for(count = 0; count < 7; count++)
	{
 		if(strcmp( day[count], str ) == 0)
		{
			index = count;
		}
	}
	return index;
}

int getMonthValue(char * str, char * month[12])
{
	int count;
	int index;
 	for(count = 0; count < 12; count++)
	{
 		if(strcmp( month[count], str ) == 0)
		{
			index = count;
		}
	}
	return index;
}

char** getArrayOfHourMinuteSeconds(char * str)
{
	char** Tmp = (char**)malloc(sizeof(char*) * 3); //allocate the memory

  	char * pch ;
  	pch = (char *)strtok (str, ":"); //token the string
	int count = 0;
  	while (pch != NULL) //while pch is not null
  	{
		Tmp[count] = malloc(strlen(pch) + 1); //create memory 
		strcpy(Tmp[count],pch);
    	pch = strtok (NULL, ":");
		count++;
  	}
	return Tmp;
}


int countParameter(char *st)
{
	char str[60];
	int i,count;
	strncpy (str,st,50); //copy the string from st to str and limit the match string to 50
	count=1;
	i=0;
	while(str[i]!='\0') //check that the string is not end of line
	{ 
		if(str[i]==' ')
			count++;
		i++;
	}
	return count;
}

/*This method splits the command line argument into tokens*/
char ** stringtokenizer(char *st,int SIZE)
{
  	char str[60];
	strncpy (str,st,50);
	char** Tmp = (char**)malloc(sizeof(char*) * SIZE); //allocate the memory

  	char * pch ;
  	pch = strtok (str, " "); //token the string
	int count = 0;
  	while (pch != NULL) //while pch is not null
  	{
		Tmp[count] = malloc(strlen(pch) + 1); //create memory 
		strcpy(Tmp[count],pch);
    	pch = strtok (NULL, " ");
		count++;
  	}
	return Tmp;
}

//show time
void showTime()
{
	while(1)
	{
	  	time_t rawtime;
	  	struct tm * timeinfo;
	  	char buffer [80];

	  	time ( &rawtime );
	  	timeinfo = localtime ( &rawtime );
		int count = 0;

	  	strftime (buffer,80,"Now it's %I:%M%p.",timeinfo);

	  	puts (buffer);
		sleep(1);
		system("clear");
	}
}

//play sound
void playsound()
{
    if ( system("gnome-mplayer 50cent.mp3") == -1 )
	{
		printf("playing sound\n");
    }
}

void setAlarm()
{
	//create an array of days
  	char *day[7] = {"Mon","Tue","Wed","Thur","Fri","Sat","Sun"};
	//create an array of months
  	char * month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul", "Aug", "Sep", "Oct","Nov", "Dec"};
  	time_t rawtime;
  	char * input;
  	int timeStringIndex ;
  	int count;
	unsigned readyToSleep ;

  	char ** tokens;
	time_t TimeT3;

	int normal_year_month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int leap_year_month_day[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  	time ( &rawtime );
  	printf ( "The current local time is: %s", ctime (&rawtime) );


  	input = ctime (&rawtime);
  	timeStringIndex = countParameter(input);

  	tokens = (char**)stringtokenizer(input, timeStringIndex);

  	int dayVal = getDayValue(tokens[0], day);
  	int monthVal = getDayValue(tokens[1], month);
  	char** arrTime = getArrayOfHourMinuteSeconds(tokens[3]);


  	struct tm Time1 = { 0 };  

  	Time1.tm_hour = atoi(arrTime[0]);
  	Time1.tm_min = atoi(arrTime[1]);
  	//Time1.tm_sec = atoi(arrTime[2]);
  	Time1.tm_sec = 0;


  	/* Give the function a sane date to work with (01/01/2000, here). */
  	Time1.tm_mday = atoi(tokens[2]);
  	Time1.tm_mon = monthVal - 1;
  	Time1.tm_year = atoi(tokens[4])- 1900;



	struct tm Time2 = Time1;  // Base Time2 on Time1, to get the same date...

  	int hour, minute;

  	/* prompt user for date */
  	printf ("Set the alarm time\n"); 
  	printf ("Enter hour: "); scanf ("%d",&hour);
  	printf ("Enter minute: "); scanf ("%d",&minute);

	Time2.tm_hour = hour;
	Time2.tm_min = minute;
  	//Time2.tm_sec = atoi(arrTime[2]);
  	Time2.tm_sec = 0;

	/* Convert to time_t. */
	time_t TimeT1 = mktime( &Time1 );
	time_t TimeT2 = mktime( &Time2 );


    double Diff = difftime( TimeT2 ,TimeT1);

	if (Diff > 0.0)
	{
		readyToSleep =  sleep((int)Diff );
		if(readyToSleep == 0)
		{
			playsound();
		}
	}
	else
	{
			/**
				The time is passed for that day therefore we have to increase the date by one to ensure that the time is on the next day.We have to calculate the number of seconds to midnight and add it to the number of seconds from midnight to the current time.This will become the number of seconds that will be used by the sleep keyword to notify the system of when to play the alarm music. If a year is a leap year.The preceding year can never be a leap year. However is a year is normal.The preceding year could be a leap year. This logic was conveniently expressed in the preceding codes.
			*/

	  	int mday = atoi(tokens[2]);
		int year = atoi(tokens[4]);
		bool status = false;

		if (isLeapYear( year ))
		{
			if (mday >= leap_year_month_day[11])
			{
				year++;
				status = isLeapYear( year );
			}

			if(status == true)
			{
				if(mday < leap_year_month_day[monthVal]) 
				{
					mday++;
				}else
				{
					mday = 1;		//initialize the day
				}

				if(mday >= leap_year_month_day[monthVal])
				{
					monthVal++;
				}
				else
				{
					monthVal = 0;  //initialize the month
				}
			}else
			{
				if(mday < normal_year_month_day[monthVal])
				{
					mday++;
				}else
				{
					mday = 1;		//initialize the day
				}

				if(mday >= normal_year_month_day[monthVal])
				{
					monthVal++;
				}else
				{
					monthVal = 0;  //initialize the month
				}
			}

		}
		else
		{
			if (mday >= normal_year_month_day[11])
			{
				year++;
				status = isLeapYear( year );
			}

			if(status == false)
			{
				if(mday < normal_year_month_day[monthVal]) 
				{
					mday++;
				}else
				{
					mday = 1;  //initialize the day
				}

				if(mday >= normal_year_month_day[monthVal])
				{
					monthVal++;
				}else
				{
					monthVal = 0;  //initialize the month
				}
			}else
			{
				if(mday < leap_year_month_day[monthVal]) 
				{
					mday++;
				}else
				{
					mday = 1;   //initialize the day
				}

				if(mday >= leap_year_month_day[monthVal])
				{
					monthVal++;
				}else
				{
					monthVal = 0;  //initialize the month
				}
			}

		}


		struct tm Time3;
		Time3.tm_hour = hour;
		Time3.tm_min = minute;
		Time3.tm_sec = 0;

	  	Time3.tm_mday = mday;
	  	Time3.tm_mon = monthVal - 1;
	  	Time3.tm_year = year - 1900;

		time_t TimeT3 = mktime( &Time3 );


		Diff = difftime( TimeT3 ,TimeT1);
		printf("Difference: %f",Diff);

		readyToSleep =  sleep((int)Diff );
		if(readyToSleep == 0)
		{
			playsound();
		}

	}

}

/**
	This function will determine if a given year is leap year
*/
bool isLeapYear(int year)
{
	bool status = false;
    if (((year % 4)== 0 && (year % 100) != 0) || ((year % 400)== 0))
        status = true;
    else 
		status = false;
	return status;
}


void timer(int delay)
{
	unsigned readyToSleep =  sleep(delay );
	if(readyToSleep == 0)
	{
		playsound();
	}
}
