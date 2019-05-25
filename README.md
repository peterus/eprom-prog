# EPROM Burner

Here you will find the circuit and the source code for a EPROM burner/programer.
This project can be used to program the famous 27/27Cxxx EPROM family.
With this circuit and software you will be able to write and read from an EPROM.

Additional to the provided hardware you will need a Arduino MEGA.
The provided circuit is easy to solder by our own with through hole components - no SMD soldering required!
I have some spare PCBs, you can contact me to get some.

## schematic

You can find the Eagle schematic in the 'schematic' folder.
Aditional you will need a Arduino MEGA board.

## source code

The source code can be found in the folder 'src', 'AVRhal' and some test-programs in 'test'.
The build system is cmake.

### compile

To compile the source code follow this steps:

   mkdir build && cd build
   cmake ..
   make
   
### flash the AVR/Arduino

   make upload_EPROM-PROG

## supported EPROMs

- 27C16 (not tested)
- 27C32 (not tested)
- 27C64 (not tested)
- 27C128 (not tested)
- 27C256 (not tested)
- 27C512 (not tested)
- 27C1001 (not tested)
- 27C2001 (not tested)
- 27C4001 (not tested)
- 27C801 (not tested)
