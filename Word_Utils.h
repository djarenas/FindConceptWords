#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Concept {
    public:
        string main_word;
        vector<string> permutations;
        vector<int> counts; 
        
        
        //Overload << opeator for the Concept objects.
        friend std::ostream& operator << (std::ostream &output, Concept &concpt)
        {
                    output << "Main word: " << concpt.main_word << std::endl;
                    output << "Permutations: \n";
                    for (int i = 0; i < concpt.permutations.size(); i++){
                        output << concpt.permutations[i] << "\t";
                    }
                    output << "\nInstances found: \n";
                    for (int i = 0; i < concpt.counts.size(); i++){
                        output << concpt.counts[i] << "\t";
                    }
                    output << std::endl;
                    return output;  
        }

};

namespace wordplay {
    vector<Concept> readWordsFile(string filename);
    vector<string> readTextFile(string filename);
    void fixSeparatedByHyphen(vector<string> &str_vec);
    void removeNumeric(vector<string> &str_vec);
    void removeSpecificCharsFromString(string &input_str, string charsToRemove);
    void removeSpecificCharsFromVector(vector<string> &strv, string charsToRemove);
    void changeAllToLowerCase(vector<string> &strv);
    void removeSmallElements(vector<string> &strv, int n);
    void countConceptInTextVector(Concept &conc, vector<string> &strv);
    void writeResultsToFile(vector<Concept> cv, string filename);
    void cout_svector(vector<string> input_vec);
}