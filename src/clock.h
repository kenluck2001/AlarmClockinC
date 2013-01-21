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
#ifndef __CLOCK_h__
#define __CLOCK_h__



#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


char ** stringtokenizer(char *st,int SIZE);  //To tokenize the string from ctime()
int countParameter(char *st); //This count the number of tokenized string
int getDayValue(char * str, char *day[7]); //This gets the day from the string
int getMonthValue(char * str, char * month[12]);//This gets the month from the string
char** getArrayOfHourMinuteSeconds(char * str); //This returns an array of hours, minutes and seconds
void playsound();		//this plays the music to wake up the user
void showTime();		//this shows the current time to the user.
void setAlarm();         //this sets the alarm clock
bool isLeapYear(int year);
void timer(int delay);

#endif
