# FindConceptWords
Search for concepts within a text file. Multiple spellings or conjugations can be used for each concept.

This C++ program first reads a text file containing the concepts you want to search for. In this input file, each row corresponds to a concept and various spellings or conjugations of the concept are stored in a customized "Concept" class. An example input file "Words.txt" is in the repository. The program then reads the target txt file, stores it as a vector of strings, cleans up characters and capitalization. Each concept is then searched for by including all possible word permutations. 


C++ skills involved:
Read input files
Vectors
String manipulations
Classes
Operator overloading


This program was not written for any of my research projects. It was intended as a refresher project for myself to relearn some of the C++ skills I had forgotten after half a decade on focusing on R. 
