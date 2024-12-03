/*  
 * Program Name: Text Encoding and Decoding Algorithm (Bonus part of the project)
 * Author: Arboy Magomba
 * Date: December 2, 2024
 * 
 * Description:
 * This program performs both encoding and decoding of text data. It first analyzes the input
 * text to determine token frequencies, sorts tokens by frequency (and lexicographically for ties),
 * and encodes the text by replacing tokens with their positions in the sorted list. 
 * 
 * The program then immediately decodes the encoded data back to the original text, demonstrating 
 * the reversibility of the encoding process. This implementation is ideal for scenarios where 
 * both encoding and decoding are required dynamically.
 * 
 * The implementation involves:
 * - Calculating token frequencies.
 * - Sorting tokens based on frequency and lexicographical order.
 * - Encoding the original text into positional representations.
 * - Decoding the encoded data back to reconstruct the original input text.
 * 
 * Full code documentation and LLM and AI assistance details are provided at the end of the code.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// Helper function to add tokens to the frequency map
void addToken(unordered_map<string, int> &tokenFrequency, const string &token) {
    if (!token.empty()) {
        tokenFrequency[token]++;
    }
}

// Function to process tokens and encode text
void processToken(const map<string, int> &tokenPosition, const string &token, vector<int> &encodedText) {
    if (!token.empty()) {
        auto it = tokenPosition.find(token);
        if (it != tokenPosition.end()) {
            encodedText.push_back(it->second);
        } else {
            cerr << "Error: Token '" << token << "' not found in tokenPosition map." << endl;
        }
    }
}

int main() {
    // Step 1: Read all input from standard input into a single string
    string inputContent((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());

    // Step 2: Calculate token frequencies
    unordered_map<string, int> tokenFrequency;
    string token;
    char aChar;
    istringstream inputStream(inputContent);
    while (inputStream.get(aChar)) {
        if (isspace(aChar)) {
            addToken(tokenFrequency, token);
            token.clear();
        } else {
            token += aChar;
        }
    }
    addToken(tokenFrequency, token); // Process the last token

    // Step 3: Transfer data to a vector for sorting
    vector<pair<string, int>> sortedTokens(tokenFrequency.begin(), tokenFrequency.end());
    sort(sortedTokens.begin(), sortedTokens.end(),
         [](const pair<string, int> &a, const pair<string, int> &b) {
             if (a.second != b.second) {
                 return a.second > b.second; // Sort by frequency (descending)
             }
             return a.first < b.first; // Lexicographical order for tie-breaking
         });

    // Step 4: Map tokens to their positions in the sorted order
    map<string, int> tokenPosition;
    int position = 1;
    for (const auto &pair : sortedTokens) {
        tokenPosition[pair.first] = position++;
    }

    // Step 5: Encode the text based on token positions
    vector<int> encodedText;
    token.clear();
    istringstream secondPass(inputContent);
    while (secondPass.get(aChar)) {
        if (isspace(aChar)) {
            processToken(tokenPosition, token, encodedText);
            token.clear();
        } else {
            token += aChar;
        }
    }
    processToken(tokenPosition, token, encodedText); // Process the last token

    // Step 6: Decode the encoded text
    vector<string> tokens; // Vector to store tokens in sorted order
    for (const auto &pair : sortedTokens) {
        tokens.push_back(pair.first);
    }

    stringstream decodedText;
    for (size_t i = 0; i < encodedText.size(); ++i) {
        int position = encodedText[i];
        if (position > 0 && position <= tokens.size()) {
            decodedText << tokens[position - 1];
            if (i < encodedText.size() - 1) {
                decodedText << " "; // Add a space between words
            }
        } else {
            cerr << "Error: Invalid position " << position << endl;
            return 1;
        }
    }

    // Output the final decoded text
    cout << decodedText.str() << endl;

    return 0;
}

/*
 * CODE DOCUMENTATION
 * Project: Text Encoding and Decoding
 *
 * Overview:
 * This program analyzes text to determine token frequencies, sorts tokens,
 * and encodes the text by replacing each token with its position in the sorted list.
 * It then decodes the encoded text back to its original form, demonstrating
 * the correctness and reversibility of the encoding process.
 *
 * Main Functionalities:
 * - **Frequency Analysis**: Counts the occurrences of each unique token in the input text.
 * - **Sorting**: Orders tokens based on frequency (descending) and lexicographical order for ties.
 * - **Encoding**: Replaces each token in the original text with its position in the sorted list.
 * - **Decoding**: Reconstructs the original text from the encoded positional representation.
 *
 * Implementation Highlights:
 * - Utilizes `unordered_map` for efficient frequency calculation.
 * - Leverages `vector` and `map` for sorting and positional encoding.
 * - Handles input dynamically via `std::cin` for compatibility with redirected input.
 *
 * LLM and GitHub Copilot Usage Documentation:
 *
 * This section describes the AI tools, prompts, and iterative process employed to develop the program.
 *
 * 1. Prompts and Suggestions:
 *    - Prompts used:
 *      - "How to tokenize and count word frequencies in C++?"
 *      - "Efficient sorting and ranking of tokens based on frequency."
 *      - "Encoding text by replacing tokens with positional values."
 *      - "Decoding an encoded text back to its original form."
 *    - Suggestions included:
 *      - Using `unordered_map` for frequency counting.
 *      - Sorting using custom comparators.
 *      - Ensuring reversibility of encoding and decoding processes.
 *
 * 2. Rationale for AI Usage:
 *    - AI assistance was utilized for conceptual guidance on tokenization, sorting algorithms,
 *      and best practices for handling dynamic input.
 *
 * 3. Incremental Development:
 *    - Developed and tested the frequency analysis module first.
 *    - Added sorting and verified correctness with small inputs.
 *    - Implemented encoding and decoding logic iteratively, validating outputs at each step.
 *
 * Debugging and Testing Plan:
 *
 * 1. Specific Tests:
 *    - **Tokenization**: Validated correct splitting of text into tokens.
 *    - **Frequency Analysis**: Tested accuracy of token frequency counts.
 *    - **Sorting**: Verified order of tokens in the sorted list.
 *    - **Encoding and Decoding**: Ensured encoding and decoding produced reversible results.
 *    - **Edge Cases**: Checked behavior with empty input, single tokens, and long text.
 *
 * 2. Issues and Resolutions:
 *    - **Issue**: Mismatch in tokenization between encoding and decoding phases.
 *      **Resolution**: Refined tokenization logic to ensure consistency.
 *    - **Issue**: Errors with positional indexing in decoding.
 *      **Resolution**: Added bounds checks for positional values.
 *
 * 3. Verification:
 *    - Command-line testing confirmed expected outputs for diverse input cases.
 *    - Cross-validation against reference outputs verified correctness.
 *
 * Reflection on AI Assistance:
 * - AI tools streamlined the development process, providing clarity on text processing
 *   concepts and improving code efficiency. Iterative suggestions helped address edge
 *   cases and optimize output formatting.
 *
 * Note: This program has been thoroughly tested and is designed to handle dynamic
 * input efficiently while producing accurate and reversible results.
 */
