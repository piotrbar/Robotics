void pidSetup();
float checkIfLinesIntersect(float l1_x1, float l1_y1, float theta, float l2_x1, float l2_y1, float l2_x2, float l2_y2);
float calculate_likelihood(float x, float y, float theta, float z);
void initialiseWeights();
void updateWeightArray(float z);
void updateCumulativeWeightArray();
void normalise();
void resample();
int findIndexOfResampledParticle (float randNum);

const int NUMBER_OF_PARTICLES = 100;
const int NUMBER_OF_WALLS = 8;

float xArray[NUMBER_OF_PARTICLES];
float yArray[NUMBER_OF_PARTICLES];
float thetaArray[NUMBER_OF_PARTICLES];
float weightArray[NUMBER_OF_PARTICLES];
float cumulativeWeightArray[NUMBER_OF_PARTICLES];

// Definitions of walls
// a: O to A
// b: A to B
// c: C to D
// d: D to E
// e: E to F
// f: F to G
// g: G to H
// h: H to O
//                                      a    b    c    d    e    f    g    h
float wallAxArray[NUMBER_OF_WALLS] = {  0,   0,  84,  84, 168, 168, 210, 210};
float wallAyArray[NUMBER_OF_WALLS] = {  0, 168, 126, 210, 210,  84,  84,   0};
float wallBxArray[NUMBER_OF_WALLS] = {  0,  84,  84, 168, 168, 210, 210,   0};
float wallByArray[NUMBER_OF_WALLS] = {168, 168, 210, 210,  84,  84,   0,   0};


task main() {
  pidSetup();
  // initialise arrays:
  // initialiseWeights();
  // ...
  // every few seconds stop and measure distance with sonar (z)
  // update all the particles, weights, etc:
  // 
  // updateWeightArray(z);
  // normalise();
  // updateCumulativeWeightArray();
  // resample();
  // MOVE!!!

}

// Takes the position estimate of a particle (x, y, theta) and the sonar measurement z
// and returns a likelihood value.
float calculate_likelihood(float x, float y, float theta, float z) {
  // check which wall the particle would hit
  float minDistance = 300.0; // distance between the particle and the wall,
  for(int i=0; i<NUMBER_OF_WALLS; ++i) {
    float Ax = wallAxArray[i];
    float Ay = wallAyArray[i];
    float Bx = wallBxArray[i];
    float By = wallByArray[i];
    
    float m = checkIfLinesIntersect(x,y,theta,Ax,Ay,Bx,By);
    // if a particle would hit the wall, find the wall that would be hit first
    if(m>=0.0) {
      if(m < minDistance) minDistance = m;
    }
  }
  
  // calculate likelihood value given the distance of particle from the wall and sonar measurement
  // TODO: improve likelihood function and use Gaussian
  float likelihood = 1/(1+(abs(z-minDistance)));
  return likelihood;
}

// Checks if direction of a particle in point (l1_x1, l1_y) and angle 'theta' intersects with a wall
// given by points l2_x1 and l2_y2. If lines don't intersect, returns -1, otherwise the expected distance
// from the particle to the wall.
float checkIfLinesIntersect(float l1_x1, float l1_y1, float theta, float l2_x1, float l2_y1, float l2_x2, float l2_y2) {
  // Calculate line equation for the current direction of a particle.
  // y = mx + b
  float length = 300.0; // arbitrary distance, long enough to intersect with any wall
  float l1_x2 = (float) (l1_x1 + length*cos(theta)); // arbitrary end of line expressing particle direction
  float l1_y2 = (float) (l1_y1 + length*sin(theta));
  
  float m1 = (l1_y2 - l1_y1)/(l1_x2 - l1_x1);
  float b1 = l1_y1 - (m1*l1_x1);
  
  // calculate line equation of the wall
  float m2 = (l2_y2 - l2_y1)/(l2_x2 - l2_x1);
  float b2 = l2_y1 - (m2*l2_x1);
  
  //check if lines intersect
  float x = (b2-b1)/(m1-m2);
  float y = m1*x+b1;
  if(y == m2*x+b2) {
    // calculate distance of the particle from point of intersection
    float distance = sqrt((x-l1_x1)*(x-l1_x1)+(y-l1_y1)*(y-l1_y1));
    return distance;
  }
  else return -1.0;
}

// Sets the weights to be equal (1/NUMBER_OF_PARTICLES) each in the beginning.
void initialiseWeights() {
  for (int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    weightArray[i] = 1/NUMBER_OF_PARTICLES;
  }
}

// Updates weights taking into account likelihood of each particle and given distance z measured by sonar.
void updateWeightArray(float z) {
  float likelihood;
  for(int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    likelihood = calculate_likelihood(xArray[i], yArray[i], thetaArray[i], z);
    weightArray[i] = likelihood*weightArray[i];
  }
}

// We assume that we have more than 1 particle.
void updateCumulativeWeightArray() {
  cumulativeWeightArray[0] = weightArray[0];
  for(int i=1; i<NUMBER_OF_PARTICLES; ++i) {
    cumulativeWeightArray[i] = cumulativeWeightArray[i-1] + weightArray[i];
  }
}

// Scales weights of all particles so that they all add up to 1.
void normalise() {
  // calculate sum of all unnormalised weights:
  int W = 0;
  for(int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    W+=weightArray[i];
  }
  for(int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    weightArray[i] = weightArray[i]/W;
  }
}

// Draws NUMBER_OF_PARTICLES particles given their weights and updates the arrays with the new particles.
// Particles with bigger weights have higher probability to be drawn.
void resample() {
  float tempXArray[NUMBER_OF_PARTICLES];
  float tempYArray[NUMBER_OF_PARTICLES];
  float tempThetaArray[NUMBER_OF_PARTICLES];
  float randNum;
  for(int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    randNum = (float) (random(100))/100.0;
    int indexOfResPart = findIndexOfResampledParticle(randNum);
    tempXArray[i] = xArray[indexOfResPart];
    tempYArray[i] = yArray[indexOfResPart];
    tempThetaArray[i] = thetaArray[indexOfResPart];
  }

  // update the arrays with old particles with the ones that were resampled.
  for(int i=0; i<NUMBER_OF_PARTICLES; ++i) {
    xArray[i] = tempXArray[i];
    yArray[i] = tempYArray[i];
    thetaArray[i] = tempThetaArray[i];
  }
}

// Iterates through the cumulativeWeightArray and returns
// index of a particle that was resampled.
int findIndexOfResampledParticle (float randNum) {
  // the range of cumulative probabilities for the first particle
  // is 0 - probability of the first particle
  if(randNum >= 0 && randNum < cumulativeWeightArray[0]) return 0;
  for(int i=1; i<NUMBER_OF_PARTICLES; ++i) {
    if(randNum>= cumulativeWeightArray[i-1] && randNum<cumulativeWeightArray[i])
      return i;
  }
  return 0 ;
}

void pidSetup() {
    nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
    nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
}
