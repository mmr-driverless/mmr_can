# mmr_can

You can add this library to your project by either cloning it or adding it as a submodule

---

### Add as a submodule (recommended)
To **add mmr_can as a submodule**, go into your project folder and run
```
git submodule add https://github.com/mmr-driverless/mmr_can.git Drivers/MMR_CAN
```

mmr_can will be cloned inside the `Drivers` folder

### Compiler setup
After adding the submodule, right click on your project's name from within the STM32CubeIDE, then `Properties (last option) > C/C++ General > Paths and Symbols`

You'll see a list of directories on the right, click on `Add`, then type `Drivers/MMR_CAN/Inc` and press enter
