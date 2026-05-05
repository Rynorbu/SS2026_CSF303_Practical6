class RadixNode:
    def __init__(self, prefix="", is_end=False):
        self.prefix = prefix
        self.children = {}
        self.is_end = is_end

class PatriciaTrie:
    def __init__(self):
        self.root = RadixNode()

    def insert(self, word: str) -> None:
        node = self.root
        remaining_word = word

        while remaining_word:
            match_found = False
            for edge_char, child in node.children.items():
                if remaining_word.startswith(edge_char):
                    # Find longest common prefix
                    i = 0
                    while i < len(child.prefix) and i < len(remaining_word) and child.prefix[i] == remaining_word[i]:
                        i += 1
                    
                    if i == len(child.prefix):
                        # Full match with edge, traverse down
                        node = child
                        remaining_word = remaining_word[i:]
                        match_found = True
                        break
                    else:
                        # Partial match, we need to split the node
                        split_node = RadixNode(child.prefix[i:], child.is_end)
                        split_node.children = child.children
                        
                        child.prefix = child.prefix[:i]
                        child.is_end = False
                        child.children = {split_node.prefix[0]: split_node}
                        
                        if i < len(remaining_word):
                            new_leaf = RadixNode(remaining_word[i:], True)
                            child.children[remaining_word[i]] = new_leaf
                        else:
                            child.is_end = True
                        
                        print(f"Inserted (with split): {word}")
                        return

            if not match_found:
                node.children[remaining_word[0]] = RadixNode(remaining_word, True)
                print(f"Inserted: {word}")
                return

        node.is_end = True
        print(f"Inserted: {word}")

    def search(self, word: str) -> bool:
        node = self.root
        remaining_word = word

        while remaining_word:
            match_found = False
            for edge_char, child in node.children.items():
                if remaining_word.startswith(edge_char):
                    if remaining_word.startswith(child.prefix):
                        node = child
                        remaining_word = remaining_word[len(child.prefix):]
                        match_found = True
                        break
            if not match_found:
                return False
                
        return node.is_end

    def delete(self, word: str) -> None:
        # A simplified deletion for demonstration: 
        # In a full production Radix tree, deleting a node also requires merging 
        # it back with its parent if the parent is left with only 1 child.
        # Here we do a logical deletion (unsetting the flag) for simplicity.
        node = self.root
        remaining_word = word
        path = []

        while remaining_word:
            match_found = False
            for edge_char, child in node.children.items():
                if remaining_word.startswith(child.prefix):
                    path.append((node, edge_char, child))
                    node = child
                    remaining_word = remaining_word[len(child.prefix):]
                    match_found = True
                    break
            if not match_found:
                print(f"Word '{word}' not found for deletion.")
                return

        if node.is_end:
            node.is_end = False
            print(f"Deleted (logical): {word}")
        else:
            print(f"Word '{word}' not found for deletion.")

# --- Testing the Implementation ---
if __name__ == "__main__":
    ptrie = PatriciaTrie()
    ptrie.insert("romane")
    ptrie.insert("romanus")
    ptrie.insert("romulus")
    
    print(f"Search 'romane': {ptrie.search('romane')}")
    print(f"Search 'romanus': {ptrie.search('romanus')}")
    print(f"Search 'rom': {ptrie.search('rom')}")
    
    ptrie.delete("romane")
    print(f"Search 'romane' after deletion: {ptrie.search('romane')}")