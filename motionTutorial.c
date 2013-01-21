void exercise1();
void exercise2();
void Forward40cm();
void Backward40cm();
void Left90deg();
void Right90deg();
void stop();

task main(){
  nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
  exercise1();
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
    Forward40cm();
    stop();
    Right90deg();
    stop();
  }
}

void Forward40cm(){
  motor[motorA] = 20;
  motor[motorC] = 20;
  wait1Msec(7000);
}

void Backward40cm(){
  motor[motorA] = -20;
  motor[motorC] = -20;
  wait1Msec(7000);
}

void Left90deg(){
  motor[motorA] = 20;
  motor[motorC] = -20;
  wait1Msec(2700);
}

void Right90deg(){
  motor[motorA] = -20;
  motor[motorC] = 20;
  wait1Msec(2700);
}

void stop(){
  motor[motorA] = 0;
  motor[motorC] = 0;
  wait1Msec(1000);
}
