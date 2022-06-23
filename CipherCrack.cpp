 #include <iostream>
 #include <fstream>
 #include <string>
 #include <map>
 #include <vector>
 #include <algorithm>
 #include <cctype>
 using namespace std;

 // Comparison function used in std::sort(), used below
 bool descendingComparison(pair<string, int>& a, pair<string, int>& b) {
    return a.second > b.second;
 }

 // Sorts map on value, then prints to specified file the determined counts
 void descendingSort(map<string, int>& map, ofstream& outfile, bool singles) {
    vector<pair<string, int>> orderedCopy;
    for (auto& it : map) {
      orderedCopy.push_back(it);
    }

    // Uses custom comparator function
    sort(orderedCopy.begin(), orderedCopy.end(), descendingComparison);

    int i = 0;
    // Print out singles map (non-zero counts)
    if (singles) {
      for (auto& it : orderedCopy) {
        if (it.second <= 0) break;
        i++;
        outfile << i << " " << it.first << " " << it.second << endl;
      }
    }
    // Print correctly ordered map (top 30, only non-zero counts)
    else {
      for (auto& it : orderedCopy) {
        i++;
        if (i == 31 || it.second <= 0) break;
        outfile << i << " " << it.first << " " << it.second << endl;
      }
    }
 }

 // Checks for whitespace, punctuation, or a number in the string
 bool isInvalid(string& checkedString) {
    for (int i = 0; i < checkedString.length(); i++) {
      // Invalid string
      if (!isalpha(checkedString[i])) return true;
    }
    // Valid string
    return false;
 }

 // Counts the user-specified patterns
 void patternCount(map<string, int>& currMap, string& currentLine, int subStringLen) {
    string substring;
    for (int j = 0; j < currentLine.length(); j++) {
      substring = currentLine.substr(j, subStringLen);
      // Validates string (no spaces && no punctuation && no numbers)
      if (!isInvalid(substring)) {
        // Make sure everything is the same case (lower in this *case*)
        transform(substring.begin(), substring.end(), substring.begin(), ::tolower);
        currMap[substring] += 1;
      }
    }
 }

 int main(int argc, char *argv[]) {
    string currentLine;
    // Maps to store occurance counts for single letters, bigrams, and trigrams
    map<string, int> singles, bigrams, trigrams;

    if (argc < 3 || argc > 3) {
      cout << "Too few/ or many command line arguments...\nPlease enter in this format: ./[executableName] <inFile> <outFile>\nClosing program...\n";
      return 1;
    }

    ifstream infile(argv[1]);

    if (infile.is_open()) {
      ofstream outfile(argv[2]);
      outfile << argv[1] << "'s Stats:\n\n";
      // Count singles, bis, and tris for each line in the input file
      while (getline(infile, currentLine)) {
        patternCount(singles, currentLine, 1);
        patternCount(bigrams, currentLine, 2);
        patternCount(trigrams, currentLine, 3);
      }
      // Sort the maps by ascending values, then print corresponding counts when applicable
      outfile << "Single Letter Count(s):" << endl;
      descendingSort(singles, outfile, true);
      outfile << endl;
      /***********************************************************************************/
      outfile << "Bigram Count(s):" << endl;
      descendingSort(bigrams, outfile, false);
      outfile << endl;
      /***********************************************************************************/
      outfile << "Trigram Count(s):" << endl;
      descendingSort(trigrams, outfile, false);

      // Close files used
      infile.close();
      outfile.close();
    }

    return 0;
 }