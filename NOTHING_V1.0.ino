#define DEATH_INTERVAL 10000
Timer deathTimer;

#define DEATH_SWITCH 500
Timer switchTimer;

enum blinkState {ALIVE, DEAD};
int blinkState = ALIVE;

byte hue=0;
Timer nextStep;
byte dead=0;

void setup() {
  // put your setup code here, to run once
}

void loop() {
  switch (blinkState) {
    case ALIVE:
      aliveLoop();
      aliveDisplay();
      break;
    case DEAD:
      deadLoop();
      break;
  }
  buttonPressed();
  setValueSentOnAllFaces(blinkState);
}

void aliveLoop(){
  if(buttonPressed() || !isAlone()){
    deathTimer.set(DEATH_INTERVAL);
    switchTimer.set(DEATH_SWITCH);
    blinkState = DEAD;
  }
}

void aliveDisplay(){
if (nextStep.isExpired()) {
    setColor( makeColorHSB( hue , 255 , 255 ) );
    hue++;     
    nextStep.set(40);
  }
}

void deadLoop(){
  if (deathTimer.isExpired()) {
    blinkState = ALIVE;
  }
  setColor(RED);
  setColorOnFace(WHITE, dead);
  setColorOnFace(WHITE, dead+2);
  setColorOnFace(WHITE, dead+4);
  if (switchTimer.isExpired()) {
    switchTimer.set(DEATH_SWITCH);
    dead = (dead + 1) % 2;
  }
}
