openocd -f interface/stlink.cfg -f board/st_nucleo_wb55.cfg -c "init" &
arm-none-eabi-gdb ./build/raven -x ./.gdbconf
