import sys

def open_log_file(filename):
	with open(filename) as f:
		lines = f.readlines()
		print lines

if len(sys.argv) == 1:
	print "need file name"
	exit(1)
else:
	print sys.argv[1]
	open_log_file(sys.argv[1])
	exit(0)
