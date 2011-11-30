m6811-elf-gcc -g -Os -mshort -Wl,-m,m68hc11elfb -o led.elf led.c

m6811-elf-objcopy --only-section=.text --only-section=.rodata --only-section=.vectors --only-section=.data --output-target=srec led.elf led.s19

