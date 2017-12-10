//
//  Backtracker.hpp
//  Backtracking
//
//  Created by Chris Hartman on 12/10/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Backtracker_hpp
#define Backtracker_hpp
#include <vector>
#include <string>
//this is a comment

template<typename Choice, typename PartialSolution>
class Backtracker {
protected:
    PartialSolution & currentPartialSolution() {return _partialSolution;}
    const PartialSolution & currentPartialSolution() const {return _partialSolution;}
public:
    void solve(){
        _numSolutions=0;
        _numNodesExplored=0;
        initializeEmptyPartialSolution();
        solveRecurse();
    }
    unsigned int getNumSolutions() {
        return _numSolutions;
    }
    unsigned int getNumNodesExplored() {
        return _numNodesExplored;
    }
    std::string report() {
        return std::to_string(_numNodesExplored) + " nodes explored to find " + std::to_string(_numSolutions) + " solutions.";
    }
private:
    virtual void initializeEmptyPartialSolution(){}
    virtual bool isFullSolution() const=0;
    virtual bool shouldExplore() const {return true;}
    virtual std::vector<Choice> choices() const=0;
    virtual void registerSolution()=0;
    virtual void applyChoice(const Choice &c)=0;
    virtual void unapplyChoice(const Choice &c)=0;
    virtual void choiceUpdate(const Choice &c){}
    virtual void choiceUnupdate(const Choice &c){}

    void solveRecurse()
    {
        ++_numNodesExplored;
        if(isFullSolution()) {
            ++_numSolutions;
            registerSolution();
        }
        for(const auto &c:choices()) {
            applyChoice(c);
            choiceUpdate(c);
            if (shouldExplore())
                solveRecurse();
            unapplyChoice(c);
            choiceUnupdate(c);
        }
    }
    
    unsigned int _numNodesExplored=0;
    unsigned int _numSolutions=0;
    PartialSolution _partialSolution;
};

template<typename Choice>
class VectorBacktracker : public Backtracker<Choice, std::vector<Choice>> {
public:
protected:
    using Backtracker<Choice, std::vector<Choice>>::currentPartialSolution;
private:
    virtual void applyChoice(const Choice &c) override
    {
        currentPartialSolution().push_back(c);
    }
    virtual void unapplyChoice(const Choice &c) override
    {
        currentPartialSolution().pop_back();
    }
};


#endif /* Backtracker_hpp */
