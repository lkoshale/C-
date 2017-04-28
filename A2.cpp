/*

Eso Gates

You are working in a Digital Circuit Testing Facility with your boss Mr. Eso Terric. He has some
very peculiar habits, and you are almost always dragged into the midst of them. Mr. Eso has heard
about the new-fangled Object Oriented Paradigm and C++ (You're late Eso!), and wants you to port
one of their existing software testing systems to make use of it. The subsystem you were tasked with is
input simulation. You will be given a combinational circuit and inputs to that circuit. You have to
calculate its output. But there are a lot of constraints because Mr. Eso likes micromanaging you.
Mr. Eso wants you to make the following assumptions --


1. There won't be any loops in the circuit. The circuit will be static.

2. There will be at most 200 gates of each type. Each gate can have any number of inputs (=2).

3. There is only 1 output gate. Inputs may be given in any arbitrary order.
Mr. Eso wants you to follow these design constraints --

	1) Create an extensible hierarchy of BasicGates, which currently have at least the following
	gates AND,OR,XOR,NAND,NOR,EMIT. Your code must easily accommodate other gates
	which will be available following an upgrade to the Fabrication Unit (FU isn't part of the
	assignment).
	2) Each BasicGate has to satisfy the following properties -
		a) They must overload the += operator to add new gates as inputs.
			For example, G1 += G2 means that G2's output is an input to G1.
		b) They must have an output() function which calculates the output of a specific gate based
			on whatever number of inputs the gate has.
	3) The main() function must only be this --
		Here read() parses the input file and returns a pointer(why?) to the single output gate.
	4) EMIT is a special kind of gate. Instead of giving inputs seperately, Mr. Eso wants you to
	   incorporate inputs via BasicGates. EMITs do not take in any inputs.
	5) Each gate will have a unique ID except EMIT. ID is ( gate_type number )
	{AND 1, AND 2, NOR 1, XOR 1, NAND 1} is one subset of valid IDs.
		EMIT will always be either a 0 or 1.
		int main() {
			BasicGate *last_gate = read();
			cout << last_gate->output() << endl;
			return 0;
			}
			
Input Format
<gate_type> <gate_id>
<gate1_type> <gate1_id> <gate2_type> <gate2_id>
<gate1_type> <gate1_id> <gate2_type> <gate2_id>
...

Line 1 contains the final gate whose output you must calculate.
Each of the lines 2,3,... (unbounded) means that gate1's output is joined to one of gate2's inputs.
Gate ID may be any number between 0 to 199. Gate Type is AND,OR,XOR,NAND,NOR,EMIT.
EMIT 0 is boolean 0 and EMIT 1 is boolean 1. Input ends when EOF is reached.	
		

*/

#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

#define SIZE 1200

class BasicGate;

using namespace std;

map<string,BasicGate*>map1;


/*Base Class which have of Basic Gates with basic traits of gates  */
class BasicGate
{
		

	protected:
		string name;	//to map each gate
		vector <BasicGate*> in;
		int id;		//id of the
		
				

	public:
		virtual bool output(){return true;}		//output method overridden in every child of BasicGate class 

		void operator +=(BasicGate *B)
 		{
			in.push_back(B);														
		}

		

};


/***********
Each child class which inherits the basic gates override the 
output function and does the bitwise operation on the array of inputs 
it has by calling the input gate's output fn which is connected to it recursively
which finally ends in the EMIT gate
***********/


/*
	gate emit which doesnt have any input and initailzed by the constructor 
	and return boolean 0 or 1
*/
class EMIT : public BasicGate
{
	bool value;		//value to store and return the emit bool value

	public:
		EMIT(bool i){		//constructor
		value = i;
		name = "EMIT";
		}

		/*the ouput function which returns the value*/
		bool output(){return value;}
};


/*
And gate derives the Basic Gate in protected mode
*/
class AND : public BasicGate
{
	public:
		//constructor to intialise the name and id and its input array
		AND(string st,int x ){
		id = x;
		name = st;
		}

		/*recursively calls the output fn of its input gates*/
		bool output()
		{
			bool out = in[0]->output() & in[1]->output();
			for(int i=2;i<in.size();i++)
			{
				out = out & in[i]->output(); 
			}

			return out;
		}
		
};

//or gate of typ basic gate 
class OR : public BasicGate
{
	public:
		
		OR(string st,int x ){
		id = x;
		name = st;
		}
		
	
			/*recursively calls the output fn of its input gates*/
		bool output()
		{
			bool out = 0;
			for(int i=0;i<in.size();i++)
			{
				out = out | in[i]->output(); 
			}

			return out;
		}			
		

};

class XOR : public BasicGate
{
	string name;
	public:
		XOR(string st,int x ){
		id = x;
		name = st;
		}
		
	/*recursively calls the output fn of its input gates*/
		bool output()
		{
			bool out = in[0]->output() ^ in[1]->output();
			for(int i=2;i<in.size();i++)
			{
				out = out ^ in[i]->output(); 
			}

			return out;
		}
};

class NAND : public BasicGate
{
	string name;
	public:
		NAND(string st,int x ){
		id = x;
		name = st;
		}
		
	/*recursively calls the output fn of its input gates*/
		bool output()
		{
			bool out = in[0]->output() & in[1]->output();
			
			for(int i=2;i<in.size();i++)
			{
				out = out & in[i]->output(); 				
			}
			out=!out;

			return out;
		}
};

class NOR : public BasicGate
{
	string name;
	public:
		NOR(string st,int x ){
		id = x;
		name = st;
		}
		
		bool output()
		{
			bool out = in[0]->output() | in[1]->output();		
			
			for(int i=2;i<in.size();i++)
			{
				out = out | in[i]->output(); 
				
			}
			out=!out;

			return out;
		}
};

BasicGate* gtype(string str,int i)
{
	BasicGate* ptr;
	
	string xyz = str+to_string(i);
	
   if(str.compare("EMIT")==0)
	{
		bool b1;

		if(i==0)
			b1 = false;
		else 
			b1 = true;
			
		ptr = new EMIT(b1);
		
	}
	else if(str.compare("AND")==0)
	{
		
	ptr = new AND(xyz,i);
	

	}else if(str.compare("OR")==0)
	{
	
		ptr = new OR(xyz,i);
		
	}else if(str.compare("XOR")==0)
	{ptr = new XOR(xyz,i);
		
	}else if(str.compare("NAND")==0)
	{
		
		ptr = new NAND(xyz,i);
	}
	else if(str.compare("NOR")==0)
	{ptr = new NOR(xyz,i);
	}

	return ptr;
}


/* a friend function which takes the input and parse it and store in the map1 of basicgate class 
   and returns a pointer of BasicGate* which points to the object of any of its child class
   which is the last gate of given circuit		
*/
BasicGate* read()
{
		string n1,n2,n3;
		int i1,i2,i3;
		string key1,key2;
		
		BasicGate *g2, *g3;
		
		cin>>n1>>i1;
		BasicGate* g1 =gtype(n1,i1);
		map1.insert(pair<string,BasicGate*>( n1+to_string(i1), g1 ) );
		
		while(cin>>n2>>i2>>n3>>i3)
		{
		
		key1 =  n2+to_string(i2);
		map<string,BasicGate*>::iterator p;
			
		p = map1.find(key1);
	
			if(p==map1.end())
			{
			 g2 = gtype(n2,i2);
			 map1.insert(pair<string,BasicGate*>(key1,g2));
			}
			else
				g2 = (*p).second;
					
		key2 = n3+to_string(i3);		
		
		p = map1.find(key2);
		
			if(p==map1.end())
			{
			 g3 =gtype(n3,i3);
			map1.insert(pair<string,BasicGate*>(key2,g3));
			}
			else
				g3 = (*p).second;
			
			(*g3)+=(g2);
			
		}		
		
		return g1;
		
} 

//main fn
int main() {
BasicGate *last_gate = read();
cout << last_gate->output() << endl;
return 0;
}


