# 4600Project2
For this project, you will be working in groups of 5.

Your task is to develop a system that can determine whether or not a particular resource allocation graph represents a deadlock state. A resource allocation graph, G(V, E), can be represented as an adjacency matrix M. Below, you may find a drawing of a resource allocation graph G and an adjacency matrix M of this same graph.

Directed Graph Depicting Current System State  

Adjacency Matrix M of Graph for Current System State
P1	P2	P3	R1	R2	R3
P1	1	0	0	0	1	0
P2	0	1	0	1	0	1
P3	0	0	1	0	0	0
R1	1	0	1	1	0	0
R2	0	1	0	0	1	0
R3	0	0	1	0	0	1
 

Your program must read a text file which specifies the number of processes; the number of resources; the number of units of each type of resource; and the adjacency matrix M. Your program will determine if the state represented by M is a deadlock. You may assume that the system’s resource allocation policy is expedient.

A text file containing the information from the example above is available here.  downloadComments within this file describe its specification. Your program must be capable of reading text files which conform to the specification described within this file. Thus, your program may be graded using a different text file that conforms to this same specification.

You may choose to implement either one of the following deadlock detection mechanisms:

You may choose to implement the graph reduction algorithm to determine whether the graph represented by M is completely reducible and hence  deadlock free;
You may determine that the state represented by G or M is a deadlock state by inspecting the resource allocation graph for the existence of a knot. 
