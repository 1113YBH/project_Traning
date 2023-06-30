#include <SoftwareSerial.h>

#define X_SW 1
#define Y_SW 2
#define Z_SW 16
#define X_MOTOR 4
#define Y_MOTOR 6
#define Z_MOTOR 8
#define X_MOTOR_DIR 3
#define Y_MOTOR_DIR 5
#define Z_MOTOR_DIR 7
#define JOY_X A1
#define JOY_Y A2
#define UP_BTN 13
#define DOWN_BTN 12
#define BT_TX 10
#define BT_RX 11

SoftwareSerial bt(BT_RX, BT_TX); 

void setup()
{
  Serial.begin(9600);
  //bt.begin(9600);
  
  pinMode(X_SW, INPUT_PULLUP);
  pinMode(Y_SW, INPUT_PULLUP);
  pinMode(Z_SW, INPUT_PULLUP);
  pinMode(X_MOTOR, OUTPUT);
  pinMode(Y_MOTOR, OUTPUT);
  pinMode(Z_MOTOR, OUTPUT);
  pinMode(X_MOTOR_DIR, OUTPUT);
  pinMode(Y_MOTOR_DIR, OUTPUT);
  pinMode(Z_MOTOR_DIR, OUTPUT);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(UP_BTN, INPUT);
  pinMode(DOWN_BTN, INPUT);
  pinMode(BT_TX, OUTPUT);
  pinMode(BT_RX, INPUT);
}

unsigned long curr_micros;
unsigned long prev_micros;

void loop()
{
  curr_micros = micros();
  if (prev_micros - curr_micros > 500)
  {
    curr_micros = prev_micros;

    int joyX = analogRead(JOY_X);
    int joyY = analogRead(JOY_Y);
    int up_btn = digitalRead(UP_BTN);
    int down_btn = digitalRead(DOWN_BTN);

    if (joyX > 800)
    {
      motor_move_X(1);
    }
    else if (joyX < 300)
    {
      motor_move_X(0);
    }

    if (joyY > 800)
    {
      motor_move_Y(1);
    }
    else if (joyY < 300)
    {
      motor_move_Y(0);
    }

    if (up_btn)
    {
      motor_move_Z(1);
    }
    else if (down_btn)
    {
      motor_move_Z(0);
    }
  }

  bluetooth();  
}

int x_flag, y_flag, z_flag;

void motor_move_X(int dir)
{
  if (dir == 1)
  {
    digitalWrite(X_MOTOR_DIR, HIGH);
  }
  else  digitalWrite(X_MOTOR_DIR, LOW);

  if (x_flag == 1)
  {
    digitalWrite(X_MOTOR, LOW);
    x_flag = 0;
  }
  else
  {
    digitalWrite(X_MOTOR, HIGH);
    x_flag = 1;
  }
}

void motor_move_Y(int dir)
{
  if (dir == 1)
  {
    digitalWrite(Y_MOTOR_DIR, HIGH);
  }
  else  digitalWrite(Y_MOTOR_DIR, LOW);

  if (y_flag == 1)
  {
    digitalWrite(Y_MOTOR, LOW);
    y_flag = 0;
  }
  else
  {
    digitalWrite(Y_MOTOR, HIGH);
    y_flag = 1;
  }
}

void motor_move_Z(int dir)
{
  if (dir == 1)
  {
    digitalWrite(Z_MOTOR_DIR, HIGH);
  }
  else  digitalWrite(Z_MOTOR_DIR, LOW);

  if (z_flag == 1)
  {
    digitalWrite(Z_MOTOR, LOW);
    z_flag = 0;
  }
  else
  {
    digitalWrite(Z_MOTOR, HIGH);
    z_flag = 1;
  }
}

void bluetooth()
{
  String str;
  if(bt.available())
  {
    //Serial.println(bt.readString());
    str = bt.readString();
  }
  if(Serial.available())
  {
    //bt.println(Serial.readString());
  }
  if(str = "x1")
  {
    motor_move_X(1);
  }
  if(str = "x0")
  {
    motor_move_X(-1);
  }
  if(str = "y1")
  {
    motor_move_Y(1);
  }
  if(str = "y0")
  {
    motor_move_Y(-1);
  }
  if(str = "z1")
  {
    motor_move_Z(1);
  }
  if(str = "z0")
  {
    motor_move_Z(-1);
  }
}