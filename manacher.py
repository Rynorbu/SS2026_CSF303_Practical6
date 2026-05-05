def manachers_algorithm(s: str) -> str:
    if not s:
        return ""
    
    # Preprocess the string to handle even/odd length palindromes uniformly
    # Example: "babad" -> "^#b#a#b#a#d#$"
    T = "^#" + "#".join(s) + "#$"
    n = len(T)
    P = [0] * n  # Array to store the radius of the longest palindrome around center i
    
    C = 0  # Center of the palindrome that currently extends furthest to the right
    R = 0  # Right boundary of this palindrome
    
    for i in range(1, n - 1):
        # Find the mirror index of i with respect to center C
        i_mirror = 2 * C - i
        
        # If i is within the right boundary, we can initialize P[i]
        # to the minimum of its mirror's radius or the distance to the right boundary.
        if R > i:
            P[i] = min(R - i, P[i_mirror])
        else:
            P[i] = 0
            
        # Attempt to expand the palindrome centered at i
        while T[i + 1 + P[i]] == T[i - 1 - P[i]]:
            P[i] += 1
            
        # If palindrome centered at i expands past R, adjust center C and right boundary R
        if i + P[i] > R:
            C = i
            R = i + P[i]
            
    # Find the maximum element in P
    max_len = 0
    center_index = 0
    for i in range(1, n - 1):
        if P[i] > max_len:
            max_len = P[i]
            center_index = i
            
    # Extract the longest palindrome from the original string
    start = (center_index - 1 - max_len) // 2
    return s[start: start + max_len]

# --- Testing the Implementation ---
if __name__ == "__main__":
    test_strings = ["babad", "cbbd", "a", "racecar", "abacabacabb"]
    
    for string in test_strings:
        result = manachers_algorithm(string)
        print(f"Original: {string} -> Longest Palindrome: {result}")