#include <Time.h>
#include <TimeLib.h>

//declare and initialize relevant variables
const int IRR_SIZE = 8;
const int VALVE_COUNT = 3;
const int PUMP_COUNT = 2;
const int RINSE_TIME = 10;

//hour, minute, second, day, month, year
int startTime[] = {00,00,00,1,1,2020};

//indicates which valve is active at the time
bool active_valve[VALVE_COUNT] = {0,0,0};

//each row represents a valve to be set and the columns are the times in which the irrigation is to take place
int irr_hours[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int irr_minutes[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int irr_seconds[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};

//each row represents a valve to be set and the columns are the day of the of the week, if that day is saved as 1, irrigation times will be active that day
bool irr_days[VALVE_COUNT][7] = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0,0,0,0,0,0,0}};

//Duration in seconds
int irr_duration;

// will store the time for ending irrigation on each active valve in index order
int irr_end_time [VALVE_COUNT][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};


const int FER_SIZE = 8;


//each row represents a valve to be set and the columns are the times in which the fertilization is to take place
int fer_hours[VALVE_COUNT][FER_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int fer_minutes[VALVE_COUNT][FER_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int fer_seconds[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};

//specifies duration of the intended fertilization event
int fer_duration[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};

//specifies pump used in the intended fertilization event
int fer_pump[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};


//each row represents a valve to be set and the columns are the day of the of the week, if that day is saved as 1, fertilization times will be active that day
bool fer_days[VALVE_COUNT][7] = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0,0,0,0,0,0,0}};

int valve_pin [VALVE_COUNT] = {2,3,4};
int pump_pin [PUMP_COUNT] = {5,6};






void setup()
{
  // put your setup code here, to run once:
  Serial.begin(19200);
  loadSchedule();
  setTime(startTime[0], startTime[1], startTime[2], startTime[3], startTime[4], startTime[5]); //hour, minute, second, day, month, year
  //set valve pin modes
  for (int i=0; i < VALVE_COUNT; i++)
  {
    pinMode(valve_pin[i], OUTPUT);
  }
  for (int i=0; i < PUMP_COUNT; i++)
  {
    pinMode(pump_pin[i], OUTPUT);
  }


}

void loop()
{
  int event =-1;
  int event_valve = -1;
  int fer_index = -1;

  checkEvent(&event, &event_valve, &fer_index);
  switch(event)
  {
    case 1: //Irrigation Start
            irrigationStart(event_valve);
            break;
    case 2: //Fertilization
            fertilization(event_valve, fer_index);
            break;
    case 3: //End irrigation
            irrigationEnd(event_valve);
            break;
  }
  delay(999);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(weekday());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}


void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

//Laods the schedule variables irrigation hours, minutes, days and duration as well as the fertilization times and durations.
void loadSchedule()
{
  //The data must come in as a csv, where \ delimits the sectors
  while(Serial.available() <= 0)
  {}
  //Stores incoming Serial Data
  String data = Serial.readString();
  char str [data.length()];
  
  

  data.toCharArray(str, data.length());
  delay(300);
  Serial.println("Start");
  const char s1[2]=",";
  char *token;

  int data_array[VALVE_COUNT][data.length()];
  data_array[0][0] =-2;
  data_array[1][0] =-2;
  data_array[2][0] =-2;

  token = strtok(str, s1);
  int i=0;
  while(token != NULL)
  {
    data_array[0][i] = String(token).toInt();
    data_array[0][i+1] = -2;
    token = strtok(NULL, s1);
    i++;
  }

  i=0;
  int sector = data_array[0][0];
  i++;
  for(int j=0; j<sizeof(startTime)/sizeof(startTime[0]); i++, j++)
  {

    startTime[j] = data_array[sector][i];

  }
  for(int j=0; j<IRR_SIZE; i++, j++)
  {

    irr_hours[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<IRR_SIZE; i++, j++)
  {

    irr_minutes[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<IRR_SIZE; i++, j++)
  {

    irr_seconds[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<7; i++, j++)
  {

    irr_days[sector][j] = data_array[sector][i];

  }
  irr_duration = data_array[sector][i];
  i++;


  for(int j=0; j<FER_SIZE; i++, j++)
  {

    fer_hours[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<FER_SIZE; i++, j++)
  {

    fer_minutes[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<FER_SIZE; i++, j++)
  {

    fer_seconds[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<FER_SIZE; i++, j++)
  {

    fer_duration[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<FER_SIZE; i++, j++)
  {

    fer_pump[sector][j] = data_array[sector][i];

  }
  for(int j=0; j<7; i++, j++)
  {

    fer_days[sector][j] = data_array[sector][i];

  }
}

//Checks for events that signal whether is is time or day for an event
//If there is an event it will identify which valves have that event
void checkEvent(int *event, int *event_valve, int *event_index)
{
  const int IRRIGATION = 1;
  const int FERTILIZATION = 2;
  const int END_IRRIGATION = 3;

  //check end irrigation
  for(int i=0; i < VALVE_COUNT; i++)
  {
    if((hour() >= irr_end_time[i][0] && irr_end_time[i][0] != -1) && (minute() >= irr_end_time[i][1] && irr_end_time[i][1] != -1) && (second() >= irr_end_time[i][2]&& irr_end_time[i][2] != -1))
    {
      *event = END_IRRIGATION;
      *event_valve = i;
      return;
    }
  }

  //check if there is an irrigation today
  for (int valve=0; valve < VALVE_COUNT; valve++)
  {
    //ignore any events concerning valves already in use
    if(active_valve[valve] == 1)
    {
      continue;
    }
    //checks if today is a day for irrigation
    if(irr_days[valve][weekday()-1] == 1)
    {
      //check if the hour right now is an hour for irrigation
      for(int hour_index = 0; hour_index < IRR_SIZE; hour_index++)
      {
        //check if the hour being looked at is the same as the hour right now
        if (irr_hours[valve][hour_index] == hour())
        {

          if(irr_minutes[valve][hour_index] == minute())
          {
            if (second() >= irr_seconds[valve][hour_index] && second() <= irr_seconds[valve][hour_index] + 5)
            {
              //we have found an hour and minute where an irrigation is to take place,
              *event = IRRIGATION;
              *event_valve = valve;
              return;
              }
          }
        }
      }
    }

    //check if any valve is open, if so, ignore any fertilization events
    bool active = false;
    for (int i = 0; i < VALVE_COUNT; i++)
    {
      if(active_valve[i] == 1)
      {
        active = true;
        break;
      }
    }

    //only check for fertilization event if all valves are closed
    if (active == false)
    {
      //checks if today is a day for fertilization
      if(fer_days[valve][weekday()-1] == 1)
      {
        //check if the hour right now is an hour for fertilization
        for(int hour_index = 0; hour_index < IRR_SIZE; hour_index++)
        {
          //check if the hour being looked at is the same as the hour right now
          if (fer_hours[valve][hour_index] == hour())
          {

            if(fer_minutes[valve][hour_index] == minute())
            {
              if (second() >= fer_seconds[valve][hour_index] && second() <= fer_seconds[valve][hour_index] + 5)
              {
                //we have found an hour and minute where an fertilization is to take place,
                *event = FERTILIZATION;
                *event_valve = valve;
                *event_index = hour_index;
                return;
              }

            }
          }
        }
      }
    }
  }

  return;

}

void irrigationStart(int valve)
{
  digitalWrite(valve_pin[valve], HIGH);
  active_valve[valve] = 1;

  time_t t = now();
  irr_end_time[valve][0] = hour(t + irr_duration);
  irr_end_time[valve][1] = minute(t + irr_duration);
  irr_end_time[valve][2] = second(t + irr_duration);
}

void irrigationEnd(int valve)
{
  //turn off valve, reset irr_end_time, reset active_valve
  digitalWrite(valve_pin[valve], LOW);
  irr_end_time[valve][0] = -1;
  irr_end_time[valve][1] = -1;
  irr_end_time[valve][2] = -1;
  active_valve[valve] = 0;
}

void fertilization(int valve, int fer_index)
{
  digitalWrite(valve_pin[valve], HIGH);
  digitalWrite(pump_pin[fer_pump[valve][fer_index]], HIGH);

  delay(fer_duration[valve][fer_index] * 1000);

  digitalWrite(pump_pin[fer_pump[valve][fer_index]], LOW);

  delay(RINSE_TIME * 1000);

  digitalWrite(valve_pin[valve], LOW);
}
