#!/bin/python

import serial
import argparse

DEBUG = 0

eprom_settings = [
	{'name': '27C801',  'size': 2**20, 'id': 0},
	{'name': '27C4001', 'size': 2**19, 'id': 1},
	{'name': '27C2001', 'size': 2**18, 'id': 2},
	{'name': '27C1001', 'size': 2**17, 'id': 3},
	{'name': '27C512',  'size': 2**16, 'id': 4},
	{'name': '27C256',  'size': 2**15, 'id': 5},
	{'name': '27C128',  'size': 2**14, 'id': 6},
	{'name': '27C64',   'size': 2**13, 'id': 7},
	{'name': '27C32',   'size': 2**12, 'id': 8},
	{'name': '27C16',   'size': 2**11, 'id': 9}
]

def set_type(ser, type, vpp):
	print("set type:")
	values = bytearray([0x01, type, vpp])
	ser.write(values)
	print(ser.readline())
	s = ser.read(3)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x11 or s[1] != type or s[2] != vpp:
		raise Exception('set_type', 'readback is not okay')

def set_address(ser, address):
	print("set address:")
	upper = (address >> 8) & 0xFF
	lower = address & 0xFF
	values = bytearray([0x02, upper, lower])
	ser.write(values)
	s = ser.read(3)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x12 or s[1] != upper or s[2] != lower:
		raise Exception('set_address', 'readback is not okay')

def read_data(ser, length):
	print("read data:")
	values = bytearray([0x03, length])
	ser.write(values)
	s = ser.read(length+1)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x13:
		raise Exception('read_data', 'readback is not okay')
	return s[1:]

def write_data(ser, data):
	print("write data:")
	ar = [0x04, len(data)] + data
	values = bytearray(ar)
	ser.write(values)
	s = ser.read(len(data)+2)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x14 or s[1] != len(data):
		raise Exception('write_data', 'readback is not okay')

def get_eprom_type(eprom):
	for e in eprom_settings:
		if eprom == e['name']:
			return e
	die("wrong EPROM selected")

def read_file(file_name, port, eprom):
	with serial.Serial(port, 9600, timeout=1) as ser:
		with open(file_name, "wb") as file:
			print(ser.name)
			line = ser.readline()
			print(line)

			set_type(ser, eprom['id'], 0)
			set_address(ser, 0)
			data_count = 0
			for i in range(0, eprom['size'], 255):
				data = read_data(ser, 255)
				data_count = data_count + 255
				#print(data)
				file.write(data)
				print("read %d from %d bytes" % (data_count, eprom['size']))

#		set_address(30)
#		write_data([0xAF, 0xFE])
#		set_address(30)
#		print(read_data(4))


if __name__ == '__main__':
	eproms = []
	for setting in eprom_settings:
		eproms.append(setting['name'])

	parser = argparse.ArgumentParser(description='Write or read from an SRAM to a file.')
	parser.add_argument('-m', '--mode', choices=['read', 'write'], help='define if read or write from file.')
	parser.add_argument('--eprom', choices=eproms, help='choose the correct 27C...')
	parser.add_argument('-f', '--file', help='file to read or write.')
	parser.add_argument('-p', '--port', help='serial port for the arduino mega.')

	args = parser.parse_args()

	eprom = get_eprom_type(args.eprom)

	if args.mode == 'read':
		print("READ")
		read_file(args.file, args.port, eprom)
	elif args.mode == 'write':
		print("WRITE")

