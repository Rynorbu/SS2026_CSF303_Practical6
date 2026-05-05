#include <iostream>
#include <unordered_map>
#include <string>

class RadixNode {
public:
    std::string prefix;
    std::unordered_map<char, RadixNode*> children;
    bool isEnd;

    RadixNode(std::string p = "", bool end = false) {
        prefix = p;
        isEnd = end;
    }

    ~RadixNode() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

class PatriciaTrie {
private:
    RadixNode* root;

public:
    PatriciaTrie() {
        root = new RadixNode();
    }

    ~PatriciaTrie() {
        delete root;
    }

    void insert(const std::string& word) {
        RadixNode* node = root;
        std::string remaining_word = word;

        while (!remaining_word.empty()) {
            bool match_found = false;
            
            for (auto const& [edge_char, child] : node->children) {
                if (remaining_word[0] == edge_char) {
                    int i = 0;
                    while (i < child->prefix.length() && i < remaining_word.length() && child->prefix[i] == remaining_word[i]) {
                        i++;
                    }
                    
                    if (i == child->prefix.length()) {
                        // Full match with edge, traverse down
                        node = child;
                        remaining_word = remaining_word.substr(i);
                        match_found = true;
                        break;
                    } else {
                        // Partial match, we need to split the node
                        RadixNode* split_node = new RadixNode(child->prefix.substr(i), child->isEnd);
                        split_node->children = child->children; // Copy existing children
                        
                        child->prefix = child->prefix.substr(0, i);
                        child->isEnd = false;
                        child->children.clear();
                        child->children[split_node->prefix[0]] = split_node;
                        
                        if (i < remaining_word.length()) {
                            RadixNode* new_leaf = new RadixNode(remaining_word.substr(i), true);
                            child->children[remaining_word[i]] = new_leaf;
                        } else {
                            child->isEnd = true;
                        }
                        
                        std::cout << "Inserted (with split): " << word << std::endl;
                        return;
                    }
                }
            }

            if (!match_found) {
                node->children[remaining_word[0]] = new RadixNode(remaining_word, true);
                std::cout << "Inserted: " << word << std::endl;
                return;
            }
        }

        node->isEnd = true;
        std::cout << "Inserted: " << word << std::endl;
    }

    bool search(const std::string& word) {
        RadixNode* node = root;
        std::string remaining_word = word;

        while (!remaining_word.empty()) {
            bool match_found = false;
            for (auto const& [edge_char, child] : node->children) {
                if (remaining_word[0] == edge_char) {
                    if (remaining_word.substr(0, child->prefix.length()) == child->prefix) {
                        node = child;
                        remaining_word = remaining_word.substr(child->prefix.length());
                        match_found = true;
                        break;
                    }
                }
            }
            if (!match_found) {
                return false;
            }
        }
        return node->isEnd;
    }

    void remove(const std::string& word) {
        // Logical deletion for simplicity, identical to the Python logic.
        RadixNode* node = root;
        std::string remaining_word = word;

        while (!remaining_word.empty()) {
            bool match_found = false;
            for (auto const& [edge_char, child] : node->children) {
                if (remaining_word.substr(0, child->prefix.length()) == child->prefix) {
                    node = child;
                    remaining_word = remaining_word.substr(child->prefix.length());
                    match_found = true;
                    break;
                }
            }
            if (!match_found) {
                std::cout << "Word '" << word << "' not found for deletion." << std::endl;
                return;
            }
        }

        if (node->isEnd) {
            node->isEnd = false;
            std::cout << "Deleted (logical): " << word << std::endl;
        } else {
            std::cout << "Word '" << word << "' not found for deletion." << std::endl;
        }
    }
};

int main() {
    PatriciaTrie ptrie;
    ptrie.insert("romane");
    ptrie.insert("romanus");
    ptrie.insert("romulus");
    
    std::cout << "Search 'romane': " << (ptrie.search("romane") ? "True" : "False") << std::endl;
    std::cout << "Search 'romanus': " << (ptrie.search("romanus") ? "True" : "False") << std::endl;
    std::cout << "Search 'rom': " << (ptrie.search("rom") ? "True" : "False") << std::endl;
    
    ptrie.remove("romane");
    std::cout << "Search 'romane' after deletion: " << (ptrie.search("romane") ? "True" : "False") << std::endl;

    return 0;
}