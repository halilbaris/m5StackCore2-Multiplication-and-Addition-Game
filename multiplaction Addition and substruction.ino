#include <M5Core2.h>
#include "font.h"
#include "images.h"

int answer[4]={0,0,0,0};
int firstN=0;
int secondN=0;
int res=0;

int correct=0;
int wrong=0;
int fase=0;
int pos=0;
int space=2;

int uT=1000;
int cT=0;
int t=0;

void setup(void)
{
    M5.begin();
    M5.Axp.SetLcdVoltage(3000);
    M5.Lcd.setFreeFont(&Dialog_plain_52);
    M5.Lcd.setSwapBytes(true); 
    M5.Lcd.setTextColor( ORANGE,TFT_BLACK);
    M5.Spk.begin();     // Initialize the speaker. 
    M5.Spk.DingDong();  // Play the DingDong sound. 
    delay(100);
}

void loop(void)
{
  M5.update();

  if(fase==0)
  {
    int operation = random(3); 
    if (operation == 0) {   ///// addition
      firstN=random(0,99);
      secondN=random(0,99);
      res=firstN+secondN;
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.drawString(String(firstN)+" + "+String(secondN)+"      ",70,80);
    }
    else if (operation == 1) { ///// Substruction
      firstN=random(0,99);
      secondN=random(0,99);
          while(secondN >= firstN ){
          firstN=random(0,99);
          secondN=random(0,99); }
          res=firstN-secondN;  
          M5.Lcd.fillScreen(TFT_BLACK);
         M5.Lcd.drawString(String(firstN)+" - "+String(secondN)+"      ",70,80);
    }
    else if (operation == 2) {  /// Multiplaction
      firstN=random(0,99);
      secondN=random(0,99);
      res=firstN*secondN;
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.drawString(String(firstN)+" x "+String(secondN)+"      ",70,80);
    }
    pos=random(3);
    //M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(LIGHTGREY ,TFT_BLACK);
    M5.Lcd.setFreeFont(&Dialog_plain_52);
    M5.Lcd.setTextColor( ORANGE,TFT_BLACK);
    M5.Lcd.drawString("True: "+String(correct)+"    ",4,5,4);
    M5.Lcd.drawString("False: "+String(wrong)+"    ",190,5,4);
    answer[pos]=res;
    for(int i=0;i<4;i++){
  
    if(answer[i]==0 & operation == 0 )
     answer[i]=random(0,200);
     M5.Lcd.fillRoundRect((space+(i*78)+(i*space)),160,78,78,5,0x0187);
     M5.Lcd.drawRoundRect((space+(i*78)+(i*space)),160,78,78,5,LIGHTGREY);
     M5.Lcd.setTextColor(TFT_ORANGE,0x0187);
     M5.Lcd.drawString(String(answer[i]),(8+space+(i*78)+(i*space)),185,4); // toplama 
     M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
     
   
    if (answer[i]==0 & operation == 1 )
        answer[i]=random(0,99);
        M5.Lcd.fillRoundRect((space+(i*78)+(i*space)),160,78,78,5,0x0187);
        M5.Lcd.drawRoundRect((space+(i*78)+(i*space)),160,78,78,5,LIGHTGREY);
        M5.Lcd.setTextColor(TFT_ORANGE,0x0187);
        M5.Lcd.drawString(String(answer[i]),(8+space+(i*78)+(i*space)),185,6); // Substruction
        M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
          
           
      if (answer[i]==0 & operation == 2 )     // multiplaction
            answer[i]=random(0,9999);
            M5.Lcd.fillRoundRect((space+(i*78)+(i*space)),160,78,78,5,0x0187);
            M5.Lcd.drawRoundRect((space+(i*78)+(i*space)),160,78,78,5,LIGHTGREY);
            M5.Lcd.setTextColor(TFT_ORANGE,0x0187);
            M5.Lcd.drawString(String(answer[i]),(10+space+(i*78)+(i*space)),185,4); // carpma
            M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
    

     } 
  }
    fase=1;
  

if(fase==1)
{

  TouchPoint_t pos= M5.Touch.getPressPoint();
  int y=pos.y;
  int x=pos.x;
  for(int i=0;i<4;i++)
  if(x>(space+(i*78)+(i*space)) && x<(space+(i*78)+(i*space))+78 && y>158)
  if(answer[i]==res)
  {
    correct++;
    M5.Lcd.pushImage(240,80,48,48,corr);
    M5.Lcd.setTextColor(TFT_GREEN,BLACK); 
    //M5.Lcd.drawString("Correct Answer is: "+String(res)+"    ",20,40,4);
    M5.Spk.DingDong();  // Play the DingDong sound.
    delay(2500);
    for(int i=0;i<4;i++)
    answer[i]=0;
    fase=0;
    }
  else
  {
    wrong++;
    M5.Lcd.pushImage(240,80,48,48,wrrong);
    M5.Lcd.setTextColor(TFT_RED,BLACK); 
    M5.Lcd.drawString("Correct Answer is: "+String(res)+"    ",20,40,4);
    M5.Axp.SetLDOEnable(3, true);  //Open the vibration. 
    M5.Spk.DingDong();  // Play the DingDong sound.
    delay(500);
    M5.Axp.SetLDOEnable(3, false);  //Open the vibration.
    M5.Spk.DingDong();  // Play the DingDong sound.  
    delay(2000);
    for(int i=0;i<4;i++)
    answer[i]=0;
    fase=0;
    }  
}
if(millis()>cT+uT){
  t++;
 M5.Lcd.setTextColor(TFT_ORANGE,BLACK);  
//M5.Lcd.drawString("Duration: "+String(t),70,40,4); 
cT=millis();
}
}
    
