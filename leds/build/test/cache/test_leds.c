#include "build/temp/_test_leds.c"
#include "src/leds.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


static uint16_t ledsVirtuales;



void setUp(void) {

   Leds_Create(&ledsVirtuales);

}



void tearDown(void) {

}



void test_LedsOffAfterCreate(void) {

   uint16_t ledsVirtuales = 0xFFFF;

   Leds_Create(&ledsVirtuales);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnLedOne(void) {

   Leds_TurnOn(1);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffLedOne(void) {

   Leds_TurnOn(1);

   Leds_TurnOff(1);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnMultipleLeds(void) {

   Leds_TurnOn(8);

   Leds_TurnOn(9);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0180)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffAnyLed(void) {

   Led_TurnAllOn();

   Leds_TurnOff(8);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFF7F)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnAllOn(void) {

   Led_TurnAllOn();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnAllOff(void) {

   Led_TurnAllOff();

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_HEX16);

}





void test_GetStatusLed(void) {

   int led_status;

   Led_TurnAllOff();

   Leds_TurnOn(5);

   led_status=Led_GetStatus(5);

   UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((led_status)), (

  ((void *)0)

  ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);

   led_status=Led_GetStatus(3);

   UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((led_status)), (

  ((void *)0)

  ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

}





void test_LedMemoryIsNotReadable(void) {

   ledsVirtuales = 0xFFFF;

   Leds_TurnOn(8);

   UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0080)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

  ((void *)0)

  ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_HEX16);

}
