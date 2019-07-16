#include "robot-config.h"
#include <cmath>
//----------------------------------------------------------------//
/*---------------------Introdcutions of controller----------------
   AXIS2 : the forward and backword move of the model, the speed 
is determined by the exact position of the axis;
   AXIS4 : turn left and right
   ButtonL1:  make the brusher to rotate clockwise
   ButtonL2:  make the brusher to rotate counterclockwise
   ButtonR1:  make the block_catcher to move up
   ButtonR2:  make the block_catcher to move down
---------------------------------------------------------------**/ 


//----value for modification-------//
const int turning_speed = 75;
const int rising_speed = 40;
const int low_speed = 35;
const int low_turning_speed = 10;
const int brushing_speed = 100;
//------shift gear-----------------//
bool move_flag = false;


//------declaration of functions for the autonoumous section------------//
void autonomous_section();
  // autonomous_section actually is the combination of these sub-function:
  /* In the end of each function below we add a stop function to the certain gear, 
  that is to say,the function(operation)is set to run a finite distance */
  void moving_fwd(int ,int  ); 
  void moving_bwd(int,int  );
  void turning_left(int,int );
  void turning_right(int,int );
  void brusher_up(int,int );
  void brusher_down(int,int );
  void catcher_up(int,int );
  void catcher_down(int,int ); 
//---------------------------------------------------------------------//



//-------function of the hand-operated section---------//
void moving_part();
void turning_part();
void brusher_part();
void catcher_part();  //rising part
void stop_driver_motor(){
    motor_driver_Left1.stop();
    motor_driver_Left2.stop();
    motor_driver_Left3.stop();
    motor_driver_Right1.stop();
    motor_driver_Right2.stop();
    motor_driver_Right3.stop();
}
void stop_brusher_motor(){
    motor_brusher_left.stop();
    motor_brusher_right.stop();
}
void stop_catcher_motor(){
  motor_riser_left.stop( vex::brakeType::hold);
  motor_riser_right.stop( vex::brakeType::hold);
}

void buttonup_pressed(){
    move_flag = !move_flag;
}

//-----------------------------------------------------//



int main() {
   void autonomous_section();
    while(1){   
        controller1.ButtonUp.pressed(buttonup_pressed);
        controller1.Screen.clearScreen();
       if (move_flag) controller1.Screen.print(1); else controller1.Screen.print(0);
       moving_part();
       turning_part();
       brusher_part();
       catcher_part();
        
       vex::task::sleep(10);
    }
    
}

int func(int a){
    return a+73;
}

int func2(int a){
    return -a+73;
}

int move_func(int a){
    return a + 23;
}

int move_func2(int a){
    return -a + 23;
}

int raiser_func(int a){
    return int(sqrt(a)*4);
}

int raiser_func2(int a){
    return int(sqrt(-a)*4);
}



void moving_part(){
    
     if(controller1.Axis3.value()>15){
         
          motor_driver_Left1.spin(vex::directionType::rev,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);
         motor_driver_Left2.spin(vex::directionType::fwd,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);
         motor_driver_Left3.spin(vex::directionType::rev,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Right1.spin(vex::directionType::fwd,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Right2.spin(vex::directionType::rev,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);
         motor_driver_Right3.spin(vex::directionType::fwd,move_flag?low_speed:func(controller1.Axis3.value()),velocityUnits::rpm);  
        
        }else if(controller1.Axis3.value()<-15){
            
          motor_driver_Left1.spin(vex::directionType::fwd,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);
         motor_driver_Left2.spin(vex::directionType::rev,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Left3.spin(vex::directionType::fwd,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Right1.spin(vex::directionType::rev,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Right2.spin(vex::directionType::fwd,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);
          motor_driver_Right3.spin(vex::directionType::rev,move_flag?low_speed:func2(controller1.Axis3.value()),velocityUnits::rpm);  
            
        }else{
         stop_driver_motor();}    
               
        
}

void turning_part(){
    
     //turn left and right,the deg of turning is decided by the operator
    
          if(controller1.Axis4.value()>30){
              motor_driver_Right1.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Right2.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Right3.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct); 
              motor_driver_Left1.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Left2.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Left3.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct); 
              
          }
         else if(controller1.Axis4.value()<-30){
              motor_driver_Left1.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Left2.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Left3.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct); 
             motor_driver_Right1.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Right2.spin(vex::directionType::rev,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
              motor_driver_Right3.spin(vex::directionType::fwd,move_flag?low_turning_speed:turning_speed,velocityUnits::pct);
          }else{
              if (controller1.Axis3.value()>-15 && controller1.Axis3.value()<15)
                 stop_driver_motor();
          }
}



void brusher_part(){
    
    if(controller1.ButtonR1.pressing()){
        motor_brusher_left.spin(vex::directionType::fwd,brushing_speed,velocityUnits::pct);
        motor_brusher_right.spin(vex::directionType::rev,brushing_speed,velocityUnits::pct);       
    }
    
    else if(controller1.ButtonR2.pressing()){
        motor_brusher_left.spin(vex::directionType::rev,brushing_speed,velocityUnits::pct);
        motor_brusher_right.spin(vex::directionType::fwd,brushing_speed,velocityUnits::pct);       
    }
    
    //if((!controller1.ButtonR1.pressing())&&(!controller1.ButtonR2.pressing()))
	else
    {  
        stop_brusher_motor();
    }
}
void catcher_part(){
  //CATCHING UP
    if(controller1.Axis2.value()>15){
        motor_riser_left.spin(vex::directionType::rev,raiser_func(controller1.Axis2.value()),velocityUnits::rpm);
        motor_riser_right.spin(vex::directionType::fwd,raiser_func(controller1.Axis2.value()),velocityUnits::rpm);
    }
  //PUT IT DOWN
    else if(controller1.Axis2.value()<-15){
        motor_riser_left.spin(vex::directionType::fwd,raiser_func2(controller1.Axis2.value()),velocityUnits::rpm);
        motor_riser_right.spin(vex::directionType::rev,raiser_func2(controller1.Axis2.value()),velocityUnits::rpm);
    }
  // if no 1-Button is pressed, just stop the motor  
    /* if((!controller1.ButtonL1.pressing())&&(!controller1.ButtonL2.pressing())) */
	else
    {  
        stop_catcher_motor();
    }
    
}

void atonomous_section(){
    /*to do operations in the 45s-
    autonomous part of the game using 
       the sub-functions below*/
    
    
}


void moving_fwd(int speed,int t){
     motor_driver_Left1.spin(directionType::fwd,speed,velocityUnits::pct);
     motor_driver_Left2.spin(directionType::fwd,speed,velocityUnits::pct);
     motor_driver_Left3.spin(directionType::fwd,speed,velocityUnits::pct);
     motor_driver_Right1.spin(directionType::fwd,speed,velocityUnits::pct);
     motor_driver_Right2.spin(directionType::fwd,speed,velocityUnits::pct);
     motor_driver_Right3.spin(directionType::fwd,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_driver_motor();
}

void moving_bwd(int speed,int t){
     motor_driver_Left1.spin(directionType::rev,speed,velocityUnits::pct);
     motor_driver_Left2.spin(directionType::rev,speed,velocityUnits::pct);
     motor_driver_Left3.spin(directionType::rev,speed,velocityUnits::pct);
     motor_driver_Right1.spin(directionType::rev,speed,velocityUnits::pct);
     motor_driver_Right2.spin(directionType::rev,speed,velocityUnits::pct);
     motor_driver_Right3.spin(directionType::rev,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_driver_motor();
}

void turning_left(int speed,int t){
    motor_driver_Right1.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_driver_Right2.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_driver_Right3.spin(directionType::fwd,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_driver_motor();
}

void turning_right(int speed,int t){
    motor_driver_Left1.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_driver_Left2.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_driver_Left3.spin(directionType::fwd,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_driver_motor();
}

void brusher_up(int speed,int t){
    motor_brusher_left.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_brusher_right.spin(directionType::rev,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_brusher_motor();
}
void brusher_down(int speed,int t){
    motor_brusher_left.spin(directionType::rev,speed,velocityUnits::pct);
    motor_brusher_right.spin(directionType::fwd,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_brusher_motor();
}
void catcher_up(int speed,int t ){
    motor_riser_left.spin(directionType::fwd,speed,velocityUnits::pct);
    motor_riser_right.spin(directionType::fwd,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_catcher_motor();
}
void catcher_down(int speed,int t){
    motor_brusher_left.spin(directionType::rev,speed,velocityUnits::pct);
    motor_brusher_right.spin(directionType::rev,speed,velocityUnits::pct);
    
    vex::task::sleep(t);
    stop_catcher_motor();
}
