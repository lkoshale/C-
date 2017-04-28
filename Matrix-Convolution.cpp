
/*


A Simple Twist!

Matrix convolution is a very common operation used in image processing tasks. Given two matrices(original matrix and kernel matrix) we get the third matrix by doing a series of element wise
multiplication, followed by a summation over a square window. Example at the end will make
this clear. In our case each time we convolve two matrices, dimension of resultant matrix is
smaller than original matrix for sure.

Your task is to implement this constrained version of convolution and apply convolution operation a number of times until convolution is not possible on resultant matrix with respect to the
same kernel. You are supposed to print the final resultant matrix.
Also after each convolution operation all negative values in the resultant matrix should be
clamped to zero. Then the next convolution is applied on this resultant matrix. Note that the first
operation is always a convolution operation and final operation is always a clamping operation.

So for a 4 × 4 matrix A convolved with 2 × 2 matrix K, sequence of operations will be :
R(3 * 3) = Convolve(A(4 * 4), K(2 * 2))
R(3 * 3) = Clamp(R(3 * 3))
R(2 * 2) = Convolve(R(3 * 3), K(2 * 2))
R(2 * 2) = Clamp(R(2 * 2))
R(1 * 1) = Convolve(R(2 * 2), K(2 * 2))
R(1 * 1) = Clamp(R(1 * 1))


To achieve this you are required to use and stick to the skeleton code provided. What follows
is a brief explanation of what needs to be done:
• Matrix class holds the matrix elements in 1-D array.
• You need to overload operator() for Matrix class which returns element of the matrix
	given its row number and column number. Note that the operator is assignable too i.e
	x = matObj(m, n) and matObj(m, n) = x must be valid operations.
• You need to impement classes Clamp, Conv and ItConv which will inherit the base class
	MatOp. While Clamp and Conv will do clamping and convolution operation, ItConv is iterative covolution which will make use of Conv and Clamp to implement the theme of problem
	statement.
• Clamp, Conv and ItConv are implemented as functors. Objects of these will be supplied as
	an argument to Matrix::apply in order to apply one of these operation on Matrix object.
	Constraints
• 1 = m, n, p, q = 1000
• INTEGERMIN = A(i, j), K(i, j) = INTEGERMAX


Input format
<Dimension of original matrix (m n)>
Followed by m*n elements
<Dimension of kernel (p q)>
Followed by p*q elements

Output format
Final Resultant Matrix


Sample Testcase

Input:
4 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
2 2
1 1
1 1

Output:
160



*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//Matrix class that have vector of elements of matrix
template <typename T> class Matrix;

//Base class for Matrix convolution
template <typename T>
class MatOp {
public: 
   virtual void operator()(Matrix<T> &m) = 0;
};

//class matrix store our matrix elements as 1D array
template <typename T>
class Matrix {
private:
   vector<T> data;
   int r,c;
public:
   //apply function called with the object to apply clamp or convolution or iteration
   //based on given object each object is defined as a functor
   void apply(MatOp<T>& op) { op(*this); }
   
   //return the row and col
   int rows() { return r; }
   int cols() { return c; }
   
   
   
   // return the refrence to the element of the vector data
   int& operator()(int row,int col){
  	int k = row*(this->c)+col;
	return data.at(k);
   }
   
   //set the private member row
   void setRow(int row){
   	this->r = row;
   }
   
   //set the private member col
   void setCol(int Col){
   	this->c = Col;
   }
   
   //set the vector Data
   void setData(vector<int> vec){
   	this->data = vec;
   }
   
   int getSize(){
   	return this->data.size();
   }
   
   //prints the data
   void printData(){
   	
   	for(int i=0;i<r;i++){
   		for(int j=0;j<c;j++){
   			cout<< this->operator()(i,j)<<" ";
   		}
   	
   		cout<<"\n";
   	}
   
   }
   
   
};


// clamp class used as a functor for the clamping of matrix
class Clamp : public MatOp<int>
{
public:
	//call operator overlaoded with argument as a refrence of Matrix A
	//iterates through data of matrix A and make 0 to all negative elements
	void operator()(Matrix<int>& A){

		int r = A.rows();
		int c = A.cols();
		for(int i=0;i<r;i++ ){
			for(int j=0;j<c;j++)
			{
				if(A(i,j)<0)
					A(i,j)=0;
			}
		}
	}	

};

//Conv class used as a functor for the Convolution of matrix
class Conv : public MatOp<int>
{
public:
	//the kernel matrix with which convolution occurs
	Matrix<int> Kernel;
	
	//call operator overloaded for convolution
	void operator()(Matrix<int>& A);

};

//call operator overloaded for convolution;
void Conv::operator()(Matrix<int>& A){
	vector<int> temp;
	int r = Kernel.rows();
	int c = Kernel.cols();
	int i,j,k,m;
	bool run = false;
	
	for(i =0;i+r<=A.rows();i++){
	   for(j=0;j+c<=A.cols();j++){
		int x = 0;
		int sum = 0;
		for(k=i;k<i+r;k++){
		  int y =0;
		   for(m=j;m<j+c;m++){
		   	
		   	run = true;
		   	sum+= A(k,m)*Kernel(x,y);
		   	y++;
		   }
		  
		    x++;
		}
		
		temp.push_back(sum);
	   
	   }
	
	}
	//cout<<i<<" "<<j<<" its\n";
	
	if(run == true){
	    A.setRow(i);
	    A.setCol(j);
		A.setData(temp);
		
	}

} 

//itConv class used as a functor for the itrative Convolution till 
// no more convolution possible of matrix
class ItConv : public MatOp<int>
{
public:
	Matrix<int>K;
	void operator()(Matrix<int>& A){
	
		Clamp X;
		Conv Y;
		Y.Kernel = K;	
		
		bool end = false;
		int u = A.getSize();
		
		while(A.getSize() >= K.getSize() && end == false){
			
			A.apply(Y);
			A.apply(X);
			if(A.getSize() != u)
				u = A.getSize();
			else
				end = true;
					
		}
		
		A.apply(X);
		
	
	}

};





int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int m,n;
    cin>>m>>n;
    Matrix<int>A;
    A.setRow(m);
    A.setCol(n);
    
    vector<int> Adata;
    
    for(int i=0;i<m*n;i++){
    	int k;
    	cin>>k;
    	Adata.push_back(k);
    }
    
    A.setData(Adata);
    
    Matrix<int>Kernl;
    int p,q;
    cin>>p>>q;
    Kernl.setRow(p);
    Kernl.setCol(q);
    
    vector<int>Kdata;
    
    for(int i=0;i<p*q;i++){
    	int k;
    	cin>>k;
    	Kdata.push_back(k);
    }
    
    Kernl.setData(Kdata);

/*
    Clamp XYZ;   
    Conv ABC;
    ABC.Kernel = Kernl;
    
    A.apply(ABC);
    A.printData();   
    cout<<"\n"<<A.rows()<<" "<<A.cols(); 
	
   */
   
   ItConv ans;
   ans.K = Kernl;
   
   A.apply(ans);
   
   A.printData();
    
    
    
    
    
     
    return 0;
}
