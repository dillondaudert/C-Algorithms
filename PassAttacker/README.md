# Password Attacker
An answer to one of Google's code test at code.google.com

**passAttack.c** is a reduced version of my first attempt using a full tree structure, 
since in working through it the first time, I came up with the second. Unfortunately, 
it is still not efficient enough to solve the problem with 1 <= N <= M <= ~14.
 
We want to count all permutations of a password given its length M and the number of unique characters in it N. To calculate this problem, we do the following: 
Find all possible permutations of passwords (N^M). These are the passwords that use from 0 - (M-1) times each character. Then subtract all passwords that only use 1 unique character (There are N choose 1 of these). Then subtract all those that only use 2 unique characters (N choose 2 * 2^M). Then those that only use 3 unique characters (N choose 3 * 3^M) ... Then those that only use N-1 characters (N choose N-1 * (N-1)^M).
