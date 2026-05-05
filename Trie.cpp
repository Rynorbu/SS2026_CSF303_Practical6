#include <iostream>
#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
    
    ~TrieNode() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    bool _deleteHelper(TrieNode* node, const std::string& word, int depth) {
        if (depth == word.length()) {
            if (!node->isEndOfWord) return false;
            node->isEndOfWord = false;
            return node->children.empty();
        }

        char c = word[depth];
        if (node->children.find(c) == node->children.end()) {
            return false;
        }

        bool shouldDeleteChild = _deleteHelper(node->children[c], word, depth + 1);

        if (shouldDeleteChild) {
            delete node->children[c];
            node->children.erase(c);
            return node->children.empty() && !node->isEndOfWord;
        }
        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        std::cout << "Inserted: " << word << std::endl;
    }

    bool search(const std::string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

    bool remove(const std::string& word) {
        if (search(word)) {
            _deleteHelper(root, word, 0);
            std::cout << "Deleted: " << word << std::endl;
            return true;
        }
        std::cout << "Word '" << word << "' not found for deletion." << std::endl;
        return false;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    
    std::cout << "Search 'apple': " << (trie.search("apple") ? "True" : "False") << std::endl;
    std::cout << "Search 'app': " << (trie.search("app") ? "True" : "False") << std::endl;
    std::cout << "Search 'appl': " << (trie.search("appl") ? "True" : "False") << std::endl;
    
    trie.remove("app");
    std::cout << "Search 'app' after deletion: " << (trie.search("app") ? "True" : "False") << std::endl;
    std::cout << "Search 'apple' after 'app' deletion: " << (trie.search("apple") ? "True" : "False") << std::endl;

    return 0;
}