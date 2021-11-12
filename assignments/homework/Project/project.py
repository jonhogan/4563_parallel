class Word:
    def __ini__(self, text, firstword = False, endword = False )
        self.word = text

class TrieNode:
    def __init__(self, word = '', increment = 0):
        self.word = [word.word]#Not sure this is right
        self.word.append(word)
        self.child = dict()
        self.count += increment

class TrieTree:
    def __init__(self):
        self.root = TrieNode()

