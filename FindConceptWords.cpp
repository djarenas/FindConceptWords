#include "Word_Utils.h"

int main(int argc, char** argv){
    
    //Check command line had sufficient inputs; terminate otherwise.
    if (argc != 4 ){
         cout << "Syntax: fcw.exe <Words_Filename> <Text_Filename> <Output_Filename>" << endl;
         cout << "Terminating program." << endl;
         return 1;
    }
    string words_filename = argv[1];
    string text_filename = argv[2];
    string output_filename = argv[3];

    //Read file that contains the main words and their permutations -> Vector of Concept.
    //Each object of the Concept class has 3 member variables: 
    //1) A main word (string) 2) Permutations of the word (vector of strings)
    //3) How many times it has been found in each performed search? (a vector of integers)
    vector<Concept> concept_vector; 
    concept_vector = wordplay::readWordsFile(words_filename); //wordplay functions from Word_Utils.cpp
    if (concept_vector.empty()) {
        cout << "Terminating. No concept/words were read." << endl;
        return 1;
    }

    //Read the text file -> Vector of strings. 
    //This will be the target vector in which concepts will be searched.
    vector<string> text_vector;
    text_vector = wordplay::readTextFile(text_filename);
     if (text_vector.empty()) {
        cout << "Terminating. Text was not successfuly read from file." << endl;
        return 1;
    }

    //Combine elements separated by hyphen.
    //Some words may have been separated by a hyphen in the original text
    //Example: {"*!Hey", "^Colle-", "ge90", "rules6"} -> {"*!Hey", "^College90", "rules6"}
    wordplay::fixSeparatedByHyphen(text_vector); 

    //Remove numbers from text elements. Delete elements with no characters left
    //Example: {"!*Hey", "^College90", "rules6"} -> {"*!Hey", "^College", "rules"}
    wordplay::removeNumeric(text_vector);

    //Remove unwanted characters
    //{"*!Hey", "^College", "rules"} -> {"Hey", "College", "rules"}
    wordplay::removeSpecificCharsFromVector(text_vector, "+=!@#$%^&*()'[]{}<>;:.,?");
    //wordplay::cout_svector(text_vector);

    //Convert all uppercase to lowercase in the target vector.
    wordplay::changeAllToLowerCase(text_vector);

    //Sort the text vector alphabetically
    sort(text_vector.begin(), text_vector.end());

    //Remove text vector elements with less than 2 characters
    //Letters by themselves are unlikely to be searched for
    wordplay::removeSmallElements(text_vector, 2);

    //Search for every concept and update their count vectors.
    //If the concept is found x times in a text vector, the counts vector is appended x. 
    for (vector<Concept>::iterator it = concept_vector.begin(); it < concept_vector.end(); it++) {
        wordplay::countConceptInTextVector((*it), text_vector);
    }

    //Write to specified results file.
    wordplay::writeResultsToFile(concept_vector, "Results.txt");

    return 0;
}