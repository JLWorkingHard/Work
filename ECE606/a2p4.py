"""
ECE606, F'22, Assignment 2, Problem 4
Template solution file.
"""

from math import log2

"""
You are not allowed to import anything else. You are, however,
allowed to use any built-in Python 3 language feature and
data structures you like. You are allowed to define any subroutines
you like to structure your code as you like.
"""
class TreeNode(object):
    def __init__(self, val=None, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    def print_by_order(self):
        li = []
        queue = [self]
        while queue:
            current = queue.pop(0)
            li.append(current.val)
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)      
        while(li[-1] == -1):
            li.pop()
        return li

class Solution(object):
    def sort_list(self,l):
        li = []
        for i in l:
            if i != -1:
                li.append(i)
        li = sorted(li)
        return li
    def opt_BST(self,partNode):
        if len(partNode) == 1:
            return TreeNode(partNode[0],left=TreeNode(-1),right=TreeNode(-1))
        middle = int(len(partNode)/2)
        node = TreeNode(partNode[middle])
        node.left = self.opt_BST(partNode[0:middle])
        if middle == len(partNode)-1:
            node.right = TreeNode(-1)
        else:
            node.right = self.opt_BST(partNode[middle+1:])
        return node
               
def optbst(t):
    """
    You need to implement this method. See the handout for its specs.
    """
    S = Solution()
    t = S.sort_list(t)
    node = S.opt_BST(t)
    l = node.print_by_order()
    return l