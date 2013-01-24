void exercise1();
void exercise2();
void Forward( int ncm );
void Backward( int ncm );
void Forward40cm();
void Backward40cm();
void Left90deg();
void Right90deg();
void stop();

task main(){
  nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;
  exercise1();
  exercise2();
}

void exercise1(){
  Forward40cm();
  stop();
  Backward40cm();
  stop();
  Right90deg();
  stop();
  Left90deg();
  stop();
}

void exercise2(){
  int i;
  for(i = 0; i < 4; i++){
    Forward(10);
    stop();
    Right90deg();
    stop();
  }
}

void Move( int ncm, int powerA, int powerB ){
  motor[motorA] = powerA;
  motor[motorB] = powerB;
  wait1Msec( ncm * (529 / (abs(powerA)/20)) );
}

void Forward( int ncm ){
  Move( ncm, 40, 40 );
}

void Backward( int ncm ){
  Move( ncm, -20, -20 );
}

void Forward40cm(){
  Forward(40);
}

void Backward40cm(){
  Backward(40);
}

void Left90deg(){
  motor[motorA] = -40;
  motor[motorB] = 40;
  wait1Msec(3600);
}

void Right90deg(){
  motor[motorA] = 40;
  motor[motorB] = -40;
  wait1Msec(3600);
}

void stop(){
  motor[motorA] = 0;
  motor[motorB] = 0;
  wait1Msec(1000);
}
