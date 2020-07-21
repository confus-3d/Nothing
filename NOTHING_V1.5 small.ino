#define DEATH_INTERVAL 10000
Timer deathTimer;
#define DEATH_SWITCH 500
Timer switchTimer;
Timer nextStep;

enum blinkState {ALIVE, DEAD};
byte blinkState = ALIVE;

byte hue=0;
byte dead=0;
byte numNeighbors = 0;
byte pastNeighbors = 0;
byte firstRun = 0;

void setup() {
}

void loop() {
  numNeighbors = 0;
  FOREACH_FACE(f) {if (!isValueReceivedOnFaceExpired(f)) numNeighbors++;} 
  if (blinkState == ALIVE) aliveLoop();
  if (blinkState == DEAD) deadLoop();
  setValueSentOnAllFaces(blinkState);
}

void aliveLoop(){
  if (buttonPressed() || pastNeighbors != numNeighbors) {deathTimer.set(DEATH_INTERVAL); blinkState = DEAD;}
  if (nextStep.isExpired()) {setColor(makeColorHSB(hue,255,255)); hue++; nextStep.set(40);}
}

void deadLoop(){
  if (firstRun == 0) {deathTimer.set(DEATH_SWITCH*2); firstRun++;}
  if (deathTimer.isExpired()) blinkState = ALIVE;
  if (pastNeighbors != numNeighbors) pastNeighbors = numNeighbors;
  setColor(RED); setColorOnFace(WHITE, dead); setColorOnFace(WHITE, dead+2); setColorOnFace(WHITE, dead+4);
  if (switchTimer.isExpired()) {switchTimer.set(DEATH_SWITCH); dead = (dead + 1) % 2;}
}
