import numpy as np

# Markov chain stored as adjacency list.
lexicon = {}

def update_lexicon(current : str, next_word : str) -> None:
    """Add item to the lexicon.

    Args:
        current (str): Input word.
        next_word (str): Output word.
    """

    # Add the input word to the lexicon if it in there yet.
    if current not in lexicon:
        lexicon.update({current: {next_word: 1} })
        return

    # Recieve the probabilties of the input word.
    options = lexicon[current]

    # Check if the output word is in the propability list.
    if next_word not in options:
        options.update({next_word : 1})
    else:
        options.update({next_word : options[next_word] + 1})

    # Update the lexicon
    lexicon[current] = options

# Populate lexicon
with open('dataset.txt', 'r') as dataset:
    for line in dataset:
        words = line.strip().split(' ')
        for i in range(len(words) - 1):
            update_lexicon(words[i], words[i+1])
        
# Adjust propability
for word, transition in lexicon.items():
    transition = dict((key, value / sum(transition.values())) for key, value in transition.items())
    lexicon[word] = transition

# Predict next word
line = input('> ')
word = line.strip().split(' ')[-1]
predicted = "Sup"
while predicted != None:
    if word not in lexicon:
        print('Word not found')
        predicted = None
    else:
    
        options = lexicon[word]
        predicted = np.random.choice(list(options.keys()), p=list(options.values()))
        print(word + ' ' + predicted)
        word = predicted
          