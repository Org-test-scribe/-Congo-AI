//Adam Gordon
//2275253
//Part 2

#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
#include <random>
#include <list>
#include<tuple>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include<string.h>
#include<ctype.h>
#include <algorithm>


using std::istringstream;
using namespace std::chrono;
using namespace std;

//class for pieces 
//each piece will be an object 
class Piece{
public:
    /*
        make vars public in order to allow access
    */
    //rank of piece
    string rank;

    //file/col of piece in terms of a,b...
    string file;

    //file num in number not letter
    string fileNum;

    //pos of piece
    string pos;

    //pos in numbers only
    string posNum;

    //type of piece (e,l,c...)
    string pieceType;

    //color of piece
    string color;
    //create constructor that sets all the class vars 
    Piece()
    {
        rank="NULL";
        file="NULL";
        fileNum="NULL";
        pos="NULL";
        posNum="NULL";
        pieceType="NULL";
        color="NULL";
    }

    Piece(string Crank, string Cfile, string CpieceType, string Ccolor)
    {
        rank=Crank;
        fileNum=Cfile;

        posNum+=fileNum;
        posNum+=rank;

        if(Cfile=="0")
        {
            file="a";
            pos+=file;
        }
        else if(Cfile=="1")
        {
            file="b";
            pos+=file;
        }
        else if(Cfile=="2")
        {
            file="c";
            pos+=file;
        }
        else if(Cfile=="3")
        {
            file="d";
            pos+=file;
        }
        else if(Cfile=="4")
        {
            file="e";
            pos+=file;
        }
        else if(Cfile=="5")
        {
            file="f";
            pos+=file;
        }
        else if(Cfile=="6")
        {
            file="g";
            pos+=file;
        }
        pos+=rank;

        pieceType=CpieceType;
        
        color=Ccolor;
    }

};


//class for FEN
class FEN{
public:

    //vectors holding all the different oieces grouped
    vector<Piece>wPawns;
    vector<Piece>bPawns;
    vector<Piece>wSpawns;
    vector<Piece>bSpawns;
    vector<Piece>wGiraffe;
    vector<Piece>bGiraffe;
    vector<Piece>wMonkey;
    vector<Piece>bMonkey;
    vector<Piece>wElephant;
    vector<Piece>bElephant;
    vector<Piece>wLion;
    vector<Piece>bLion;
    vector<Piece>wCrocodile;
    vector<Piece>bCrocodile;
    vector<Piece>wZebra;
    vector<Piece>bZebra;


    //holds all posOf pieces
    //each elem is a rank 
    vector<string> posPieces;

    //holds side to move
    string sideToMove;

    //holds number of moves made
    int moveNumber;

    //holds all pieces for the board
    vector<Piece> pieces;

    //constrictor that takes in FEN String 
    FEN(string FENString)
    {
        //call process FENString function 
        processFEN(FENString);
    }

    //method-> prepoc of string, splits into pos string, side to move and num of moves
    //returns vector of split string
    vector<string> splitFENString(string FENString, char delim)
    {
        //create string stream from our FEN string
        stringstream ss(FENString);
        //create token that gets assigned the split string 
        string token;
        //vector holds the split string
        vector<string> splitFEN;
        //splitnthe string by spaces and store in vector
        while(getline(ss, token, delim))
        {
            splitFEN.push_back(token);
        }

        return splitFEN;
    }

    void processFEN(string FENString)
    {
        //split up the FEN string
        vector<string> splitFEN=splitFENString(FENString, ' ');

        //assign the class vars
        string sideToMoveAbr=splitFEN[1];
        if(sideToMoveAbr=="b")
        {
            sideToMove="black";
        }
        else
        {
            sideToMove="white";
        }

        moveNumber=stoi(splitFEN[2]);

        //again split up string by "/" this time
        posPieces=splitFENString(splitFEN[0], '/');

        //call create pieces
        pieces=createPieces();

        //populate the piece arrays
        populateArrays();
    }

    vector<Piece> createPieces()
    {
        //universal vector containing pieces
        vector<char> PSW={'P','G','M','E','L','C','Z','S'};
        vector<char> PSB={'p','g','m','e','l','c','z','s'};
        //holds all pieces for this particular FEN string
        vector<Piece> piecesVec;

        int currRank=7;
        int currFile=0;

        for(int i=0; i<posPieces.size();++i)
        {
            //get curr string
            string currString=posPieces[i];
            //curr rank is just loop itr

            for(int j=0; j<currString.length();++j)
            {
                //check if curr elem is a symbol
                if(find(PSW.begin(), PSW.end(), currString[j]) != PSW.end())
                {
                    //dealing with white symbol
                    string rank=to_string(currRank);
                    string file= to_string(currFile);

                    //piece type char->string
                    string currVal;
                    currVal+=currString[j];
                    Piece piece(rank,file, currVal, "white");
                    piecesVec.push_back(piece);

                    currFile+=1;
                }
                else if(find(PSB.begin(), PSB.end(), currString[j]) != PSB.end())
                {
                    //dealing with white symbol
                    string rank=to_string(currRank);
                    string file= to_string(currFile);
                    //piece type char->string
                    string currVal;
                    currVal+=currString[j];
                    Piece piece(rank,file, currVal, "black");
                    piecesVec.push_back(piece);

                    currFile+=1;
                }
                else
                {
                    //dealing with number=empty space
                    string currVal;
                    currVal+=currString[j];
                    currFile+=stoi(currVal);
                }
            }

            currRank--;
            currFile=0;
        }

        return piecesVec;
    }

    void populateArrays()
    {
        for(Piece i : pieces)
        {
            if(i.pieceType=="p")
            {
                //black pawn
                bPawns.push_back(i);
            }
            else if(i.pieceType=="P")
            {
                //white pawn
                wPawns.push_back(i);
            }
            else if(i.pieceType=="s")
            {
                //black superpawn
                bSpawns.push_back(i);
            }
            else if(i.pieceType=="S")
            {
                //white superpawn
                wSpawns.push_back(i);
            }
            else if(i.pieceType=="g")
            {
                //black giraffe
                bGiraffe.push_back(i);
            }
            else if(i.pieceType=="G")
            {
                //wgite giraffe
                wGiraffe.push_back(i);
            }
            else if(i.pieceType=="m")
            {
                //black monkey
                bMonkey.push_back(i);
            }
            else if(i.pieceType=="M")
            {
                //white monkey
                wMonkey.push_back(i);
            }
            else if(i.pieceType=="e")
            {
                //black elephant
                bElephant.push_back(i);
            }
            else if(i.pieceType=="E")
            {
                //white elephant
                wElephant.push_back(i);
            }
            else if(i.pieceType=="l")
            {
                //black lion
                bLion.push_back(i);
            }
            else if(i.pieceType=="L")
            {
                //white lion
                wLion.push_back(i);
            }
            else if(i.pieceType=="c")
            {
                //black croc
                bCrocodile.push_back(i);
            }
            else if(i.pieceType=="C")
            {
                //white croc
                wCrocodile.push_back(i);
            }
            else if(i.pieceType=="z")
            {
                //black zebra
                bZebra.push_back(i);
            }
            else if(i.pieceType=="Z")
            {
                //white zebra
                wZebra.push_back(i);
            }
        }
    }

    static bool comp(Piece &a, Piece &b) {
        if(a.pos[0]==b.pos[0])
        {
            return a.pos[1]<b.pos[1];
        }
        return a.pos[0]<b.pos[0];
    }

    void output()
    {
        //print out white pawns
        sort(wPawns.begin(), wPawns.end(), comp);
        cout<<"white pawn: ";
        for(Piece i : wPawns)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black pawns
        sort(bPawns.begin(), bPawns.end(), comp);
        cout<<"black pawn: ";
        for(Piece i : bPawns)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white super pawn
        sort(wSpawns.begin(), wSpawns.end(), comp);
        cout<<"white superpawn: ";
        for(Piece i : wSpawns)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black super pawn
        sort(bSpawns.begin(), bSpawns.end(), comp);
        cout<<"black superpawn: ";
        for(Piece i : bSpawns)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white giraffe
        sort(wGiraffe.begin(), wGiraffe.end(), comp);
        cout<<"white giraffe: ";
        for(Piece i : wGiraffe)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black giraffe
        sort(bGiraffe.begin(), bGiraffe.end(), comp);
        cout<<"black giraffe: ";
        for(Piece i : bGiraffe)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out monkey giraffe
        cout<<"white monkey: ";
        sort(wMonkey.begin(), wMonkey.end(), comp);
        for(Piece i : wMonkey)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black monkey
        cout<<"black monkey: ";
        sort(bMonkey.begin(), bMonkey.end(), comp);
        for(Piece i : bMonkey)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white elpehangt
        cout<<"white elephant: ";
        sort(wElephant.begin(), wElephant.end(), comp);
        for(Piece i : wElephant)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //pront b;ack elpehant 
        cout<<"black elephant: ";
        sort(bElephant.begin(), bElephant.end(), comp);
        for(Piece i : bElephant)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white lion
        sort(wLion.begin(), wLion.end(), comp);
        cout<<"white lion: ";
        for(Piece i : wLion)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black lion
        sort(bLion.begin(), bLion.end(), comp);
        cout<<"black lion: ";
        for(Piece i : bLion)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white croc
        sort(wCrocodile.begin(), wCrocodile.end(), comp);
        cout<<"white crocodile: ";
        for(Piece i : wCrocodile)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black croc
        sort(bCrocodile.begin(), bCrocodile.end(), comp);
        cout<<"black crocodile: ";
        for(Piece i : bCrocodile)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out white zebra
        sort(wZebra.begin(), wZebra.end(), comp);
        cout<<"white zebra: ";
        for(Piece i : wZebra)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        //print out black zebra
        sort(bZebra.begin(), bZebra.end(), comp);
        cout<<"black zebra: ";
        for(Piece i : bZebra)
        {
            cout<<i.pos<<" ";
        }
        cout<<endl;

        cout<<"side to play: "<<sideToMove<<endl;
    }
};


//class for board

class Board{
public:

    vector<vector<string>>board;
    Board(FEN FENObj)
    {
        for(int i=0; i<7; ++i)
        {
            vector<string> row {"0","0","0","0","0","0","0"};
            board.push_back(row);
        }
        vector<Piece> pieces=FENObj.pieces;

        //satrt filling in board piece by piece
        for(Piece i : pieces)
        {
            //cout<<stoi(i.rank)<<" "<<stoi(i.fileNum)<<endl;
            board[stoi(i.rank)-1][stoi(i.fileNum)]=i.pieceType;
        }

    }

    void printBoard()
    {
        for(int i=0; i<board.size();++i)
        {
            for(int j=0; j<board.size();++j)
            {
                cout<<board[i][j];
            }
            cout<<endl;
        }
    }
};

static bool comp(string a, string b) {
    return a<b;
}

vector<vector<int>> getGWP(string piecePosString)
{

    vector<vector<int>> GWP;
    //convert from [col][row]->[row][col]
    string piecex;
    piecex+=piecePosString[0];
    string piecey;
    piecey+=piecePosString[1];

    vector<int> piecePosGame;
    vector<int> piecePosWork;

    piecePosGame.push_back(stoi(piecex));
    piecePosGame.push_back(stoi(piecey));

    piecePosWork.push_back(stoi(piecey));
    piecePosWork.push_back(stoi(piecex));

    GWP.push_back(piecePosGame);
    GWP.push_back(piecePosWork);

    return GWP;
}
vector<string> converToAnswerString(vector<string> possibleMoves, Piece piece)
{
    vector<string>moves;
    for(string i : possibleMoves)
    {

        //increment the row
        string newRow;
        newRow+=i[0];
        int intRow=stoi(newRow);
        intRow++;
        string finalRow=to_string(intRow);

        //switch row and col
        string switchedString;
        switchedString+=i[1];
        switchedString+=finalRow;

        //get letter 
        char letter;
        if(switchedString[0]=='0')
        {
            letter='a';
        }
        else if(switchedString[0]=='1')
        {
            letter='b';
        }
        else if(switchedString[0]=='2')
        {
            letter='c';
        }
        else if(switchedString[0]=='3')
        {
            letter='d';
        }
        else if(switchedString[0]=='4')
        {
            letter='e';
        }
        else if(switchedString[0]=='5')
        {
            letter='f';
        }
        else if(switchedString[0]=='6')
        {
            letter='g';
        }

        string finalString;
        finalString+=letter;
        finalString+=switchedString[1];

        string combinedString=piece.pos+finalString;
        moves.push_back(combinedString);
    }

    return moves;
}

char letterToNum(char letter)
{
    if(letter=='a')
    {
        return '0';
    }
    else if(letter=='b')
    {
        return '1';
    }
    else if(letter=='c')
    {
        return '2';
    }
    else if(letter =='d')
    {
        return '3';
    }
    else if(letter == 'e')
    {
        return '4';
    }
    else if(letter =='f')
    {
        return '5';
    }
    else
    {
        return '6';
    }
}


pair<string, string> makeMovePair(string move)
{
    pair<string, string> movePair;
    /*
        *d1d2
        *0123
        *cols->0
             ->2
        *rows->1
             ->3
    */
    string start;
    start+=move[1]-1;
    start+=letterToNum(move[0]);

    string end;
    end+=move[3]-1;
    end+=letterToNum(move[2]);


    movePair=make_pair(start,end);
    // cout<<"START: "<<movePair.first[0]<<movePair.first[1]<<endl;
    // cout<<"END: "<<movePair.second[0]<<movePair.second[1]<<endl;

    return movePair;
}

string recreateFEN(vector<vector<string>> board, FEN FENString)
{
    string newFENString;

    /*keep track of zeros to add up*/
    int count=0;
    /*loop through board starting at bottom*/
    for(int i=6; i>=0; --i)
    {
        for(int j=0; j<7; ++j)
        {
            if(board[i][j]=="0")
            {
                count+=1;
            }
            else
            {
                //add count
                if(count!=0)
                {
                    newFENString+=to_string(count);
                    //then add piece
                    newFENString+=board[i][j];
                    count=0;
                }
                else
                {
                    newFENString+=board[i][j];
                }
            }
        }
        if(count!=0)
        {
            newFENString+=to_string(count);
        }
        count=0;
        if(i!=0)
        {
            newFENString+="/";
        }

    }

    /*switch person to move*/
    if(FENString.sideToMove=="black")
    {
        newFENString+=" ";
        newFENString+="w";
        newFENString+=" ";
        newFENString+=to_string(FENString.moveNumber+1);
    }
    else
    {
        newFENString+=" ";
        newFENString+="b";
        newFENString+=" ";
        newFENString+=to_string(FENString.moveNumber);
    }
    return newFENString;
}

vector<string> makeMove(vector<vector<string>> board, string move, FEN FENString)
{
    pair<string, string> movePair=makeMovePair(move);

    string startRow;
    startRow+=movePair.first[0];
    string startCol;
    startCol+=movePair.first[1];

    string endRow;
    endRow+=movePair.second[0];
    string endCol;
    endCol+=movePair.second[1];


    string startPiece=board[stoi(startRow)][stoi(startCol)];
    string endPiece=board[stoi(endRow)][stoi(endCol)];

    // for(vector<string> i:board)
    // {
    //     for(string j :i)
    //     {
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    /*check for river*/
    string piece=board[stoi(startRow)][stoi(startCol)];
    if(piece=="p" && endRow=="0")
    {
        board[stoi(startRow)][stoi(startCol)]="s";
    }
    if(piece=="P" && endRow=="6")
    {
        board[stoi(startRow)][stoi(startCol)]="S";
    }
    if(islower(piece[0]))
    {
        for(int i=0; i<7; ++i)
        {
            string check=board[3][i];
            if(islower(check[0]))
            {
                if(stoi(startRow)!=3 || (stoi(startCol)!=i && stoi(startRow)!=3))
                {
                    board[3][i]="0";   
                }
            }
        }
    }
    else if(isupper(piece[0]))
    {
        for(int i=0; i<7; ++i)
        {
            string check=board[3][i];
            if(isupper(check[0]))
            {
                if(stoi(startRow)!=3 || (stoi(startCol)!=i && stoi(startRow)!=3))
                {
                    board[3][i]="0";   
                }
            }
        }
    }
    
    vector<string> fenGameState;
    if(board[stoi(endRow)][stoi(endCol)]=="l")
    {
        fenGameState.push_back("White wins");
    }
    else if(board[stoi(endRow)][stoi(endCol)]=="L")
    {
        fenGameState.push_back("Black wins");
    }
    else
    {
        fenGameState.push_back("Continue");
    }

    //execute move
    board[stoi(endRow)][stoi(endCol)]=board[stoi(startRow)][stoi(startCol)];
    board[stoi(startRow)][stoi(startCol)]="0";

    if(movePair.first[0]=='3' && movePair.second[0]=='3')
    {
        //both start(curr) pos and end pos are in river and therefore piece drowns
        board[stoi(endRow)][stoi(endCol)]="0";
    }

    // for(vector<string> i:board)
    // {
    //     for(string j :i)
    //     {
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    
    string newFENString=recreateFEN(board, FENString);
    fenGameState.push_back(newFENString);

    return fenGameState;

}






/*LION MOVE GENERATOR*/
vector<string> lionMoves(vector<vector<string>> board, FEN FENString)
{
    /* 
        ->lion can moe in any direction provided its inside its 3x3 girf
        -> or crosses the river to make an immeadite kill lion

        ->check if can go:
            ->up,down,left,right,diagLefUp, diagLeftDown, diagRightUp, diagRightDown:
            ->inside 3x3 grid
            ->or going accross river for immeadite kill lion 
    */

   //holds possible moves indv
    vector<string> possibleMoves;
    
    //holds all possible moves inf inal form to be returned 
    vector<string> allPossibleMoves;

    vector<Piece> bLionArray=FENString.bLion;
    Piece bLion=bLionArray[0];
    string bLionPosString=bLion.pos;

    vector<Piece> wLionArray=FENString.wLion;
    Piece wLion=wLionArray[0];
    string wLionPosString=wLion.pos;

    // cout<<"BLACK LION: "<<bLionPosString<<endl;
    // cout<<"WHITE LION: "<<wLionPosString<<endl;

    if(FENString.sideToMove=="black")
    {
        //black turn therefoe only consider black
        //get pos of white lion 
        vector<Piece> lionArray=FENString.bLion;
        Piece lion=lionArray[0];
        string lionPosString=lion.posNum;
        lionPosString[1]-=1;

        string lionx;
        lionx+=lionPosString[0];
        string liony;
        liony+=lionPosString[1];

        vector<int> lionPosGame;
        vector<int> lionPosWork;

        lionPosGame.push_back(stoi(lionx));
        lionPosGame.push_back(stoi(liony));

        lionPosWork.push_back(stoi(liony));
        lionPosWork.push_back(stoi(lionx));

        //cout<<"LION POS: "<<lionPosWork[0]<<lionPosWork[1]<<endl;

        //upper bound of lion 3x3 grid
        int lionUpperBound=4;
        //lower bound of lion
        int lionLowerBound=6;
        //lion left bound
        int lionLeftBound=2;
        //lion right bound
        int lionRightBound=4;

        //checking if can move up in bounds
        if((lionPosWork[0]-1 > lionUpperBound || lionPosWork[0]-1==lionUpperBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of above pos
            vector<int> upperPos;
            upperPos.push_back(lionPosWork[0]-1);
            upperPos.push_back(lionPosWork[1]);
            //piece above is what is physically in the upper pos
            string pieceAbove=board[upperPos[0]][upperPos[1]];

            // cout<<"IN BOUNDS UPPER"<<endl;
            // cout<<"UPPER POS ELEM: "<<board[upperPos[0]][upperPos[1]]<<endl;

            if(pieceAbove=="0")
            {
                //cout<<"UPPER POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(upperPos[0]);
                pos+=to_string(upperPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece above, if enemy piece can move, if our own then cant
                char comp=pieceAbove[0];
                //cout<<"UPPER POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                   // cout<<"UPPER POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(upperPos[0]);
                    pos+=to_string(upperPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }

        //checking if can move down in bounds
        if((lionPosWork[0]+1 < lionLowerBound || lionPosWork[0]+1==lionLowerBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of above pos
            vector<int> lowerPos;
            lowerPos.push_back(lionPosWork[0]+1);
            lowerPos.push_back(lionPosWork[1]);
            //piece above is what is physically in the upper pos
            string pieceBelow=board[lowerPos[0]][lowerPos[1]];

            // cout<<"IN BOUNDS LOWER"<<endl;
            // cout<<"LOWER POS ELEM: "<<board[lowerPos[0]][lowerPos[1]]<<endl;

            if(pieceBelow=="0")
            {
                //cout<<"LOWER POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(lowerPos[0]);
                pos+=to_string(lowerPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece above, if enemy piece can move, if our own then cant
                char comp=pieceBelow[0];
                //cout<<"LOWER POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                    //cout<<"LOWER POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(lowerPos[0]);
                    pos+=to_string(lowerPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }    

        //check if can move left in bounds
        if((lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound))
        {
            //check if empty or taken
            vector<int> leftPos;
            leftPos.push_back(lionPosWork[0]);
            leftPos.push_back(lionPosWork[1]-1);
            string pieceLeft=board[leftPos[0]][leftPos[1]];

            // cout<<"IN BOUNDS LEFT"<<endl;
            // cout<<"LEFT POS: "<<board[leftPos[0]][leftPos[1]]<<endl;


            if(pieceLeft=="0")
            {
                //cout<<"LEFT POS EMPTY: "<<board[leftPos[0]][leftPos[1]]<<endl;
                string pos;
                pos+=to_string(leftPos[0]);
                pos+=to_string(leftPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //cout<<"LEFT POS TAKEN: "<<board[leftPos[0]][leftPos[1]]<<endl;
                //there is a piece above, if enemy piece can move, if our own then cant
                //get index 0 for char->string
                char comp=pieceLeft[0];
                if(isupper(comp))
                {
                    //cout<<"LEFT POS ENEMY"<<endl;
                    //apponent piece so can move
                    string pos;
                    pos+=to_string(leftPos[0]);
                    pos+=to_string(leftPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }  

        //checking if can move right in bounds
        if((lionPosWork[1]+1 < lionRightBound || lionPosWork[1]+1==lionRightBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> rightPos;
            rightPos.push_back(lionPosWork[0]);
            rightPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceRight=board[rightPos[0]][rightPos[1]];

            // cout<<"IN BOUNDS RIGHT"<<endl;
            // cout<<"RIGHT POS ELEM: "<<board[rightPos[0]][rightPos[1]]<<endl;

            if(pieceRight=="0")
            {
               // cout<<"RIGHT POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(rightPos[0]);
                pos+=to_string(rightPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceRight[0];
                //cout<<"RIGHT POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                    //cout<<"RIGHT POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(rightPos[0]);
                    pos+=to_string(rightPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }

        //checking if can move diag up left
        if((lionPosWork[0]-1 > lionUpperBound || lionPosWork[0]-1==lionUpperBound) && (lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> udlPos;
            udlPos.push_back(lionPosWork[0]-1);
            udlPos.push_back(lionPosWork[1]-1);
            //piece above is what is physically in the upper pos
            string pieceUDL=board[udlPos[0]][udlPos[1]];

            // cout<<"IN BOUNDS UDL"<<endl;
            // cout<<"UDL POS ELEM: "<<board[udlPos[0]][udlPos[1]]<<endl;

            if(pieceUDL=="0")
            {
                //cout<<"UDL POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(udlPos[0]);
                pos+=to_string(udlPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceUDL[0];
                //cout<<"UDL POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                    //cout<<"UDL POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(udlPos[0]);
                    pos+=to_string(udlPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;

        }

        //checking if can move diag up right
        if((lionPosWork[0]-1 > lionUpperBound || lionPosWork[0]-1==lionUpperBound) && (lionPosWork[1]+1<lionRightBound || lionPosWork[1]+1==lionRightBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> udrPos;
            udrPos.push_back(lionPosWork[0]-1);
            udrPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceUDR=board[udrPos[0]][udrPos[1]];

            // cout<<"IN BOUNDS UDR"<<endl;
            // cout<<"UDR POS ELEM: "<<board[udrPos[0]][udrPos[1]]<<endl;

            if(pieceUDR=="0")
            {
                //cout<<"UDR POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(udrPos[0]);
                pos+=to_string(udrPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceUDR[0];
                //cout<<"UDR POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                   // cout<<"UDR POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(udrPos[0]);
                    pos+=to_string(udrPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            // cout<<endl;
        }

        //checking if can move diag down right
        if((lionPosWork[0]+1 < lionLowerBound || lionPosWork[0]+1==lionLowerBound) && (lionPosWork[1]+1<lionRightBound || lionPosWork[1]+1==lionRightBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> ldrPos;
            ldrPos.push_back(lionPosWork[0]+1);
            ldrPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceLDR=board[ldrPos[0]][ldrPos[1]];

            // cout<<"IN BOUNDS LDR"<<endl;
            // cout<<"LDR POS ELEM: "<<board[ldrPos[0]][ldrPos[1]]<<endl;

            if(pieceLDR=="0")
            {
               // cout<<"LDR POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(ldrPos[0]);
                pos+=to_string(ldrPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceLDR[0];
                //cout<<"LDR POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                   // cout<<"LDR POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(ldrPos[0]);
                    pos+=to_string(ldrPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            //cout<<endl;
        }

        //checking if can move diag down left
        if((lionPosWork[0]+1 < lionLowerBound || lionPosWork[0]+1==lionLowerBound) && (lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> ldlPos;
            ldlPos.push_back(lionPosWork[0]+1);
            ldlPos.push_back(lionPosWork[1]-1);
            //piece above is what is physically in the upper pos
            string pieceLDL=board[ldlPos[0]][ldlPos[1]];

            // cout<<"IN BOUNDS LDL"<<endl;
            // cout<<"LDL POS ELEM: "<<board[ldlPos[0]][ldlPos[1]]<<endl;

            if(pieceLDL=="0")
            {
                //cout<<"LDL POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(ldlPos[0]);
                pos+=to_string(ldlPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceLDL[0];
               // cout<<"LDL POS TAKEN"<<endl;
                if(isupper(comp))
                {
                    //apponent piece so can move
                   // cout<<"LDL POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(ldlPos[0]);
                    pos+=to_string(ldlPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            // cout<<endl;
        }

        /* 
            ->check to see if can cross river and kill enemy lion
                ->left diag
                ->right dia
                ->straight ahead
                ->make sure no pieces in way
        */

       //check staright infront
       if(bLionPosString[0]==wLionPosString[0])
       {
            bool canKill=true;
            //cout<<"ATTEMPT KILL"<<endl;

            string colBLion;
            colBLion+=bLion.posNum[0];

            string rowBLion;
            rowBLion+=bLion.posNum[1];

            string rowWLion;
            rowWLion+=wLion.posNum[1];

            string colWLion;
            colWLion+=wLion.posNum[0];
           // cout<<bLionPosString[0]<<bLionPosString[1]<<endl;
           // cout<<board[0][2]<<endl;
            //loop through board and check if other pieces aling the path
            for(int row=stoi(rowBLion)-2; row>=stoi(rowWLion);--row)
            {
               // cout<<"("<<row<<","<<colBLion<<")"<<board[row][stoi(colBLion)]<<endl;
                if(board[row][stoi(colBLion)]!="0")
                {
                    canKill=false;
                    //cout<<"CANNOT KILL"<<endl;
                }
            }
            if(canKill)
            {
               // cout<<"CAN KILL"<<endl;
                allPossibleMoves.push_back(bLionPosString+wLionPosString);
            }
       }

        //check right diagonal
        if(bLionPosString=="c5" && wLionPosString=="e3" && board[3][3]=="0")
        {
            allPossibleMoves.push_back(bLionPosString+wLionPosString);
        }


        //check left diag
        if(bLionPosString=="e5" && wLionPosString=="c3" && board[3][3]=="0")
        {
            allPossibleMoves.push_back(bLionPosString+wLionPosString);
        }

        for(string i : possibleMoves)
        {
            //increment the row
            string newRow;
            newRow+=i[0];
            int intRow=stoi(newRow);
            intRow++;
            string finalRow=to_string(intRow);

            //switch row and col
            string switchedString;
            switchedString+=i[1];
            switchedString+=finalRow;

            //get letter 
            char letter;
            if(switchedString[0]=='0')
            {
                letter='a';
            }
            else if(switchedString[0]=='1')
            {
                letter='b';
            }
            else if(switchedString[0]=='2')
            {
                letter='c';
            }
            else if(switchedString[0]=='3')
            {
                letter='d';
            }
            else if(switchedString[0]=='4')
            {
                letter='e';
            }
            else if(switchedString[0]=='5')
            {
                letter='f';
            }
            else if(switchedString[0]=='6')
            {
                letter='g';
            }


            string finalString;
            finalString+=letter;
            finalString+=switchedString[1];

            string combinedString=lion.pos+finalString;
            
            allPossibleMoves.push_back(combinedString);
            // cout<<endl;
        }
 
    }

    else if(FENString.sideToMove=="white")
    {
        //whites turn therefore nly cnsider white 

        //get pos of white lion 
        vector<Piece> lionArray=FENString.wLion;
        Piece lion=lionArray[0];
        string lionPosString=lion.posNum;
        lionPosString[1]-=1;

        string lionx;
        lionx+=lionPosString[0];
        string liony;
        liony+=lionPosString[1];

        vector<int> lionPosGame;
        vector<int> lionPosWork;

        lionPosGame.push_back(stoi(lionx));
        lionPosGame.push_back(stoi(liony));

        lionPosWork.push_back(stoi(liony));
        lionPosWork.push_back(stoi(lionx));

        //cout<<"LION POS: "<<lionPosWork[0]<<lionPosWork[1]<<endl;

        //upper bound of lion 3x3 grid
        int lionUpperBound=2;
        //lower bound of lion
        int lionLowerBound=0;
        //lion left bound
        int lionLeftBound=2;
        //lion right bound
        int lionRightBound=4;

        //checking if can move up in bounds
        if((lionPosWork[0]+1 < lionUpperBound || lionPosWork[0]+1==lionUpperBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of above pos
            vector<int> upperPos;
            upperPos.push_back(lionPosWork[0]+1);
            upperPos.push_back(lionPosWork[1]);
            //piece above is what is physically in the upper pos
            string pieceAbove=board[upperPos[0]][upperPos[1]];

            // cout<<"IN BOUNDS UPPER"<<endl;
            // cout<<"UPPER POS ELEM: "<<board[upperPos[0]][upperPos[1]]<<endl;

            if(pieceAbove=="0")
            {
               // cout<<"UPPER POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(upperPos[0]);
                pos+=to_string(upperPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece above, if enemy piece can move, if our own then cant
                char comp=pieceAbove[0];
                //cout<<"UPPER POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                   // cout<<"UPPER POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(upperPos[0]);
                    pos+=to_string(upperPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }

        //checking if can move down in bounds
        if((lionPosWork[0]-1 > lionLowerBound || lionPosWork[0]-1==lionLowerBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of above pos
            vector<int> lowerPos;
            lowerPos.push_back(lionPosWork[0]-1);
            lowerPos.push_back(lionPosWork[1]);
            //piece above is what is physically in the upper pos
            string pieceBelow=board[lowerPos[0]][lowerPos[1]];

            // cout<<"IN BOUNDS LOWER"<<endl;
            // cout<<"LOWER POS ELEM: "<<board[lowerPos[0]][lowerPos[1]]<<endl;

            if(pieceBelow=="0")
            {
                //cout<<"LOWER POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(lowerPos[0]);
                pos+=to_string(lowerPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece above, if enemy piece can move, if our own then cant
                char comp=pieceBelow[0];
               // cout<<"LOWER POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                   // cout<<"LOWER POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(lowerPos[0]);
                    pos+=to_string(lowerPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }    

        //check if can move left in bounds
        if((lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound))
        {
            //check if empty or taken
            vector<int> leftPos;
            leftPos.push_back(lionPosWork[0]);
            leftPos.push_back(lionPosWork[1]-1);
            string pieceLeft=board[leftPos[0]][leftPos[1]];

            // cout<<"IN BOUNDS LEFT"<<endl;
            // cout<<"LEFT POS: "<<board[leftPos[0]][leftPos[1]]<<endl;


            if(pieceLeft=="0")
            {
               // cout<<"LEFT POS EMPTY: "<<board[leftPos[0]][leftPos[1]]<<endl;
                string pos;
                pos+=to_string(leftPos[0]);
                pos+=to_string(leftPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                // cout<<"LEFT POS TAKEN: "<<board[leftPos[0]][leftPos[1]]<<endl;
                //there is a piece above, if enemy piece can move, if our own then cant
                //get index 0 for char->string
                char comp=pieceLeft[0];
                if(islower(comp))
                {
                    // cout<<"LEFT POS ENEMY"<<endl;
                    //apponent piece so can move
                    string pos;
                    pos+=to_string(leftPos[0]);
                    pos+=to_string(leftPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }  

        //checking if can move right in bounds
        if((lionPosWork[1]+1 < lionRightBound || lionPosWork[1]+1==lionRightBound))
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> rightPos;
            rightPos.push_back(lionPosWork[0]);
            rightPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceRight=board[rightPos[0]][rightPos[1]];

            // cout<<"IN BOUNDS RIGHT"<<endl;
            // cout<<"RIGHT POS ELEM: "<<board[rightPos[0]][rightPos[1]]<<endl;

            if(pieceRight=="0")
            {
                // cout<<"RIGHT POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(rightPos[0]);
                pos+=to_string(rightPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceRight[0];
                // cout<<"RIGHT POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                    // cout<<"RIGHT POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(rightPos[0]);
                    pos+=to_string(rightPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;
        }

        //checking if can move diag up left
        if((lionPosWork[0]+1 < lionUpperBound || lionPosWork[0]+1==lionUpperBound) && (lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> udlPos;
            udlPos.push_back(lionPosWork[0]+1);
            udlPos.push_back(lionPosWork[1]-1);
            //piece above is what is physically in the upper pos
            string pieceUDL=board[udlPos[0]][udlPos[1]];

            // cout<<"IN BOUNDS UDL"<<endl;
            // cout<<"UDL POS ELEM: "<<board[udlPos[0]][udlPos[1]]<<endl;

            if(pieceUDL=="0")
            {
                // cout<<"UDL POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(udlPos[0]);
                pos+=to_string(udlPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceUDL[0];
                // cout<<"UDL POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                    // cout<<"UDL POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(udlPos[0]);
                    pos+=to_string(udlPos[1]);
                    possibleMoves.push_back(pos);
                }
            }
            // cout<<endl;

        }

        //checking if can move diag up right
        if((lionPosWork[0]+1 < lionUpperBound || lionPosWork[0]+1==lionUpperBound) && (lionPosWork[1]+1<lionRightBound || lionPosWork[1]+1==lionRightBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> udrPos;
            udrPos.push_back(lionPosWork[0]+1);
            udrPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceUDR=board[udrPos[0]][udrPos[1]];

            // cout<<"IN BOUNDS UDR"<<endl;
            // cout<<"UDR POS ELEM: "<<board[udrPos[0]][udrPos[1]]<<endl;

            if(pieceUDR=="0")
            {
                // cout<<"UDR POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(udrPos[0]);
                pos+=to_string(udrPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceUDR[0];
                // cout<<"UDR POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                    // cout<<"UDR POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(udrPos[0]);
                    pos+=to_string(udrPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            // cout<<endl;
        }

        //checking if can move diag down right
        if((lionPosWork[0]-1 > lionLowerBound || lionPosWork[0]-1==lionLowerBound) && (lionPosWork[1]+1<lionRightBound || lionPosWork[1]+1==lionRightBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> ldrPos;
            ldrPos.push_back(lionPosWork[0]-1);
            ldrPos.push_back(lionPosWork[1]+1);
            //piece above is what is physically in the upper pos
            string pieceLDR=board[ldrPos[0]][ldrPos[1]];

            // cout<<"IN BOUNDS LDR"<<endl;
            // cout<<"LDR POS ELEM: "<<board[ldrPos[0]][ldrPos[1]]<<endl;

            if(pieceLDR=="0")
            {
                // cout<<"LDR POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(ldrPos[0]);
                pos+=to_string(ldrPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceLDR[0];
                // cout<<"LDR POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                    // cout<<"LDR POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(ldrPos[0]);
                    pos+=to_string(ldrPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            // cout<<endl;
        }

        //checking if can move diag down left
        if((lionPosWork[0]-1 > lionLowerBound || lionPosWork[0]-1==lionLowerBound) && (lionPosWork[1]-1>lionLeftBound || lionPosWork[1]-1==lionLeftBound) )
        {
            //check if empty or taken
            
            //upper pos is the coords of right pos
            vector<int> ldlPos;
            ldlPos.push_back(lionPosWork[0]-1);
            ldlPos.push_back(lionPosWork[1]-1);
            //piece above is what is physically in the upper pos
            string pieceLDL=board[ldlPos[0]][ldlPos[1]];

            // cout<<"IN BOUNDS LDL"<<endl;
            // cout<<"LDL POS ELEM: "<<board[ldlPos[0]][ldlPos[1]]<<endl;

            if(pieceLDL=="0")
            {
                // cout<<"LDL POS IS EMPTY"<<endl;
                string pos;
                pos+=to_string(ldlPos[0]);
                pos+=to_string(ldlPos[1]);
                possibleMoves.push_back(pos);
            }
            else
            {
                //there is a piece right, if enemy piece can move, if our own then cant
                char comp=pieceLDL[0];
                // cout<<"LDL POS TAKEN"<<endl;
                if(islower(comp))
                {
                    //apponent piece so can move
                    // cout<<"LDL POS TAKEN BY ENEMY"<<endl;
                    string pos;
                    pos+=to_string(ldlPos[0]);
                    pos+=to_string(ldlPos[1]);
                    possibleMoves.push_back(pos);
                }
            }

            // cout<<endl;
        }

        /* 
            ->check to see if can cross river and kill enemy lion
                ->left diag
                ->right dia
                ->straight ahead
                ->make sure no pieces in way
        */

       //check staright infront
       if(bLionPosString[0]==wLionPosString[0])
       {
            bool canKill=true;
           // cout<<"ATTEMPT KILL"<<endl;

            string colBLion;
            colBLion+=bLion.posNum[0];

            string rowBLion;
            rowBLion+=bLion.posNum[1];

            string rowWLion;
            rowWLion+=wLion.posNum[1];

            string colWLion;
            colWLion+=wLion.posNum[0];

            //loop through board and check if other pieces aling the path
            for(int row=stoi(rowBLion)-2; row>=stoi(rowWLion);--row)
            {
               // cout<<"("<<row<<","<<colBLion<<")"<<board[row][stoi(colBLion)]<<endl;
                if(board[row][stoi(colBLion)]!="0")
                {
                    canKill=false;
                    //cout<<"CANNOT KILL"<<endl;
                }
            }

            if(canKill)
            {
               // cout<<"CAN KILL"<<endl;
                allPossibleMoves.push_back(wLionPosString+bLionPosString);
            }
       }

        //check right diagonal
        if(bLionPosString=="c5" && wLionPosString=="e3" && board[3][3]=="0")
        {
            allPossibleMoves.push_back(wLionPosString+bLionPosString);
        }


        //check left diag
        if(bLionPosString=="e5" && wLionPosString=="c3" && board[3][3]=="0")
        {
            allPossibleMoves.push_back(wLionPosString+bLionPosString);
        }

        for(string i : possibleMoves)
        {

            //increment the row
            string newRow;
            newRow+=i[0];
            int intRow=stoi(newRow);
            intRow++;
            string finalRow=to_string(intRow);

            //switch row and col
            string switchedString;
            switchedString+=i[1];
            switchedString+=finalRow;

            //get letter 
            char letter;
            if(switchedString[0]=='0')
            {
                letter='a';
            }
            else if(switchedString[0]=='1')
            {
                letter='b';
            }
            else if(switchedString[0]=='2')
            {
                letter='c';
            }
            else if(switchedString[0]=='3')
            {
                letter='d';
            }
            else if(switchedString[0]=='4')
            {
                letter='e';
            }
            else if(switchedString[0]=='5')
            {
                letter='f';
            }
            else if(switchedString[0]=='6')
            {
                letter='g';
            }


            string finalString;
            finalString+=letter;
            finalString+=switchedString[1];

            string combinedString=lion.pos+finalString;
            allPossibleMoves.push_back(combinedString);

            // cout<<endl;
        }
 
    }

    //sort the array of moves
   // sort(allPossibleMoves.begin(), allPossibleMoves.end(), comp);
    return allPossibleMoves;
}

/*ZEBRA MOVE GENERATOR*/
vector<string> zebraMoves(vector<vector<string>> board, FEN FENString)
{
    //holds inv possible moves
    vector<string> possibleMoves;
    //all final possible moves
    vector<string> allPossibleMoves;

    //get array containg all zebras for black and white peaces
    vector<Piece> wZebraArray=FENString.wZebra;
    vector<Piece> bZebraArray=FENString.bZebra;

    Piece wZebra;
    Piece bZebra;

    //can contain zero zeras and so need to check for that
    if(FENString.sideToMove=="white")
    {
        //whites turn to moe so calc pos only for white zebra
       // cout<<"WHITE TURM"<<endl;
        //create a pice for the zebras if they exist
        if(wZebraArray.size()!=0)
        {
         //   cout<<"WHITE ZEBRA PRESENT"<<endl;
            wZebra=wZebraArray[0];
        }
        else
        {
            //just return empty allPossibleMoves are there are none
          //  cout<<"NO WHITE ZEBRA"<<endl;
            return allPossibleMoves;
        }

        //get pos of zebra
        string zebraPosString=wZebra.posNum;
        zebraPosString[1]--;

        vector<vector<int>> GWP=getGWP(zebraPosString);

        vector<int> zebraPosGame=GWP[0];
        vector<int> zebraPosWork=GWP[1];

       // cout<<"WORK POS ZEB: "<<zebraPosWork[0]<<zebraPosWork[1]<<endl;

        /*
            POSSIBLE COMBINATIONS
                ->LLU
                ->LLD
                ->LUU
                ->LDD

                ->RRU
                ->RRD
                ->RUU
                ->RDD

                ->UUL
                ->UUR
                ->ULL
                ->URR

                ->DDL
                ->DDR
                ->DLL
                ->DRR

            AFTR EQUIV
                ->UUR/RUU
                ->URR/RRU
                ->DDR/RDD
                ->DRR/RRD

                ->UUL/LUU
                ->ULL/LLU
                ->DDL/LDD
                ->DLL/LLD
        */


       // UUR/RUU
       vector<int> UUR={zebraPosWork[0]+2, zebraPosWork[1]+1};

       // URR/RRU
       vector<int> URR={zebraPosWork[0]+1, zebraPosWork[1]+2};

       // DDR/RDD
       vector<int> DDR={zebraPosWork[0]-2, zebraPosWork[1]+1};

       // DRR/RRD
       vector<int> DRR={zebraPosWork[0]-1, zebraPosWork[1]+2};

       // UUL/LUU
       vector<int> UUL={zebraPosWork[0]+2, zebraPosWork[1]-1};

       // ULL/LLU
       vector<int> ULL={zebraPosWork[0]+1, zebraPosWork[1]-2};

       // DDL/LDD
       vector<int> DDL={zebraPosWork[0]-2, zebraPosWork[1]-1};

       // DLL/LLD
       vector<int> DLL={zebraPosWork[0]-1, zebraPosWork[1]-2};


        if(UUR[0]>=0 && UUR[1]>=0 && UUR[0]<=6 && UUR[1]<=6)
        {
            string uur=board[UUR[0]][UUR[1]];
            //cout<<uur<<endl;
            if(uur=="0" || islower(uur[0]))
            {
                    string pos;
                    pos+=to_string(UUR[0]);
                    pos+=to_string(UUR[1]);
                    possibleMoves.push_back(pos);
                    //cout<<"UUR IS VALID"<<endl;
            }
        }

        
        if(URR[0]>=0 && URR[1]>=0 && URR[0]<=6 && URR[1]<=6)
        {
            string urr=board[URR[0]][URR[1]];
           // cout<<urr<<endl;
            if(urr=="0" || islower(urr[0]))
            {
                string pos;
                pos+=to_string(URR[0]);
                pos+=to_string(URR[1]);
                possibleMoves.push_back(pos);
               // cout<<"URR IS VALID"<<endl;
            }
        }

        if(DDR[0]>=0 && DDR[1]>=0 && DDR[0]<=6 && DDR[1]<=6)
        {
            string ddr=board[DDR[0]][DDR[1]];
            //cout<<ddr<<endl;
            if(ddr=="0" || islower(ddr[0]))
            {
                string pos;
                pos+=to_string(DDR[0]);
                pos+=to_string(DDR[1]);
                possibleMoves.push_back(pos);
               // cout<<"DDR IS VALID"<<endl;
            }
        }

        if(DRR[0]>=0 && DRR[1]>=0 && DRR[0]<=6 && DRR[1]<=6)
        {
            string drr=board[DRR[0]][DRR[1]];
            //cout<<drr<<endl;
            if(drr=="0" || islower(drr[0]))
            {
                string pos;
                pos+=to_string(DRR[0]);
                pos+=to_string(DRR[1]);
                possibleMoves.push_back(pos);
                //cout<<"DRR IS VALID"<<endl;
            }
        }

        if(UUL[0]>=0 && UUL[1]>=0 && UUL[0]<=6 && UUL[1]<=6)
        {
            string uul=board[UUL[0]][UUL[1]];
            //cout<<uul<<endl;
            if(uul=="0" || islower(uul[0]))
            {
                string pos;
                pos+=to_string(UUL[0]);
                pos+=to_string(UUL[1]);
                possibleMoves.push_back(pos);
               // cout<<"UUL IS VALID"<<endl;
            }
        }

        if(ULL[0]>=0 && ULL[1]>=0 && ULL[0]<=6 && ULL[1]<=6)
        {
            string ull=board[ULL[0]][ULL[1]];
            //cout<<ull<<endl;
            if(ull=="0" || islower(ull[0]))
            {
                string pos;
                pos+=to_string(ULL[0]);
                pos+=to_string(ULL[1]);
                possibleMoves.push_back(pos);
                //cout<<"ULL IS VALID"<<endl;
            }
        }

        if(DDL[0]>=0 && DDL[1]>=0 && DDL[0]<=6 && DDL[1]<=6)
        {
            string ddl=board[DDL[0]][DDL[1]];
           // cout<<ddl<<endl;
            if(ddl=="0" || islower(ddl[0]))
            {
                    string pos;
                    pos+=to_string(DDL[0]);
                    pos+=to_string(DDL[1]);
                    possibleMoves.push_back(pos);
                   // cout<<"DDL IS VALID"<<endl;
            }
        }

        if(DLL[0]>=0 && DLL[1]>=0 && DLL[0]<=6 && DLL[1]<=6)
        {
            string dll=board[DLL[0]][DLL[1]];
            //cout<<dll<<endl;
            if(dll=="0" || islower(dll[0]))
            {
                    string pos;
                    pos+=to_string(DLL[0]);
                    pos+=to_string(DLL[1]);
                    possibleMoves.push_back(pos);
                   // cout<<"DLL IS VALID"<<endl;
            }
        }

       allPossibleMoves=converToAnswerString(possibleMoves, wZebra);

    }
    else if(FENString.sideToMove=="black")
    {
        //whites turn to moe so calc pos only for white zebra
       // cout<<"WHITE TURM"<<endl;
        //create a pice for the zebras if they exist
        if(bZebraArray.size()!=0)
        {
         //   cout<<"WHITE ZEBRA PRESENT"<<endl;
            bZebra=bZebraArray[0];
        }
        else
        {
            //just return empty allPossibleMoves are there are none
          //  cout<<"NO WHITE ZEBRA"<<endl;
            return allPossibleMoves;
        }

        //get pos of zebra
        string zebraPosString=bZebra.posNum;
        zebraPosString[1]--;

        vector<vector<int>> GWP=getGWP(zebraPosString);

        vector<int> zebraPosGame=GWP[0];
        vector<int> zebraPosWork=GWP[1];

       // cout<<"WORK POS ZEB: "<<zebraPosWork[0]<<zebraPosWork[1]<<endl;

        /*
            POSSIBLE COMBINATIONS
                ->LLU
                ->LLD
                ->LUU
                ->LDD

                ->RRU
                ->RRD
                ->RUU
                ->RDD

                ->UUL
                ->UUR
                ->ULL
                ->URR

                ->DDL
                ->DDR
                ->DLL
                ->DRR

            AFTR EQUIV
                ->UUR/RUU
                ->URR/RRU
                ->DDR/RDD
                ->DRR/RRD

                ->UUL/LUU
                ->ULL/LLU
                ->DDL/LDD
                ->DLL/LLD
        */


       // UUR/RUU
       vector<int> UUR={zebraPosWork[0]-2, zebraPosWork[1]+1};

       // URR/RRU
       vector<int> URR={zebraPosWork[0]-1, zebraPosWork[1]+2};

       // DDR/RDD
       vector<int> DDR={zebraPosWork[0]+2, zebraPosWork[1]+1};

       // DRR/RRD
       vector<int> DRR={zebraPosWork[0]+1, zebraPosWork[1]+2};

       // UUL/LUU
       vector<int> UUL={zebraPosWork[0]-2, zebraPosWork[1]-1};

       // ULL/LLU
       vector<int> ULL={zebraPosWork[0]-1, zebraPosWork[1]-2};

       // DDL/LDD
       vector<int> DDL={zebraPosWork[0]+2, zebraPosWork[1]-1};

       // DLL/LLD
       vector<int> DLL={zebraPosWork[0]+1, zebraPosWork[1]-2};


        if(UUR[0]>=0 && UUR[1]>=0 && UUR[0]<=6 && UUR[1]<=6)
        {
            string uur=board[UUR[0]][UUR[1]];
            //cout<<uur<<endl;
            if(uur=="0" || isupper(uur[0]))
            {
                    string pos;
                    pos+=to_string(UUR[0]);
                    pos+=to_string(UUR[1]);
                    possibleMoves.push_back(pos);
                //   cout<<"UUR IS VALID"<<endl;
            }
        }

        
        if(URR[0]>=0 && URR[1]>=0 && URR[0]<=6 && URR[1]<=6)
        {
            string urr=board[URR[0]][URR[1]];
            //cout<<urr<<endl;
            if(urr=="0" || isupper(urr[0]))
            {
                string pos;
                pos+=to_string(URR[0]);
                pos+=to_string(URR[1]);
                possibleMoves.push_back(pos);
            // cout<<"URR IS VALID"<<endl;
            }
        }

        if(DDR[0]>=0 && DDR[1]>=0 && DDR[0]<=6 && DDR[1]<=6)
        {
            string ddr=board[DDR[0]][DDR[1]];
            // cout<<ddr<<endl;
            if(ddr=="0" || isupper(ddr[0]))
            {
                string pos;
                pos+=to_string(DDR[0]);
                pos+=to_string(DDR[1]);
                possibleMoves.push_back(pos);
                // cout<<"DDR IS VALID"<<endl;
            }
        }

        if(DRR[0]>=0 && DRR[1]>=0 && DRR[0]<=6 && DRR[1]<=6)
        {
            string drr=board[DRR[0]][DRR[1]];
            // cout<<drr<<endl;
            if(drr=="0" || isupper(drr[0]))
            {
                string pos;
                pos+=to_string(DRR[0]);
                pos+=to_string(DRR[1]);
                possibleMoves.push_back(pos);
                //  cout<<"DRR IS VALID"<<endl;
            }
        }

        if(UUL[0]>=0 && UUL[1]>=0 && UUL[0]<=6 && UUL[1]<=6)
        {
            string uul=board[UUL[0]][UUL[1]];
            // cout<<uul<<endl;
            if(uul=="0" || isupper(uul[0]))
            {
                string pos;
                pos+=to_string(UUL[0]);
                pos+=to_string(UUL[1]);
                possibleMoves.push_back(pos);
                // cout<<"UUL IS VALID"<<endl;
            }
        }

        if(ULL[0]>=0 && ULL[1]>=0 && ULL[0]<=6 && ULL[1]<=6)
        {
            string ull=board[ULL[0]][ULL[1]];
            // cout<<ull<<endl;
            if(ull=="0" || isupper(ull[0]))
            {
                string pos;
                pos+=to_string(ULL[0]);
                pos+=to_string(ULL[1]);
                possibleMoves.push_back(pos);
                // cout<<"ULL IS VALID"<<endl;
            }
        }

        if(DDL[0]>=0 && DDL[1]>=0 && DDL[0]<=6 && DDL[1]<=6)
        {
            string ddl=board[DDL[0]][DDL[1]];
            // cout<<ddl<<endl;
            if(ddl=="0" || isupper(ddl[0]))
            {
                    string pos;
                    pos+=to_string(DDL[0]);
                    pos+=to_string(DDL[1]);
                    possibleMoves.push_back(pos);
                //   cout<<"DDL IS VALID"<<endl;
            }
        }

        if(DLL[0]>=0 && DLL[1]>=0 && DLL[0]<=6 && DLL[1]<=6)
        {
            string dll=board[DLL[0]][DLL[1]];
            //cout<<dll<<endl;
            if(dll=="0" || isupper(dll[0]))
            {
                    string pos;
                    pos+=to_string(DLL[0]);
                    pos+=to_string(DLL[1]);
                    possibleMoves.push_back(pos);
                // cout<<"DLL IS VALID"<<endl;
            }
        }

       allPossibleMoves=converToAnswerString(possibleMoves, bZebra);
    }

    //sort(allPossibleMoves.begin(), allPossibleMoves.end(), comp);
    return allPossibleMoves;
}


/*GIRAGGE MOVE GEN*/
vector<string> giraffeMoves(vector<vector<string>>board, FEN FENString)
{
    //holds inv possible moves
    vector<string> possibleMoves;
    //all final possible moves
    vector<string> allPossibleMoves;

    //get array containg all zebras for black and white peaces
    vector<Piece> wGiraffeArray=FENString.wGiraffe;
    vector<Piece> bGiraffeArray=FENString.bGiraffe;

    Piece wGiraffe;
    Piece bGiraffe;

    if(FENString.sideToMove=="white")
    {
        //whites turn to moe so calc pos only for white zebra
        //create a pice for the zebras if they exist
        if(wGiraffeArray.size()!=0)
        {
            wGiraffe=wGiraffeArray[0];
        }
        else
        {
            //just return empty allPossibleMoves are there are none
            return allPossibleMoves;
        }

        //get pos of zebra
        string giraffePosString=wGiraffe.posNum;
        giraffePosString[1]--;

        vector<vector<int>> GWP=getGWP(giraffePosString);

        vector<int> giraffePosGame=GWP[0];
        vector<int> giraffePosWork=GWP[1];

        /*
            check all positions aftr moving down 1-> diag left/ diag right/ down
            if out of bounds do not need to chek down 2
            if in bounds check 2 down
        */

       /*LEFT*/
        if(giraffePosWork[1]-1>=0)
        {
            //left
            string newLeftPos=board[giraffePosWork[0]][giraffePosWork[1]-1];
            if(newLeftPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]);
                pos+=to_string(giraffePosWork[1]-1);
                possibleMoves.push_back(pos);
            }

            if(giraffePosWork[1]-2>=0)
            {
                string newPos=board[giraffePosWork[0]][giraffePosWork[1]-2];
                if(newPos=="0" || islower(newPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]);
                    pos+=to_string(giraffePosWork[1]-2);
                    possibleMoves.push_back(pos);
                }
            }
        }

       /*RUGHT*/
        if(giraffePosWork[1]+1<=6)
        {
            //right
            string newLeftPos=board[giraffePosWork[0]][giraffePosWork[1]+1];
            if(newLeftPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]);
                pos+=to_string(giraffePosWork[1]+1);
                possibleMoves.push_back(pos);
            }

            if(giraffePosWork[1]+2<=6)
            {
                string newPos=board[giraffePosWork[0]][giraffePosWork[1]+2];
                if(newPos=="0" || islower(newPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]);
                    pos+=to_string(giraffePosWork[1]+2);
                    possibleMoves.push_back(pos);
                }
            }
        }


       /*DOWN*/
        //first check if possible to move down (in bounds)
        if(giraffePosWork[0]-1>=0)
        {
            //down pos
            string newDownPos=board[giraffePosWork[0]-1][giraffePosWork[1]];
            if(newDownPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]-1);
                pos+=to_string(giraffePosWork[1]);
                possibleMoves.push_back(pos);
            }

            /*deal with 1 down*/
            //LEFT (diag left)
            if(giraffePosWork[1]-1>=0)
            {
                //diag down left
                string newPos=board[giraffePosWork[0]-1][giraffePosWork[1]-1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-1);
                    pos+=to_string(giraffePosWork[1]-1);
                    possibleMoves.push_back(pos);
                }
            }
            if(giraffePosWork[1]+1<=6)
            {
                //diag down right
                string newPos=board[giraffePosWork[0]-1][giraffePosWork[1]+1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-1);
                    pos+=to_string(giraffePosWork[1]+1);
                    possibleMoves.push_back(pos);
                }
            }

            /*down 2*/
            if(giraffePosWork[0]-2>=0)
            {
                //down pos
                string newDownPos=board[giraffePosWork[0]-2][giraffePosWork[1]];
                if(newDownPos=="0" || islower(newDownPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-2);
                    pos+=to_string(giraffePosWork[1]);
                    possibleMoves.push_back(pos);
                }

                /*deal with 1 down*/
                //LEFT (diag left)
                if(giraffePosWork[1]-2>=0)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]-2][giraffePosWork[1]-2];
                    if(newPos=="0" || islower(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]-2);
                        pos+=to_string(giraffePosWork[1]-2);
                        possibleMoves.push_back(pos);
                    }
                }
                if(giraffePosWork[1]+2<=6)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]-2][giraffePosWork[1]+2];
                    if(newPos=="0" || islower(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]-2);
                        pos+=to_string(giraffePosWork[1]+2);
                        possibleMoves.push_back(pos);
                    }
                }
            }

        }

        /*UP*/
        if(giraffePosWork[0]+1<=6)
        {
            //up pos
            string newUpPos=board[giraffePosWork[0]+1][giraffePosWork[1]];
            if(newUpPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]+1);
                pos+=to_string(giraffePosWork[1]);
                possibleMoves.push_back(pos);
            }

            /*deal with 1 up*/
            //LEFT (diag left)
            if(giraffePosWork[1]-1>=0)
            {
                //diag down left
                string newPos=board[giraffePosWork[0]+1][giraffePosWork[1]-1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+1);
                    pos+=to_string(giraffePosWork[1]-1);
                    possibleMoves.push_back(pos);
                }
            }

            if(giraffePosWork[1]+1<=6)
            {
                //diag down right
                string newPos=board[giraffePosWork[0]+1][giraffePosWork[1]+1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+1);
                    pos+=to_string(giraffePosWork[1]+1);
                    possibleMoves.push_back(pos);
                }
            }
            /*double up*/
            if(giraffePosWork[0]+2<=6)
            {
                //down pos
                string newDownPos=board[giraffePosWork[0]+2][giraffePosWork[1]];
                if(newDownPos=="0" || islower(newDownPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+2);
                    pos+=to_string(giraffePosWork[1]);
                    possibleMoves.push_back(pos);
                }

                /*deal with 1 down*/
                //LEFT (diag left)
                if(giraffePosWork[1]-2>=0)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]+2][giraffePosWork[1]-2];
                    if(newPos=="0" || islower(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]+2);
                        pos+=to_string(giraffePosWork[1]-2);
                        possibleMoves.push_back(pos);
                    }
                }
                if(giraffePosWork[1]+2<=6)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]+2][giraffePosWork[1]+2];
                    if(newPos=="0" || islower(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]+2);
                        pos+=to_string(giraffePosWork[1]+2);
                        possibleMoves.push_back(pos);
                    }
                }
            }

        }
        allPossibleMoves=converToAnswerString(possibleMoves, wGiraffe);

    }

    if(FENString.sideToMove=="black")
    {
        //whites turn to moe so calc pos only for white zebra
        //create a pice for the zebras if they exist
        if(bGiraffeArray.size()!=0)
        {
            bGiraffe=bGiraffeArray[0];
        }
        else
        {
            //just return empty allPossibleMoves are there are none
            return allPossibleMoves;
        }

        //get pos of zebra
        string giraffePosString=bGiraffe.posNum;
        giraffePosString[1]--;

        vector<vector<int>> GWP=getGWP(giraffePosString);

        vector<int> giraffePosGame=GWP[0];
        vector<int> giraffePosWork=GWP[1];

        /*
            check all positions aftr moving down 1-> diag left/ diag right/ down
            if out of bounds do not need to chek down 2
            if in bounds check 2 down
        */

       /*LEFT*/
        if(giraffePosWork[1]-1>=0)
        {
            //left
            string newLeftPos=board[giraffePosWork[0]][giraffePosWork[1]-1];
            if(newLeftPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]);
                pos+=to_string(giraffePosWork[1]-1);
                possibleMoves.push_back(pos);
            }

            if(giraffePosWork[1]-2>=0)
            {
                string newPos=board[giraffePosWork[0]][giraffePosWork[1]-2];
                if(newPos=="0" || isupper(newPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]);
                    pos+=to_string(giraffePosWork[1]-2);
                    possibleMoves.push_back(pos);
                }
            }
        }

       /*RUGHT*/
        if(giraffePosWork[1]+1<=6)
        {
            //right
            string newLeftPos=board[giraffePosWork[0]][giraffePosWork[1]+1];
            if(newLeftPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]);
                pos+=to_string(giraffePosWork[1]+1);
                possibleMoves.push_back(pos);
            }

            if(giraffePosWork[1]+2<=6)
            {
                string newPos=board[giraffePosWork[0]][giraffePosWork[1]+2];
                if(newPos=="0" || isupper(newPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]);
                    pos+=to_string(giraffePosWork[1]+2);
                    possibleMoves.push_back(pos);
                }
            }
        }
       /*DOWN*/
        //first check if possible to move down (in bounds)
        if(giraffePosWork[0]-1>=0)
        {
            //down pos
            string newDownPos=board[giraffePosWork[0]-1][giraffePosWork[1]];
            if(newDownPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]-1);
                pos+=to_string(giraffePosWork[1]);
                possibleMoves.push_back(pos);
            }

            /*deal with 1 down*/
            //LEFT (diag left)
            if(giraffePosWork[1]-1>=0)
            {
                //diag down left
                string newPos=board[giraffePosWork[0]-1][giraffePosWork[1]-1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-1);
                    pos+=to_string(giraffePosWork[1]-1);
                    possibleMoves.push_back(pos);
                }
            }
            if(giraffePosWork[1]+1<=6)
            {
                //diag down right
                string newPos=board[giraffePosWork[0]-1][giraffePosWork[1]+1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-1);
                    pos+=to_string(giraffePosWork[1]+1);
                    possibleMoves.push_back(pos);
                }
            }

            /*down 2*/
            if(giraffePosWork[0]-2>=0)
            {
                //down pos
                string newDownPos=board[giraffePosWork[0]-2][giraffePosWork[1]];
                if(newDownPos=="0" || isupper(newDownPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]-2);
                    pos+=to_string(giraffePosWork[1]);
                    possibleMoves.push_back(pos);
                }

                /*deal with 1 down*/
                //LEFT (diag left)
                if(giraffePosWork[1]-2>=0)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]-2][giraffePosWork[1]-2];
                    if(newPos=="0" || isupper(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]-2);
                        pos+=to_string(giraffePosWork[1]-2);
                        possibleMoves.push_back(pos);
                    }
                }
                if(giraffePosWork[1]+2<=6)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]-2][giraffePosWork[1]+2];
                    if(newPos=="0" || isupper(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]-2);
                        pos+=to_string(giraffePosWork[1]+2);
                        possibleMoves.push_back(pos);
                    }
                }
            }

        }

        /*UP*/
        if(giraffePosWork[0]+1<=6)
        {
            //up pos
            string newUpPos=board[giraffePosWork[0]+1][giraffePosWork[1]];
            if(newUpPos=="0")
            {
                string pos;
                pos+=to_string(giraffePosWork[0]+1);
                pos+=to_string(giraffePosWork[1]);
                possibleMoves.push_back(pos);
            }

            /*deal with 1 up*/
            //LEFT (diag left)
            if(giraffePosWork[1]-1>=0)
            {
                //diag down left
                string newPos=board[giraffePosWork[0]+1][giraffePosWork[1]-1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+1);
                    pos+=to_string(giraffePosWork[1]-1);
                    possibleMoves.push_back(pos);
                }
            }

            if(giraffePosWork[1]+1<=6)
            {
                //diag down right
                string newPos=board[giraffePosWork[0]+1][giraffePosWork[1]+1];
                if(newPos=="0")
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+1);
                    pos+=to_string(giraffePosWork[1]+1);
                    possibleMoves.push_back(pos);
                }
            }
            /*double up*/
            if(giraffePosWork[0]+2<=6)
            {
                //down pos
                string newDownPos=board[giraffePosWork[0]+2][giraffePosWork[1]];
                if(newDownPos=="0" || isupper(newDownPos[0]))
                {
                    string pos;
                    pos+=to_string(giraffePosWork[0]+2);
                    pos+=to_string(giraffePosWork[1]);
                    possibleMoves.push_back(pos);
                }

                /*deal with 1 down*/
                //LEFT (diag left)
                if(giraffePosWork[1]-2>=0)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]+2][giraffePosWork[1]-2];
                    if(newPos=="0" || isupper(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]+2);
                        pos+=to_string(giraffePosWork[1]-2);
                        possibleMoves.push_back(pos);
                    }
                }
                if(giraffePosWork[1]+2<=6)
                {
                    //diag down left
                    string newPos=board[giraffePosWork[0]+2][giraffePosWork[1]+2];
                    if(newPos=="0" || isupper(newPos[0]))
                    {
                        string pos;
                        pos+=to_string(giraffePosWork[0]+2);
                        pos+=to_string(giraffePosWork[1]+2);
                        possibleMoves.push_back(pos);
                    }
                }
            }

        }
        allPossibleMoves=converToAnswerString(possibleMoves, bGiraffe);

    }


    

   // sort(allPossibleMoves.begin(), allPossibleMoves.end(), comp);
    return allPossibleMoves;
}



/*PAWN GEN*/
vector<string> pawnMoves(vector<vector<string>> board, FEN FENString)
{
    //holds inv possible moves

    //all final possible moves
    vector<string> allPossibleMoves;

    vector<string> allItrMoves;

    //get array containg all zebras for black and white peaces
    vector<Piece> wPawnArray=FENString.wPawns;
    vector<Piece> bPawnArray=FENString.bPawns;

    Piece wPawn;
    Piece bPawn;

    //can contain zero zeras and so need to check for that
    if(FENString.sideToMove=="white")
    {
        if(wPawnArray.size()!=0)
        {
            //   cout<<"WHITE ZEBRA PRESENT"<<endl;
            //wPawn=wPawnArray[0];      

            for(Piece pawn: wPawnArray)
            {
                vector<string> possibleMoves;
                wPawn=pawn;
                //get pos of zebra
                string pawnPosString=wPawn.posNum;
                pawnPosString[1]--;

                vector<vector<int>> GWP=getGWP(pawnPosString);

                vector<int> pawnPosGame=GWP[0];
                vector<int> pawnPosWork=GWP[1];

                /*LOOK FORWARD FIRST*/
                if(pawnPosWork[0]+1<=6)
                {
                    /*can move forwrad, check diags and forward*/

                    //forward
                    string forwardPos=board[pawnPosWork[0]+1][pawnPosWork[1]];
                    if(forwardPos=="0" || islower(forwardPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]+1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);
                    }

                    //right diag
                    if(pawnPosWork[1]+1<=6)
                    {
                        string newPos=board[pawnPosWork[0]+1][pawnPosWork[1]+1];
                        if(newPos=="0" || islower(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);
                        }
                    }

                    //left diag
                    if(pawnPosWork[1]-1>=0)
                    {
                        string newPos=board[pawnPosWork[0]+1][pawnPosWork[1]-1];
                        if(newPos=="0" || islower(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);
                        }
                    }
                }

                //check backwards
                if(pawnPosWork[0]>3 && pawnPosWork[0]>=0)
                {
                    /*past the river*/

                    //check back 1
                    string back1=board[pawnPosWork[0]-1][pawnPosWork[1]];
                    if(back1=="0")
                    {
                        //block behind is empty so can move
                        string pos;
                        pos+=to_string(pawnPosWork[0]-1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);

                        //check 2 back
                        string back2=board[pawnPosWork[0]-2][pawnPosWork[1]];
                        if(back2=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-2);
                            pos+=to_string(pawnPosWork[1]);
                            possibleMoves.push_back(pos);
                        }
                    }

                }
                vector<string> currItrMoves;
                currItrMoves=converToAnswerString(possibleMoves, wPawn);
                for(string i : currItrMoves)
                {
                    allItrMoves.push_back(i);
                }
            }

            allPossibleMoves=allItrMoves;
        }
        else
        {
            //just return empty allPossibleMoves are there are none
            //  cout<<"NO WHITE ZEBRA"<<endl;
            return allPossibleMoves;
        }
    }

    else if(FENString.sideToMove=="black")
    {
        //whites turn to moe so calc pos only for white zebra
       // cout<<"WHITE TURM"<<endl;
        //create a pice for the zebras if they exist
        if(bPawnArray.size()!=0)
        {
            for(Piece pawn: bPawnArray)
            {
                vector<string> possibleMoves;
                bPawn=pawn;
                //get pos of zebra
                string pawnPosString=bPawn.posNum;
                pawnPosString[1]--;

                vector<vector<int>> GWP=getGWP(pawnPosString);

                vector<int> pawnPosGame=GWP[0];
                vector<int> pawnPosWork=GWP[1];

                /*LOOK FORWARD FIRST*/
                if(pawnPosWork[0]-1>=0)
                {
                    /*can move forwrad, check diags and forward*/

                    //forward
                    string forwardPos=board[pawnPosWork[0]-1][pawnPosWork[1]];
                    if(forwardPos=="0" || isupper(forwardPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]-1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);
                    }

                    //right diag
                    if(pawnPosWork[1]+1<=6)
                    {
                        string newPos=board[pawnPosWork[0]-1][pawnPosWork[1]+1];
                        if(newPos=="0" || isupper(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);
                        }
                    }

                    //left diag
                    if(pawnPosWork[1]-1>=0)
                    {
                        string newPos=board[pawnPosWork[0]-1][pawnPosWork[1]-1];
                        if(newPos=="0" || isupper(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);
                        }
                    }
                }
                //check backwards
                if(pawnPosWork[0]<3 && pawnPosWork[0]<=6)
                {
                    /*past the river*/

                    //check back 1
                    string back1=board[pawnPosWork[0]+1][pawnPosWork[1]];
                    if(back1=="0")
                    {
                        //block behind is empty so can move
                        string pos;
                        pos+=to_string(pawnPosWork[0]+1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);

                        //check 2 back
                        string back2=board[pawnPosWork[0]+2][pawnPosWork[1]];
                        if(back2=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+2);
                            pos+=to_string(pawnPosWork[1]);
                            possibleMoves.push_back(pos);
                        }
                    }

                }
                vector<string> currItrMoves;
                currItrMoves=converToAnswerString(possibleMoves, bPawn);
                for(string i : currItrMoves)
                {
                    allItrMoves.push_back(i);
                }
            }

            allPossibleMoves=allItrMoves;
    }
    }

   //sort(allPossibleMoves.begin(), allPossibleMoves.end(), comp);
    return allPossibleMoves;
}

/*SUPER PAWNS*/
vector<string> sPawnMoves(vector<vector<string>> board, FEN FENString)
{
    //holds inv possible moves

    //all final possible moves
    vector<string> allPossibleMoves;

    vector<string> allItrMoves;

    //get array containg all zebras for black and white peaces
    vector<Piece> wPawnArray=FENString.wSpawns;
    vector<Piece> bPawnArray=FENString.bSpawns;

    Piece wPawn;
    Piece bPawn;

    //can contain zero zeras and so need to check for that
    if(FENString.sideToMove=="white")
    {
        if(wPawnArray.size()!=0)
        {
            //   cout<<"WHITE ZEBRA PRESENT"<<endl;
            //wPawn=wPawnArray[0];      

            for(Piece pawn: wPawnArray)
            {
                vector<string> possibleMoves;
                wPawn=pawn;
                //get pos of zebra
                string pawnPosString=wPawn.posNum;
                pawnPosString[1]--;

                vector<vector<int>> GWP=getGWP(pawnPosString);

                vector<int> pawnPosGame=GWP[0];
                vector<int> pawnPosWork=GWP[1];

                /*SIDEWAYS*/
                if(pawnPosWork[1]+1<=6)
                {
                    string rightPos=board[pawnPosWork[0]][pawnPosWork[1]+1];
                    if(rightPos=="0" || islower(rightPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]);
                        pos+=to_string(pawnPosWork[1]+1);
                        possibleMoves.push_back(pos);
                    }
                    
                }
                /*SIDEWAYS*/
                if(pawnPosWork[1]-1>=0)
                {
                    string rightPos=board[pawnPosWork[0]][pawnPosWork[1]-1];
                    if(rightPos=="0" || islower(rightPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]);
                        pos+=to_string(pawnPosWork[1]-1);
                        possibleMoves.push_back(pos);
                    }
                    
                }

                /*LOOK FORWARD FIRST*/
                if(pawnPosWork[0]+1<=6)
                {
                    /*can move forwrad, check diags and forward*/

                    //forward
                    string forwardPos=board[pawnPosWork[0]+1][pawnPosWork[1]];
                    if(forwardPos=="0" || islower(forwardPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]+1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);
                    }

                    //right diag
                    if(pawnPosWork[1]+1<=6)
                    {
                        string newPos=board[pawnPosWork[0]+1][pawnPosWork[1]+1];
                        if(newPos=="0" || islower(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);
                        }
                    }

                    //left diag
                    if(pawnPosWork[1]-1>=0)
                    {
                        string newPos=board[pawnPosWork[0]+1][pawnPosWork[1]-1];
                        if(newPos=="0" || islower(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);
                        }
                    }
                }
               //check backwards
                if(pawnPosWork[0]-1>=0)
                {
                    //check back 1
                    string back1=board[pawnPosWork[0]-1][pawnPosWork[1]];
                    if(back1=="0")
                    {
                        //block behind is empty so can move
                        string pos;
                        pos+=to_string(pawnPosWork[0]-1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);

                        //check 2 back
                        if(pawnPosWork[0]-2>=0)
                        {
                            string back2=board[pawnPosWork[0]-2][pawnPosWork[1]];
                            if(back2=="0")
                            {
                                string pos;
                                pos+=to_string(pawnPosWork[0]-2);
                                pos+=to_string(pawnPosWork[1]);
                                possibleMoves.push_back(pos);
                            }
                        }
                    }

                    //diag ack
                    if(pawnPosWork[0]-1>=0 && pawnPosWork[1]-1>=0)
                    {
                        string diagbackL1=board[pawnPosWork[0]-1][pawnPosWork[1]-1];
                        if(diagbackL1=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);

                            if(pawnPosWork[0]-2>=0 && pawnPosWork[1]-2>=0)
                            {
                                string diagbackL2=board[pawnPosWork[0]-2][pawnPosWork[1]-2];
                                if(diagbackL2=="0")
                                {
                                    string pos;
                                    pos+=to_string(pawnPosWork[0]-2);
                                    pos+=to_string(pawnPosWork[1]-2);
                                    possibleMoves.push_back(pos);
                                }
                            }
                        }

                    }
                    //diag ack
                    if(pawnPosWork[0]-1>=0 && pawnPosWork[1]+1<=6)
                    {
                        string diagbackR1=board[pawnPosWork[0]-1][pawnPosWork[1]+1];
                        if(diagbackR1=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);


                            if(pawnPosWork[0]-2>=0 && pawnPosWork[1]+2<=6)
                            {
                                string diagbackR2=board[pawnPosWork[0]-2][pawnPosWork[1]+2];
                                if(diagbackR2=="0")
                                {
                                    string pos;
                                    pos+=to_string(pawnPosWork[0]-2);
                                    pos+=to_string(pawnPosWork[1]+2);
                                    possibleMoves.push_back(pos);
                                }
                            }
                        }
                    }
                }
                vector<string> currItrMoves;
                currItrMoves=converToAnswerString(possibleMoves, wPawn);
                for(string i : currItrMoves)
                {
                    allItrMoves.push_back(i);
                }
            }

            allPossibleMoves=allItrMoves;
        }
        else
        {
            //just return empty allPossibleMoves are there are none
            //  cout<<"NO WHITE ZEBRA"<<endl;
            return allPossibleMoves;
        }
    }

    else if(FENString.sideToMove=="black")
    {
        //whites turn to moe so calc pos only for white zebra
       // cout<<"WHITE TURM"<<endl;
        //create a pice for the zebras if they exist
        if(bPawnArray.size()!=0)
        {
            for(Piece pawn: bPawnArray)
            {
                vector<string> possibleMoves;
                bPawn=pawn;
                //get pos of zebra
                string pawnPosString=bPawn.posNum;
                pawnPosString[1]--;

                vector<vector<int>> GWP=getGWP(pawnPosString);

                vector<int> pawnPosGame=GWP[0];
                vector<int> pawnPosWork=GWP[1];

                /*SIDEWAYS*/
                if(pawnPosWork[1]+1<=6)
                {
                    string rightPos=board[pawnPosWork[0]][pawnPosWork[1]+1];
                    if(rightPos=="0" || isupper(rightPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]);
                        pos+=to_string(pawnPosWork[1]+1);
                        possibleMoves.push_back(pos);
                    }
                    
                }
                /*SIDEWAYS*/
                if(pawnPosWork[1]-1>=0)
                {
                    string rightPos=board[pawnPosWork[0]][pawnPosWork[1]-1];
                    if(rightPos=="0" || isupper(rightPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]);
                        pos+=to_string(pawnPosWork[1]-1);
                        possibleMoves.push_back(pos);
                    }
                    
                }

                /*LOOK FORWARD FIRST*/
                if(pawnPosWork[0]-1>=0)
                {
                    /*can move forwrad, check diags and forward*/

                    //forward
                    string forwardPos=board[pawnPosWork[0]-1][pawnPosWork[1]];
                    if(forwardPos=="0" || isupper(forwardPos[0]))
                    {
                        string pos;
                        pos+=to_string(pawnPosWork[0]-1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);
                    }

                    //right diag
                    if(pawnPosWork[1]+1<=6)
                    {
                        string newPos=board[pawnPosWork[0]-1][pawnPosWork[1]+1];
                        if(newPos=="0" || isupper(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);
                        }
                    }

                    //left diag
                    if(pawnPosWork[1]-1>=0)
                    {
                        string newPos=board[pawnPosWork[0]-1][pawnPosWork[1]-1];
                        if(newPos=="0" || isupper(newPos[0]))
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]-1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);
                        }
                    }
                }
               //check backwards
                if(pawnPosWork[0]+1<=6)
                {
                    //check back 1
                    string back1=board[pawnPosWork[0]+1][pawnPosWork[1]];
                    if(back1=="0")
                    {
                        //block behind is empty so can move
                        string pos;
                        pos+=to_string(pawnPosWork[0]+1);
                        pos+=to_string(pawnPosWork[1]);
                        possibleMoves.push_back(pos);

                        //check 2 back
                        if(pawnPosWork[0]+2<=6)
                        {
                            string back2=board[pawnPosWork[0]+2][pawnPosWork[1]];
                            if(back2=="0")
                            {
                                string pos;
                                pos+=to_string(pawnPosWork[0]+2);
                                pos+=to_string(pawnPosWork[1]);
                                possibleMoves.push_back(pos);
                            }
                        }
                    }

                    //diag ack
                    if(pawnPosWork[0]+1<=6 && pawnPosWork[1]-1>=0)
                    {
                        string diagbackL1=board[pawnPosWork[0]+1][pawnPosWork[1]-1];
                        if(diagbackL1=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]-1);
                            possibleMoves.push_back(pos);

                            if(pawnPosWork[0]+2<=6 && pawnPosWork[1]-2>=0)
                            {
                                string diagbackL2=board[pawnPosWork[0]+2][pawnPosWork[1]-2];
                                if(diagbackL2=="0")
                                {
                                    string pos;
                                    pos+=to_string(pawnPosWork[0]+2);
                                    pos+=to_string(pawnPosWork[1]-2);
                                    possibleMoves.push_back(pos);
                                }
                            }
                        }

                    }
                    //diag ack
                    if(pawnPosWork[0]+1<=6 && pawnPosWork[1]+1<=6)
                    {
                        string diagbackR1=board[pawnPosWork[0]+1][pawnPosWork[1]+1];
                        if(diagbackR1=="0")
                        {
                            string pos;
                            pos+=to_string(pawnPosWork[0]+1);
                            pos+=to_string(pawnPosWork[1]+1);
                            possibleMoves.push_back(pos);

                            if(pawnPosWork[0]+2<=6 && pawnPosWork[1]+2<=6)
                            {
                                string diagbackR2=board[pawnPosWork[0]+2][pawnPosWork[1]+2];
                                if(diagbackR2=="0")
                                {
                                    string pos;
                                    pos+=to_string(pawnPosWork[0]+2);
                                    pos+=to_string(pawnPosWork[1]+2);
                                    possibleMoves.push_back(pos);
                                }
                            }
                        }
                    }
                }
                vector<string> currItrMoves;
                currItrMoves=converToAnswerString(possibleMoves, bPawn);
                for(string i : currItrMoves)
                {
                    allItrMoves.push_back(i);
                }
            }

            allPossibleMoves=allItrMoves;
    }
    }

    //sort(allPossibleMoves.begin(), allPossibleMoves.end(), comp);
    return allPossibleMoves;
}




//function to collect input
vector<string> getInput()
{
    //gets number of fen strings
    int N;
    cin>>N;
    cin.ignore();

    vector<string> FENStrings;
    for(int i=0; i<N; ++i)
    {
        //get FEN string 
        string FEN;
        getline(cin, FEN);
        FENStrings.push_back(FEN);
    }

    return FENStrings;
}

vector<string> generateMoves(vector<vector<string>> board, FEN FENString)
{
    //generate all moves and store
    vector<vector<string>> allMoves;
    vector<string> allMovesFinal;

    /*add Lion Moves*/
    vector<string> allLionMoves=lionMoves(board, FENString);
    allMoves.push_back(allLionMoves);

    vector<string> allZebraMoves=zebraMoves(board, FENString);
    allMoves.push_back(allZebraMoves);

    vector<string> allGiraffeMoves=giraffeMoves(board, FENString);
    allMoves.push_back(allGiraffeMoves);

    vector<string> allPawnMoves=pawnMoves(board, FENString);
    allMoves.push_back(allPawnMoves);

    vector<string> allSPawnMoves=sPawnMoves(board, FENString);
    allMoves.push_back(allSPawnMoves);

    for(vector<string> i : allMoves)
    {
        for(string j : i)
        {
            allMovesFinal.push_back(j);
        }
    }

    return allMovesFinal;

}



int calcMaterialScore(vector<vector<string>> board, FEN FENString)
{
    int whiteScore=0;
    int blackScore=0;

    bool whiteLion=false;
    bool blackLion=false;
    for(vector<string> i : board)
    {   
        for(string j : i)
        {
            if(j=="p")
            {
                blackScore+=100;
            }
            else if(j=="P")
            {
                whiteScore+=100;
            }
            else if(j=="z")
            {
                blackScore+=300;
            }
            else if(j=="Z")
            {
                whiteScore+=300;
            }
            else if(j=="s")
            {
                blackScore+=350;
            }
            else if(j=="S")
            {
                whiteScore+=350;
            }
            else if(j=="g")
            {
                blackScore+=400;
            }
            else if(j=="G")
            {
                whiteScore+=400;
            }
            else if(j=="l")
            {
                blackLion=true;
            }
            else if(j=="L")
            {
                whiteLion=true;
            }
        }        
    }
    
    int rawScore=whiteScore-blackScore;
    return rawScore;

}

int calcMobilityScore(vector<vector<string>> board, FEN FENString)
{

    vector<string> allMovesW;
    vector<string> allMovesB;
    
    if(FENString.sideToMove=="white")
    {
        allMovesW=generateMoves(board, FENString);

        FENString.sideToMove="black";
        allMovesB=generateMoves(board, FENString);
    }
    else 
    {
        allMovesB=generateMoves(board, FENString);

        FENString.sideToMove="white";
        allMovesW=generateMoves(board, FENString);
    }

    return allMovesW.size()-allMovesB.size();
}

string checkAttack(vector<vector<string>> board, string move)
{
    pair<string, string> movePair=makeMovePair(move);

    string endRow;
    string endCol;

    endRow+=movePair.second[0];
    endCol+=movePair.second[1];

    string piece=board[stoi(endRow)][stoi(endCol)];
    return piece;
}

int calcAttackScore(vector<vector<string>> board, FEN FENString)
{
    /*
        ->how many moves will result in attack
        ->if move attack is lion add 10
    */

   /*deal with black*/

    vector<string> allMovesW;
    vector<string> allMovesB;

    if(FENString.sideToMove=="white")
    {
        allMovesW=generateMoves(board, FENString);
        
        FENString.sideToMove="black";
        allMovesB=generateMoves(board, FENString);
    }
    else
    {
        allMovesB=generateMoves(board, FENString);
        
        FENString.sideToMove="white";
        allMovesW=generateMoves(board, FENString);
    }

    int attackScoreW=0;

/*combine into one loop*/
    for(string move : allMovesW)
    {
        string piece=checkAttack(board, move);
        if(islower(piece[0]) && piece!="0")
        {
            //attack on black
            attackScoreW+=1;
            if(piece=="l")
            {
                attackScoreW+=10;
            }
        }
    }

    int attackScoreB=0;
    for(string move : allMovesB)
    {
        string piece=checkAttack(board, move);
        if(isupper(piece[0]) && piece!="0")
        {
            //attack on black
            attackScoreB+=1;
            if(piece=="L")
            {
                attackScoreB+=10;
            }
        }
    }

    return attackScoreW-attackScoreB;

}

int doEval(vector<vector<string>> board, FEN FENString)
{
    bool blackLion=false;
    bool whiteLion=false;
    bool tie=true;

    int rawScore;

    for(vector<string> i : board)
    {
        for(string j : i)
        {
            if(j=="l")
            {
                blackLion=true;
            }
            else if(j=="L")
            {
                whiteLion=true;
            }
            else if(j=="s" || j=="S" || j=="z" || j=="Z" || j=="g" || j=="G" || j=="p" || j=="P")
            {
                tie=false;
            }
        }
    }



    if(blackLion && !whiteLion)
    {
        rawScore= -10000;
    }
    else if(whiteLion && !blackLion)
    {

        rawScore= 10000;
    }
    else if(tie && whiteLion && blackLion)
    {
        rawScore= 0;
    }
    else
    {
        int materialScore=calcMaterialScore(board, FENString);
        int mobilityScore=calcMobilityScore(board, FENString);
        int attackScore=calcAttackScore(board, FENString);

        rawScore=materialScore+mobilityScore+attackScore;
    }

    if(FENString.sideToMove=="black")
    {
        return rawScore*(-1);
    }
    return rawScore;
}

// bool isGameOver(vector<vector<string>> currState, FEN FENString)
// {
//     bool gameNotOver=false;

//     int eval=doEval(currState, FENString);
//     if(eval==10000 || eval==-10000 )
//     {
//         return true;
//     }
//     return gameNotOver;
// }

bool isGameOver(vector<vector<string>> board)
{
    bool wLion=false;
    bool bLion=false;
    
    for(vector<string> i : board)
    {
        for(string j : i)
        {
            if(j=="l")
            {
                bLion=true;
            }
            else if(j=="L")
            {
                wLion=true;
            }
        }
    }

    if(wLion && bLion)
    {
        return false;
    }
    return true;
}

int alphaBeta(vector<vector<string>>currState, int depth, FEN FENString, int alpha, int beta)
{
    if(isGameOver(currState) || depth<=0)
    {
        return doEval(currState, FENString);
    }
    vector<string>moves=generateMoves(currState, FENString);
    for(string move : moves)
    {
        /*makeMove returns a FENString*/
        vector<string> moveArr=makeMove(currState, move,FENString);
        FEN nextStateFEN=moveArr[1];
        Board board(nextStateFEN);
        vector<vector<string>> nextState=board.board;
        int eval=-alphaBeta(nextState, depth-1, nextStateFEN,-beta, -alpha);
        if(eval>=beta)
        {
            return beta;
        }
        if(eval>alpha)
        {
            alpha=eval;
        }
    }

    return alpha;
}

//main function
int main()
{
    //get input
    vector<string> FENStrings=getInput();

    vector <FEN> FENArray;
    for(string i: FENStrings)
    {
        FEN fen(i);
        FENArray.push_back(fen);
    }

    vector<Board> boards;
    for(int i=0; i<FENArray.size();++i)
    {
        Board board(FENArray[i]);
        boards.push_back(board);
    }

    vector<int> scores;
    for(int i=0; i<FENArray.size(); ++i)
    {
        int curr=doEval(boards[i].board, FENArray[i]);
        scores.push_back(curr);
    }
    // ofstream myfile;
    // myfile.open("output.txt");
    // for(int i : scores)
    // {
    //     cout<<i<<endl;
    //     myfile<<i<<endl;
    // }
    // myfile.close();
    vector<int> miniMaxScore;
    for(int i=0; i<FENArray.size();++i)
    {
        int curr=alphaBeta(boards[i].board, 4, FENArray[i],-1000000,1000000);
        miniMaxScore.push_back(curr);
    }

    ofstream myfile;
    myfile.open("output.txt");
    for(int i : miniMaxScore)
    {
        cout<<i<<endl;
        myfile<<i<<endl;
    }
    myfile.close();


}