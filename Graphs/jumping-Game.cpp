/*

Chromatic Jump

There is a fun puzzle game that's getting popular among the gaming community. In this
game, the player is locked in a maze with different colored tiles. The player can only move towards
adjacent tiles, or choose to teleport to any tile with the same color. He starts from one corner and
has to reach the opposite corner. Highest score is awarded for minimum jumps.
You are a Game-Playing AI researcher looking for a fun exercise. How would you write an
algorithm that solves this puzzle to get the highest score?

• You should solve a simplified version of the puzzle. The puzzle is 1D instead of 2D/3D.
• The puzzle is represented as a string of length N with 0-9 being the only valid characters.
• Each digit represents a unique color.
• The player starts at the leftmost tile and has to reach the rightmost tile.

Example 1 455556413
Player starts at leftmost 4. Teleports to other 4. Jumps to 1. Jumps to 3. Goal Reached. Minimum jumps = 3

Example 2 0123456789
Player jumps to each adjacent tile as there are no repeated colors. Total Jumps = 9

But, Murphy's law strikes again. As you were getting ready to code the solution, you noticed
that the game doesn't store the color tiles as plainly. So, after scanning the process' memory, you
found out that for each color, it stores which locations have that color in some arbitrary order.
Locations start from 0.

For Example 1 above, this would be--
1 = {7}; 3 = {8}; 4 = {0,6}; 5 = {1,2,3,4}; 6={5}
Color 1 is present at index 7, 4 is present at 0 & 6, etc...


So, now you have two subtasks--
1. Convert the game's data structure back to a string representing the puzzle as above.
2. Solve for minimum jumps needed on this string


Input Format (exactly 10 lines)
Line 01 : a
0 a1 a2 ... -1
Line 02 : b
0 b1 b2 ... -1
...
Line 10 : j0 j1 j2 ... -1

Line i contains all indices for color i.
Each line has -1 at the end as delimiter

Output Format
<string of length N>
<minimum jumps>

Example Input
-1
7 -1
-1
8 -1
0 6 -1
4 2 3 1 -1
5 -1
-1
-1
-1

Example Output
455556413
3

Constraints
1 <= N <= 1000

Hints & Suggestions
1. Use an O(n) algorithm and corresponding Data Structures for Subtask 1.
2. You must complete this assignment using Graphs. Use appropriate Data Structures.
3. Use space-efficient Data Structures for Graphs if you can.
4. Try to use Data Structures from STL.
5. Try to use as much OOP as possible.


*/

#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>

using namespace std;


//nodes of the graph G which has adjacent nodes as in the set 
//the node with same color which it can transport has an edge in G
class Node{

public:
	//index in the final string
	int index;	
	//color of the node
	int color;
	//edges to other nodes
	set<Node*>adj;
	//source Node
	bool source;
	//end Node
	bool end;
	bool visited;
	int j;
	
	
	Node(){
		source = false;
		end = false;
		visited = false;
	}
	
};


//taking input and building the graph
int main()
{
	//vector for storing the Nodes
	vector<Node*>allNode;
	
	//map stores the set of nodes with same color
	map<int,set<Node*> >mymap;
	
	int in;
	for(in=0;in<10;in++)
	{
		int pos;
		cin>>pos;
		set<Node*> S;
		//till delimiter
		while(pos!=-1)
		{
			Node* temp = new Node;
			temp->index = pos;
			temp->color = in;
			//insert in array
			allNode.push_back(temp);
			//insert in set
			S.insert(temp);
			cin>>pos;
		}
		
		//inserting the set in map
		mymap.insert(pair<int,set<Node*> >(in,S) );
		
	
	}

	//total number of Nodes
	int size = allNode.size();
	
	//array of Nodes according to their position
	Node* arr[size];
	
	vector<Node*>::iterator it;
	for(it=allNode.begin();it!=allNode.end();it++)
	{
		int p = (*it)->index;
		if(p<size){
			arr[p] = (*it);
		}
		
	}
	//marking source and end nodes
	arr[0]->source = true;
	arr[size-1]->end = true;
	
	string num="";
	
	for(int i=0;i<size;i++)
	{
		char ch = arr[i]->color + '0';
		num+=ch;
	}

	cout<<num<<"\n";	

	//creating edges in the graph 
	//edges bw adjacent nodes and also
	// with Nodes having same color having an edge

	for(int i=0;i<size;i++)
	{
		Node* t = arr[i];
		if(i-1>=0){
			t->adj.insert(arr[i-1]);
		}
		
		if(i+1<size)
		{
			t->adj.insert(arr[i+1]);
		}
		
		//inserting the Nodes with same color 
		//i.e. making an edge bw them
		map<int,set<Node*> >::iterator p;
		p = mymap.find(t->color);
		if(p!=mymap.end())
		{
			set<Node*>::iterator itr;
			itr = (p->second).begin();
			while(itr!= (p->second).end()){
				
			
				if((*itr)->index!=t->index){
					t->adj.insert((*itr));
				}
				
					itr++;
				
				
			}
		}
	}
	
	
	//traverse the graph and find the jumps required
	
	queue<Node*>Q;
	
	arr[0]->j = 0;
	arr[0]->visited = true;
	Q.push(arr[0]);
	
	bool f = false;
	Node* last;
	
	while(Q.empty()==false)
	{
			
		Node* k = Q.front();
		Q.pop();
		
		set<Node*>::iterator z;
		z = k->adj.begin();		
		while(z!= k->adj.end())
		{
			if((*z)->visited == false){
			
				(*z)->visited = true;
				(*z)->j = k->j + 1;
		 		Q.push(*z);
			 	 	
				if((*z)->end == true)
			 	{
			 		last = (*z);
			 		f = true;	
				 	break;
				}
			
			}
			
			z++;
		}
		
		if(f==true)
			break;
			
	}	
	
	cout<< (arr[size-1]->j)<<"\n";	
	
}



