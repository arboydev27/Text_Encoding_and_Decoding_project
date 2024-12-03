/*
 * Program Name: Text Encoding Algorithm
 * Author: Arboy Magomba
 * Date: November 20, 2024
 * 
 * Description:
 * This program processes input text to determine the frequency of each unique token,
 * sorts the tokens based on their frequency in descending order (and lexicographically
 * for ties), and encodes the text by replacing each token with its position in the sorted list.
 * 
 * It supports handling redirected input efficiently and ensures robust parsing for accurate 
 * tokenization and frequency analysis. The program is designed for tasks that require 
 * analyzing and encoding text data dynamically.
 * 
 * The implementation involves:
 * - Calculating token frequencies
 * - Sorting tokens based on frequency and lexicographical order
 * - Encoding the original text into positional representations
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
// This function increments the frequency count for a given token in the map
void addToken(unordered_map<string, int> &tokenFrequency, const string &token) {
    if (!token.empty()) {
        tokenFrequency[token]++;
    }
}

// Function to process tokens and encode text
// Looks up a token's position in the tokenPosition map and appends it to the encodedText vector
void processToken(const map<string, int> &tokenPosition, const string &token, vector<int> &encodedText) {
    if (!token.empty()) {
        auto it = tokenPosition.find(token);
        if (it != tokenPosition.end()) {
            encodedText.push_back(it->second); // Add the token's position to the encoded text
        } else {
            cerr << "Error: Token '" << token << "' not found in tokenPosition map." << endl;
        }
    }
}

int main() {
    // Step 1: Read all input from standard input into a single string
    // This approach allows the program to handle redirected input seamlessly
    string inputContent((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());

    // Step 2: Calculate token frequencies
    // Parse the input content to count occurrences of each token
    unordered_map<string, int> tokenFrequency; // Map to store token frequencies
    string token; // Current token being processed
    char aChar; // Current character being read

    istringstream inputStream(inputContent); // Create a stream from the input content
    while (inputStream.get(aChar)) {
        if (isspace(aChar)) { // If the character is a space, process the current token
            addToken(tokenFrequency, token);
            token.clear(); // Reset the token for the next word
        } else {
            token += aChar; // Append the character to the current token
        }
    }
    addToken(tokenFrequency, token); // Process the last token if present

    // Step 3: Transfer data to a vector for sorting
    // Move the token-frequency pairs to a vector and sort them
    vector<pair<string, int>> sortedTokens(tokenFrequency.begin(), tokenFrequency.end());
    sort(sortedTokens.begin(), sortedTokens.end(),
         [](const pair<string, int> &a, const pair<string, int> &b) {
             if (a.second != b.second) {
                 return a.second > b.second; // Sort by frequency (descending)
             }
             return a.first < b.first; // Lexicographical order for tie-breaking
         });

    // Step 4: Map tokens to their positions in the sorted order
    // Create a map that associates each token with its position in the sorted list
    map<string, int> tokenPosition;
    int position = 1; // Positions start at 1
    for (const auto &pair : sortedTokens) {
        tokenPosition[pair.first] = position++;
    }

    // Step 5: Output the unique tokens in sorted order
    // Print the sorted tokens as a single space-separated line
    for (const auto &pair : sortedTokens) {
        cout << pair.first << " ";
    }
    cout << endl << "**********" << endl;

    // Step 6: Encode the text based on token positions
    // Parse the input content again and encode tokens into their corresponding positions
    vector<int> encodedText; // Vector to store the encoded text
    token.clear(); // Reset token for the second pass

    istringstream secondPass(inputContent); // Reuse the stored input content
    while (secondPass.get(aChar)) {
        if (isspace(aChar)) { // If the character is a space, process the current token
            processToken(tokenPosition, token, encodedText);
            token.clear(); // Reset the token for the next word
        } else {
            token += aChar; // Append the character to the current token
        }
    }
    processToken(tokenPosition, token, encodedText); // Process the last token if present

    // Output the encoded text
    // Print the encoded text as a single space-separated line
    for (int position : encodedText) {
        cout << position << " ";
    }
    cout << endl;

    return 0;
}

/*
 * CODE DOCUMENTATION
 * Project: Text Frequency and Encoding
 *
 * Overview:
 * This program analyzes text to determine token frequencies, sorts the tokens,
 * and encodes the text by replacing each token with its position in the sorted list.
 * It is designed for dynamic text analysis tasks where tokenization, frequency analysis,
 * and encoding are required.
 *
 * Main Functionalities:
 * - **Frequency Analysis**: Counts the occurrences of each unique token in the input text.
 * - **Sorting**: Orders tokens based on frequency (descending) and lexicographical order for ties.
 * - **Encoding**: Replaces each token in the original text with its position in the sorted list.
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
 *    - Suggestions included:
 *      - Using `unordered_map` for frequency counting.
 *      - Sorting using custom comparators.
 *      - Handling edge cases like empty input or single tokens.
 *
 * 2. Rationale for AI Usage:
 *    - AI assistance was utilized for conceptual guidance on tokenization, sorting algorithms,
 *      and best practices for handling dynamic input.
 *
 * 3. Incremental Development:
 *    - Developed and tested the frequency analysis module first.
 *    - Added sorting and verified correctness with small inputs.
 *    - Implemented encoding logic and validated output format against sample cases.
 *
 * Debugging and Testing Plan:
 *
 * 1. Specific Tests:
 *    - **Tokenization**: Validated correct splitting of text into tokens.
 *    - **Frequency Analysis**: Tested accuracy of token frequency counts.
 *    - **Sorting**: Verified order of tokens in the sorted list.
 *    - **Encoding**: Ensured correct replacement of tokens with positional values.
 *    - **Edge Cases**: Checked behavior with empty input, single tokens, and long text.
 *
 * 2. Issues and Resolutions:
 *    - **Issue**: Incorrect tokenization for punctuation-bound words.
 *      **Resolution**: Refined parsing logic to include all characters.
 *    - **Issue**: Misalignment between tokenization and encoding phases.
 *      **Resolution**: Ensured consistent token processing in all phases.
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
 * input efficiently while producing accurate results.
 */
