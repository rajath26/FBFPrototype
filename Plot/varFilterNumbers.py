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

	dictOpsPerSecond = defaultdict(list)
	dictfpr = defaultdict(list)

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
					dictOpsPerSecond[int(row[0])].append(row[1])
					dictfpr[int(row[0])].append(row[2])
			finally:
				csvF.close()

	fig = plt.figure(figsize=(6,5))
	#title = "FBF " + fprDict[fprMethod] + " vs Number of Filters in the FBF"
	#plt.title(title)
	ax = fig.add_subplot(111)

	filterlist = []
	for filterNum, v in dictOpsPerSecond.items():	
		filterlist.append(int(filterNum))

	filterlist.sort()

	for numberOfFilters in filterlist:
		lab = "FBF with " + str(numberOfFilters) + " number of filters"
		if numberOfFilters == 24: 
			ax.plot(dictOpsPerSecond[numberOfFilters], dictfpr[numberOfFilters], '-', label=lab, lw=2)
		elif numberOfFilters == 12:
			ax.plot(dictOpsPerSecond[numberOfFilters], dictfpr[numberOfFilters], ':', label=lab, lw=2)
		elif numberOfFilters == 6:
			ax.plot(dictOpsPerSecond[numberOfFilters], dictfpr[numberOfFilters], '--', label=lab, lw=2)
		elif numberOfFilters == 3:
			ax.plot(dictOpsPerSecond[numberOfFilters], dictfpr[numberOfFilters], 'r-.', label=lab, lw=2)

	ax.legend(loc='lower right', prop={'size':10})

	ax.grid()
	ax.set_xlabel("Operations per second")
	ax.set_ylabel("FPP")
	ax.set_yscale('log')
	ax.set_xlim(50,250)
	#ax.set_xscale('log')
	
	plt.show()

