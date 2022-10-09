#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using std::cout;
using std::string;
using std::vector;

class Concept 
{
    public:
        string main_word;
        vector<string> permutations;
        vector<int> counts; 
        
        
        //Operator overloading for console output
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
    int find_countString(string strTarget, string inputString);
    vector<string> convertFiletoVector(string filename);
    void cout_svector(vector<string> input_vec, int n);
    void removeCharsFromString( string &str, string charsToRemove );
    void cleanstrVector (vector<string> &strv, string charsToRemove);
    void change_toLowerCase (vector<string> &strv);
    vector<Concept> read_wordfile (string filename);
    Concept search_conceptInStrvec (Concept wordconcept, vector<string> strv);
    void saveResultsToFile (vector<Concept> cv, string filename);


}