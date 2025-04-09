Upon cloning repository, change all mentions of bootloaderfinal to your projects name. Ex:
git clone https://github.com/stuntangel/stm32_template test_name
mv bootloaderfinal.ioc test_name.ioc
STM32_Programmer_CLI -l usb
note to self: use the usb port on the right side of my computer! /dev/ttyACM0
It is necessary to add user to dialout group in linux
Flash: DISPLAY=:1 steam-run /home/ryan/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32CubeProgrammer
nix-shell -p gcc-arm-embedded-13
arm-none-eabi-objcopy so.elf -O binary so.bin
