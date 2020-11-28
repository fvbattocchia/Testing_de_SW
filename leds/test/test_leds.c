#include "unity.h"
#include "leds.h"

static uint16_t ledsVirtuales;

void setUp(void) {
   Leds_Create(&ledsVirtuales);
}

void tearDown(void) {
}
/*Después de la inicialización todos los LEDs deben quedar apagados.*/
void test_LedsOffAfterCreate(void) {
   uint16_t ledsVirtuales = 0xFFFF;
   Leds_Create(&ledsVirtuales);
   TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}
/*Se puede prender un LED individual.*/
void test_TurnOnLedOne(void) {
   Leds_TurnOn(1);
   TEST_ASSERT_EQUAL_HEX16(1, ledsVirtuales);
}
/*Se puede apagar un LED individual.*/
void test_TurnOffLedOne(void) {
   Leds_TurnOn(1);
   Leds_TurnOff(1);
   TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}
/*Se pueden prender y apagar múltiples LED’s.*/
void test_TurnOnMultipleLeds(void) {
   Leds_TurnOn(8);
   Leds_TurnOn(9);
   TEST_ASSERT_EQUAL_HEX16(0x0180, ledsVirtuales);
}
/*Se pueden prender y apagar múltiples LED’s.*/
void test_TurnOffAnyLed(void) {
   Led_TurnAllOn();
   Leds_TurnOff(8);
   TEST_ASSERT_EQUAL_HEX16(0xFF7F, ledsVirtuales);
}
/*Se pueden prender todos los LEDs de una vez*/
void test_TurnAllOn(void) {
   Led_TurnAllOn();
   TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}
/*Se pueden apagar todos los LEDs de una vez.*/
void test_TurnAllOff(void) {
   Led_TurnAllOff();
   TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}
/*Se puede consultar el estado de un LED*/
void test_GetStatusLed(void) {
   int led_status;
   Led_TurnAllOff();
   Leds_TurnOn(5);
   led_status=Led_GetStatus(5);
   TEST_ASSERT_EQUAL_INT(1, led_status);
   led_status=Led_GetStatus(3);
   TEST_ASSERT_EQUAL_INT(0, led_status);
}
