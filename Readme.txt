-- How do I compile the code ? 

Run make command to create the executable. 

$ make

-- How do I run experiments ? 

- The make command creates an executable called "Simulation". Running that will give you options as to which experiment you can run. Here is a sample output. 

$./Simulation

  ERROR :: Usage: ./Simulation <test_case>
  0: Smart VS Dumb membership check
  1: Number of elements VS FPP
  2: Filter size VS FPP
  3 : Number of hashes VS FPP
  4 : Refresh Rate VS FPP
  5 : Number of Constituent Bloom Filter VS FPP
  6 : Dynamic Resizing

  7 : Recyclable Bloom Filter Experiment

- You have to pass the number of the test you want to run. For example if you want to run the smart vs simple membership check, you need to run the following command: 

$./Simulation 0

-- How do I plot the results of the experiment ? 

- There is a folder called "Results" where the results are dumped in a text file. The file name of the results text file is based on the test case name and timestamp of the experiment run. There is another folder called "Plot" which contains matplotlib script to plot the results. Usage of the python scripts can be got by simple running the script. For example: 

$python SmartVsDumbMembershipCheck.py
Invalid usage
python SmartVsDumbMembershipCheck.py <smartFPRcsv> <dumbFPRcsv>

For example if you have to plot of the results of the smart vs simple membership check experiment, run the following command: 

$python SmartVsDumbMembershipCheck.py ../Results/dumbVsSmartMemTest2015-07-23\:17\:02\:47smartMemCheckFPR_2015-07-23\:17\:02\:47.csv ../Results/dumbVsSmartMemTest2015-07-23\:17\:02\:47dumbmemCheckFPR_2015-07-23\:17\:02\:47.csv

-- How do I plot the results present in the thesis ? 

- Note that the parameters of the data strucutre are already set inside macros in the header files. 

-- Fig.6.1 in Chapter 6

1) Run the experiment
$./Simulation 0
2) Using the results file generated plot using the matplotlib script SmartVsDumbMembershipCheck

-- Fig. 6.2 in Chapter 6

1) Run the experiment
$./Simulation 1
2) Plot the results using matplotlib script FPRMethodsVSnumElements.py

-- Fig. 6.3 in Chapter 6

1) Run the experiment
$./Simulation 2
2) Plot the results using matplotlib script FPRMethodsVSBFsize.py

-- Fig. 6.4 in Chapter 6

1) Run the experiment
$./Simulation 4
2) Plot the results using matplotlib script varRR.py

-- Fig. 6.5 in Chapter 6

1) Run the experiment 
$./Simulation 5
2) Plot the results using matplotlib script varFilterNumbers.py

-- Fig. 6.6 in Chapter 6

1) Run the experiment
$./Simulation 6
2) Plot the results using matplotlib script dynamicResizingPlot.py