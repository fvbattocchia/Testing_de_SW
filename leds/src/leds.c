#include "leds.h"


#define LED(x) x-1
static uint16_t * leds;
static uint16_t estado;

enum {
   ALL_LEDS_OFF = 0,
   ALL_LEDS_ON = ~ALL_LEDS_OFF
};

static int Leds_ConvertirNumeroEnBit(int numero_led) {
   return 1 << LED(numero_led);//(numero_led - 1);
}

static void Leds_HardwareUpdate(void) {
   *leds = estado;
}

void Leds_Create(uint16_t * direccion) {
   leds = direccion;
   estado = ALL_LEDS_OFF;
   Leds_HardwareUpdate();
};

void Leds_TurnOn(int led) {
   estado |= Leds_ConvertirNumeroEnBit(led);
   Leds_HardwareUpdate();
};

void Leds_TurnOff(int led) {
   estado &= ~Leds_ConvertirNumeroEnBit(led);
   Leds_HardwareUpdate();
};

void Led_TurnAllOn(void) {
   estado = ALL_LEDS_ON;
   Leds_HardwareUpdate();
}

void Led_TurnAllOff(void) {
   estado = ALL_LEDS_OFF;
   Leds_HardwareUpdate();
}

int Led_GetStatus(int led){
  return (estado & Leds_ConvertirNumeroEnBit(led))>>LED(led);
}
