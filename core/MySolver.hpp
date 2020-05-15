//MySolver.hpp
//Author: Jason Li
//ID 11014426

#ifndef MYSOLVER_HPP
#define MYSOLVER_HPP

#include "OthelloAI.hpp"
#include <vector>
#include <iostream>
namespace taichenl{
    class MySolver: public OthelloAI{
        public:

        //chooseMove returns a pair of integers to indicate the next move
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;

        //evaluate() returns an integer indicating how likely to choose this move
        int evaluate(const OthelloGameState& s);

        //findmove() returns a vector of pair integers.
        std::vector <std::pair<int, int>> findMove(const OthelloGameState& s);

        //searchBlack returns a integer indicating the evaluation value using 
        //recursive functions
        int searchBlack(const OthelloGameState& s, int depth);

        //same as above
        int searchWhite(const OthelloGameState& s, int depth);
    };
}

#endif