void exercise1();
void exercise2();
void stop();

void rotate( int deg );
void move( int ncm );

int x = 0;
int y = 0;
int rotation = 0;

int rotationsForCm = 35.45; //number of rotations required for a cm
float rotationsFordeg = 5.63; //number of rotations required to turn for a degree

int power = 40;

task main(){
  nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
  //exercise1();
  exercise2();
}

void exercise1(){
  move( 40 );
  move( -40 );
  rotate( 90 );
  rotate( -90 );
}

void exercise2(){
  int i;
  for(i = 0; i < 4; i++){
    move( 10 );
    rotate( 90 );
  }
}

int cm2rotations( int ncm ){
  return ncm * rotationsForCm;
}

int deg2rotations( int deg ){
  return deg * rotationsFordeg;
}

void updatePosition(){
  // Uncomment to track only a single dot
  //nxtClearPixel( 10 + x/200, 10 + y/200 );
  x += cosDegrees( rotation );
  y += sinDegrees( rotation );
  nxtSetPixel( x/200, y/200 );
}

void stop(){
  motor[motorA] = 0;
  motor[motorC] = 0;
  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorC] = 0;
  wait1Msec(1000);
}

void rotate( int deg ){
  int rotations = deg2rotations( abs(deg) );
  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorC] = 0;
  
  nMotorEncoderTarget[motorA] = rotations;
  nMotorEncoderTarget[motorC] = rotations;

  int sign = (deg < 0) ? -1 : 1;

  motor[motorA] = sign * -power;
  motor[motorC] = sign * power;
  while(nMotorRunState[motorA] != runStateHoldPosition && nMotorRunState[motorA] != runStateIdle){
  }

  rotation += deg;
  stop();
}

void move( int ncm ){
  int rotations = cm2rotations( abs(ncm) );
  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorC] = 0;
  
  nMotorEncoderTarget[motorA] = rotations;
  nMotorEncoderTarget[motorC] = rotations;

  int sign = (ncm < 0) ? -1 : 1;
  
  motor[motorA] = sign * power;
  motor[motorC] = sign * power;
  while(nMotorRunState[motorA] != runStateHoldPosition && nMotorRunState[motorA] != runStateIdle){
    if(nMotorEncoder[motorA] > 0 && motor[motorA] > 0){
      updatePosition();
    }
  }

  stop();
}
