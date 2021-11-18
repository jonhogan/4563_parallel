import numpy as np

#Markov chain

lexiWord = {}

def update_lexiWord(current : str, next : str)-> None:
    
    #Add new words to the words lexicon
    if current not in lexiWord:
        lexiWord.update({current:{next: 1}})
        return

    #Get the probabilities of the input word
    options = lexiWord[current]

    
    
