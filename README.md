# mmr_can

You can add this library to your project by either cloning it or adding it as a submodule

---

## Add as a submodule (recommended)
To **add mmr_can as a submodule**, go into your project folder and run
```
git submodule add https://github.com/mmr-driverless/mmr_can.git Drivers/MMR_CAN
```

mmr_can will be cloned inside the `Drivers` folder

### Compiler setup
After adding the submodule, right click on your project's name from within the STM32CubeIDE, then `Properties (last option) > C/C++ General > Paths and Symbols`

You'll see a list of directories on the right, click on `Add`, then type `Drivers/MMR_CAN/Inc` and press enter


# Examples

## Setup

Configure the CAN peripheral in the _.ioc_ file, then call the following initialization function
inside _main_.

```c
#include "mmr_can.h"

int main() {
  // MX_CAN_INIT()...
  
  if (MMR_CAN_BasicSetupAndStart(&hcan) != HAK_OK) {
    Error_Handler();
  }

  // while (1) {...
}
```

## Sending a message
```c
void sendAMessage() {
  // my_data_type data = something;
  uint16_t data = 123;
  MmrCanPacket packet = {
    .data = (uint8_t*)(&data),
    .length = sizeof(data),
    .header.messageId = MMR_CAN_MESSAGE_ID_<ID>,
  };

  if (MMR_CAN_Send(&hcan, packet) != HAL_OK) {
    ; // Error
  }
}
```

## Receiving a message
```c
void receiveAMessage() {
  CanRxBuffer buffer = {};
  MmrCanMessage message = {
    .store = buffer,
  };

  MmrResult result = MMR_CAN_TryReceive(&hcan, &message);
  if (result == MMR_RESULT_ERROR) {
    ; // Error
  }
  else if (result == MMR_RESULT_PENDING) {
    return;
  }

  if (message.header.messageId == MMR_CAN_MESSAGE_ID<TARGET_ID>) {
    uint16_t data = *(uint16_t*)buffer;
  }
}
```