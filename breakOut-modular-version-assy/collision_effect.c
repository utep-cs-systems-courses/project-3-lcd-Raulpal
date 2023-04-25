#include "buzzer.h"
#include "collision_effect.h"


void sound_effect()
{
  buzzer_set_period(5000); // make sound //
  __delay_cycles(200000);  // duration // 
  buzzer_set_period(0);  // turn of buzzer //
}
