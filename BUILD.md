# Linux Guide to SMT32 for EE329
## Setup
ensure that gcc-arm-embedded-13 and st-flash are installed. Ex:
```
sudo apt-get install -y gcc-arm-embedded-13 st-flash
```
##Linking and creating object files 
```
arm-none-eabi-gcc "../Core/Src/main.c" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4A6xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"Core/Src/main.o"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "Core/Src/main.o"
```
## Compiling to .elf file
```
arm-none-eabi-gcc -o "bootloaderfinal.elf" @"objects.list"  -Wl,--start-group  -Wl,--end-group -mcpu=cortex-m4 -T"~/STM32CubeIDE/workspace_1.18.0/bootloaderfinal/STM32L4A6ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="bootloaderfinal.map" -Wl,--gc-sections -static  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
```
## Creating the .bin file
```
arm-none-eabi-objcopy  -O binary bootloaderfinal.elf  "bootloaderfinal.bin"
```
## flashing the .bin file to STM32
```
st-flash --reset write ./Debug/bootloaderfinal.bin 0x08000000
```
## Debugging
note: if it complains that it can not write to the usb port, run (where 008 is the port mentioned in the error message):
```
sudo chmod o+w /dev/bus/usb/001/PORT
```
Additionally, make sure the USB port is seen on your computer (either /dev/ttyACM0 or /dev/ttyUSB0
