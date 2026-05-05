#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string manachersAlgorithm(const std::string& s) {
    if (s.empty()) return "";

    // Preprocess the string to handle even/odd length palindromes uniformly
    // Example: "babad" -> "^#b#a#b#a#d#$"
    std::string T = "^";
    for (char c : s) {
        T += "#";
        T += c;
    }
    T += "#$";

    int n = T.length();
    std::vector<int> P(n, 0); // Array to store the radius of the longest palindrome
    
    int C = 0; // Center of the palindrome that currently extends furthest to the right
    int R = 0; // Right boundary of this palindrome
    
    for (int i = 1; i < n - 1; i++) {
        // Find the mirror index of i with respect to center C
        int i_mirror = 2 * C - i;
        
        // Initialize P[i]
        if (R > i) {
            P[i] = std::min(R - i, P[i_mirror]);
        } else {
            P[i] = 0;
        }
            
        // Attempt to expand the palindrome centered at i
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
            P[i]++;
        }
            
        // If palindrome centered at i expands past R, adjust center C and right boundary R
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }
            
    // Find the maximum element in P
    int max_len = 0;
    int center_index = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > max_len) {
            max_len = P[i];
            center_index = i;
        }
    }
            
    // Extract the longest palindrome from the original string
    int start = (center_index - 1 - max_len) / 2;
    return s.substr(start, max_len);
}

int main() {
    std::vector<std::string> test_strings = {"babad", "cbbd", "a", "racecar", "abacabacabb"};
    
    for (const std::string& str : test_strings) {
        std::string result = manachersAlgorithm(str);
        std::cout << "Original: " << str << " -> Longest Palindrome: " << result << std::endl;
    }
    
    return 0;
}