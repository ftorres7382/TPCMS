#include <Time.h>
#include <TimeLib.h>

//declare and initialize relevant variables
const int IRR_SIZE = 8;
const int VALVE_COUNT = 3;

//indicates which valve is active at the time
bool active_valve[VALVE_COUNT] = {0,0,0};

//each row represents a valve to be set and the columns are the times in which the irrigation is to take place
int irr_hours[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int irr_minutes[VALVE_COUNT][IRR_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};

//each row represents a valve to be set and the columns are the day of the of the week, if that day is saved as 1, irrigation times will be active that day
bool irr_days[VALVE_COUNT][7] = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0,0,0,0,0,0,0}};

//Duration in seconds
int irr_duration;
const int FER_SIZE = 8;


//each row represents a valve to be set and the columns are the times in which the fertilization is to take place
int fer_hours[VALVE_COUNT][FER_SIZE] = {{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
int fer_minutes[VALVE_COUNT][FER_SIZE] ={{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};

//each row represents a valve to be set and the columns are the day of the of the week, if that day is saved as 1, fertilization times will be active that day
bool fer_days[VALVE_COUNT][7] = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0,0,0,0,0,0,0}};

//Duration in seconds, will account for rinse time as well, it cannot take a value lower than rinse time
int fer_duration;





void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setTime(7,26,59,2,12,2020);
  loadSchedule();

}

void loop() 
{
  int event =-1;
  bool event_valve[VALVE_COUNT] = {0,0,0};

  checkEvent(&event, event_valve);
  digitalClockDisplay();
  Serial.println(event);
  Serial.print(event_valve[0]);
  Serial.print(" ");
  Serial.print(event_valve[1]);
  Serial.print(" ");
  Serial.println(event_valve[2]);

  if(second() == 10)
  {
    active_valve[0] = 1;
    active_valve[1] = 1;
    active_valve[2] = 1;
  }


  
  delay(1000);
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
  //Test events can happen at 7:27, wednesday
  //sets event at valve 0, wednesday
  irr_days[0][3] = 1;
  irr_days[1][3] = 1;
  irr_days[2][3] = 1;
  //sets event at valve 0, at 7
  irr_hours[0][0] = 7;
  irr_hours[1][0] = 7;
  irr_hours[2][0] = 7;
  //sets event at valve 0, at minute 27
  irr_minutes[0][0] = 27;
  irr_minutes[1][0] = 27;
  irr_minutes[2][0] = 27;


  irr_duration = 120;
  fer_duration = 120;
}


//Checks for events that signal wether is is time or day for an event
//If there is an event it will identify which valves have that event
void checkEvent(int *event, bool *event_valve)
{
  const int IRRIGATION = 1;

  //check if there is an irrigation today
  for (int valve=0; valve < VALVE_COUNT; valve++, event_valve++)
  {
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
            //we have found an hour and minute where an irrigation is to take place, 
            *event = IRRIGATION;
            *event_valve = 1;

          }
        }
      }
    }
  }

  if(*event != -1)
  {
    return;
  }
}