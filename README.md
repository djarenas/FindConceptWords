# FindConceptWords
Search for concepts within a text file. Multiple words, spellings, or conjugations can be used for each concept.

This C++ program first reads a text file containing the concepts you want to search for. In this input file, each row corresponds to a concept and various spellings or conjugations of the concept are stored in a customized "Concept" class. An example input file "Words.txt" is included in the repository.

The program then reads the target txt file and stores it as a vector of strings. The program checks for strings that may have been separated between new lines by a hyphen. It removes numeric characters and a set of custom characters (i.e. ^, &, *) from each string. Changes all the text to lower case and removes single character strings. An example input file "ArenasPRB2010.txt" is included in the repository.

The program then searches the vector of strings for each of the concepts' word permutations. The text vector is sorted alphabetically to prevent unnecessary searches. The concept object keeps track of how many times it was found in each search as a vector of integers. The results are outputed to a tab separated text file.

Compilation: g++ -std=c++11 BoseCorrection.cpp Word_Utils.cpp -o fcw.exe

Execution syntax: fcw.exe < Words_Filename > < Text_Filename > < Output_Filename >

Execution example: bc.exe "Words.txt" "ArenasPRB2010.txt" "output_file.txt"
