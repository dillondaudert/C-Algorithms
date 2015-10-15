##Maximum Subarray Algorithm

From the Introduction to Algorithms book, 
a recursive, divide-and-conquer algorithm with efficiency big-theta (n^2) was provided, 
and hints were given to develop the following:

The algorithm solves the maximum subarray problem in linear time, big-theta (n).

####Pseudocode

The procedure FIND_MAX_SUBARRAY takes the array A and its length, A.length, and returns
the left index, right index and the sum of the maximum subarray within A.
The array index begins at 1

```
FIND_MAX_SUBARRAY(A, A.length)
max-left = max-left-here = 1
max-right = 1
max-sum = max-sum-here = A[1]
index = 2
for index to n
    if A[index] < max-sum-here + A[index]
        max-sum-here = max-sum-here + A[index]
    else
        max-left-here = index
        max-sum-here = A[index]
    if max-sum-here < max-sum

    else
        max-sum = max-sum-here
        max-left = max-left-here
        max-right = index 
return max-left, max-right, max-sum
```
