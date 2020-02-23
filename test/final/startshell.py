import random

QUESTION_FILE = './q.txt'
AC = '\033[34mAccepted\033[0m'

questionnaire = open(QUESTION_FILE, 'r')

Q = []
R = [
     '\033[31mWrong Answer\033[0m',
     '\033[33mTime Limit Exceeded\033[0m', 
     '\033[35mMemory Limit Exceeded\033[0m',
     '\033[37mCompiliation Error\033[0m', 
     '\033[33mRuntime Error\033[0m', 
     '\033[32mLJ\'s Error\033[0m',
     '\033[36mRP Error\033[0m'
    ]

for question in questionnaire:
    Q.append(question[ : len(question) - 1])

print(Q[random.randrange(0, len(Q))])

while True:
    try:
        answer = input('[yes/no] ')

        if answer != 'yes':
            print(R[random.randrange(0, len(R))])
        else:
            print(AC)
            break
    except:
        pass
