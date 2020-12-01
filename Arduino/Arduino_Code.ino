#include <Time.h>
#include <TimeLib.h>

//declare and initialize relevant variables
const int IRR_SIZE = 8;
const int VALVE_COUNT = 3;
const int PUMP_COUNT = 2;
const int RINSE_TIME = 10;

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
int fer_minutes[VALVE_COUNT][FER_SIZE] ={{-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1}};
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
  Serial.begin(115200);
  setTime(7,26,57,2,12,2020);
  //set valve pin modes
  for (int i=0; i < VALVE_COUNT; i++)
  {
    pinMode(valve_pin[i], OUTPUT);
  }
  for (int i=0; i < PUMP_COUNT; i++)
  {
    pinMode(pump_pin[i], OUTPUT);
  }
  loadSchedule();

}

void loop() 
{
  int event =-1;
  int event_valve = -1;
  int fer_index = -1;

  checkEvent(&event, &event_valve, &fer_index);
  digitalClockDisplay();
  Serial.println(event);
  Serial.println(event_valve);
  switch(event)
  {
    case 1: //Irrigation Start
            irrigationStart(event_valve);
            Serial.println("Irrigation Started");
            break;
    case 2: //Fertilization
            fertilization(event_valve, fer_index);
            break;
    case 3: //End irrigation
            irrigationEnd(event_valve);
            Serial.println("Irrigation Ended");
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
  //Test events can happen at 7:27, wednesday
  //sets event at valve 0, wednesday
  // irr_days[0][3] = 1;
  // irr_days[1][3] = 1;
  // irr_days[2][3] = 1;
  //sets event at valve 0, at 7
  // irr_hours[0][0] = 7;
  // irr_hours[1][0] = 7;
  // irr_hours[2][0] = 7;
  //sets event at valve 0, at minute 27
  // irr_minutes[0][0] = 27;
  // irr_minutes[1][0] = 27;
  // irr_minutes[2][0] = 27;
  //sets event at valve 0, at second X
  // irr_seconds[0][0] = 0;
  // irr_seconds[1][0] = 10;
  // irr_seconds[2][0] = 20;

  fer_days[0][3] = 1;
  fer_days[1][3] = 1;
  // fer_days[2][3] = 1;
  //sets event at valve 0, at 7
  fer_hours[0][0] = 7;
  fer_hours[1][0] = 7;
  // fer_hours[2][0] = 7;
  //sets event at valve 0, at minute 27
  fer_minutes[0][0] = 27;
  fer_minutes[1][0] = 27;
  // fer_minutes[2][0] = 27;
  //sets event at valve 0, at second X
  fer_seconds[0][0] = 10;
  fer_seconds[1][0] = 50;
  // fer_seconds[2][0] = 35;
  //set fertilization to a pump
  fer_pump[0][0] = 0;
  fer_pump[1][0] = 1;

  //set fertilization duration 
  fer_duration[0][0] = 30;
  fer_duration[1][0] = 30;

  irr_duration = 30;
}

//Checks for events that signal wether is is time or day for an event
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
  Serial.println("Fertilization Started in pump:");
  Serial.println(fer_pump[valve][fer_index]);

  delay(fer_duration[valve][fer_index] * 1000);

  digitalWrite(pump_pin[fer_pump[valve][fer_index]], LOW);
  Serial.println("Fertilization STOPPED");

  delay(RINSE_TIME * 1000);

  digitalWrite(valve_pin[valve], LOW);
  Serial.println("Rinse has STOPPED");
}