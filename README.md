Problem description:
	N numbers sum to K, find all possible numbers Used brute force method with recursion.


General Idea: 
	for each combination return from n-1, insert a new comma after the last comma of each combination. 
	for example. lets say n-1 returns a collection of combinations. 
	One of them is 111,,11,1111. The last comma is at 6. 
	so we will insert a new comma at 6, 7, 8, ..., 10 resepectively and push each of these new collection. 
	Then return the collection

Algorithm:
  //base case n==2:
  //  for i from 0 to k:
  //    result.push([i,j-i])
  
  //get prev = (k,n-1)
  //foreach solution in prev    //  
  //      for i from solution.last() to k
  //          newSol = solution
  //          newSol.push(i)
  //          result.push(newSol)
  //return result


To compile:
	g++ PossibleSum.cpp -o demo
