//define pins for sensors
#define THIGH 3
#define ROT 4

// pins for solenoids
#define MUSCLE_THIGH 9
#define MUSCLE_CALF 10

//define global variables
//myoware (THIGH)
int cur_T;
int pre_T;
int dx_T;
int dx_max;
int dx_min = -dx_max;


//Rotory sensor
int cur_R;
int max_limit;
int min_limit;
int time_step = 30; //in milliseconds

void setup() {
  
  cur_T = analogRead(THIGH);
  cur_R = analogRead(ROT);
  
}

void loop() {

  pre_T = cur_T;
  cur_T = analogRead(THIGH);

  int discrete = interpretor(cur_T, pre_T);

  if (cur_R < max_limit && cur_R > min_limit ){

    actuate(discrete);
    
  }


}

int interpretor(int cur, int pre){

  int dx = (cur - pre) / (time_step / 1000); //converting milliseconds to seconds

  return dx;
  
}

int limit(int angle){
  
  int result;
  
  if (angle > max_limit || angle < min_limit){

    result = 0;
    return result;
  }

  else{

    result = 0;
    return result;
  }
}


void actuate( int dx){

  int x;
  if (dx > 0){

    x = (dx / dx_max) * 255;
    analogWrite(MUSCLE_THIGH, x);
    
  }
  else{

    x = -1 * (dx / dx_max) * 255;
    analogWrite(MUSCLE_CALF, x);
  }
  
}

