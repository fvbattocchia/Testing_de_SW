#include "build/temp/_test_leds.c"
#include "src/leds.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


static uint16_t ledsVirtuales;



void setUp(void) {

   Leds_Create(&ledsVirtuales);

}







void test_LedsOffAfterCreate(void) {

   uint16_t ledsVirtuales = 0xFFFF;

   Leds_Create(&ledsVirtuales);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnLedOne(void) {

   Leds_TurnOn(1);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffLedOne(void) {

   Leds_TurnOn(1);

   Leds_TurnOff(1);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnMultipleLeds(void) {

   Leds_TurnOn(8);

   Leds_TurnOn(9);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0180)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffAnyLed(void) {

   Led_TurnAllOn();

   Leds_TurnOff(8);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFF7F)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnAllOn(void) {

   Led_TurnAllOn();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnAllOff(void) {

   Led_TurnAllOff();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_HEX16);

}



void test_GetStatusLed(void) {

   int led_status;

   Led_TurnAllOff();

   Leds_TurnOn(5);

   led_status=Led_GetStatus(5);

   UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((led_status)), (

  ((void *)0)

  ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

   led_status=Led_GetStatus(3);

   UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((led_status)), (

  ((void *)0)

  ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);

}
