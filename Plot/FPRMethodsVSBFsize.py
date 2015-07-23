import csv
import sys
import matplotlib.pyplot as plt

"""
Usage: python <script_name> <smartFPRcsv> <effFPRcsv> <newFBFAnalysiscsv>
"""
def usage():
	print "python " + sys.argv[0] + " <smartFPRcsv> <effFPRcsv> <newFBFAnalysiscsv>"

if __name__ == '__main__':
	if len(sys.argv) != 4:
		print "Invalid usage"
		usage()
		sys.exit()

	BFsizeSmartFPR=[]
	smartFPR = []
	BFsizeEffFPR = []
	effFPR = []
	BFsizeFbfAnalysis = []
	fbfAnalysis = []

	with open(sys.argv[1], 'rU') as smartFPRcsv:
			try:
				smartFPRreader = csv.reader(smartFPRcsv, delimiter=',')
				for row in smartFPRreader:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					BFsizeSmartFPR.append(row[0])
					smartFPR.append(row[1])
			finally:
				smartFPRcsv.close()

	with open(sys.argv[2], 'rU') as effFPRcsv:
			try:
				effFPRreader = csv.reader(effFPRcsv, delimiter=',')
				for row in effFPRreader:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					BFsizeEffFPR.append(row[0])
					effFPR.append(row[1])
			finally:
				effFPRcsv.close()

	with open(sys.argv[3], 'rU') as fbfAnalysisFPRcsv:
			try:
				fbfAnalysisFPRreader = csv.reader(fbfAnalysisFPRcsv, delimiter=',')
				for row in fbfAnalysisFPRreader:
					if ( row[0].strip() == "TEST PARAMETERS"):
						break
					BFsizeFbfAnalysis.append(row[0])
					fbfAnalysis.append(row[1])
			finally:
				fbfAnalysisFPRcsv.close()

	fig = plt.figure(figsize=(6,5))
	#plt.title("FBF False Positive Probability vs Number of bits in the constituent bloom filters")
	ax = fig.add_subplot(111)

	smartFPRline = ax.plot(BFsizeSmartFPR, smartFPR, '--', label="Empirical FPP", lw=2)
	effFPRline = ax.plot(BFsizeEffFPR, effFPR, '-', label="FPP using FBF analysis", lw=2)
	#fbfAnalysisline = ax.plot(BFsizeFbfAnalysis, fbfAnalysis, '-', label="New FBF false positive probability", lw=1)

	lines = smartFPRline + effFPRline #+ fbfAnalysisline
	labels = [l.get_label() for l in lines]
	ax.legend(lines, labels, loc='upper left', prop={'size':10})

	ax.grid()
	ax.set_xlabel("Number of bits in constituent filters")
	ax.set_ylabel("FPP")
	ax.set_yscale('log')

	plt.show()

