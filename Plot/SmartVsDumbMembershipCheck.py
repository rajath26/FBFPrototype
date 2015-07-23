import csv
import sys
import matplotlib.pyplot as plt

"""
Usage: python <script_name> <smartFPRcsv> <dumbFPRcsv> 
"""
def usage():
	print "python " + sys.argv[0] + " <smartFPRcsv> <dumbFPRcsv> "

if __name__ == '__main__':
	if len(sys.argv) != 3:
		print "Invalid usage"
		usage()
		sys.exit()

	numElementsSmartFPR=[]
	smartFPR = []
	numElementsDumbFPR = []
	dumbFPR = []
	
	with open(sys.argv[1], 'rU') as smartFPRcsv:
			try:
				smartFPRreader = csv.reader(smartFPRcsv, delimiter=',')
				for row in smartFPRreader:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					numElementsSmartFPR.append(row[0])
					smartFPR.append(row[1])
			finally:
				smartFPRcsv.close()

	with open(sys.argv[2], 'rU') as dumbFPRcsv:
			try:
				dumbFPRreader = csv.reader(dumbFPRcsv, delimiter=',')
				for row in dumbFPRreader:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					numElementsDumbFPR.append(row[0])
					dumbFPR.append(row[1])
			finally:
				dumbFPRcsv.close()

	fig = plt.figure(figsize=(6,5))
	#plt.title("FBF membership check")
	ax = fig.add_subplot(111)

	smartFPRline = ax.plot(numElementsSmartFPR, smartFPR, '-', label="FPP using FBF membership check", lw=2)
	dumbFPRline = ax.plot(numElementsDumbFPR, dumbFPR, '--', label="FPP using the simple approach", lw=2)

	lines = smartFPRline + dumbFPRline 
	labels = [l.get_label() for l in lines]
	ax.legend(lines, labels, loc='upper left', prop={'size':10})

	ax.grid()
	ax.set_xlabel("Number of Operations")
	ax.set_ylabel("FPP")
  	ax.set_yscale('log')
  	#ax.set_xscale('log')

	plt.show()

