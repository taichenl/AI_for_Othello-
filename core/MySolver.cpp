//MySolver.cpp
#include "MySolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>



ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, taichenl::MySolver, 
"My AI (Required)");




//Take parameter of the OthelloGamesStatas and return a pair of integers
std::pair<int, int> taichenl::MySolver::chooseMove(const OthelloGameState& state)
{
    //Initializing two vectors. The first one is to make a vector of pairs,
    //which are possible move for AI to choose
    //The second vector is the value of each move with evalualtion number.
    //The higher the evaluation is, the more likely AI will choose
    std::vector<std::pair<int, int>> potentialMove= findMove(state);
    std::vector<int> value;

    //Loop through the vector of moves and push each of the search value
    //into the vector for later use
    for (std::pair<int, int> v: potentialMove){
            //Make a new copy of gameState by a unique pointer
            std::unique_ptr<OthelloGameState> p;
            p = state.clone();
            p->makeMove(v.first, v.second);

            //plug in values in to the vector
            //I make two search function to differeniate whose turn is it.
            if (state.isBlackTurn()){
                value.push_back(searchBlack(*p, 4));
            }
            else{
                value.push_back(searchWhite(*p, 4));
            }
    }
    //After Initilizing, the code below is designed to find the best move by finding 
    //the index for the vector
    int index;
    for (int i = 0; i<value.size(); i++){
        if (value[i] == *max_element(value.begin(), value.end())and state.isBlackTurn()){
            index = i;
        }
        if (value[i] == *min_element(value.begin(), value.end())and state.isWhiteTurn()){
            index = i;
        }
    }
    return potentialMove[index];
}



//The evaulation function is based on the more it can get for one move. 
int taichenl::MySolver::evaluate(const OthelloGameState& s){
    return s.blackScore()-s.whiteScore();
}



//findmove() will return a vector of pairs that contains move insides.
//It will loop through the entire board and check all the valid move and add
//to the vector
std::vector <std::pair<int, int>>taichenl::MySolver:: findMove(const OthelloGameState& s){
    std::vector <std::pair<int, int>> availableMove;
    for (int i = 0; i <s.board().height(); i++){
        for (int j = 0; j <s.board().width(); j++){
            if (s.isValidMove(i, j)){
                std::pair<int, int> move;
                move.first = i;
                move.second = j;
                availableMove.push_back(move);
            }
        }
    }
    return availableMove;
}



//Since it's hard to differ whose turn is the current states is. I make a serach black 
//function is specifically used for black moves. When the move is called, and use isBlack 
//turn. It will tell whether it's in the current stats or not. 
int taichenl::MySolver::searchBlack(const OthelloGameState& s, int depth){
    if (depth == 0 or s.isGameOver()){
        return evaluate(s);
    }
    else{
        if (s.isBlackTurn()){
            std::vector <int> list;
            for (std::pair<int, int> move: findMove(s)){
                std::unique_ptr<OthelloGameState> p;
                p = s.clone();
                p->makeMove(move.first, move.second);
                list.push_back(searchBlack(*p, depth-1));
                
            }
            return *max_element (list.begin(), list.end());
        }
        else{
            std::vector <int> list1;
            for (std::pair<int, int> move: findMove(s)){
                std::unique_ptr<OthelloGameState> p;
                p = s.clone();
                p->makeMove(move.first, move.second);
                list1.push_back(searchBlack(*p, depth-1));
            }
            return *min_element (list1.begin(), list1.end());   
        }
        
    }
}


//Same function as above except it's using white to determine whose turn it is. 
int taichenl::MySolver::searchWhite(const OthelloGameState& s, int depth){
    if (depth == 0 or s.isGameOver()){
        return evaluate(s);
    }
    else{
        if (s.isWhiteTurn()){
            std::vector <int> list;
            for (std::pair<int, int> move: findMove(s)){
                std::unique_ptr<OthelloGameState> p;
                p = s.clone();
                p->makeMove(move.first, move.second);
                list.push_back(searchWhite(*p, depth-1));
                
            }
            //different than black because the value of evalulation is reversed
            return *min_element (list.begin(), list.end());
        }
        else{
            std::vector <int> list1;
            for (std::pair<int, int> move: findMove(s)){
                std::unique_ptr<OthelloGameState> p;
                p = s.clone();
                p->makeMove(move.first, move.second);
                list1.push_back(searchWhite(*p, depth-1));
            }
            return *max_element (list1.begin(), list1.end());   
        }
        
    }
}
