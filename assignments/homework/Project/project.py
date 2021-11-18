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
<<<<<<< HEAD

    
    
=======
>>>>>>> ede60d50d1431f0a8ceb76b3a6ffc9def39c4b23
