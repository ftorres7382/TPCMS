String data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Before available");
  while(Serial.available() <= 0)
    {}
  Serial.println("After available");
  data = Serial.readString();

  //if data is not null, turn a pin to high
  // Serial.println(data.length());
  Serial.println("Before If");
  if(data.length() > 1){
    Serial.println(data);
    digitalWrite(3, HIGH);
    Serial.println("Inside If");
  }
  Serial.println("After If");
}
