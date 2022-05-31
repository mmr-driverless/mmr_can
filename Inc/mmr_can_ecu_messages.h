#ifndef MMR_CAN_ECU_MESSAGES_H_
#define MMR_CAN_ECU_MESSAGES_H_

#include <stdint.h>

typedef struct EcuPedalThrottle {
  float apsAVoltage;
  float apsBVoltage;
  float throttleAVoltage;
  float throttleBVoltage;
} EcuPedalThrottle;

typedef struct EcuTemperatures {
  int16_t oil;
  int16_t engine;
  int16_t intake;
  int16_t ambient;
} EcuTemperatures;

typedef struct EcuEngineFn1 {
  float engineRpm;
  float gear;
  uint16_t vehicleSpeed;
  uint16_t throttle;
} EcuEngineFn1;

typedef struct EcuPressures {
  float oil;
  float fuel;
  float intake;
  float ambient;
} EcuPressures;

typedef struct EcuEngineFn2 {
  float batteryVoltage;
  float acceleratorPedal;
  float fanControl;
} EcuEngineFn2;

#endif // !MMR_CAN_ECU_MESSAGES_H_