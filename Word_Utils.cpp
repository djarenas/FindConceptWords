#include "Word_Utils.h"

namespace wordplay {

    void saveResultsToFile (vector<Concept> cv, string filename){
        std::ofstream ofile (filename);
        int x = 1;
        //Save name of columns
        ofile << "Concept (main word)" << "\tPermutations" << "\tCounts\n";
        //Save each concept in this column format
        for (int i = 0; i < cv.size(); i++){
            //Main word
            ofile << cv[i].main_word;
            //Permutations
            ofile << "\t" << cv[i].permutations[1];
            for (int j = 1; j < cv[i].permutations.size(); j++){
                ofile << "," << cv[i].permutations[j];
            }
            ofile << "\t";
            //Number of counts
            ofile << cv[i].counts[0];
            ofile << "\n";
            //Counts
        }
        ofile.close();
        return; 
    }

    vector<Concept> read_wordfile (string filename){
        //Declare variables
        std::ifstream ifile (filename); //File object
        string line; //A string that holds the information for each line
        vector<Concept> cv;

        while (std::getline(ifile, line)) //Get each line from file. Then, while you have lines...
        {
            Concept dummy;
            std::stringstream iss(line);
            string input;
            vector<string> dv;
            int i = 0;
            while (iss >> input){
                if (i == 0){dummy.main_word = input;}
                dummy.permutations.push_back(input);
                i = i + 1;
            }
            cv.push_back(dummy);
        }
        return cv;
    }

    Concept search_conceptInStrvec (Concept wordconcept, vector<string> strv){
        
        int r = 0;
        Concept resultC; 
        resultC = wordconcept;

        //In each of the string vector elements...
        for (int i = 0; i < strv.size(); i++){
            //Search each word for the concept
            for (int j = 0; j < wordconcept.permutations.size(); j++){
                if (strv[i] == wordconcept.permutations[j]){
                    r = r + 1;
                }
            }
        }
        resultC.counts.push_back(r);
        return resultC;
    }

    void cout_svector(vector<string> input_vec, int n)
    {
        for (int i = 0; i < n; i++){
            cout << input_vec[i] << "\t";
        }
        return;
    }

    void cleanstrVector (vector<string> &strv, string charsToRemove){
        for (int i = 0; i < strv.size(); i++){
            removeCharsFromString(strv[i], charsToRemove);
        }
        return;
    }

    void removeCharsFromString( string &str, string charsToRemove ) {
    for ( unsigned int i = 0; i < charsToRemove.size(); ++i ) {
            str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
    }

    void change_toLowerCase (vector<string> &strv){
        for (int i = 0; i < strv.size(); i++){
            std::transform(strv[i].begin(), strv[i].end(), strv[i].begin(),
            [](unsigned char c){ return std::tolower(c); });      
        }
    }
    vector<string> convertFiletoVector(string filename){
        //Purpose: Reads a file and converts it to a vector of strings

        //Declare variables
        std::ifstream ifile (filename); //File object
        string line; //A string that holds the information for each line
        vector<string> output_vector;

        while (std::getline(ifile, line)) //Get each line from file. Then, while you have lines...
        {
            std::stringstream iss(line);
            std::string input;
            while(iss >> input){
                output_vector.push_back(input);
            };
        }
        ifile.close();
        return output_vector;
    }
}