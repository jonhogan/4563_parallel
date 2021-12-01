# Source: https://nurdabolatov.com/parallel-processing-large-file-in-python

import multiprocessing as mp
import os
import numpy as np
import time

#Start time
start = time.time()

#Markov chain stored as adjacency list.
lexicon = {}

def update_lexicon(word : str, next_word : str) -> None:
    '''
    Add item to the lexicon:

    Args:
        word (str): Input word.
        next_word (str): Output word.
    '''

    #Add the input word to the lexicon if it in there yet.
    if word not in lexicon:
        lexicon.update({word: {next_word: 1} })
        return

    #Receive the probabilities of the input word.
    next_words = lexicon[word]

    #Check if the output word is in the propability list.
    if next_word not in next_words:
        next_words.update({next_word : 1})
    else:
        next_words.update({next_word : next_words[next_word] + 1})

    #Update the lexicon
    lexicon[word] = next_words


def process_line(line):
    line.replace('\n','')
    words =("start " + line.lower()).split(' ')
    for i in range(len(words) - 1):
        update_lexicon(words[i], words[i+1])


def parallel_read(file_name):
    # Maximum number of processes we can run at a time
    cpu_count = mp.cpu_count()

    file_size = os.path.getsize(file_name)
    chunk_size = file_size // cpu_count

    # Arguments for each chunk (eg. [('input.txt', 0, 32), ('input.txt', 32, 64)])
    chunk_args = []
    with open(file_name, 'r') as f:
        def is_start_of_line(position):
            if position == 0:
                return True
            # Check whether the previous character is EOL
            f.seek(position - 1)
            return f.read(1) == '\n'

        def get_next_line_position(position):
            # Read the current line till the end
            f.seek(position)
            f.readline()
            # Return a position after reading the line
            return f.tell()

        chunk_start = 0
        # Iterate over all chunks and construct arguments for `process_chunk`
        while chunk_start < file_size:
            chunk_end = min(file_size, chunk_start + chunk_size)

            # Make sure the chunk ends at the beginning of the next line
            while not is_start_of_line(chunk_end):
                chunk_end -= 1

            # Handle the case when a line is too long to fit the chunk size
            if chunk_start == chunk_end:
                chunk_end = get_next_line_position(chunk_end)

            # Save `process_chunk` arguments
            args = (file_name, chunk_start, chunk_end)
            chunk_args.append(args)

            # Move to the next chunk
            chunk_start = chunk_end

    with mp.Pool(cpu_count) as p:
        # Run chunks in parallel
        p.starmap(process_chunk, chunk_args)

    # results = []
    # Combine chunk results into `results`
    # for chunk_result in chunk_results:
    #     for result in chunk_result:
    #         results.append(result)
    # return results

def process_chunk(file_name, chunk_start, chunk_end):
    with open(file_name, 'r') as f:
        # Moving stream position to `chunk_start`
        f.seek(chunk_start)

        # Read and process lines until `chunk_end`
        for line in f:
            chunk_start += len(line)
            if chunk_start > chunk_end:
                break
            process_line(line)


if __name__ == '__main__':
    
    parallel_read('dataset2.txt')
    #Adjust probability
    for word, transition in lexicon.items():
        transition = dict((key, value / sum(transition.values())) for key, value in transition.items())
        lexicon[word] = transition

    #Predict next word
    #line = input('Enter first word:  ')
    #word = line.strip().split(' ')[-1]

    #print(lexicon)
    word = 'start'
    predicted = "Sup"
    newString = ''
    count = 0

    while predicted != None:
        if word not in lexicon:
            #print('Word not found')
            predicted = None
            if newString.replace(" ","") == "":
                word = "start"
                predicted = "sup"
            
            else:
                print(newString)
        else:
            next_words = lexicon[word]
            predicted = np.random.choice(list(next_words.keys()), p=list(next_words.values()))
            #print(word + ' ' + predicted)
            #print('Adding word to string')
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