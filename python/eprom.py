#!/bin/python

import serial

with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as ser:
	print(ser.name)
	line = ser.readline()
	print(line)
	
	print("set type:")
	values = bytearray([1, 0, 0])
	ser.write(values)
	print(ser.readline())
	s = ser.read(3)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))
	
	print("set address:")
	values = bytearray([2, 0, 10])
	for key, x in enumerate(values):
		print("%i: 0x%0.2X" % (key, x))
	ser.write(values)
	#print(ser.readline())
	s = ser.read(3)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))

	print("read data:")
	values = bytearray([3, 20])
	ser.write(values)
	#print(ser.readline())
	s = ser.read(21)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))
	
	print("set address:")
	values = bytearray([2, 0, 25])
	ser.write(values)
	s = ser.read(3)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))

	print("write data:")
	values = bytearray([4, 2, 0xAF, 0xFE])
	ser.write(values)
	s = ser.read(4)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))
	
	print("set address:")
	values = bytearray([2, 0, 25])
	ser.write(values)
	s = ser.read(3)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))

	print("read data:")
	values = bytearray([3, 4])
	ser.write(values)
	#print(ser.readline())
	s = ser.read(26)
	for key, x in enumerate(s):
		print("%i: 0x%0.2X" % (key, x))
