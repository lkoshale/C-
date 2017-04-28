/*

Bigg Integers!
At his workplace, Mr X needs to deal with huge numbers on a daily basis. Unfortunately, the
native int type in C++ cannot store integers which have more than 10 decimal digits. He needs
your help to perform basic operations such as those mentioned below on these big integers.

Operators to be Implemented:
• Arithmetic Operators:
	– Addition ’+’ (add)
	– Subtraction ’-’ (sub)
	– Mutliplication ’*’ (mul)
	– Division ’/’ (div)
	– Modulus ’%’ (mod)
	– Factorial ’!’ (fac)
	– Power ’ˆ’ (pow)
• Comparison Operators:
	– Equals ’==’ (eq)
	– Not Equals ’!=’ (neq)
	– Greater than Equals ’>=’ (geq)
	– Less than Equals ’<=’ (leq)
Constraints
	• You must handle operations on integers with upto 1000 digits
	• For pow operator, base can be negative but the exponent is positive.
	• For rest of the operators except ’!’, both numbers can be negative.


Input format:

<operator-keyword1> <number1> <number2>
<operator-keyword2> <number1> <number2>
...

Note:
1. Operator keywords are mentioned in parentheses above.
2. For the factorial operator, there will be only one operand.

Output format
<result1>
<result2>
...

Note:
• For comparison operators, output 1 for true, 0 for false.
• In mod operation a%b, if b is negative, result lies in (b,0] otherwise in [0,b).
• In div operation a=b, print the quotient ba=bc.
• Result of div is in Egyptian fraction expansion’s Integer e.g -1/2 => -1 not 0 but 1/2 => 0
• You do not have to print leading 0s in results.


Sample Testcase

Input:
add -3245643213456234 23456754324523
mul 35434653434545 234234345345
pow 2938579324832 2
eq 1234567890123 1234567890132
fac 14

Output:
-3222186459131711
8300012849767603882943025
8635248448330092971828224
0
87178291200

*/


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include<stdbool.h>
#include <sstream>


using namespace std;

//overloading of comparison operator over strings
//taking two strings as input and outbut is true or false
bool operator>=(string s1,string s2);
bool operator<=(string s1,string s2);
bool operator!=(string s1,string s2);
bool operator==(string s1,string s2);



string trunc(string &s)
{
	string out;
	int flag=0;
	if(s.at(0)=='-'){
		s = s.substr(1);
		flag=1;
	}
	
	int x;
	for(x=0;x<s.length();x++)
	{
		if(s.at(x) != '0'){
			break;
		}
	}
	
	if(x== s.length()){
		out = "0";
		return out;
	}
	

	if(flag==1)
		out = "-"+s.substr(x);
	else
	    out = s.substr(x);
	    
	return out;

}

//overloading the ! operator to compute factorial
//input as a vector of string and output is a single string 
string operator!(string op1);

//+ operator overloaded to divide the two large integer as strings
string operator/(string op1,string op2);

//+ operator overloaded to comput modulo of the two large integer as strings
string operator%(string op1,string op2);

//+ operator overloaded to multiply the two large integer as strings 
string operator*(string op1,string op2);

//overloading - operator over strings
string operator-(string s1,string s2);

bool operator<=(string s1,string s2)
{
	if(s1.compare(s2)==0)
		return true;
	
	if(s1>=s2)
		return false;
	else
		return true;
		
}

string append(string s1,string s2)
{
	return s1+s2;
}



//operator == overloaded for integers which are in string format
bool operator==(string s1,string s2)
{
	s1 = trunc(s1);
	s2 = trunc(s2);
	
	if(s1.compare(s2)==0)
		return true;
	else 
		return false;

}


//operator >= overloaded for strings
bool operator>=(string s1,string s2)
{
	s1= trunc(s1);
	s2= trunc(s2);

	if(s1.compare(s2)==0)
		return true;


	if(s1.at(0) == '-' && s2.at(0) != '-')
		return false;
	else if(s1.at(0) != '-' && s2.at(0) == '-')
		return true;
	else if(s1.at(0) != '-' && s2.at(0) != '-')
	{
		s1 = trunc(s1);
		s2 = trunc(s2);

		if(s1.length()>s2.length())
			return true;
		else if(s1.length()<s2.length())
			return false;
		else{
			for(int i=0 ; i<s1.length();i++)
			{
				if( (s1.at(i)-'0') > (s2.at(i)-'0') )
					return true;
				else if( (s1.at(i)-'0') < (s2.at(i)-'0') )
					return false;
			}
		}
	}
	else{
		s1 = trunc(s1);
		s2 = trunc(s2);

		if(s1.length()>s2.length())
			return false;
		else if(s1.length()<s2.length())
			return true;
		else{
			for(int i=1 ; i<s1.length();i++)
			{
				if( (s1.at(i)-'0') > (s2.at(i)-'0') )
					return false;
				else if( (s1.at(i)-'0') < (s2.at(i)-'0') )
					return true;
			}
			
			return true;
		}
		
		
	}
	
	return true;
}




//+ operator overloaded to add the two large integer as strings
string operator+(string s1,string s2)
{
//Adding bit by bit the given two string of integers

	s1 = trunc(s1);
	s2 = trunc(s2);

	string out = "";
	int len1 = s1.length();
	int len2 = s2.length();
	int len,max;

	if(len1>len2){
		len = len2; max = 1;
	}else{
		len = len1; max = 2;
	}	

	int i,x,y,overflow=0;

	for(i=0;i<len;i++)
	{
		int k = s1.at(len1-1-i)-'0';
		int j = s2.at(len2-1-i)-'0';

		int r = (overflow+k+j)%10;
		overflow = (overflow+k+j)/10;
		
		char ch = r + '0';
		out= ch + out;
	}

	if(len1!=len2)
	{
		if(max==1){
			for(x=i;x<len1;x++)
			{
				int k = s1.at(len1-1-x)-'0';
				int r = (overflow+k)%10;
				overflow = (overflow+k)/10;
				
				char ch = r + '0';
				out= ch + out;
			}

		}else if(max==2)
		{
			for(x=i;x<len2;x++)
			{
				int k = s2.at(len2-1-x)-'0';
				int r = (overflow+k)%10;
				overflow = (overflow+k)/10;
				
				char ch = r + '0';
				out = ch+out;
			}
		}
	
	}

	if(overflow != 0){
		char ch = overflow + '0';
		out=ch+out;			
	}

	return out;
}

string operator-(string s1,string s2)
{
	
	s1 = trunc(s1);
	s2 = trunc(s2);
	
	string out = "";
	int len1 = s1.length();
	int len2 = s2.length();
	int len,max;
	int i,y,underflow=0;
	

	if(s1.compare(s2)==0)
	{
		out = out+"0";
		return out;
	}
	else if(s1>=s2){
		len = len2;
		 max = 1;		
	}
	else{
		len = len1; 
		max = 2;
	}
	
	if(max == 1){
		for(i=0;i<len;i++)
		{
			int k = s1.at(len1-1-i)-'0';
			int j = s2.at(len2-1-i)-'0';

			int r = (underflow+k-j)%10;
			if(r<0)
				r = 10+r;


			if((underflow+k-j) < 0)
				underflow = -1;
			else
				underflow = 0;
			
			char ch = r + '0';
			out= ch + out;	
		}
		
		while(i<len1){
		int k = s1.at(len1-1-i)-'0';
		int r = (underflow+k)%10;
		if(r<0)
			r = 10+r;
		
		if((underflow+k) < 0)
			underflow = -1;
		else
			underflow = 0;

		char ch = r + '0';
		out= ch + out;
		i++;

		}
	}
	else if(max == 2){
		for(i=0;i<len;i++)
		{
			int k = s1.at(len1-1-i)-'0';
			int j = s2.at(len2-1-i)-'0';

			int r = (underflow+j-k)%10;
			if(r<0) r = 10+r;			

			if((underflow+j-k) < 0)
				underflow = -1;
			else
				underflow = 0;
			
			char ch = r + '0';
			out= ch + out;	
		}
	
		while(i<len2){
		int k = s2.at(len2-1-i)-'0';
		int r = (underflow+k)%10;
		if(r<0)	r = 10+r;
			
		if((underflow+k) < 0)
			underflow = -1;
		else
			underflow = 0;

		char ch = r + '0';
		out= ch + out;
		i++;
		}
	}
	int x;
	for(x=0;x<out.length();x++)
	{
		if(out.at(x) != '0'){
			break;
		}
	}

	string st = out.substr(x);

	if(max==2) st= "-"+st;

	return st;
}

string Add(string st1,string st2)
{
	string out="";

	if(st1.at(0) == '-' && st2.at(0) == '-'){
		out = st1.substr(1)+st2.substr(1);
		out = "-" + out;
	}else if(st1.at(0) == '-' && st2.at(0) != '-'){
		out = st2-st1.substr(1);
	}else if(st1.at(0) != '-' && st2.at(0) == '-'){
		out = st1-st2.substr(1);
	}else 
		out = st1+st2;

	return out;
}

string Sub(string st1,string st2)
{
	string out="";

	if(st1.at(0) == '-' && st2.at(0) == '-'){
		out = st2.substr(1)-st1.substr(1);
	}else if(st1.at(0) == '-' && st2.at(0) != '-'){
		out = st1.substr(1)+st2;
		out = "-" + out;
	}else if(st1.at(0) != '-' && st2.at(0) == '-'){
		out = st1+st2.substr(1);
	}else 
		out = st1-st2;

	return out;
	
}

string operator*(string st1,string st2)
{
	st1 = trunc(st1);
	st2 = trunc(st2);
	
	string out="";
	string str1,str2,pre;

	int x,y;

	if(st1.at(0) == '-' && st2.at(0) == '-'){
		pre = "+";
		str1 = st1.substr(1);
		str2 = st2.substr(1);
	}else if(st1.at(0) == '-' && st2.at(0) != '-'){
		pre = "-";
		str1 = st1.substr(1); 
		str2 = st2;
	}else if(st1.at(0) != '-' && st2.at(0) == '-'){
		pre = "-";
		str2 = st2.substr(1); 
		str1 = st1;
	}else {
		str2 = st2; 
		str1 = st1;	
	}
	string temp = "0";

	for(x=0;x<str2.length();x++)
	{
		string sum="0";
		int k = str2.at(str2.length()-1-x)-'0';

		for(int l=0;l<k;l++)
		{
			sum = str1+sum;
		}

		for(int m=0;m<x;m++)		
		{
			sum = sum+"0";
		}

		temp = temp+sum;		
	}

	if(pre.compare("-")==0)
		temp= "-" + temp;

	return temp;
}

string operator!(string op)
{
	op = trunc(op);
	if(op.compare("0")==0)
		return "1";	

	string t = "1";
	string n = "2";
	string p = "1";
	string temp;

	while(n<=op)
	{
		p = p*n;				//product p
		n= n+t;		//op-1
	}

	return p;
	
}


pair<int,string> num(string div,string t)
{
	pair<int,string>p;
	int j;
	int k;
	
	if(div>=t && div.compare(t)!=0)
	{
		p.first = 0;
		p.second = t;
		return p;
	}

	for(j=1;j<=10;j++)
	{
		if(div>=t && div.compare(t)!=0)
		{
			k = j-1;
			break;
		}
		else 
		{
			t = t-div;
		}
	}

	p.first = k;
	p.second = t;
	return p;
}


string operator/(string s1,string s2)
{
	string out="";
	string temp="";
	int i;
	
	
	
	for(i=0;i<s1.length();i++)
	{
		temp = temp+s1.at(i);
		temp = trunc(temp);
		pair<int,string> p = num(s2,temp);
		temp = p.second;
		char ch = p.first + '0';
		out = out+ch;
		
	}
	
	out = trunc(out);
	return out;
	
}


/*
string operator/(string s1,string s2)
{
	string out="";
	string temp;
	int i=0,j=0;

	
	int len = s2.length();
	string str = s1.substr(0,len);

	if(str.compare(s2)!=0 && s2>=str){
			str = str + s1.at(len);
			i++;
	}
	
	while(s1>=s2)
	{
		j=0;
		while(str>=s2)
		{
			str = str-s2;
			j++;
		}
		
		char ch = j+'0';
		out = out+ch;
		int flag ;
		
		if(len+i < s1.length() ){
		
			int x=0;
			while(s2>=str && s2.compare(str)!=0 && len+x+i < s1.length())
			{
			//	s1 = s1.replace(len+i+x-1,1,"0");
				
				str=trunc(str);
				if(s1.at(len+i+x) == '0'&&str.compare("0")==0 )
				{
					out+="0";
					flag =0;
				}
				else if(x>=1)
				{
					out+="0";
					flag =1;
				}
				str = str+s1.at(len+i+x);

				str = trunc(str);
				x++;
			}
			i = i+x;
			
			if(s2.compare(str)!=0 && s2>=str && len+i >s1.length() ){			
				if(flag==1)
					out+="0";				
				
				break;
	 		}
		}
		else 
			break;
			
	}
	return out;
}


*/

string rem(string s1,string s2)
{
	string out="";
	string temp="";
	int i;
		
	for(i=0;i<s1.length();i++)
	{
		temp = temp+s1.at(i);
		temp = trunc(temp);
		pair<int,string> p = num(s2,temp);
		temp = p.second;
		char ch = p.first + '0';
		out = out+ch;
		
	}
	
	out = trunc(out);
	temp = trunc(temp);
	return temp;
}

string Div(string st1,string st2)
{
	string out;
	string n = "1";
	
	if(st1.at(0) == '-' && st2.at(0) == '-'){
			out = st1.substr(1)/st2.substr(1);
			
	}else if(st1.at(0) == '-' && st2.at(0) != '-'){
		
		if(st2>=st1.substr(1) && st2.compare(st1.substr(1))!=0)
			out ="-1";
		else{	
			out = st1.substr(1)/st2;
			out = out+n;
			out = "-"+out;
		}
	}else if(st1.at(0) != '-' && st2.at(0) == '-'){
		if(st2.substr(1)>=st1 && st1.compare(st2.substr(1))!=0)
		{
			out = "-1";
		}else{
			out = st1/st2.substr(1);
			out = out+n;
			out = "-"+out;
		}
		
	}else {
		
		out = st1/st2;
		
	}
	
	return out;
}


string operator^(string s1,string s2)
{
	string m;
		
	if(s2.compare("0")==0) 
	    return "1";
	
	string k,l;
	string d = "2";
	string t = "1";
	k = s2/d;
	l = s2-t;
	
	string r = rem(s2,d);
	
	if( r.compare("0")==0)
	{
		m = s1^k;
		string out = m*m;
		return out;
	}
	else
	{
		m = s1^l;
		string out = s1*m;
		return out;
	}
	
		
}


string pow(string s2,string s3)
{
	
	string t ="2";
	string flag = rem(s3,t);
	string out;
	
	if(s2.at(0)=='-'){
		out = s2.substr(1)^s3;
		if(flag.compare("1")==0)
			out = "-"+out;
	}
	else
		out = s2^s3;
		
	return out;
			
}

string operator%(string st1,string st2)
{
	string out;
	
	if(st1.at(0) == '-' && st2.at(0) == '-'){
	
		if(st2.substr(1)>=st1.substr(1) && st2.compare(st1)!=0)
			out ="-"+st1.substr(1);
		else{
			out = rem(st1.substr(1),st2.substr(1));
			out = "-"+out;
		}
				
	}else if(st1.at(0) == '-' && st2.at(0) != '-'){
		if(st2>=st1.substr(1) && st2.compare(st1.substr(1))!=0)
		{
			out = st2-st1.substr(1);
		}
		else{
			out = rem(st1.substr(1),st2);
			if(out.compare("0")!=0)
				out = st2-out;
		}
		
	}else if(st1.at(0) != '-' && st2.at(0) == '-'){
		if(st2.substr(1)>=st1 && st1.compare(st2.substr(1))!=0)
		{
			out = st2.substr(1)-st1;
			out = "-"+out;
		}
		else{
			out = rem(st1,st2.substr(1));
			if(out.compare("0")!=0){
				out = st2.substr(1)-out;
				out= "-"+out;
			}
		}
		
	}else {
		if(st2>=st1 && st2.compare(st1)!=0)
			out = st1;
		else
			out = rem(st1,st2);
	}
	
	out = trunc(out);
	
	return out;
}




//main function for taking input
int main()
{
	string line;

	while(getline(cin,line))
	{
		string s1,s2,s3,out="";	
		stringstream ss(line);
		
		ss>>s1>>s2>>s3;

		if(s1.compare("add")==0)
			cout<<Add(s2,s3);
		else if(s1.compare("sub")==0)
			cout<<Sub(s2,s3);
		else if(s1.compare("mul")==0)
			cout<<s2*s3;
		else if(s1.compare("fac")==0)
			cout<<!s2;
		else if(s1.compare("eq")==0)
			cout<<(s2==s3);
		else if(s1.compare("neq")==0)
			cout<<!(s2==s3);
		else if(s1.compare("geq")==0)
			cout<<(s2>=s3);
		else if(s1.compare("leq")==0)
			cout<<(s2<=s3);
		else if(s1.compare("div")==0)
			cout<<Div(s2,s3);
		else if(s1.compare("pow")==0)
			cout<<pow(s2,s3);
		else if(s1.compare("mod")==0)
			cout<<s2%s3;
			
			cout<<"\n";
	}

	
	
}



    
