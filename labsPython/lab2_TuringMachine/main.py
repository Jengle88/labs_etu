tableOfStates = {
    'q1': {'0': ['0', 1, 'q1'], '1': ['1', 1, 'q1'], '2': ['2', 1, 'q1'], '+': ['+', 1, 'q2'], '-': ['-', 1, 'q3'],
           ' ': [' ', 1, 'q1']},
    'q2': {'0': ['0', -1, 'q4'], '1': ['1', -1, 'q5'], '2': ['2', -1, 'q6']},
    'q3': {'0': ['0', -1, 'q7'], '1': ['1', -1, 'q8'], '2': ['2', -1, 'q9']},
    'q4': {'0': ['0', 0, 'q10'], '1': ['1', 0, 'q10'], '2': ['2', 0, 'q10'], '+': ['+', -1, 'q4'],
           '-': ['-', -1, 'q4']},
    'q5': {'0': ['1', 0, 'q10'], '1': ['2', 0, 'q10'], '2': ['0', -1, 'q5'], '+': ['+', -1, 'q5'],
           '-': ['-', -1, 'q5'], ' ': ['1', 0, 'q10']},
    'q6': {'0': ['2', 0, 'q10'], '1': ['0', -1, 'q5'], '2': ['1', -1, 'q5'], '+': ['+', -1, 'q6'],
           '-': ['-', -1, 'q6']},
    'q7': {'0': ['0', 0, 'q10'], '1': ['1', 0, 'q10'], '2': ['2', 0, 'q10'], '+': ['+', -1, 'q7'],
           '-': ['-', -1, 'q7']},
    'q8': {'0': ['2', -1, 'q8'], '1': ['0', 0, 'q10'], '2': ['1', 0, 'q10'], '+': ['+', -1, 'q8'],
           '-': ['-', -1, 'q8']},
    'q9': {'0': ['1', -1, 'q8'], '1': ['2', -1, 'q8'], '2': ['0', 0, 'q10'], '+': ['+', -1, 'q9'],
           '-': ['-', -1, 'q9']},
    'q10': {'0': ['0', -1, 'q10'], '1': ['1', -1, 'q10'], '2': ['2', -1, 'q10'], '+': ['+', -1, 'q10'],
            '-': ['-', -1, 'q10'], ' ': [' ', 1, 'q11']},
    'q11': {'0': [' ', 1, 'q11'], '1': ['1', 0, 'qT'], '2': ['2', 0, 'qT'], '+': ['+', -1, 'q12'],
            '-': ['-', -1, 'q12'], ' ': [' ', 0, 'qT']},
    'q12': {' ': ['0', 0, 'qT']}
    }

lenta = list(input())
state = 'q1'
endState = 'qT'
ind = 0

while state != endState:
    symb, step, chState = tableOfStates[state][lenta[ind]]
    lenta[ind] = symb
    ind += step
    state = chState

print(*lenta, sep="")
