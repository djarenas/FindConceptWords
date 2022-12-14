#include "Word_Utils.h"

namespace wordplay {

    //Purpose: Read a space or tab delimited text file --> Vector of Concept.
    //The file should have one concept per row, and each row has word permutations of the
    //same concept. First word will be considered the main word. 
    //(i.e. "optics optic optical optically") -> Main word is "optics", rest are permutations.
    vector<Concept> readWordsFile(string filename) {
        vector<Concept> conc_vector = {}; //Return variable. Returned empty if there were errors.
        string line;
        
        //Open filestream, check if it opens
        std::ifstream ifile (filename); 
        if (ifile.is_open()) { 
            cout << "Opening Words file: " << filename << "\n";
        }
        else {
            cout << "Unable to open Words file: " << filename << "\n"; 
            return conc_vector;
        }

        //Keep track if there was an unsuccessful read.
        //Keep line number in case you need to orient user on where a reading error occurred.
        //Make a boolean to keep track of the first word to save separately into the concept's main word.
        bool successful_read = true;
        int ln = 0;
        bool first_word = true;

        //For each row of the words file (which contains one concept).        
        while (successful_read && std::getline(ifile, line)) {
            Concept conc;
            std::stringstream iss(line);
            string input;

            //Keep track of first word so that it is assigned as main word.
            bool first_word = true;
            
            //Fore every word in the line
            while (iss >> input){
                if (iss.fail()) {
                    successful_read = false;
                    cout << "Read error in Words File." << endl;
                    cout << "Line number: " << ln << endl;
                    break;
                }
                
                //Update permutations vector for this concept
                conc.permutations.push_back(input);

                //Additionally save the first word as the main word of the Concept structure.
                if (first_word) {
                    conc.main_word = input;
                    first_word = false;
                }
            }

            //Update the concept vector
            conc_vector.push_back(conc);
            //Updates line number
            ln++;
        }

        //If a read was not successful, the return vector will be empty.
        if (!successful_read) {
            conc_vector.clear();
        }

        ifile.close();
        return conc_vector;
    }

    //Purpose: Reads the text file --> Vector of strings.
    vector<string> readTextFile(string filename) {
        vector<string> output_vector = {}; //Return variable. Empty if there were errors.
        std::ifstream ifile (filename);
        string line;

        //Open text file, check if it opens.
        if (ifile.is_open()) { 
            cout << "Opening Text file: " << filename << "\n";
        }
        else {
            cout << "Unable to open Text file: " << filename << "\n"; 
            return output_vector;
        }

        //Keep track if there was an unsuccessful read.
        //Keep line number in case you need to orient user on where a reading error occurred.
        bool successful_read = true;
        int ln = 0;

        //For every word in this line.
        while (successful_read && std::getline(ifile, line)) {
            std::stringstream iss(line);
            std::string input;

            while(iss >> input){
                //Check if there were read errors
                if (iss.fail()) {
                    successful_read = false;
                    cout << "Read error in Text file." << endl;
                    cout << "Line number: " << ln << endl;
                    break;
                }   

                output_vector.push_back(input);
            }         
        }

        //If a read was not successful, the return vector will be empty.
        if (!successful_read) {
            output_vector.clear();
        }

        ifile.close();
        return output_vector;
    }

    //Purpose: Find and fix possible word-separations by hyphens.
    //Input: Vector of strings that was read from a text file.
    //Vector of string is modified in original location. Size changes depending on how many
    //elements were combined. Example: {"Colle-", "ge", "rules"} -> {"College", "rules"}
    void fixSeparatedByHyphen(vector<string> &str_vec) {
       
        //Each string in the vector (except the last one).
        vector<string>::iterator it = str_vec.begin();
        while(it != str_vec.end()-1) {  
            
            //Find strings that end in hyphen
            if ((*it).back() == '-') {
                (*it).pop_back(); //Remove hyphen (last character).
                *(it+1) = *it + *(it+1); //Make next element the combination of the two.
                it = str_vec.erase(it); //Delete this element and points to the next element.
            }
            //If not, iterate to next element
            else {
                it++;
            }
        }

        return;
    }

    //Purpose: Take a vector of strings, remove digits from each element.
    //Removes and element if there are no characters left. Original vector modified in place.
    void removeNumeric(vector<string> &str_vec) {
 
        //Each string in the vector.
        vector<string>::iterator it = str_vec.begin();
        while(it != str_vec.end()) {  
            
            //Check every character for a digit. Remove from string if so.
            string::iterator cit = (*it).begin();
            while (cit < (*it).end()) {
                if (isdigit((*cit))) {
                    cit = (*it).erase(cit);
                }
                else {
                    cit++;
                }
            }

            //Remove vector element if now empty
            if ((*it).empty()) {
                it = str_vec.erase(it); //Delete this element and point to next element.
            }
            else {
                it++;
            }
        }

        return;
    }

    //Purpose: Remove unwanted characters from a string.
    //Input: 1) Target string 2) A string of the characters to remove.
    void removeSpecificCharsFromString(string &targ, string charsToRemove ) {
        string::iterator tit = targ.begin();

        //For every character in the target string
        while (tit != targ.end()) {
            string::iterator cit = charsToRemove.begin();
            bool wanted = true;

            //Compare to all characters you would like to remove.   
            while (cit != charsToRemove.end() && wanted) {
                //Remove this character from the target if equal to a char you want to remove.
                if (*(tit) == *(cit)) {
                    wanted = false;
                }
                else {
                    cit++;
                }
            }

            if (wanted) {
                tit++;
            }
            else {
                tit = targ.erase(tit);
            }
        }
    }

    //Purpose: Takes a string of vectors and removes unwanted characters.
    //Input: 1) A vector of strings 2) A string of the characters to remove (i.e. "&*!)(").
    //Original vector of strings is modified in place.
    void removeSpecificCharsFromVector(vector<string> &str_vec, string charsToRemove) {
        
        vector<string>::iterator it = str_vec.begin();
        
        //For each string in the vector
        while(it != str_vec.end()) {  
            
            removeSpecificCharsFromString((*it), charsToRemove);
            
            //If the remaining string is empty, remove it from the vector
            if ((*it).empty()){
                it = str_vec.erase(it); //Deletes this element and points to the next one.
            }
            else {
                it++;
            }
        }
        return;
    }

    //Purpose: Takes a vector of strings and makes all characters lowercase.
    //Vector of strings modified in place.
    void changeAllToLowerCase(vector<string> &str_vec) {
        
        //Each string in the vector
        for (vector<string>::iterator it = str_vec.begin(); it != str_vec.end(); ++it){
            //Each character in the string
            for (unsigned int j = 0; j < (*it).length(); j++){
                if (isupper((*it)[j])){
                    (*it)[j]  = tolower((*it)[j]);
                }
            }
        }
        
        return;
    }

    //Purpose: Take a vector of strings. Remove elements with less than n characters.
    //The original vector is modified in place.
    void removeSmallElements(vector<string> &strv, int n) {

        vector<string>::iterator it = strv.begin();
        
        //Remove elements with less than n characters.
        while(it < strv.end()){
            if ((*it).length() < n){
                it = strv.erase(it); //Delete this element and point to next one.
            }
            else {
                it++;
            }
        }
    }





    //Purpose: Vector of strings -> Unordered map [strings, number of occurrences].
    //Example: {"hello", "bro", "hello", "again"} -> {hello: 2, bro: 1; again: 1}.
    unordered_map<string,int> mapVector (vector<string> text_vector) {
        unordered_map<string,int> usi; //Return variable.
        int n = text_vector.size();

        //For every string in the text vector.
        for (int i = 0; i < n; i++) {
            //If not in map -> Make a new key with value of 1.
            if (usi.find(text_vector[i]) == usi.end()) {
                usi[text_vector[i]] = 1;
            }
            //If in map -> Update mapped value by additional 1.
            else {
                usi[text_vector[i]]++;
            }
        }
    return usi;
    }

    //Purpose: Cout the map.
    void printMap (unordered_map<string,int> text_map) {
        for (auto i = text_map.begin(); i != text_map.end(); i++) {
            cout << i->first << ": " << i->second << endl;
        }
    }

    //Purpose: Reads a concept and the mapped text vector --> Updates the concept counts.
    //Input: 1) Concept 2) Map of text_vector. Strings are the key and the mapped value is the
    //amount of times it was found in the original text vector.
    //Takes advantade of maps to minimize number of operations.
    void countFromMap (Concept &conc, unordered_map<string,int> &text_map) {
        int ct = 0;

        //For each word permutation.
        for (int i = 0; i < conc.permutations.size(); i++) {
            ct+= text_map[conc.permutations[i]];
        }

        //Update the counts on the concept.
        conc.counts.push_back(ct);
    }

    //Purpose: Take a vector of concepts --> Save to file.
    void writeResultsToFile (vector<Concept> cv, string filename) {
        
        std::ofstream ofile (filename);
        if (ofile.is_open()) {
            cout << "Saving results into : " << filename << "\n";
        }
        else {
            cout << "Could not open : " << filename << ". No data has been written." << endl;
        }        

        //Write column names
        ofile << "Concept (main word)" << "\tPermutations" << "\tCounts\n";
        
        //Write out each concept searched for
        for (int i = 0; i < cv.size(); i++){

            ofile << cv[i].main_word << "\t";
            
            //Permutations
            if (cv[i].permutations.size() > 1){
                ofile << cv[i].permutations[1];
            }
            for (int j = 2; j < cv[i].permutations.size(); j++){
                ofile << "," << cv[i].permutations[j];
            }
            
            ofile << "\t";

            //Number of counts
            if (cv[i].counts.size() > 0){
                ofile << cv[i].counts[0];
            }
            for (int j = 1; j < cv[i].counts.size(); j++){
                ofile << "," << cv[i].counts[j];
            }
            ofile << endl;
        }
        
        ofile.close();
        return; 
    }

    //Purpose: Console output a string of vectors.
    void printVector(vector<string> input_vec) {
        int n = input_vec.size();
        {
            for (int i = 0; i < n; i++){
                cout << input_vec[i] << "\t";
            }
            cout << endl;
            return;
        }
    }

}