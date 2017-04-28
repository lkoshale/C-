/*
Eso Sort!


Mr Eso Teric is back again! As the HR of the company Drump Technologies is on a maternity
leave, the company’s CEO Mr Drump has hired a replacement, Mr Flinton. Unfortunately, Mr
Flinton messed up all the employee records of the company. Now it’s up to Mr Eso to fix these
records, since he has done a wonderful job last time (according to him ;) )
Each employee has an ID associated with them and a certain position in the company. Their
salary per hour is fixed based on their position. A record of all the employees were sorted in a
manner suitable to Mr Drump, but Mr Flinton has rearranged them.
Mr Eso needs to rearrange it back to how Mr Drump wanted it, and that is, in decreasing
order of their salary for this year. However note that only the salary per hour is fixed, but the
total salary earned by each employee depends on the time they have put in for the company!

The following information is given as input:
• The positions and the salary earned per hour by the employees belonging to this position.
• Employee records in increasing order of their employee ID.
• The sorting algorithm Mr Eso needs to use in order to solve this problem ("Insertion",
	"Merge" or "Selection").
• A weekly log which can be used to find the duration each employee has worked this year.
	Here are a few points to note while sorting:
• If two employees have the same salary this year, the one with the higher position comes
	first (decreasing hierarchy of positions is given as input).
• If the position and salary are the same, the one whose name comes first in alphabetical
	order comes first.
• If the names are same as well, the one with the smaller employee ID comes first.
	Mr Drump also wants to know the "swap number" which is the
• number of swaps for selection sort
• number of shifts for insertion sort
• number of inversions for merge sort

you need to perform in order to sort the employee records (we have mentioned the sorting
algorithm, so this number should be deterministic). Your final output must contain this number
and a list of all the employee IDs in the required order. Also note that, the names of employees
and their positions are a single alphanumeric string and would never start with a digit.

Mr Drump also wants you to use the following main function.

int main() {
	pair<vector<Employee>, string> records = read();
	int (*sort)(vector<Employee>&); //Function pointer
	
	if(records.second=="Merge")
		sort = merge_sort;
	else if(records.second=="Insertion")
		sort = insertion_sort;
	else sort = selection_sort;
		cout<<sort(records.first)<<endl;

	print(records.first);
	
	return 0;
}

Design

We expect you to include the following design implementations in your code:
• Comparison between two employees must be done using the ’<’ or ’>’ operator only.
• Your print and sort functions must work for any kinds of input. For example, the same
function should be used for sorting integers.


Input format
<position1> <salary_per_hour1>
<position2> <salary_per_hour2>
...
...
<employee_id1> <name1> <position1>
<employee_id2> <name2> <position2>
...
...
<sorting_algorithm>
<employee_id1> <week_no1> <hours_per_week1>
<employee_id2> <week_no2> <hours_per_week2>
...
...


Output format
<swap_number>
<employee_id1> <employee_id2> ...

Sample Testcase

Input:
Manager 1000
SDE1 100
SDE2 90
1001 Raman Manager
1002 Manas SDE2
1003 Trisha SDE1
Selection
1001 1 20
1001 4 12
1002 2 10
1002 1 15
1003 1 20
1003 2 11

Output:
1
1001 1003 1002

Explanation:
Raman has a total salary of (20+12)*1000 = 32000. Similarly Manas has a salary of 2250 and
Trisha, 3100. Hence the decreasing order of salaries is <1001 1003 1002>, and the number of
swaps while performing selection sort on <1001 1002 1003> to get <1001 1003 1002> is 1.


*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<cstdlib>
#include<sstream>


using namespace std;

// a global variable to store number of swaps while sorting
int swap_no = 0;

//class employe to store all the credential of any employee
class Employee;

//vector to store the objects of class Employee to store and sort it
vector<Employee> employee;

//class employe to store all the credential of any employee
class Employee{
	
	public:
		//employee id position
		string id;
		string position;

		//position num is heirachy of position based on input
		// the one input first will have lower value -> hiegher heirachy
		int position_num;
		
		//employee name,salary per hour and total salary
		string name;
		int sal_per_hr;
		int total_hr;
		int total_sal;
		
		/*
		'>' operator overloadaed to compare two employee based on its salary 
		,name,postion,id 
		*/
		bool operator>(Employee e);
};


/*
'>' operator overloadaed to compare two employee based on its salary 
,name,postion,id 
*/
bool Employee :: operator>(Employee e)
{
	if(this->total_sal > e.total_sal)
		return true;
	else if(this->total_sal < e.total_sal)
		return false;
	else if(this->position_num < e.position_num)
		return true;
	else if(this->position_num > e.position_num)
		return false;
	else if(this->name.compare(e.name)< 0)
		return true;
	else if(this->name.compare(e.name)> 0)
		return false;
	else if(this->id.compare(e.id)<0)
		return true;
	else if(this->id.compare(e.id)>0)	
		return false;
    	else 
        	return false;
        
}

//copy content Employee pointer to employee object and return it 
Employee cpy(Employee* e)
{
	Employee em;
	
	em.id = e->id;
	em.position = e->position;
	em.position_num = e->position_num;
	em.name = e->name;
	em.sal_per_hr = e->sal_per_hr;
	em.total_hr = e->total_hr;

	em.total_sal = e->total_hr * e->sal_per_hr;

	return em;	
}



//parse the input and return a pair of vector and string(nbame of sorting algorithm)
// also add the Employee object in vector of Employee
pair< vector<Employee>,string > read()
{

	map< string,pair<int,int> >mymap1;//position and slalry and object
	map<string,Employee*>mymap2; 	//id to position 

	vector<Employee>emp;

	string line;
	string algo;
	int num =1;
	while(getline(cin,line))
	{
		
		string s1,s2,s3;
		stringstream ss(line);
	
		ss>>s1>>s2>>s3;	

		if(s2.empty()&&s3.empty())
		{
			algo = s1;			
		}
		else if(s3.empty() && !isdigit(s1[0]))
		{
			
			int pay = atoi(s2.c_str());
			pair<int,int> n = make_pair(pay,num);
		
			mymap1.insert(pair<string,pair<int,int> >(s1,n));
			num=num+1;
		}
		else if(isdigit(s1[0]) && !isdigit(s2[0]))
		{
			
			
			string id = s1;
			
			map<string,pair<int,int> >::iterator p;
			p = mymap1.find(s3);
			
			Employee* e = new Employee();
			e->id = id;
			e->position = s3;
			e->name = s2;
			e->sal_per_hr = (p->second).first;
			e->total_hr = 0;
			e->total_sal = 0;
			e->position_num = (p->second).second;
			
			mymap2.insert(pair<string,Employee*>(id,e));
		}
		else if(isdigit(s1[0])&&isdigit(s2[0])&&isdigit(s3[0]))
		{	string id = s1;
			int hr = atoi(s3.c_str());
			map<string,Employee*>::iterator it;		
			it = mymap2.find(id);
			(it->second)->total_hr += hr;
			
		}

	}
		
	map<string,Employee*>::iterator itr1;
		
	for(itr1 = mymap2.begin();itr1!=mymap2.end();itr1++)
	{
		Employee t = cpy(itr1->second);	
		emp.push_back(t);			
	}

	return make_pair(emp,algo);	
}

//a generic template T 
template<class T>

/**
insertion_sort function returning the total number of shift
and input is vector of generic data type to sort
**/
int insertion_sort(vector<T>& emp)
{
	int i,j;
	T temp;
	
	//iterarte from 2nd element to last
	for(i=1;i<emp.size();i++)
	{
		
		temp = emp[i];
		j = i-1;
		// compare with the elements above it if its greater then move it up
		while(j>=0&&(temp>emp[j]))
		{
			//shifting up
			emp[j+1] = emp[j];
			j--;
			swap_no++;
		}
		
		emp[j+1]=temp;

	}
	
	return swap_no;
}

/**
selection sort function returning the total number of swaps
argument as a vector of generic data typ
iterate for each element till last
and finding the maximum number below it then swaping it
**/
template<class T>
int selection_sort(vector<T>& emp )
{
	int i, j,max_index;

	for(i=0;i<emp.size();i++)
	{
		max_index = i;
	
		for(j=i+1;j<emp.size();j++)
		{
			if(emp[j]>emp[max_index])
				max_index = j;
		}
		
		if(i!= max_index)
		{
			T temp = emp[i];
			emp[i] = emp[max_index];
			emp[max_index] = temp;
		
			swap_no++;
		}

	}
	
	return swap_no;

}


/***
create two temprory vector copy the elements in them
merge the two divided small vector based on m then merge them back in sorted order in
parent vector
**/
template<class T>
void merge(vector<T>&em,int left,int midle,int right)
{
	int lsize = midle-left+1;
	int rsize = right - midle;

	vector<T>vleft;
	vector<T>vright;
	
	int x,y;

	for(x=0;x<lsize;x++)
	{
		vleft.push_back(em[x+left]);
	}

	for(y=0;y<rsize;y++)
	{
		vright.push_back(em[midle+1+y]);
	}

	int i=0,j=0,k=left;

	while(i<lsize && j<rsize)
	{
		if(vleft[i]>vright[j])
		{
			em[k] = vleft[i];
			i++;
			k++;
		}
		else
		{
			em[k] = vright[j];
			j++;
			k++;
			swap_no=swap_no+lsize-i;
		}
	}

	while(i<lsize)
	{
		em[k] = vleft[i];
		i++;
		k++;
	}

	while(j<rsize)
	{
		em[k] = vright[j];
		j++;
		k++;
	}

}


//recursively divide the vector into two and call the merge 
//function to mrege them back
template<class T>
void rec_divide(vector<T>& em ,int l,int r)
{
	if( l < r )
	{
		//midlle index
		int m = l+(r-l)/2;

		//recursively dividng
		rec_divide(em,l,m);
		rec_divide(em,m+1,r);
		
		//merging them back 
		merge(em,l,m,r);

	}

}


/*
merge sort with argument as a vectore of genric data type
*/
template<class T>
int merge_sort(vector<T>& emp)
{
	int left=0;
	int right=emp.size()-1;
	
	rec_divide(emp,left,right);

    return swap_no;

}


//print the id of employee in vector argument
void print(vector<Employee>emp)
{
	int i;
	for(i=0;i<emp.size();i++)
	{
		cout<<emp[i].id<<" ";
	}

}

//main function
int main() {
pair<vector<Employee>, string> records = read();
int (*sort)(vector<Employee>&); //Function pointer
if(records.second=="Merge")
sort = merge_sort;
else if(records.second=="Insertion")
sort = insertion_sort;
else sort = selection_sort;
cout<<sort(records.first)<<endl;
print(records.first);
return 0;
}
