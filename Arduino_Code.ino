#include <Time.h>
#include <TimeLib.h>

//declare and initialize relevant variables
const int irr_size = 8;
int irr_hours [irr_size] = {-1,-1,-1-1,-1,-1,-1,-1};
int irr_minutes[irr_size] = {-1,-1,-1-1,-1,-1,-1,-1};

//each index represents a day of the week, if that day is saved as 1, irrigation times will be active that day
bool irr_days = {0,0,0,0,0,0,0};

//Duration in seconds
int irr_duration;


const int fer_size = 8;
int fer_hours [fer_size] = {-1,-1,-1-1,-1,-1,-1,-1};
int fer_minutes [fer_size] = {-1,-1,-1-1,-1,-1,-1,-1};  

//each index represents a day of the week, if that day is saved as 1, irrigation times will be active that day
bool fer_days = {0,0,0,0,0,0,0};

//Duration in seconds, will account for rinse time as well, it cannot take a value lower than rinse time
int fer_duration;





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setTime(7,26,45,2,11,2020);
  loadSchedule();


  


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalClockDisplay();
  delay(5500);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}


void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void loadSchedule(){
  
  irr_hours[0] = 0; irr_hours[1] = 0; irr_hours[2] = 0; irr_hours[3] = 0; irr_hours[4] = 0; irr_hours[5] = 0; irr_hours[6] = 0; irr_hours[7] = 0;
  irr_minutes[0] = 0; irr_minutes[1] = 0; irr_minutes[2] = 0; irr_minutes[3] = 0; irr_minutes[4] = 0; irr_minutes[5] = 0; irr_minutes[6] = 0; irr_minutes[7] = 0;
  irr_days[0] = 0; irr_days[1] = 0; irr_days[2] = 0; irr_days[3] = 0; irr_days[4] = 0; irr_days[5] = 0; irr_days[6] = 0;
  irr_duration = 120;

  
  fer_hours[0] = 0; fer_hours[1] = 0; fer_hours[2] = 0; fer_hours[3] = 0; fer_hours[4] = 0; fer_hours[5] = 0; fer_hours[6] = 0; fer_hours[7] = 0;
  fer_minutes[0] = 0; fer_minutes[1] = 0; fer_minutes[2] = 0; fer_minutes[3] = 0; fer_minutes[4] = 0; fer_minutes[5] = 0; fer_minutes[6] = 0; fer_minutes[7] = 0;
  fer_days[0] = 0; fer_days[1] = 0; fer_days[2] = 0; fer_days[3] = 0; fer_days[4] = 0; fer_days[5] = 0; fer_days[days
  fer_duration = 120;

}