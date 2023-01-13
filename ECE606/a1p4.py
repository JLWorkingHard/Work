"""
ECE606, F'22, Assignment 1, Problem 4
Template solution file.
"""

import random

"""
You are not allowed to import anything else. You are, however,
allowed to use any built-in Python 3 language feature and
data structures you like. You are allowed to define any subroutines
you like to structure your code as you like.
"""
def avgntrials(l, k):
    """
    You need to implement this method. See the handout for its specs.
    """
    n = len(l)
    loop_account = []
    for trail in range(1000):
        count = 0
        while True:
            i = random.randint(0,n-1)
            count += 1
            num = 0
            for j in l:
                if j > l[i]:
                    num += 1
            if num == k-1:
                loop_account.append(count)
                break
    return (sum(loop_account)/1000)
    
            
        
        
