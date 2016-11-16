
//Define input pins
int muscle_pin = 0;
//Define output pins

//Define sensor variables
int muscle_current;
int muscle_previous;

//Define derivative variables
int derivative_current;
int derivative_previous = 0;

int k_p; 

int time_step = 50; //define time step of 50ms
 
void setup() {
  
muscle_current = analogRead(muscle_pin); //assign initial muscle sensor input to variable

}

void loop() {

  //measure muscle sensor input
  delay(time_step);
  muscle_previous = muscle_current; //assign previous muscle sensor value
  delay(time_step);
  muscle_current = analogRead(muscle_pin); //assign current muscle sensor value

  derivative_previous = derivative_current; //assign previous derivative
  derivative_current = (muscle_current - muscle_previous) / time_step; //take discrete derivative

  k_p = actuation_rate(derivative_current, derivative_previous);

  //if current derivative is positive, leg is extending
  if(derivative_current > 0){
    
    //apply k_p to front muscle, actuate front muscle and deflate back muscle
    
  }
  
  //if current derivative is negative, leg is bending
  if(derivative_current < 0){

    //apply k_p to back muscle and deflate front muscle
    
  }
}


int actuation_rate(int d_current, int d_previous){

  //decide rate of actuation based on the comparison of the current and previous derivatives
  
}


