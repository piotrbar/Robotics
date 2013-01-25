void exercise1();
void exercise2();
void stop();

void rotate( int deg );
void move( int ncm );

int x = 10;
int y = 10;
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
    move( 40 );
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
  //nxtClearPixel( x/10, y/10 );
  x += cosDegrees( rotation );
  y += sinDegrees( rotation );
  nxtSetPixel( x/10, y/10 );
}

void stop(){
  motor[motorA] = 0;
  motor[motorC] = 0;
  wait1Msec(100);
}

void rotate( int deg ){
  int rotations = deg2rotations( abs(deg) );
  nMotorEncoder[motorA] = 0;
  
  int sign = (deg < 0) ? -1 : 1;
  
  motor[motorA] = sign * -power;
  motor[motorC] = sign * power;
  
  while( true ){
    if(abs(nMotorEncoder[motorA]) > rotations){
      break;
    }
  }
  
  rotation += deg;
  
  nMotorEncoder[motorA] = 0;
  stop();
}

void move( int ncm ){
  int rotations = cm2rotations( abs(ncm) );
  nMotorEncoder[motorA] = 0;
  
  int sign = (ncm < 0) ? -1 : 1;
  
  motor[motorA] = sign * power;
  motor[motorC] = sign * power;
  
  while( true ){
    if(rotations % abs(nMotorEncoder[motorA]) == 0){
      updatePosition();
    }
    if(abs(nMotorEncoder[motorA]) > rotations){
      break;
    }
  }
  
  updatePosition();

  nMotorEncoder[motorA] = 0;
  stop();
}
