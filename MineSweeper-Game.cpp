
/*

Minesweeper

This task is a throwback to those days when Minesweeper was still the game you would play to
pass your time. For those of you who haven’t heard this game, here are the rules of Minesweeper.

Rules:
The game is played on an N X N grid of ’cells’, each of which is either empty or contains an
explosive mine. The player’s task is to locate all of the M mines without causing any of them to
explode. The location of the mines however, is a secret to the player. At the beginning of the
game the player has no information as to whether any given cell contains a mine or not. The
only course of action is to ’reveal’ the contents of a chosen cell. Should the player choose to
reveal a mine, the game is over and the player loses. However, if an empty cell is revealed, two
useful things will happen.

• The player is shown, how many of the revealed cell’s eight neighbours contain mines.
• If the chosen cell has no neighbours which are mines, all of its neighbours are ’revealed’
	To understand the game further, play the game a few times to get the hang of it. It can be
	played here: http://minesweeperonline.com/.

Your task is to design a minesweeper game given the values of N (the size of the grid) and
M (the number of mines) and the locations of all the mines. Once these values are given, the
board has been set. Now the player begins to play, and the positions where he chooses to click
are given. For each ’click’, you must print one of the following:
• "Won" if all the cells except the mines have been revealed.
• "Lost" if a mine has been revealed.
• A number "x" where x is the number of cells that have been revealed up to this point which
	are not mines.

Once "Won"/"Lost" has been printed, the further locations do not matter and must be ignored.
Use appropriate classes and functions to design your program.

Input format
First line contains the values of N and M separated by a space. The next line contains M values,
which indicate the location of the mines assuming the NxN grid is numbered from 0 to N2 from
left to right, top to bottom. For example, in a 5x5 grid, the location 8 indicates the position (1,3).
The next few lines indicate the positions (in the form of coordinates) the player has chosen to
reveal.

<N> <M>
<M values indicating locations of mines>
<loc 1>
<loc 2>
<loc 3>
..
..

Output format
<result 1>
<result 2>
<result 3>
..
..

Result could be "Won" or "Lost" or a number.

Sample Testcase

Input:
5 5
3 6 10 17 22
1 2
2 4
0 3

Output:
19
Lost


Explanation:
The initial minesweeper grid looks like the Fig 1, with the mines indicated by ’*’ in all the locations
mentioned in the input. In the first click, the player choses to reveal the cell (1,2) which is
surrounded by 2 mines: the one at 3 or (0,3) and 6 or (1,1). Since only one cell is revealed, the
output is 1. Please note that the number 2 is not to be outputted. The numbers shown in this
grid are the number of mines surrounding that cell, and the number indicates that that cell has
been revealed. It is the ’number of cells revealed’ that should be printed.


- - - * -			- - - * -			- - - * -
- * - - - 			- * 2 - - 			- * 2 1 1
* - - - -			* - - - - 			* - - 1 0
- - * - - 			- - * - - 			- - * 2 0
- - * - - 			- - * - - 			- - * 2 0
Fig 1 				Fig 2				 Fig 3

In the next click, the player chooses the location (2,4) which is not surrounded by any mines.
Hence, all of its neighbours are revealed. Note that, one of its neighbours (3,4) is also not
surrounded by any mines, hence all of its neighbours are revealed too. The configuration after
this play is shown in Fig 3. A total of 9 cells have been revealed, which needs to be printed.
Finally, the player chooses to reveal the cell (0,3) which contains a mine. Therefore, the user
loses the game, and ’Lost’ is printed.




*/


#include<iostream>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;

// class cell that represent one single cell of the minesweeper game
class cell{
public:
	// loaction of the cell 0 to N^2
	int id;
	// if the cell is already revelead or not
	bool reveal;
	// if the cell is a mine
	bool mine;
	
	//number of mine in its neighbour
	int num;
	//empty constructor
	cell(){}
	
	//sets id reveal and mine attributes 
	cell(int k){
		id = k;
		num=0;
		reveal = false;
		mine = false;
	}
	

};

//class Matrix which stores the n*n cels of minesweeper game in a 1d vector
class Mat{
public:
	//current no. of revealed cells in game
	int Rno;
	//size of the matrix
	int n;
	//vector that stores all the element in the matrix
	vector<cell*>Matrix;
	
	//call operator overloaded to get the value at index i,j in the matrix
	cell* operator()(int i,int j){
		int index = (this->n)*i + j;
		return this->Matrix.at(index);
	}
	
	bool checkM(int r,int c){
		if(r>=0 && c>=0 && r<n && c<n){
			int index = (this->n)*r + c;
			return !(this->Matrix.at(index)->mine);
		}
		return true;
	}
	
	//recursively check for the mines in neighbour and reveal if no mine found
	void Reveal(int r,int c);
	
};

void Mat:: Reveal(int r,int c)
{
	if(r>=0 && c>=0 && r<n && c<n)
	{
		bool flag = false;
		cell* temp = (*this)(r,c);
		
		if(temp->mine == false && temp->reveal == false )
		{
			temp->reveal = true;

            flag =checkM(r-1,c-1)&&checkM(r-1,c)&&checkM(r-1,c+1)&&checkM(r,c-1)&&checkM(r,c+1)&&checkM(r+1,c-1)&&checkM(r+1,c)&&checkM(r+1,c+1);
			
			if(flag==true){
				this->Rno++;
				this->Reveal(r-1,c-1);
				this->Reveal(r-1,c);
				this->Reveal(r-1,c+1);
				this->Reveal(r,c-1);
				this->Reveal(r,c+1);
				this->Reveal(r+1,c-1);
				this->Reveal(r+1,c);
				this->Reveal(r+1,c+1);
			}
			else
				this->Rno++;
		
			
		}

		
	}

}



int main()
{
	int n,m;
	cin>>n>>m;
	
	Mat M;
	
	M.n = n;
	M.Rno = 0;
	
	for(int i=0;i<(n*n);i++){
	
		cell* t = new cell(i);
		M.Matrix.push_back(t);
	}
	
	for(int i=0;i<m;i++){
		int loc;
		cin>>loc;
		cell* temp = M.Matrix.at(loc);
		temp->mine = true;
	}

	int row,col;
	
	while(cin>>row>>col)
	{

		cell* curr = M(row,col);
		if(curr->mine == true){
			cout<<"Lost\n";
			break;
		}
		
		M.Reveal(row,col);	
		
		if(M.Rno == (n*n - m)){
			cout<<"Won\n";
			break;
		}
		else{
			cout<<M.Rno<<"\n";
		}
		
	}
	

	return 0;
}


