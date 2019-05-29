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
	#print("read data:")
	upper = (length >> 8) & 0xFF
	lower = length & 0xFF
	values = bytearray([0x03, upper, lower])
	ser.write(values)
	s = ser.read(length+1)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x13:
		raise Exception('read_data', 'readback is not okay')
	return s[1:]

def write_data_start(ser):
	print("write data start:")
	values = bytearray([0x04])
	ser.write(values)
	s = ser.read(1)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x14:
		raise Exception('write_data_start', 'readback is not okay')

def write_data(ser, data):
	length = len(data)
	upper = (length >> 8) & 0xFF
	lower = length & 0xFF
	values = bytearray([0x05, upper, lower]) + data
	#print(values)
	ser.write(values)
	s = ser.read(length+3)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x15 or s[1] != upper or s[2] != lower:
		raise Exception('write_data', 'readback is not okay')

def write_data_end(ser):
	print("write data end:")
	values = bytearray([0x06])
	ser.write(values)
	s = ser.read(1)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x16:
		raise Exception('write_data_end', 'readback is not okay')

def verify(ser):
	print("verify empty:")
	values = bytearray([0x07])
	ser.write(values)
	s = ser.read(2)
	if DEBUG == 1:
		for key, x in enumerate(s):
			print("%i: 0x%0.2X" % (key, x))
	if s[0] != 0x17:
		raise Exception('verify', 'readback is not okay')
	return s[1]

def get_eprom_type(eprom):
	for e in eprom_settings:
		if eprom == e['name']:
			return e
	die("wrong EPROM selected")

def read_file(file_name, port, eprom):
	with open(file_name, "wb") as file:
		print(ser.name)
		line = ser.readline()
		print(line)

		set_type(ser, eprom['id'], 0)
		set_address(ser, 0)
		data_count = 0
		size = 1024
		for i in range(0, eprom['size'], size):
			data = read_data(ser, size)
			data_count = data_count + size
			#print(data)
			file.write(data)
			percent = data_count / eprom['size'] * 100
			print("read %d from %d bytes: %.2f%%" % (data_count, eprom['size'], percent))


def write_file(file_name, port, eprom):
	with open(file_name, "rb") as file:
		print(ser.name)
		line = ser.readline()
		print(line)

		set_type(ser, eprom['id'], 0)
		set_address(ser, 0)
		write_data_start(ser)
		data_count = 0
		size = 126
		for i in range(0, eprom['size'], size):
			data = file.read(size)
			#print(data)
			write_data(ser, data)
			data_count = data_count + size
			percent = data_count / eprom['size'] * 100
			print("write %d from %d bytes: %.2f%%" % (data_count, eprom['size'], percent))
			#break
		write_data_end(ser)

def verify_empty(ser, eprom):
	print(ser.name)
	print(ser.readline())

	set_type(ser, eprom['id'], 0)
	status = verify(ser)
	if status == 0:
		print("Chip is empty!")
	else:
		print("Chip is NOT empty!")


if __name__ == '__main__':
	eproms = []
	for setting in eprom_settings:
		eproms.append(setting['name'])

	parser = argparse.ArgumentParser(description='Write or read from an SRAM to a file.')
	parser.add_argument('-m', '--mode', choices=['read', 'write', 'verify'], help='define if read or write from file.')
	parser.add_argument('--eprom', choices=eproms, help='choose the correct 27C...')
	parser.add_argument('-f', '--file', help='file to read or write.')
	parser.add_argument('-p', '--port', help='serial port for the arduino mega.')

	args = parser.parse_args()
	eprom = get_eprom_type(args.eprom)

	with serial.Serial(args.port, 57600) as ser:
	#with serial.Serial(port, 57600, timeout=1) as ser:
		if args.mode == 'read':
			print("READ")
			read_file(args.file, ser, eprom)
		elif args.mode == 'write':
			print("WRITE")
			write_file(args.file, ser, eprom)
		elif args.mode == 'verify':
			print("VERIFY")
			verify_empty(ser, eprom)

