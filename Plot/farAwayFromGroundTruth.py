import sys
import csv
from collections import defaultdict

"""
usage: python farAwayFromGroundTruth.py <ground_truth_file> <our_method_file>
"""
def usage():
	print "Invalid usage"
	print "python farAwayFromGroundTruth.py <ground_truth_file> <our_method_file>"

def main():
	if len(sys.argv) != 3:
		usage()
		sys.exit()

	ground_truth_file=sys.argv[1]
	our_method_file=sys.argv[2]
	dict = defaultdict(list)

	with open(ground_truth_file, 'rU') as groundF:
		try:
			reader = csv.reader(groundF, delimiter=',')
			for row in reader:
				if ( row[0].strip() == "TEST PARAMETERS"):
					break
				dict[int(row[0])].append(float(row[1]))
		finally:
			groundF.close()
				
	with open(our_method_file, 'rU') as ourF:
		try:
			reader = csv.reader(ourF, delimiter=',')
			for row in reader:
				if ( row[0].strip() == "TEST PARAMETERS"):
					break
				dict[int(row[0])].append(float(row[1]))
		finally:
			ourF.close()		

	l=[]
	for ops in dict:
		per_change=(dict[ops][0] - dict[ops][1])/dict[ops][0]
		per_change = per_change * 100;
		l.append(per_change)
		
	print l
	print max(l)
	
if __name__=='__main__':
	main()