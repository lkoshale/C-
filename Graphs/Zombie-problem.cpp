
/*

Resident Final

You're a l33t h4x0r staying at a large hotel when suddenly, Zombie Apocalypse! You are
trapped inside with your friends and there are infected people in the hotel!
The deadly Z-virus spreads through contact. But it is very strange in how it spreads.
Each strain can only spread a fixed number of generations because of mutations. All of the strains
have that same number.

There are multiple strains of this virus. Only when a certain number of different strains all infect
the same individual, will (s)he turn into a zombie (after incubation).
Otherwise it's just like seasonal fevers with different symptoms.
Using advanced pattern recognition and security camera footage, you were able to find 2 things--
1. Identify who has direct contact with whom.
2. Which residents have the initial strains. (Each strain causes different symptoms and heat
	signatures for the IR cameras)

You only have a couple of hours (to be exact 2.5 hours, the exam time) left.
Hurry! There's only one small task remaining.
Find out how many of your immediate friends are safe, and whether you are the Final Uninfected Resident of
the hotel.

Directions
• The protagonist is always node 0.
• At the beginning, each strain is infecting only one resident. A resident can be the initial
	vector for multiple strains.
• There is no limit on the number of people a strain spreads to, in each generation.
• This simulation is steady state. This means, direct contacts do not change and are constant.
	The strains have already spread. You are trying to find out what the steady state is.
• For the output, you must print--
	? The number of your immediate friends that are safe (not going to become zombies)
	? A string saying either --
	? "GAME OVER" if you don't survive
	? "RESIDENT FINAL" if only you survived
	? No line if neither of the above cases


Constraints
N = 1
G = 0
1 = S = N
1 = M = S

Input Format
N (number of residents)
G (max generations for any strain)
S (number of strain types)
M (minimum # of strains for total infection)
< NxN adjacency matrix >
< S indices for the initially infected >


Output Format
< Number of immediate friends uninfected >
< GAME OVER | RESIDENT FINAL | empty >



Example Input
7 2 2 2
0 1 0 0 0 1 0
1 0 1 0 0 0 0
0 1 0 1 0 0 1
0 0 1 0 1 0 0
0 0 0 1 0 1 0
1 0 0 0 1 0 0
0 0 1 0 0 0 0
2 4


Example Output
2
GAME OVER


Explanation
You are 0. Initially, Resident 2 is infected with * strain and 4 is infected with # strain (leftmost figure).
Since we assume constant contact, * strain spreads to 3,1,6. Similarly, # strain spreads to 3,5.
These are the Generation 1 residents. Since G=2, the strains spread for one more step.
And so, the third figure. Now, since M=2, the residents who will become zombies are 0,2,3,4. 1,5,6 are safe.
Now 1,5 are the immediate friends of 0 and they are safe (not becoming zombies). Hence first line is 2.
Resident 0 is completely infected. Hence, we print "GAME OVER".

*/



#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

class Node{
public:
	int id;
	set<Node*>adj;
	bool infect;
	int pstrain;
	set<int>stype;
	
	Node(){}
	Node(int i){
		id = i;
		infect = false;
		pstrain = 0;
	}
	
	void AddEdge(Node* q){
		this->adj.insert(q);
	}
	
};

class Graph{
public:
	//CAN BE LONG
	int N; 
	int G;
	int S;
	int M;
	
	set<Node*>allNode;
	Node* root;


};

bool spread(Node* p1,Node* p2)
{
    
    bool flag = false;
		//p1-> to p2 spread
		for(auto it = p1->stype.begin();it!=p1->stype.end();it++)
		{
			
			set<int>::iterator f;
			f = p2->stype.find(*it);
			
			if(f==p2->stype.end()){
				p2->stype.insert(*it);
				p2->pstrain++;
				flag = true;
			}		
		
		}
    return flag;
}


int main(){
	long int n;
	int g,s,m;
	cin>>n>>g>>s>>m;
	
	set<Node*>hinf;
	Graph G;
	map<int,Node*>mymap;
	
	for(long int i=0;i<n;i++){
		
		Node* t = new Node(i);
		
		mymap.insert(pair<long int,Node*>(i,t));
		G.allNode.insert(t);
	}
	
	for(long int i=0;i<n;i++){
		map<int,Node*>::iterator p;
		p = mymap.find(i);
		for(long int j=0;j<n;j++){
			int k;
			cin>>k;
			if(k==1){
				map<int,Node*>::iterator q;
				q = mymap.find(j);
			
				(p->second)->AddEdge(q->second);
			}
		}
	}

	for(int i=0;i<s;i++){
		int id;
		cin>>id;
		map<int,Node*>::iterator itr;
		itr = mymap.find(id);
		if(itr!=mymap.end()){
			(itr->second)->pstrain++;
			(itr->second)->stype.insert(i);
			//in half infected people
			hinf.insert(itr->second);
		}
	}

	for(int i=0;i<g;i++){
		set<Node*>temp;
		for(auto it = hinf.begin();it!=hinf.end();++it){
			
			for(auto xyz = (*it)->adj.begin();xyz!=(*it)->adj.end();++xyz){
			    bool t;
				t = spread((*it),(*xyz));
				if(t==true)
				    temp.insert((*xyz));
			}
			
		}
		hinf = temp;
	}
	
	//printing the graph
	/*
	for(auto i = G.allNode.begin();i!=G.allNode.end();i++)
	{
	
		cout<<(*i)->id<<" "<<(*i)->pstrain <<"->";
		for(auto ir = (*i)->adj.begin();ir!=(*i)->adj.end();ir++)
		{
			cout<<(*ir)->id<<" ";
		
		}
		
		cout<<"\n";
	
	}
	*/
	map<int,Node*>::iterator u;
	u = mymap.find(0);
	
	Node* first = u->second;
	
	int count=0;
	for(auto it = first->adj.begin();it!=first->adj.end();it++)
	{
		if((*it)->stype.size() < m)
			count++;
	}
	
	cout<<count<<"\n";
	
	int counter2=0;
	for(auto i = ++(G.allNode.begin());i!=G.allNode.end();i++)
	{
		if((*i)->stype.size() >= m)
			counter2++;
	}
    
	
	if(counter2 == G.allNode.size()-1 && first->stype.size()<m){
		cout<<"RESIDENT FINAL"<<"\n";
	}
	
	if(first->stype.size()>=m){
		cout<<"GAME OVER"<<"\n";
	}
}




