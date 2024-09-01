# e-data-writer
This is a simple project where I hooked up an Arduino to my Casio G-Shock G-2900's buttons and automated the entering of text in the e-Data mode (which is massively painful to do manually).

# Schematic
What Arduino pin a button is connected to is documented in the main file (spoiler: lower nibble of port D). Besides that, there should be a voltage divider (2R + R) between each of the output pins and the watch button pads. To prevent any of the buttons triggering while the Arduino is running the bootloader code or new code is being uploaded, because the buttons are active low, a MOSFET can be put between ground and the watch's ground and controlled by pin 13 with a pull-down resistor.
