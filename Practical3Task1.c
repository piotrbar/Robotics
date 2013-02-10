#pragma config(Sensor, S1,     rightLightSensor,    sensorCOLORGREEN)
#pragma config(Sensor, S2,     rightTouchSensor,    sensorTouch)
#pragma config(Sensor, S3,     leftTouchSensor,     sensorTouch)
#pragma config(Sensor, S4,     leftLightSensor,     sensorCOLORGREEN)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void pidSetup();
void rotate(int deg);
void stop();
void move(int ncm);
int cm2rotations(int ncm);
int deg2rotations(int deg);
void moveToTarget();

int power = 10;
float rotationsForCm = 28.14; //number of rotations required for a cm
float rotationsFordeg = 3.48; //number of rotations required to turn for a degree

const tSensors rightTouchSensor = (tSensors) S2;
const tSensors leftTouchSensor = (tSensors) S3;

bool handleObstacleLeft = false;
bool handleObstacleRight = false;
bool passingByObstacle = false;

task checkObstacles(){
        while(true){
                  handleObstacleLeft = SensorValue(leftTouchSensor) == 1;
                        handleObstacleRight = SensorValue(rightTouchSensor) == 1;
        }
}

task obstacleHandler(){  
      passingByObstacle = true;
        
          int direction = (handleObstacleLeft == true) ? -1 : 1;  
            handleObstacleLeft = false;
              handleObstacleRight = false;
                
                  move(-10);
                    rotate(-direction*90);
                      move(15);
                        rotate(direction*70);
                          move(10);
                            
                              passingByObstacle = false;
}

void moveToTarget(){
         motor[motorA] = power;
              motor[motorC] = power;
}

task main() {
        pidSetup();     
            StartTask(checkObstacles);
                wait1Msec(500);
                    while(true){
                              wait1Msec(400);
                                    if(handleObstacleLeft){
                                                  StopTask(obstacleHandler);
                                                            StartTask(obstacleHandler);
                                    } else if(handleObstacleRight){
                                                  StopTask(obstacleHandler);
                                                            StartTask(obstacleHandler);
                                    } else if(!passingByObstacle){
                                                  moveToTarget();
                                    } 
                    }
}

void pidSetup() {
        nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
            nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
}

void rotate(int deg) {
        int rotations = deg2rotations(abs(deg));
            nMotorEncoder[motorA] = 0;
                nMotorEncoder[motorC] = 0;
                
                    nMotorEncoderTarget[motorA] = rotations;
                        nMotorEncoderTarget[motorC] = rotations;
                        
                            int sign = (deg < 0) ? -1 : 1;
                            
                                motor[motorA] = sign * -power;
                                    motor[motorC] = sign * power;
                                        while (nMotorRunState[motorA] != runStateIdle && nMotorRunState[motorA] != runStateHoldPosition) {}
                                            
                                                stop();
}

void move(int ncm) {
        int rotations = cm2rotations(abs(ncm));
            nMotorEncoder[motorA] = 0;
                nMotorEncoder[motorC] = 0;
                
                    int sign = (ncm < 0) ? -1 : 1;
                    
                        nMotorEncoderTarget[motorA] = rotations;
                            motor[motorA] = sign * power;
                                motor[motorC] = sign * power;
                                
                                    while (nMotorRunState[motorA] != runStateIdle && nMotorRunState[motorA] != runStateHoldPosition) {}
                                        stop();
}

int cm2rotations(int ncm) {
        return ncm * rotationsForCm;
}

int deg2rotations(int deg) {
        return deg * rotationsFordeg;
}

void stop() {
        motor[motorA] = 0;
            motor[motorC] = 0;
                nMotorEncoder[motorA] = 0;
                    nMotorEncoder[motorC] = 0;
                        wait1Msec(100);
}
