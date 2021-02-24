# CS_354_IDS
Class project creating a minimal viable intrusion detection system.


FileIO classes - 
  FileIO(string name)
    Constructor, takes one variable "name" which denotes your filename
  read()
     reads given filename and outputs to terminal line by line
  readLine(string pattern)
     takes one variable "pattern", reads given filename and outputs lines that include given pattern to terminal
  
  When compiled, program takes 2+ command line arguments. 
  First argument is mandatory and denotes the filename to be read. 
  Second and more are optional and denote the pattern you are searching for.
  
  e.x. ./a.out example_file_name.txt 
  e.x. ./a.out example_file_name.txt example string to match  // spaces are fine all command line arguments after the first
                                                              // are concatinated in program.
