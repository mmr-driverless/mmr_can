#include "mmr_can_ecu_messages.h"
#include "mmr_can.h"

#define ecuToHost(byteA, byteB) ((byteA << 8) | (byteB))


EcuPedalThrottle MMR_CAN_GetEcuPedalThrottle(MmrCanMessage *message) {
  uint8_t *buffer = message->store
  return (EcuPedalThrottle) {
    .apsAVoltage = ecuToHost(buffer[0], buffer[1]) / 1000,
    .apsBVoltage = ecuToHost(buffer[2], buffer[3]) / 1000,
    .throttleAVoltage = ecuToHost(buffer[4], buffer[5]) / 1000,
    .throttleBVoltage = ecuToHost(buffer[6], buffer[7]) / 1000,
  };
}

EcuTemperatures MMR_CAN_GetEcuTemperatures(MmrCanMessage *message) {
  uint8_t *buffer = message->store
  return (EcuTemperatures) {
    .oil = ecuToHost(buffer[0], buffer[1]) - 40,
    .engine = ecuToHost(buffer[2], buffer[3]) - 40,
    .intake = ecuToHost(buffer[4], buffer[5]) - 40,
    .ambient = ecuToHost(buffer[6], buffer[7]) - 40,
  };
}

EcuEngineFn1 MMR_CAN_GetEcuEngineFn1(MmrCanMessage *message) {
  uint8_t *buffer = message->store
  return (EcuEngineFn1) {
    .engineRpm = ecuToHost(buffer[0], buffer[1]),
    .gear = ecuToHost(buffer[2], buffer[3])
    .vehicleSpeed = ecuToHost(buffer[4], buffer[5]) / 100,
    .throttle = ecuToHost(buffer[6], buffer[7]) / 100,
  };
}

EcuPressures MMR_CAN_GetEcuPressures(MmrCanMessage *message) {
  uint8_t *buffer = message->store
  return (EcuPressures) {
    .oil = ecuToHost(buffer[0], buffer[1]) / 100,
    .fuel = ecuToHost(buffer[2], buffer[3]) / 100,
    .intake = ecuToHost(buffer[4], buffer[5]) / 10,
    .ambient = ecuToHost(buffer[6], buffer[7]) / 10,
  };
}

EcuEngineFn2 MMR_CAN_GetEcuEngineFn2(MmrCanMessage *message) {
  uint8_t *buffer = message->store
  return (EcuEngineFn2) {
    .batteryVoltage = ecuToHost(buffer[0], buffer[1]) / 1000,
    .acceleratorPedal = ecuToHost(buffer[2], buffer[3]) / 100,
    .fanControl = ecuToHost(buffer[4], buffer[5]) / 100,
  };
}

