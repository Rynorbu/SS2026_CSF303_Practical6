class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True
        print(f"Inserted: {word}")

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word

    def delete(self, word: str) -> bool:
        def _delete(node, word, depth):
            if depth == len(word):
                if not node.is_end_of_word:
                    return False
                node.is_end_of_word = False
                return len(node.children) == 0
            
            char = word[depth]
            if char not in node.children:
                return False
            
            should_delete_child = _delete(node.children[char], word, depth + 1)
            
            if should_delete_child:
                del node.children[char]
                return len(node.children) == 0 and not node.is_end_of_word
            return False

        if self.search(word):
            _delete(self.root, word, 0)
            print(f"Deleted: {word}")
            return True
        print(f"Word '{word}' not found for deletion.")
        return False

# --- Testing the Implementation ---
if __name__ == "__main__":
    trie = Trie()
    trie.insert("apple")
    trie.insert("app")
    
    print(f"Search 'apple': {trie.search('apple')}")
    print(f"Search 'app': {trie.search('app')}")
    print(f"Search 'appl': {trie.search('appl')}")
    
    trie.delete("app")
    print(f"Search 'app' after deletion: {trie.search('app')}")
    print(f"Search 'apple' after 'app' deletion: {trie.search('apple')}")