//
//  main.cpp
//  Backtracking
//
//  Created by Chris Hartman on 12/6/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <numeric>
using std::iota;
#include <utility>
using std::move;

#include "Backtracker.hpp"
class NQueens : public VectorBacktracker<int> {
public:
    NQueens(int n):_n(n){}
    int getNumSolutions() {
        return _numSolutions;
    }
private:
    bool isFullSolution() const override
    {
        return currentPartialSolution().size()==_n;
    }
    
    bool shouldExplore() const override
    {
        auto & p = currentPartialSolution();
        auto myRow = int(p.size())-1;
        auto myCol = p[myRow];
        for(int row=0;row<myRow;++row) {
            auto col=p[row];
            if (myCol==col || myCol-col==myRow-row || myCol-col==row-myRow)
                return false;
        }
        return true;
    }
    
    std::vector<int> choices() const override
    {
        std::vector<int> ret(_n);
        std::iota(begin(ret), end(ret), 0);
        return ret;
    }
    
    void registerSolution() override
    {
        auto & p = currentPartialSolution();
        ++_numSolutions;
        for(auto qcol:p) {
            for(int j=0;j<_n;++j)
                if (j==qcol)
                    cout << "Q ";
                else
                    cout << ". ";
            cout << endl;
        }
        cout << endl;
    }
    
private:
    int _n;
    int _numSolutions=0;
};
//using Index = unsigned int;
//class SubSetBacktracker : public VectorBacktracker<Index> {
//private:
//    virtual size_t numElements() const =0;
//    virtual std::vector<Index> choices(const PartialSolution &p)const
//    {
//        int start = p.empty() ? 0 : p.back()+1;
//        vector<Index> c(numElements()-start);
//        iota(begin(c),end(c),start);
//        return c;
//    }
//};


//class SubSetSum : public VectorBacktracker<char> {
//public:
//    SubSetSum(const vector<int> set, int desiredSum):_set(set),_desiredSum(desiredSum){}
//
//private:
//    bool isFullSolution(const PartialSolution &p) const override
//    {
//        if(p.size()!=_set.size())
//            return false;
//        auto sum=0;
//        for(int i=0;i<p.size();++i)
//            if(p[i])
//                sum+=_set[i];
//        return sum==_desiredSum;
//    }
//
//    bool shouldExplore(const PartialSolution &p) const override
//    {
//        if( p.size() >_set.size())
//            return false;
//        auto sum=0;
//        for(int i=0;i<p.size();++i)
//            if(p[i])
//                sum+=_set[i];
//        return (sum <= _desiredSum);
//    }
//
//    std::vector<char> choices(const PartialSolution &) const override
//    {
//        return {false,true};
//    }
//
//    void registerSolution(const PartialSolution &p) override
//    {
//        for(int i=0;i<p.size();++i)
//            if(p[i])
//                cout << _set[i] << " ";
//        cout << endl;
//    }
//
//    vector<int> _set;
//    int _desiredSum;
//};
//
//class SubSetSumIndexed : public SubSetBacktracker {
//public:
//    SubSetSumIndexed(const vector<int> set, int desiredSum):_set(set),_desiredSum(desiredSum){}
//private:
//    int sum(const PartialSolution &p) const
//    {
//        auto sum=0;
//        for(auto i:p)
//            sum += _set[i];
//        return sum;
//    }
//
//    virtual bool isFullSolution(const PartialSolution &p) const override
//    {
//        return sum(p) == _desiredSum;
//    }
//
//    virtual bool shouldExplore(const PartialSolution &p) const override
//    {
//        return sum(p) <= _desiredSum;
//    }
//
//    virtual size_t numElements() const override {
//        return _set.size();
//    }
//
//    virtual void registerSolution(const PartialSolution &p) override
//    {
//        for(auto i:p)
//            cout << _set[i] << " ";
//        cout << endl;
//    }
//
//private:
//    vector<int> _set;
//    int _desiredSum;
//};
//
//struct Item {
//    int _weight;
//    int _value;
//};
//
//class Knapsack : public VectorBacktracker<char>
//{
//public:
//    Knapsack(vector<Item> items,int capacity):_items(move(items)),_capacity(capacity){}
//    void printBestSolution()
//    {
//        for(int i=0;i<_bestSolution.size();++i)
//            if(_bestSolution[i])
//                cout << i << " ";
//        cout << endl;
//   }
//
//private:
//    virtual bool isFullSolution(const PartialSolution &p) const
//    {
//        return p.size()==_items.size();
//    }
//
//    virtual bool shouldExplore(const PartialSolution &p)const
//    {
//        if(p.size() > _items.size())
//            return false;
//        auto sum=0;
//        auto curValue = 0;
//        for(int i=0;i<p.size();++i)
//            if(p[i]) {
//                sum+=_items[i]._weight;
//                curValue+=_items[i]._value;
//            }
//        if (sum>_capacity)
//            return false;
//        auto remainingCapacity = _capacity-sum;
//        auto bestUnitValue = 0.0;
//        for(auto i = p.size(); i<_items.size();++i) {
//            auto unitValue = double(_items[i]._value)/_items[i]._weight;
//            if (unitValue>bestUnitValue)
//                bestUnitValue = unitValue;
//        }
//        auto bestPossibleValue = curValue + remainingCapacity*bestUnitValue;
//        if (bestPossibleValue < _bestValue)
//            return false;
//        return true;
//    }
//
//    virtual std::vector<char> choices(const PartialSolution &)const
//    {
//        return {false,true};
//    }
//
//    virtual void registerSolution(const PartialSolution &p)
//    {
//        auto totalValue=0;
//        for(int i=0;i<p.size();++i)
//            if(p[i])
//                totalValue+=_items[i]._value;
//        if(totalValue > _bestValue) {
//            _bestValue = totalValue;
//            _bestSolution = p;
//        }
//    }
//
//    vector<Item> _items;
//    int _capacity;
//    PartialSolution _bestSolution;
//    int _bestValue=0;
//};

int main() {
    NQueens board(8);
    board.solve();
    cout << board.report() << endl;
    
//    SubSetSum s1({2, 3, 5, 6, 8, 10},100);
//    s1.solve();
//
//    SubSetSum s2({10,8,6,5,3,2},100);
//    s2.solve();
//
//    SubSetSumIndexed s3({2, 3, 5, 6, 8, 10},100);
//    s3.solve();
//
//    SubSetSumIndexed s4({10,8,6,5,3,2},100);
//    s4.solve();

//    Knapsack k({{4,40},{7,42},{5,25},{3,12}},10);
//    k.solve();
//    k.printBestSolution();
    return 0;
}

/*
 Write a more general version where (add this choice to partial solution) is user defined (to make SubsetSum more efficient.)
 
 
 */
    
