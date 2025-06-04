this code all comes fully functioning as of my graduation, designed in platformio with no gurantees that it will work on your machine, sorry, but the code framework is there.

Parts list:

4x orange LEDs
4x white LEDs
2x red LEDs
(all are surcface mount LEDs with extremely small. (<0.5mm od wire) Wires must fit through small 1mm x 2mm hole)

1x ESP32 devkit

assorted resistors, tailor depending on your LED's rated current and voltage.
I used a 30 ohm and 100 ohm resistor in parallel to achieve ~26.4 ohms, which was close enough to the 27.5 ohms that I calculated before

power switch (basic two position power switch from any tech supply store will work, mine was rated for 6A @ 125VAC, but calculate for your own expected max draw and voltage)

battery (18650 lithium ion battery used for mine)

3d printed parts

<= 1mm plastic sheet for the headlight & taillight covers (not needed, just for looks)

assorted m2 metric hardware


pins are explained in the code comments, but be warned that depending on the esp32 used, some pins are taken up by the bluetooth, and you may need to reallocate them simply by changing their number at the top of the code.




TO USE THIS, use this app for android https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US
