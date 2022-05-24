#include <stdlib.h>
#include <stdint.h>

#include "src/GUI/GUI.h"
#include "src/Devices/Fridge.h"
#include "src/Devices/Light.h"
#include "src/Devices/PowerManager.h"

// ///////////////////////////////////
// 
//    D E V I C E S
// 
// ///////////////////////////////////
static GUI* gui;
static Fridge* fridge;
static Light* light;
static PowerManager* powerManager;

// ///////////////////////////////////
// 
//    I N T E R R U P T 
// 
// ///////////////////////////////////
#define INTERRUPT_DELAY_US 50000
static hw_timer_t* it_timer;

void IRAM_ATTR iterruptFunction( void )
{
  
  gui->it_update();
  fridge->it_update();
  light->it_update();
  powerManager->it_update();

}

// ///////////////////////////////////
// 
//          S E T U P ( )
// 
// ///////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println("#########################################");
  Serial.println("# Potatoz OS Initialisation :           #");
  Serial.println("#########################################");

  /*---------------------------
    Settup Memory storage
    ---------------------------*/

  // TODO

  /*---------------------------
    Settup Devices
    ---------------------------*/
  
  // Fridge
  Serial.print(" - Init Fridge : ");
  fridge = new Fridge();
  Serial.print(" - Init Fridge : [DONE]\n");

  // Light
  Serial.print(" - Init Light : ");
  light = new Light();
  Serial.print(" - Init Light : [DONE]\n");

  // PowerManager :
  Serial.print(" - Init PowerManager : ");
  powerManager = new PowerManager();
  Serial.print(" - Init PowerManager : [DONE]\n");

  // GUI
  Serial.print(" - Init GUI : ");
  gui = new GUI(fridge,light,powerManager);
  Serial.print(" - Init GUI : [DONE]\n");

  /*---------------------------
    Settup interuption function
    ---------------------------*/

  //Using timer0, freq diviseur is 80 (80Mhz base freq), counting up
  it_timer = timerBegin(0,80,true);

  // Activating interruption on timer
  timerAttachInterrupt(it_timer, &iterruptFunction, true);

  // Define delay for interruption and enable it
  timerAlarmWrite(it_timer, INTERRUPT_DELAY_US, true);
  timerAlarmEnable(it_timer); 

}



// ///////////////////////////////////
// 
//         L O O P ( )
// 
// ///////////////////////////////////
void loop()
{


  gui->refreshGUI();

}