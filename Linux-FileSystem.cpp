/***********************

this program mimics Linux file system basics
with help of OOP

************************/




/*

File system!

You are asked to mimic the working of the terminal of a Linux machine. You will be given a
sequence of commands which need to be executed and its corresponding output should be
printed, if applicable.

• mkdir - Creates an empty directory. Takes one argument: name of the directory.
• touch - Creates an empty file. Takes one argument: name of the file
• cd - Change to specified directory. Takes one argument: name of directory.
• pwd - Prints the path to current working directory. No arguments.
• rm - Removes a folder or a file. Takes one argument: name of file or folder.
• ls - Prints the contents of the current directory (first all the folders in alphabetical order,
	followed by all the files in alphabetical order). No arguments


Behaviours and Assumptions
• The root directory is "/" and it is initially empty.
• Print the output only for pwd and ls.
• Print the output for errors as mentioned below.
	– For mkdir/touch, if the specified folder/file already exists in the current directory, print
		"Exists".
	– For cd, if the specified folder does not exist in the current directory, print "Does not exist".
	– Similarly for rm, if the specified file/folder does not exist, print "Does not exist".
• cd .. changes current directory to the parent directory. Note that .. will be given as an
	argument only for the cd command and it cannot be used for any other command. Also,
	when cd .. is invoked in / , it should remain in / .
• Unlike Linux you can use rm to delete a file as well as folder.
• To simplify further, rm command can delete empty as well as non-empty folder.
• Folder or file names can begin with alphabet, digit or "_".
• Names are case sensitive strings and contain only [a-z, A-Z, 0-9, _ ]
• In a particular directory a file and a folder can not have same name.


Constraints
• The number of commands is unbounded.
• All commands except ls and pwd have one argument following it.


Input format
<cmd1> <arg1>
<cmd2> <arg2>
...

Output format
<result1>
<result2>
..


Sample Testcase

Input:
pwd
ls
mkdir f1
cd f1
touch file1
touch file2
mkdir f2
ls
mkdir f2
cd f2
pwd
cd f3


Output:
/
——————–> empty line (no contents in /)
f2 file1 file2
Exists
/f1/f2
Does not exist


*/




/***********************************************
****** DRIVER PROGRAM FOR OOAIA EXAM 1 *********
********* TO IMPLEMENT FILE SYSTEM *************
*** COMPILE USING: g++ driver.cpp -std=c++14 ***
************************************************/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <stdbool.h>
using namespace std;


template<class T>
bool myfun(T t1,T t2)
{

	if(t1.name.length()>t2.name.length())
		return true;
	else if(t1.name.length()<t2.name.length())
		return false;
	else if(t1.name.length()==t2.name.length())
	{
		int i;
		for(i=0;i<t1.name.length();i++)
		{
			char ch = t1.name.at(i);
			char ch2 = t2.name.at(i);
						

			if(ch>ch2){
				return true;
			}
			else if(ch<ch2)
				return false;

		}
	}
	
	return true;
}




class File{

public:
	string name;
	File(string s1){
		name = s1;
	}

};


class Folder{

	public:
		Folder* parent;
		string name;
		string path;
		
		vector<Folder> dir;
		vector<File>file;

		Folder(string s1,Folder* p)
		{
			parent = p;
			name = s1;
		}

		void addfolder(Folder x){
			dir.push_back(x);
		}

		void addfile(File x){
			file.push_back(x);
		}

		int search(string s1,string s2)
		{
			int flag=0;
			if(dir.size()!=0 && s2.compare("folder")==0)
			{
				int i;
				for(i=0;i<dir.size();i++)
				{
					if(dir[i].name.compare(s1)==0){
						flag = 1;
						break;
					}
				}
			}

			if(file.size()!=0 && s2.compare("file")==0)
			{
				int i;
				for(i=0;i<file.size();i++)
				{
					if(file[i].name.compare(s1)==0){
						flag = 1;
						break;
					}
				}
			}

			return flag;
		}		

		Folder* find(string s){

				int i;
				for(i=0;i<dir.size();i++)
				{
					if(dir[i].name.compare(s)==0){
						break;
					}
				}
				return &dir[i];
					
		}

		void sortk()
		{
			int i,j;
			
			if(dir.size()!=0){
			for(i=0;i<dir.size()-1;i++)
			{
				for(j=i;j<dir.size()-1-i;j++)
				{
					if(myfun(dir[i],dir[i+1])==true)
					{
						Folder temp = dir[i];
						dir[i] = dir[i+1];
						dir[i+1] = temp;
					}
				}
			}
			
			}

			if(file.size()!=0){
			
			for(i=0;i<file.size()-1;i++)
			{
				for(j=i;j<file.size()-1-i;j++)
				{
					if(myfun(file[i],file[i+1])==true)
					{
						File temp = file[i];
						file[i] = file[i+1];
						file[i+1] = temp;
					}
				}
			}
			
			}

		}



		
};





int main() {

	//Create a home folder called '/' which does not have 
	//a parent directory. 
	Folder home("/",NULL);
	home.path = "/";

	//Store the path to the current directory 
	vector<Folder*> env;
	
	//Map for commands to use switch-case
	string str_arr[]={"mkdir","touch","cd","pwd","rm","ls"};
	map<string,int> cmd_map;
	int i=0;
	for(auto &val:str_arr) cmd_map[val]=i++;

	Folder* ptr = &home;
	env.push_back(ptr);
	int in=0;
	
	//Taking commands as input
	string inp;
	while(getline(cin,inp)) {
		stringstream ss(inp);
		string cmd, arg;
		ss>>cmd>>arg;
		
		if(cmd.compare("mkdir")==0){
			//mkdir 
				Folder* f = env[in];
				if(f->search(arg,"folder")==0){
					Folder x(arg,f);
					if(in==0){
						x.path = f->path+arg;
					}
					else
					{
						x.path = f->path+"/"+arg;
					}

					f->addfolder(x);

				}
				else  cout<<"Exists\n";

		}else if(cmd.compare("touch")==0){
			//touch
				Folder* f1 = env[in];
				if(f1->search(arg,"file")==0 && f1->search(arg,"folder")==0){
					File y(arg);
					f1->addfile(y);
				}
				else cout<<"Exists\n";
				
		}else if(cmd.compare("cd")==0){

				if(arg.compare("..")==0){
					in = 0;
					int j;
					for(j=env.size()-1;j>0;j--)
					{
						env.pop_back();
					}
				}
				else{
					Folder* f2 = env[in];
					if(f2->search(arg,"folder")!=0){
						Folder* f3 = f2->find(arg); 
						env.push_back(f3);
						in++;
					}
					else cout<<"Does not exist\n";
				}
		}
		else if(cmd.compare("pwd")==0){
	
			cout<<env[in]->path<<"\n";
		
		}
		else if(cmd.compare("rm")==0)
		{
			//rm
			Folder* f= env[in];
			if(f->search(arg,"folder")!=0)
			{
				vector<Folder>::iterator itr;
				for(itr=f->dir.begin();itr!=f->dir.end();itr++)
				{
					if(itr->name.compare(arg)==0)
						break;
				}
				f->dir.erase(itr);

			}
			else if(f->search(arg,"file")!=0)
			{
				vector<File>::iterator p;
				for(p=f->file.begin();p!=f->file.end();p++)
				{
					if(p->name.compare(arg)==0)
						break;
				}
				f->file.erase(p);
			}
			else cout<<"Does not exist\n";
			
		}
		else if(cmd.compare("ls")==0)
		{
			int i,j;
			Folder* f= env[in];

			f->sortk();

			for(i=0;i< f->dir.size();i++)
			{
				cout<< (f->dir[i].name) <<" ";				
			}

			for(j=0;j< f->file.size();j++)
			{
				cout<<(f->file[j].name)<<" ";				
			}
			cout<<"\n";

		}
		else  cout<<"Invalid Command"<<endl; 
		

	}
					
	
	return 0;
}
