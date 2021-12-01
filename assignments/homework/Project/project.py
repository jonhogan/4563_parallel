import numpy as np
import time

#Start time
start = time.time()

#Markov chain stored as adjacency list.
lexicon = {}

def update_lexicon(word : str, next_word : str) -> None:
    '''
    Add item to the lexicon.

    Args:
        word (str): Input word.
        next_word (str): Output word.
    '''

    #Add the input word to the lexicon if it in there yet.
    if word not in lexicon:
        lexicon.update({word: {next_word: 1} })
        return

    #Receive te probabilities of the input word.
    next_words = lexicon[word]

    #Check if the output word is in the propability list.
    if next_word not in next_words:
        next_words.update({next_word : 1})
    else:
        next_words.update({next_word : next_words[next_word] + 1})

    #Update the lexicon
    lexicon[word] = next_words


#Populate lexicon
with open('dataset2.txt', 'r') as dataset:
    for line in dataset:
        line.replace('\n','')
        words =("start " + line.lower()).split(' ')
        for i in range(len(words) - 1):
            update_lexicon(words[i], words[i+1])
        
#Adjust probability
for word, transition in lexicon.items():
    transition = dict((key, value / sum(transition.values())) for key, value in transition.items())
    lexicon[word] = transition

word = 'start'
predicted = "Sup"
newString = ''
count = 0

while predicted != None:
    if word not in lexicon:
        predicted = None
        if newString.replace(" ","") == "":
          word = "start"
          predicted = "sup"
        
        else:
          print(newString)
    else:
    
        next_words = lexicon[word]
        predicted = np.random.choice(list(next_words.keys()), p=list(next_words.values()))
        if predicted == '\n':
          word = "start"
          predicted = "sup"
          count = 0
        elif predicted == '':
          word = "start"
          predicted = "sup"
          count = 0
        elif predicted == ' ':
          word = "start"
          predicted = "sup"
          count = 0
        elif count == 0:
          newString = newString + predicted
          word = predicted
        else:
           newString = newString + ' ' + predicted
           word = predicted
    count += 1

end = time.time()
timer = (end - start)*1000

print('Program ran in {:%.3f} milliseconds'.format(timer)) 