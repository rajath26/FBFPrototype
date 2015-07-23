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

	dictRROpsPerSecond = defaultdict(list)
	dictRRfpr = defaultdict(list)

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
					dictRROpsPerSecond[int(row[0])].append(row[1])
					dictRRfpr[int(row[0])].append(row[2])
			finally:
				csvF.close()

	fig = plt.figure(figsize=(7,6))
	#title = "FBF " + fprDict[fprMethod] + " vs Refresh Rate"
	#plt.title(title)
	ax = fig.add_subplot(111)

	RRlist = []
	for refreshRate, v in dictRROpsPerSecond.items():	
		RRlist.append(int(refreshRate))

	RRlist.sort()

	count=0
	for refreshRate in RRlist:
		lab = "FBF with refresh rate of " + str(refreshRate) + " s"
		if refreshRate == 1:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], '-', label=lab, lw=2)
		elif refreshRate == 2:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], '--', label=lab, lw=2)
		elif refreshRate == 3:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], ':', label=lab, lw=2)
		elif refreshRate == 5:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], '-.', label=lab, lw=2)

		"""
		if count %2 == 0:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], '-', label=lab, lw=1)
		else:
			ax.plot(dictRROpsPerSecond[refreshRate], dictRRfpr[refreshRate], '--', label=lab, lw=1)
		count+=1
		"""

	ax.legend(loc='upper left', prop={'size':10})

	ax.grid()
	ax.set_xlabel("Operations per second")
	ax.set_ylabel("FPP")
	ax.set_yscale('log')
	ax.set_xscale('log')

	plt.show()

