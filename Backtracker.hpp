//
//  Backtracker.hpp
//  Backtracking
//
//  Created by Chris Hartman on 12/10/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef BACKTRACKING_BACKTRACKER_HPP
#define BACKTRACKING_BACKTRACKER_HPP
#include <vector>
// for std::vector
#include <string>
// for std::string
#include <numeric>
// for std::iota

#include "indexview.hpp"
using namespace indexview;

template<typename Choice, typename PartialSolution>
class Backtracker {
public:
    void solve(){
        _numSolutions=0;
        _numNodesExplored=0;
        _partialSolution=emptyPartialSolution();
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
protected:
    PartialSolution & currentPartialSolution() {return _partialSolution;}
    [[nodiscard]] const PartialSolution & currentPartialSolution() const {return _partialSolution;}
private:
    virtual PartialSolution emptyPartialSolution(){return {};}
    // this should set up auxiliary information and return an empty PartialSolution
    // is this a violation of SRP? Is it exception safe?
    [[nodiscard]] virtual bool isFullSolution() const {return true;}
    [[nodiscard]] virtual bool shouldExplore() const {return true;}
    [[nodiscard]] virtual std::vector<Choice> choices() const=0;
    virtual void registerSolution()=0;
    virtual void applyChoice(const Choice &c)=0;
    virtual void unapplyChoice(const Choice &c)=0;

    void solveRecurse()
    {
        ++_numNodesExplored;
        if(isFullSolution()) {
            ++_numSolutions;
            registerSolution();
        }
        for(const auto &c:choices()) {
            applyChoice(c);
            if (shouldExplore())
                solveRecurse();
            unapplyChoice(c);
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
    virtual void choiceUpdate(const Choice &c){}
    virtual void choiceUnupdate(const Choice &c){}
    void applyChoice(const Choice &c) final
    {
        currentPartialSolution().push_back(c);
        choiceUpdate(c);
    }
    void unapplyChoice(const Choice &c) final
    {
        choiceUnupdate(c);
        currentPartialSolution().pop_back();
    }
};

template<typename Element>
class SubSetBacktracker : public VectorBacktracker<unsigned int> { //maybe unsigned short?
public:
    explicit SubSetBacktracker(std::vector<Element> elements):_elements(std::move(elements))
    {}
protected:
  void choiceUpdate(const unsigned int &c) final {elementUpdate(_elements[c]);}
     void choiceUnupdate(const unsigned int &c) final {elementUnupdate(_elements[c]);}
    virtual void elementUpdate(const Element &e){}
    virtual void elementUnupdate(const Element &e){}
    Element & baseElement(unsigned int i)
    {
        return _elements[i];
    }
    const Element & baseElement(unsigned int i) const
    {
        return _elements[i];
    }
    
    ConstIndexView<Element, unsigned int> currentElements() const
    {
        return makeIndexView(_elements, currentPartialSolution());
    }
    
private:
    [[nodiscard]] std::vector<unsigned int> choices() const final
    {
        auto & p = currentPartialSolution();
        int start = p.empty() ? 0 : p.back()+1;
        std::vector<unsigned int> c(_elements.size()-start);
        std::iota(begin(c),end(c),start);
        return c;
    }

    std::vector<Element> _elements;
};
#endif /*BACKTRACKING_BACKTRACKER_HPP*/
