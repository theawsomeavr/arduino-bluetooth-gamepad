/*
 * Copyright (c) 2016 Evan Kale
 * Email: EvanKale91@gmail.com
 * Website: www.ISeeDeadPixel.com
 *          www.evankale.blogspot.ca
 *
 * This file is part of BluetoothPS2Controller.
 *
 * BluetoothPS2Controller is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 


#define ANALOG_DEADZONE 50

#define BLUETOOTH_SERIAL_RATE 115200




uint32_t lastBtnState = 0;
int8_t lastX1 = 0;
int8_t lastY1 = 0;
int8_t lastX2 = 0;
int8_t lastY2 = 0;

uint32_t btnState = 0;
int8_t x1 = 0;
int8_t y1 = 0;
int8_t x2 = 0;
int8_t y2 = 0;
int b[12]={2,3,4,5,6,7,8,9,10,11,12,A4};
void setup()
{
  Serial.begin(BLUETOOTH_SERIAL_RATE);

  //delay(500);
for(int a;a!=12;a++){
  pinMode(b[a],INPUT_PULLUP);
}
pinMode(A0,0);
pinMode(A1,0);
pinMode(A2,0);
pinMode(A3,0);
 // uint8_t error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT, false, false);

/*  if (!error)
  {
    gamepadInitialized = true;
  }*/
}
int aa[12];
int state[12];
void loop()
{
   btnState=0;
    for(int a;a!=12;a++){
    state[a]=0;
    }
  for(int a;a!=12;a++){
  aa[a]=digitalRead(b[a]);  
  }
   for(int a;a!=12;a++){
    
    if(aa[0]==0&&state[0]==0){
    btnState =1;
    state[0]=1;
    }
     if(aa[1]==0&& state[1]==0){
      
    btnState =btnState+2;
    state[1]=1;
    }
     if(aa[2]==0&& state[2]==0){
    btnState =btnState+4;
    state[2]=1;
    }
     if(aa[3]==0&& state[3]==0){
    btnState =btnState+8;
    state[3]=1;
    }
     if(aa[4]==0&& state[4]==0){
    btnState =btnState+16;
    state[4]=1;
    }
     if(aa[5]==0&& state[5]==0){
    btnState =btnState+32;
    state[5]=1;
    }
      if(aa[6]==0&& state[6]==0){
    btnState =btnState+64;
    state[6]=1;
    }
      if(aa[7]==0&& state[7]==0){
    btnState =btnState+128;
    state[7]=1;
    }
      if(aa[8]==0&& state[8]==0){
    btnState =btnState+16384;
    state[8]=1;
    }
      if(aa[9]==0&& state[9]==0){
    btnState =btnState+32768;
    state[9]=1;
    }
       if(aa[10]==0&& state[10]==0){
    btnState =btnState+8192;
    state[10]=1;
    }
       if(aa[11]==0&& state[11]==0){
    btnState =btnState+4096;
    state[11]=1;
    }
   }

  /*x1=map(analogRead(A0),0,1023,-127,127);
   y1=map(analogRead(A1),0,1023,-127,127);
  sendGamepadState(0, x1, y1, 0, 0);*/
 //   ps2x.read_gamepad();
//ps2x.ButtonDataByte();
    x1 =map(analogRead(A0),0,1023,-127,127);
    y1 = map(analogRead(A1),0,1023,127,-127);
    x2 =map(analogRead(A2),0,1023,127,-127);
    y2 = map(analogRead(A3),0,1023,-127,127);

    if (-ANALOG_DEADZONE <= x1 && x1 <= ANALOG_DEADZONE)
      x1 = 0;
    if (-ANALOG_DEADZONE <= y1 && y1 <= ANALOG_DEADZONE)
      y1 = 0;
    if (-ANALOG_DEADZONE <= x2 && x2 <= ANALOG_DEADZONE)
      x2 = 0;
    if (-ANALOG_DEADZONE <= y2 && y2 <= ANALOG_DEADZONE)
      y2 = 0;
    
    if (lastBtnState != btnState
      || lastX1 != x1 || lastY1 != y1
      || lastX2 != x2 || lastY2 != y2)
    {
      
      sendGamepadState(btnState, x1, y1, x2, y2);

      lastBtnState = btnState;
      lastX1 = x1;
      lastY1 = y1;
      lastX2 = x2;
      lastY2 = y2;
    }
  
  delay(10);
}

void sendGamepadState(uint32_t btnState0, int8_t x1, int8_t y1, int8_t x2, int8_t y2)
{
  Serial.write((uint8_t)0xFD);
  Serial.write((uint8_t)0x06);
  Serial.write((uint8_t)x1);
  Serial.write((uint8_t)y1);
  Serial.write((uint8_t)x2);
  Serial.write((uint8_t)y2);
  uint8_t btnState1 = btnState0 & 0xFF;
  uint8_t btnState2 = (btnState0 >> 8) & 0xFF;
  Serial.write((uint8_t)btnState1);
  Serial.write((uint8_t)btnState2);
 // Serial.println(btnState1);
}
