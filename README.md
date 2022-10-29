# FindConceptWords
Search for concepts within a text file. Multiple words, spellings, or conjugations can be used for each concept.

This C++ program first reads a text file containing the concepts you want to search for. In this input file, each row corresponds to a concept and various spellings or conjugations of the concept. The program stores them in a customized "Concept" class. An example input file "Words.txt" is included in the repository.

The program then reads the target text file and stores it as a vector of strings. The strings are preprocessed by 1) Checking for strings that may have been separated between new lines by a hyphen; 2) Removing  numeric characters and customizable non-alphanumeric (i.e. ^, &, *); 3) Changing all to lower case; 4) Removing single character strings. An example input file "ArenasPRB2010.txt" is included in the repository.

The program maps the vector of strings into an unordered map that contains unique strings and their repeated occurrences. Each concept is then compared to the map and the concept is updated with the number of times it appeared on this search. The Concepts and their counts are written to an output file.

Compilation: g++ -std=c++11 FindConceptWords.cpp Word_Utils.cpp -o fcw.exe

Execution syntax: fcw.exe <Words_Filename> <Text_Filename> <Output_Filename>

Execution example: fcw.exe "Words.txt" "ArenasPRB2010.txt" "output_file.txt"
