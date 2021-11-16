class LetterNode:
    letter = ''
    count = 0
    def __ini__(self, text, firstword = False, endword = False ):
        self.word = text
        letter = self.word[0]