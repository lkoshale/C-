
/*

The Last Resort

Brief Story

You are an intern working for a company that specializes in multi-faceted projects. You are
associated with two teams, a backend team working on a new Distributed File System, and the
frontend team which is making a GUI. There is a clash of interests between those two groups and
you have to satisfy both their needs, as you are the acting bridge between the two teams. Your
supervisor tells you, "You are their last resort".
Goal

You have to maintain a sorted list of files/folders, with no nesting (no tree, just a list). You are
given an unchangeable sort() function. You need not write any sorting code. Just reuse this.

template <typename T, class F>
void sort(std::vector<T> &data, F& cmp) {
	int L = data.size();
	for(int i=0; i<L; ++i)
		for(int j=i; j>0 && cmp(data[j],data[j-1]); --j)
			std::swap(data[j-1],data[j]);
}


The sort() accepts a vector of data to be sorted and a compare Functor 1.
Your job is mainly to implement the compare Functor with the details that follow. And some extra
code for IO.
Input Format
You are given a sequence of requests from both Backend and GUI. They will be explained later.
1. append requests from backend. May appear multiple times.
2. resort (pronounced Re-sort) requests from UI. May appear any number of times.
3. end for end of input. Appears only once at the end.
4. Each line is one of the following -
append <type> <name>
resort <flag1> <flag2>
end
Output Format
For each line of input, you have to print a sorted list of strings in a single line. For end you have to
print a number (explained later). The strings are names only. No types need to be printed.

Detailed Explanation

append:
• This command means you have to append a file/folder to your sorted list.
• type can be either file | folder
• name is a string with characters from "A-Z a-z 0-9 _"

resort:
• This command means you have to Re-Sort your current list based on certain boolean flags.
• flag1 & flag2 can be either Y | N. flag1 takes priority.
? flag1 ? Folders First
? flag2 ? Case Sensitive
• flag1 states that all folders must be printed first in the sorted list.
? flag1 = Y means print all folders first
? flag1 = N means files and folders are interleaved
• flag2 is the case sensitivity of the sort after arranging according to flag1.
? flag2 = Y means the sort is case sensitive
? flag2 = N means the sort is case insensitive
• Relative ordering among characters is Asciibetical (ascii values are compared)
• flag1 & flag2 are initialized to N at the beginning.

compare Functor:

• You have to write a single stateful Functor that can be given as a parameter to the
unchangeable sort(). The compare should follow Strict Weak Ordering like those in STL.
• It should adjust its ordering based on the flags every time a resort appears in input.
• It should cumulatively keep track of how many times it is called.
The number at the end is this number.


Sample Input
append folder KB9
append file 7Bw
append folder ew
append file Ln
append folder Kb9
resort Y Y
end

Sample Output
KB9
7Bw KB9
7Bw ew KB9
7Bw ew KB9 Ln
7Bw ew KB9 Kb9 Ln
KB9 Kb9 ew 7Bw Ln
19




*/


#include<iostream>
#include<string>
#include<functional>
#include<stdbool.h>
#include<cstring>
#include<cctype>
#include<vector>
#include<sstream>


using namespace std;


//directory class to store the file or folder type and its name with default constructor
class directory
{
	public:
		//name of folder or file
		string name;
		//type folder or file
		string type;

	//constructor
	directory(string n,string t){
		name = n;
		type = t;
	}

};

/*
class compare which is a functor with overloaded call operator
and is made adaptable to STL functional by inheriting binary_functions class
*/
class Compare
{
	private:
		//flags 
		bool flag1;
		bool flag2;

	public:
	 		int call;
			//constructor
			Compare(bool f1=false,bool f2=false)
			{
				flag1 = f1;
				flag2 = f2;
				call = 0;
			}
			
			//update the private flags as input
			void update_flag(bool f1,bool f2)
			{
				flag1 = f1;
				flag2 = f2;
			}

			//call operator overloaded 
			bool operator() (directory d1,directory d2);
		
		

};

/*
call operator overloaded to make the object a functor with arguments as
object of directory class and returning value true or false
*/
bool Compare :: operator()(directory d1,directory d2){

		//no of calls
		call++;

		//converting to c string
		const char* c1 = d1.name.c_str();
		const char* c2 = d2.name.c_str();
		
		int len;
		
	 	if(d1.name.length()>d2.name.length())
			len = 1;
		else if(d1.name.length()<d2.name.length())
			len = -1;
			
	//if both flags false
	if(flag1==false && flag2==false){
		int i;
		bool f = false;
		bool eq;
		
		//iterate to all characters in string
		for(i=0;i<d1.name.length() && i<d2.name.length();i++)
		{
			//converted to lower case and storing ascii values
			int ch1 = (int)tolower(c1[i]); 		
			int ch2 = (int)tolower(c2[i]);

			// if ch1 ascii value less return true			
			if(ch1<ch2){
				f = true;
				eq = false;
				break;
			}
			else if(ch1>ch2)
			{
				f = false;
				eq = false;
				break;					
			}	
			else if(ch1==ch2)
			{
				eq=true;	
			}	
			//if equal next char
		}
		
		if(eq==true)
		{
			if(len==-1)
				return true;
			else 
				return false;
		}
		else 
			return f;
	}
	else if(flag1==true && flag2==false)
	{
		int i;	
		bool f = false;
		bool eq;
		
		for(i=0;i<d1.name.length() && i<d2.name.length();i++)
		{
			int ch1 = (int)tolower(c1[i]); 		//if unchangeable c remains unchange
			int ch2 = (int)tolower(c2[i]);

			if(d1.type.compare("folder")==0 && d2.type.compare("folder")!=0)
			{
				f = true;
				eq=false;
				break;
			}
			else if(d1.type.compare("folder")!=0 && d2.type.compare("folder")==0)
			{
				f= false;
				eq=false;
				break;
			}
			else
			{
				if(ch1<ch2){
					f = true;
					eq = false;
					break;
				}
				else if(ch1>ch2)
				{
					f = false;
					eq = false;
					break;					
				}
				else if(ch1==ch2)
				{
					eq = true;
				}	
				
			}
	
		}
		
		if(eq==true)
		{
			if(len==-1)
				return true;
			else 
				return false;
		}
		else 
			return f;
		
	}
	else if(flag1==false && flag2==true)
	{
		int i;	
		bool f = false;
		bool eq;
		for(i=0;i<d1.name.length() && i<d2.name.length();i++)
		{
			int ch1 = (int)c1[i]; 		
			int ch2 = (int)c2[i];
			
			if(ch1<ch2){
				f = true;
				eq = false;
				break;
			}
			else if(ch1>ch2)
			{
				f = false;
				eq= false;
				break;					
			}
			else if(ch1==ch2)
				eq= true;
		}
		
	if(eq==true)
		{
			if(len==-1)
				return true;
			else 
				return false;
		}
		else 
			return f;
	}
	else
	{
		int i;	
		bool f = false;
		bool eq;
		for(i=0;i<d1.name.length() && i<d2.name.length();i++)
		{
			int ch1 = (int)c1[i]; 		
			int ch2 = (int)c2[i];
			
			if(d1.type.compare("folder")==0 && d2.type.compare("folder")!=0)
			{
				f = true;
				eq=false;
				break;
			}
			else if(d1.type.compare("folder")!=0 && d2.type.compare("folder")==0)
			{
				f= false;
				eq=false;
				break;
			}
			else
			{
				if(ch1<ch2){
					f = true;
					eq = false;
					break;
				}
				else if(ch1>ch2)
				{
					f = false;
					eq = false;
					break;					
				}	
				else if(ch1==ch2)
					eq = true;
			}
		}
		if(eq==true)
		{
			if(len==-1)
				return true;
			else 
				return false;
		}
		else 
			return f;
	}

}

//given sort function
template <typename T, class F>
void sort(std::vector<T> &data, F& cmp) {
int L = data.size();
for(int i=0; i<L; ++i)
for(int j=i; j>0 && cmp(data[j],data[j-1]); --j)
std::swap(data[j-1],data[j]);
}

void print(vector<directory> vec)
{
	vector<directory>::iterator itr;
	for(itr = vec.begin();itr<vec.end();itr++)
	{
		cout<<(*itr).name<<" ";
	}
	cout<<"\n";
}

//main function
int main()
{
	Compare cmp;

	vector<directory>vec;

	string line;
	while(getline(cin,line))
	{
		string s1,s2,s3;
		stringstream ss(line);

		ss>>s1>>s2>>s3;

		if(s1.compare("end")==0)
		{
			cout<<cmp.call<<"\n";
			break;
		}
		else if(s1.compare("append")==0)
		{
			directory temp(s3,s2);
			vec.push_back(temp);
			sort(vec,cmp);
			print(vec);

		}
		else if(s1.compare("resort")==0)
		{
			if(s2.compare("Y")==0 && s3.compare("Y")==0)
				cmp.update_flag(true,true);
			else if(s2.compare("N")==0 && s3.compare("Y")==0)
				cmp.update_flag(false,true);
			else if(s2.compare("Y")==0 && s3.compare("N")==0)
				cmp.update_flag(true,false);
			else if(s2.compare("N")==0 && s3.compare("N")==0)
				cmp.update_flag(false,false);			
			
			sort(vec,cmp);
			print(vec);
			
		}
				
		
	}
}


