#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class tokenizer
{


private:


    string cleanToken(const string& token) {
        string cleanToken;
        for (char c : token) {
            // Check if the character is a valid UTF-8 character
            if ((c >= -1 && c <= 255) || (c >= 0xC2 && c <= 0xF4)) {
                if (isalnum(c) || c == ' ' || c == '\t') {
                    cleanToken += c;
                }
                else if (c == '\n') {
                    // Replace line breaks with symbolic representation
                    cleanToken += "\\n";
                }
                else if (c == '\r') {
                    // Replace carriage returns with symbolic representation
                    cleanToken += "\\r";
                }
                else if (c == '\t') {
                    // Replace tabs with symbolic representation
                    cleanToken += "\\t";
                }
            }
        }
        return cleanToken;
    }
public:
    int tokenize() {
        // Prompt the user for the input file name and output file name.
        string inputFileName, outputFileName;
        std::cout << "Please enter the name of the input text file: ";
        std::cin >> inputFileName;
        std::cout << "Please enter the name of the output CSV file: ";
        std::cin >> outputFileName;

        // Prompt the user for verbose output option.
        char verboseOption;
        std::cout << "Do you want verbose output? (slow) [y/n]: ";
        std::cin >> verboseOption;
        bool verboseOutput = (verboseOption == 'y' || verboseOption == 'Y');

        // Open the input text file.
        ifstream inputFile(inputFileName);

        if (!inputFile) {
            cerr << "Error: Unable to open input file." << endl;
            return 1;
        }

        // Open the output CSV file.
        ofstream outputFile(outputFileName);

        if (!outputFile) {
            cerr << "Error: Unable to open output file." << endl;
            return 1;
        }

        // Process the input file line by line.
        string line;
        int tokenNumber = 0; // Initialize the token number

        while (getline(inputFile, line)) {
            // Create a stringstream to tokenize the line.
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (ss >> token) {
                // Remove unwanted characters from the token.
                string cleanedToken = cleanToken(token); // Rename the variable

                // Add the cleaned token to the vector of tokens if it's not empty.
                if (!cleanedToken.empty()) {
                    tokens.push_back(cleanedToken);
                }

                // Print verbose output if enabled
                if (verboseOutput) {
                    cout << "Token #" << tokenNumber << ": " << token << " (" << cleanedToken << ")" << endl;
                }

                tokenNumber++;
            }

            // Write the tokens to the output CSV file.
            for (size_t i = 0; i < tokens.size(); i++) {
                outputFile << tokens[i];
                // Add a comma if it's not the last token.
                if (i < tokens.size() - 1) {
                    outputFile << ",";
                }
            }

            // Add a new line after each line of the input file.
            outputFile << endl;
        }

        // Close the input and output files.
        inputFile.close();
        outputFile.close();

        std::cout << "Tokenization completed. The CSV file has been saved as " << outputFileName << "." << endl;

        return 0;
    }


};

