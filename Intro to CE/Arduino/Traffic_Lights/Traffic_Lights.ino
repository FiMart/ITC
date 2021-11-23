#define W_R_LED 2
#define W_Y_LED 3 
#define W_G_LED 4
#define WEST_Button 10

#define S_R_LED 5
#define S_Y_LED 6 
#define S_G_LED 7 
#define SOUTH_Button 11

#define HM_G_LED 8
#define HM_R_LED 9 
#define WALK_Button 12

#define goS     0
#define waitS   1
#define goW     2
#define waitW   3
#define sToHM   4
#define wToHM   5
#define goHM1   6
#define waitHM1 7
#define goHM2   8
#define waitHM2 9

struct State
{
  unsigned long ST_Out;   // 6-bit pattern to street output
  unsigned long Time;     // delay in milli seconds units
  unsigned long Next[8];  // next state for inputs 0,1,2,3,4,5,6,7
};

typedef const struct State SType;

SType FSM[10] =
{
  {B10000101, 2000, {0, 4, 1, 1, 0, 4, 1, 1}}, // State0 = {goS, SToHM, waitS, waitS, goS, sToHM, waitS, waitS}
  {B10001001, 300,  {2, 2, 2, 2, 2, 2, 2, 2}}, // State1 = {goW, goW, goW, goW, goW, goW, goW, goW}
  {B00110001, 2000, {2, 5, 2, 5, 3, 5, 3, 5}}, // State2 = {goW, wToHM, goW, wToHM, waitW, wToHM, waitW, wToHM}
  {B01010001, 300,  {0, 0, 0, 0, 0, 0, 0, 0}}, // State3 = {goS, goS, goS, goS, goS, goS, goS, goS}
  {B10001001, 300,  {6, 6, 6, 6, 6, 6, 6, 6}}, // State4 = {goHM1, goHM1, goHM1, goHM1, goHM1, goHM1, goHM1, goHM1}
  {B01010001, 300,  {6, 6, 6, 6, 6, 6, 6, 6}}, // State5 = {goHM1, goHM1, goHM1, goHM1, goHM1, goHM1, goHM1, goHM1}
  {B10010010, 300,  {6, 6, 7, 7, 7, 7, 7, 7}}, // State6 = {goHM1, goHM1, waitHM1, waitHM1, waitHM1, waitHM1, waitHM1, waitHM1}
  {B10010000, 300,  {8, 8, 8, 8, 8, 8, 8, 8}}, // State7 = {goHM2, goHM2, goHM2, goHM2, goHM2, goHM2, goHM2, goHM2}
  {B10010010, 300,  {9, 9, 9, 9, 9, 9, 9, 9}}, // State8 = {waitHM2, waitHM2, waitHM2, waitHM2, waitHM2, waitHM2, waitHM2, waitHM2}
  {B10010000, 300,  {6, 6, 2, 2, 0, 0, 2, 0}}  // State9 = {goHM1, goHM1, goW, goW, goS, goS, goW, goS}
};

unsigned long S = 0; // index to the current state

void setup()
{
  pinMode(W_R_LED, OUTPUT);
  pinMode(W_Y_LED, OUTPUT);
  pinMode(W_G_LED, OUTPUT);
  pinMode(WEST_Button, INPUT_PULLUP);

  pinMode(S_R_LED, OUTPUT);
  pinMode(S_Y_LED, OUTPUT);
  pinMode(S_G_LED, OUTPUT);
  pinMode(SOUTH_Button, INPUT_PULLUP);

  pinMode(HM_G_LED, OUTPUT);
  pinMode(HM_R_LED, OUTPUT);
  pinMode(WALK_Button, INPUT_PULLUP);
}

int input, input1, input2, input3;

void loop()
{
  digitalWrite(W_R_LED, (FSM[S].ST_Out & B10000000));
  digitalWrite(W_Y_LED, (FSM[S].ST_Out & B01000000));
  digitalWrite(W_G_LED, (FSM[S].ST_Out & B00100000));

  digitalWrite(S_R_LED, (FSM[S].ST_Out & B00010000));
  digitalWrite(S_Y_LED, (FSM[S].ST_Out & B00001000));
  digitalWrite(S_G_LED, (FSM[S].ST_Out & B00000100));

  digitalWrite(HM_G_LED, (FSM[S].ST_Out & B00000010));
  digitalWrite(HM_R_LED, (FSM[S].ST_Out & B00000001));

  delay(FSM[S].Time);

  input1 = !digitalRead(SOUTH_Button);
  input2 = !digitalRead(WEST_Button);
  input3 = !digitalRead(WALK_Button);

  input = 4 * input2 + 2 * input1 + input3;
  S = FSM[S].Next[input];
}
