##Google's Password Attacker algorithm

####Pseudocode
For any combination of N characters having M length, how many possible combinations are there?

A character is allowed to repeat a maximum of N - M + 1 times, referred to as the rIndex (repeat index)

The idea behind this brute-force attempt is that every root branch looks identical, so only one needs to be generated.
A tree structure is generated one level at a time (Breadth first). Because the only thing we're interested
 in is the final count, parent levels are freed after their children are generated.
 A count of the nodes per level is kept in the NodeList struct.

The function CREATE_CHILDREN adds the children to a separate list as the parents. If a node isn't 
exhausted, it will generate a child for each N. If a node is exhausted, the values of the pattern 
no longer matter, so it will generate N - (level - rIndex) children with an arbitrary pattern.
The function also increments the count for that tree level

The function CHECK_EXHAUSTED checks if a pattern seen up to that point for a certain node contains 
the maximum number of repeats (rIndex). If so, mark as exhausted.

N NodeList structs are made and an array of pointers to them is kept. 

After each level is generated, the parents are freed using FREE_LEVEL(NodeList)
```
FIND_NUM_POSSIBLE(M, N)

	
	

```
######Relevant Structs
```
NodeList{
	Node *Head
	Count
}

Node{
	Level
	Pattern
	Exhausted
	Node *Next
}
```
######Node functions
```
CREATE_CHILDREN(ParentNodeList, ChildNodeList)
//If node isn't exhausted
Node = ParentNodeList.Head
While Node = Node.Next != NULL
If !Node.Exhausted
	//Generate children for each of N
	for i to N
		ADD_NODE(
			Level = Node.Level+1
			Pattern = Pattern.append[i]
			Exhausted = CHECKEXHAUSTED(Pattern)
			ChildNodeList
		)
Else //Node exhausted
	for i to (N - (level - rIndex))
		ADD_NODE(
			Level = Node.Level+1
			Pattern = NULL
			Exhausted = true
			ChildNodeList
		)

ADD_NODE(Level, Pattern, Exhausted, NodeList)
Node New{
	Level
	Pattern
	Exhausted
	NodeList.Head
}
NodeList.Head = New
NodeList.Count++


FREE_LEVEL(NodeList)
Node = NodeList.Head
for Node in NodeList
	
	
	
```
######Helper functions
```
CHECK_EXHAUSTED(M, N, Pattern)
rIndex = M - N + 1
array[M] = {0}
repeatCount = 0
for i in Pattern
	array[i]++
for i in Pattern
	repeatCount += array[i]-1
if repeatCount == rIndex - 1 //Minus 1 because rIndex is how many times a value can repeat, while
			     //repeatCount is counting the repeats (not the first occurence)	
	return true
else 	return false

```
