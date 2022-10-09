#include "Word_Utils.h"

int main(int argc, char** argv){
    string wordfilename = argv[1];
    string txtfilename = argv[2];
    string resultfilename = argv[3];

    //Read file that contains the concepts (main words and their permutations)
    vector<Concept> concept_vector;
    concept_vector = wordplay::read_wordfile(wordfilename); //Into a 2D vector with variable column number

    //Read the text file and convert to a vector of strings. Clean it up.
    vector<string> vs;
    vs = wordplay::convertFiletoVector(txtfilename); //Separate all words into elements on a vector string
    wordplay::cleanstrVector(vs, ",!*()?.'"); //Remove punctuations, other characters
    wordplay::change_toLowerCase(vs); //Change all characters to lower case

    //Search the string vector. Update each concept with the amount of times it was found.
    for (int i = 0; i < concept_vector.size(); i++){
        concept_vector[i] = wordplay::search_conceptInStrvec (concept_vector[i], vs);
    }
    
    //Output to console a concept example
    cout << concept_vector[1]; //Using the operator << overload for Concept class

    //Save results to file
    wordplay::saveResultsToFile(concept_vector, resultfilename);

    return 0;
}