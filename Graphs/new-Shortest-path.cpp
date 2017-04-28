
/*

Metro 2050

Sometime far far away in the future, the public transportation system has been revolutionised
with the advent of the ‘loop’ companies. Our friend Tom has landed in the year 2050 and finds
himself lost in the city of Chennai. He needs to get from one place to another, but the metro
seems to have some new rules.

The rules are listed as follows:
• Every pair of connected stations has a fare assigned to it
• The amount to be paid while traveling from station A to station B, is the difference between
the fare from A to B and the cumulative fare that has been paid to reach station A.

	fare(A,B) - total fare to reach station A

If the difference is negative, the passenger can travel free of cost from A to B.
Forgetful that he is, Tom hasn’t brought a lot of money along with him. Now he needs your
help to figure out the most cost-efficient way to go from the first station to the last station. You
are given the total number of stations N, and the fare C between the E pair of stations that are
connected.

Constraints
• 1 = N = 50000
• 1 = E = 500000
• 1 = C = 107

Input format

The first line has the values of N and E which is followed by E lines, each specifying the cost
between two stations.

<N> <E>
<station1> <station2> <C>
<station1> <station2> <C>
<station1> <station2> <C>
..
Output format
<Min-cost>

Sample Testcase
Input:
7 7
1 2 10
2 3 60
3 7 80
1 4 30
4 5 40
5 6 30
6 7 60
Output:
60

Explanation:

There are two ways to get from Station 1 to Station 7:
• 1 -> 2 -> 3 -> 7
• 1 -> 4 -> 5 -> 6 -> 7

For the first path, Tom first pays 10 units of fare to go from station 1 to 2. Next, he has to
pay 60-10 = 50 units to go from 2 to 3. Now, to go from 3 to 7, he has to pay 80-(10+50) = 20
units. Thus the total cost of this path is (10+50+20) = 80 units.
For the second path, Tom pays 30 units to reach station 4 from station 1. To go from station
4 to 5, he has to pay 40-30 = 10 units. From station 5 to 6, he has to pay 30-(30+10) = -10, but
since this is a negative value, he doesn’t pay anything to go from 5 to 6. Now, from station 6 to
7, he has to pay 60-(30+10) = 20 units. Thus the total cost becomes (30+10+20) = 60 units.
Therefore, the second path is the most cost efficient, with a cost of 60.

*/
#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<cstdlib>
#include<map>
#include<queue>

using namespace std;

// node of the graph which has an id and a map to diff nodes(edges)
// with a weight 
class Node{

public:
	//node id
	int id;
	int cost;
	
	//edges to other node with weight
	vector< pair<int,Node*> >E;
	
	//for DFS
	bool visited;
	Node(int k){
		id = k;
		visited = false;
		cost = 2147483647;
	}
	
	//add the edge to the dest Node with given cost(weight)
	void AddEdge(Node* dest,int cost){
		E.push_back(pair<int,Node*>(cost,dest));
	}
	
};

//graph which has set of nodes and mincost to travel from start to dest node
class Graph{
public:
	//total no. of nodes
	int N;
	vector<Node*>V;
	Node* start;
	Node* dest;
	int minC;
	Graph(){
		minC = 	2147483647; //int_max
	
	}
	
	//to traverse the graph and find all paths to the dest
//	void DFS(Node* cur,int c);
	
	void Dijk(Node* cur);
	
	Node* delMin()
	{
		vector<Node*>::iterator p;
		vector<Node*>::iterator m;
		p = this->V.begin();
		m = p;
		while(p!= this->V.end()){
			if((*p)->cost < (*m)->cost )
			{
				m = p;
			}
			p++;
		}
		Node* temp = (*m);
		this->V.erase(m);
		
		return temp;
	}
	
	bool operator()(Node* t1,Node* t2){
		if(t1->cost > t2->cost)
			return true;
		else
			return false;
			
	}
	

};


void Graph::Dijk(Node* root){
	
	
	root->cost = 0;
	
	priority_queue<Node*,vector<Node*>,Graph>pq;

	for(auto it = V.begin();it!=V.end();it++){
		pq.push(*it);
	}
	
	while(pq.empty()==false)
	{
		Node* t = pq.top();
		pq.pop();
		
		vector< pair<int,Node*> >::iterator itr;
		
		for(itr=t->E.begin();itr!=t->E.end();itr++)
		{
			int cst = (*itr).first - t->cost; // w-C
			if(cst < 0)
				cst = t->cost;
			else
				cst = cst + t->cost;
					
			if( (*itr).second->cost > cst)
			{
				//decrease key
			//	(*itr).second->cost = cst;
				Node* temp = (*itr).second;
				temp->cost = cst;
				pq.push(temp);
			}
			
		}
		
	}
	
	
	
}

//take input and build the graph 
int main()
{
	int n,e;
	cin>>n>>e;
	
	map<int,Node*>mymap;
	Graph G;
	G.N = n;
	
	for(int i=1;i<=n;i++){
		Node* t = new Node(i);
		mymap.insert(pair<int,Node*>(i,t));
		G.V.push_back(t);
	}
	
	
	for(int i=0;i<e;i++)
	{
		int src,dest,c;
		cin>>src>>dest>>c;
		map<int,Node*>::iterator it1;
		map<int,Node*>::iterator it2;
		it1 = mymap.find(src);
		it2 = mymap.find(dest);
		
		if(it1!=mymap.end() && it2!=mymap.end() )
		{
			(it1->second)->AddEdge((it2->second),c);
			(it2->second)->AddEdge((it1->second),c);
		}
		
	}
    
	map<int,Node*>::iterator p;
	p = mymap.find(1);
	
	map<int,Node*>::iterator q;
	q = mymap.find(n);



	G.start = p->second;
	G.dest = q->second;
		
	
	G.Dijk(p->second);
	
	G.minC = G.dest->cost;
	
	if(G.minC == 2147483647 )
	{
		cout<<"NO PATH EXISTS\n";
	}
	else
		cout<<G.minC<<"\n";
	
}



