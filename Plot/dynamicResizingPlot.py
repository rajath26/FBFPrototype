import csv
import sys
import matplotlib.pyplot as plt
from collections import defaultdict

"""
Usage: python <FPR_method_name> <csv>
"""
def usage():
	print "python " + sys.argv[0] + " <FPR_method_name> <csv>"
	print "FPR method names are: \n 1: Emperical FPP \n 2: Conditional FPP \n 3: New FPP \n"

if __name__ == '__main__':
	if len(sys.argv) != 3:
		print "Invalid usage"
		usage()
		sys.exit()

	numElements = []
	fpr = []
	target = []
	rr = []
	filters = []
	targets = []

	fprMethod = int(sys.argv[1])
	if int(fprMethod) == 1 or int(fprMethod) == 2 or int(fprMethod) == 3:
		print " "
	else:
		usage()
		sys.exit()

	fprDict = {1: "Emperical FPP", 2: "Conditional FPP", 3: "New FPP"}

	with open(sys.argv[2], 'rU') as csvF:
			try:
				readerF = csv.reader(csvF, delimiter=',')
				for row in readerF:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					elif row[0].strip() == "TARGET":
						target = row[1]
					elif row[0].strip() == "END":
						break
					else:
						numElements.append(row[0])
						fpr.append(row[1])
						rr.append(row[2])
						filters.append(row[3])
						targets.append(target)
			finally:
				csvF.close()

	fig = plt.figure(figsize=(6,5))
	#title = "Dynamic Resizing"
	#plt.title(title)
	ax = fig.add_subplot(111)

	fprline = ax.plot(numElements, fpr, '-', label="FPP of FBF", lw=2)
	targetline = ax.plot(numElements, targets, '-+', label='target FPP', lw=2)
	ax2 = ax.twinx()
	rrline = ax2.plot(numElements, rr, linestyle=':', drawstyle='steps', label='refresh rate of FBF', lw=2)
	filtersline = ax2.plot(numElements, filters, linestyle='--', drawstyle='steps', label='number of filters in the FBF', lw=2)

	lns = fprline + targetline + rrline + filtersline
	labs = [l.get_label() for l in lns]
	ax.legend(lns, labs, loc='lower right', prop={'size':10})

	#ax.grid()
	ax.set_xlabel("Time (s)")
	ax.set_ylabel("FPP")
	ax2.set_ylabel("Refresh rate in seconds / Number of filters")
	ax.set_yscale('log')
	#ax2.set_yscale('log');
	ax.set_ylim(0, float(target)+float(target)+float(target))
	ax2.set_ylim(0,15)
	ax.set_xlim(0,50)


	plt.show()

