#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <random>
#include <ctime>
#include <cctype>
#include <string>
#include <utility>
class language


{
public:
// Token frequency data structure
using TokenFrequency = std::map<std::string, int>;

// Token probability data structure
using TokenProbabilities = std::map<std::pair<std::string, std::string>, std::vector<std::string>>;

// Function to tokenize text into words/tokens
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : text) {
        if (std::isalnum(c) || c == '\'') {
            token += std::tolower(c);
        }
        else if (!token.empty()) {
            tokens.push_back(token);
            token.clear();
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to create token frequency
TokenFrequency createTokenFrequency(const std::vector<std::string>& tokens) {
    TokenFrequency frequency;
    for (const std::string& token : tokens) {
        frequency[token]++;
    }
    return frequency;
}



// Function to create token probabilities for pairs of tokens
    TokenProbabilities createTokenProbabilities(const std::vector<std::string>& tokens) {
        TokenProbabilities probabilities;
        for (size_t i = 0; i < tokens.size() - 2; ++i) {
            probabilities[std::make_pair(tokens[i], tokens[i + 1])].push_back(tokens[i + 2]);
        }
        return probabilities;
    }

    // Updated function to predict the next token based on two tokens
    std::string predictNextToken(const TokenProbabilities& probabilities, const std::string& firstToken, const std::string& secondToken) {
        auto key = std::make_pair(firstToken, secondToken);
        if (probabilities.find(key) != probabilities.end()) {
            const std::vector<std::string>& nextTokens = probabilities.at(key);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, nextTokens.size() - 1);
            int randomIndex = dist(gen);
            return nextTokens[randomIndex];
        } else {
            return "No prediction available.";
        }
    }
    std::string generateTokens(const TokenProbabilities& probabilities, const std::string& seedToken1, const std::string& seedToken2, int maxTokens) {
        std::string generatedText;

        // Start with the two seed tokens
        std::string firstToken = seedToken1;
        std::string secondToken = seedToken2.empty() ? predictNextToken(probabilities, firstToken, "") : seedToken2;

        generatedText += firstToken + " " + secondToken + " ";

        for (int i = 2; i < maxTokens; ++i) { // Starting from 2 as we already have two tokens
            std::string nextToken = predictNextToken(probabilities, firstToken, secondToken);
            generatedText += nextToken + " ";
            firstToken = secondToken;
            secondToken = nextToken;
        }
        return generatedText;
    }

// Function to generate tokens from a user prompt
    std::string generateFromPrompt(const TokenProbabilities& probabilities, const std::string& prompt, int maxTokens) {
        std::vector<std::string> promptTokens = tokenize(prompt);
        std::string generatedText = prompt + " ";
        
        std::string firstToken, secondToken;
        if (promptTokens.size() >= 2) {
            firstToken = promptTokens[promptTokens.size() - 2];
            secondToken = promptTokens.back();
        } else if (promptTokens.size() == 1) {
            firstToken = promptTokens[0];
            secondToken = predictNextToken(probabilities, promptTokens[0], "");
        } else {
            firstToken = "the";
            secondToken = predictNextToken(probabilities, "the", "");
        }

        for (int i = 0; i < maxTokens; ++i) {
            std::string nextToken = predictNextToken(probabilities, firstToken, secondToken);
            generatedText += nextToken + " ";
            firstToken = secondToken;
            secondToken = nextToken;
        }
        return generatedText;
    }
int model() {
    // Read the CSV file
    std::string filePath = "csv.csv";
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return 1;
    }

    // Tokenize and process the text
    std::vector<std::string> tokens;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> lineTokens = tokenize(line);
        tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
    }

    // Create token frequency and token probabilities
    TokenFrequency tokenFrequency = createTokenFrequency(tokens);
    TokenProbabilities tokenProbabilities = createTokenProbabilities(tokens);

  
    while (true) {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Enter a word (or 'exit' to quit)" << std::endl;
        std::cout << "2. Generate a continuous string of tokens" << std::endl;
        std::cout << "3. Prompt model mode" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Enter a word mode
            std::string firstToken, secondToken;
            std::cout << "Enter the first word: ";
            std::cin >> firstToken;
            std::cout << "Enter the second word (or leave blank for random): ";
            std::cin.ignore(); // Ignores the newline character left in the buffer
            std::getline(std::cin, secondToken);

            if (firstToken == "exit") {
                break;
            }

            if (secondToken.empty()) {
                secondToken = predictNextToken(tokenProbabilities, firstToken, "");
            }

            std::string nextToken = predictNextToken(tokenProbabilities, firstToken, secondToken);
            std::cout << "Predicted next token: " << nextToken << std::endl;
        }
       
        else if (choice == 2) {
            // Generate a continuous string of tokens with seed tokens
            std::string seedToken1, seedToken2;
            int maxTokens;

            std::cout << "Enter the first seed token: ";
            std::cin >> seedToken1;
            std::cout << "Enter the second seed token (or leave blank for random): ";
            std::cin.ignore(); // Ignores the newline character left in the buffer
            std::getline(std::cin, seedToken2);

            std::cout << "Enter the maximum number of tokens to generate: ";
            std::cin >> maxTokens;

            std::string generatedText = generateTokens(tokenProbabilities, seedToken1, seedToken2, maxTokens);
            std::cout << "Generated text: " << generatedText << std::endl;
        }
        else if (choice == 3) {
            // Prompt model mode
            std::string prompt;
            int maxTokens;
            std::cout << "Enter a prompt: ";
            std::cin.ignore(); // Ignores the newline character left in the buffer
            std::getline(std::cin, prompt);
            std::cout << "Enter the maximum number of tokens to generate: ";
            std::cin >> maxTokens;

            std::string generatedText = generateFromPrompt(tokenProbabilities, prompt, maxTokens);
            std::cout << "Generated text from prompt: " << generatedText << std::endl;
        }
        else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }


    return 0;
}

};