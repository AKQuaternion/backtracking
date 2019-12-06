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
using std::accumulate;
using std::iota;
using std::move;
#include <iterator>
using std::begin;
using std::end;
#include <algorithm>
using std::all_of;
#include "Backtracker.hpp"

class NQueens : public VectorBacktracker<int> {
public:
  explicit NQueens(unsigned long n) : _n(n) {}

private:
  [[nodiscard]] bool isFullSolution() const override {
    return currentPartialSolution().size() == _n;
  }

  [[nodiscard]] bool shouldExplore() const override {
    auto &p = currentPartialSolution();
    auto myRow = int(p.size()) - 1;
    auto myCol = p[myRow];
    for (int row = 0; row < myRow; ++row) {
      auto col = p[row];
      if (myCol == col || myCol - col == myRow - row ||
          myCol - col == row - myRow)
        return false;
    }
    return true;
  }

  [[nodiscard]] std::vector<int> choices() const override {
    std::vector<int> ret(_n);
    std::iota(begin(ret), end(ret), 0);
    return ret;
  }

  void registerSolution() override {
    auto &p = currentPartialSolution();
    for (auto qcol : p) {
      for (auto j = 0ul; j < _n; ++j)
        if (j == qcol)
          cout << "Q ";
        else
          cout << ". ";
      cout << endl;
    }
    cout << endl;
  }

private:
  unsigned long _n;
};

struct QueenPosition {
  int _row;
  int _col;
};

class NQueens2 : public VectorBacktracker<QueenPosition> {
public:
  explicit NQueens2(int n) : _n(n) {}

private:
  [[nodiscard]] bool isFullSolution() const override {
    return currentPartialSolution().size() == _n;
  }

  [[nodiscard]] vector<QueenPosition> choices() const override {
    auto &p = currentPartialSolution();
    vector<QueenPosition> ret;
    auto row = int(p.size());
    for (int col = 0; col < _n; ++col) {
      QueenPosition me{row, col};
      auto doesNotAttackMe = [me](const QueenPosition &pos) {
        return pos._col != me._col &&
               me._col - pos._col != me._row - pos._row &&
               me._col - pos._col != pos._row - me._row;
      };
      if (all_of(p.begin(), p.end(), doesNotAttackMe)) {
        ret.push_back(me);
      }
    }
    return ret;
  }

  void registerSolution() override {
    auto &p = currentPartialSolution();
    for (auto qpos : p) {
      for (int j = 0; j < _n; ++j)
        if (j == qpos._col)
          cout << "Q ";
        else
          cout << ". ";
      cout << endl;
    }
    cout << endl;
  }

private:
  int _n;
};

// class Knapsack : public VectorBacktracker<char>
//{
// public:
//    Knapsack(vector<Item> items,int
//    capacity):_items(move(items)),_capacity(capacity){} void
//    printBestSolution()
//    {
//        for(int i=0;i<_bestSolution.size();++i)
//            if(_bestSolution[i])
//                cout << i << " ";
//        cout << endl;
//   }
//
// private:
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

// template <typename Number>
class SubSetSum : public SubSetBacktracker<int> {
  using Number = int;
  // In the future we can deduce the int, maybe?
  //    using SubSetBacktracker<Number>::currentPartialSolution;
  //    using SubSetBacktracker<Number>::element;
public:
  SubSetSum(const vector<Number> &set, int desiredSum)
      : SubSetBacktracker<Number>(set), _desiredSum(desiredSum) {}

private:
  [[nodiscard]] bool isFullSolution() const override {
    return sum() == _desiredSum;
  }

  [[nodiscard]] bool shouldExplore() const override {
    return sum() <= _desiredSum;
  }

  void registerSolution() override {
    for (auto i : currentElements())
      cout << i << " ";
    cout << endl;
  }

  [[nodiscard]] int sum() const {
    return accumulate(begin(currentElements()), end(currentElements()), 0);
  }

  int _desiredSum;
};

class SubSetSumEfficient : public SubSetBacktracker<int> {
  using Number = int;
  // In the future we can deduce the int, maybe?
  //    using SubSetBacktracker<Number>::currentPartialSolution;
  //    using SubSetBacktracker<Number>::element;
public:
  SubSetSumEfficient(const vector<Number> &set, int desiredSum)
      : SubSetBacktracker<Number>(set), _desiredSum(desiredSum), _currentSum{} {
  }

private:
  [[nodiscard]] bool isFullSolution() const override {
    return _currentSum == _desiredSum;
  }

  [[nodiscard]] bool shouldExplore() const override {
    return _currentSum <= _desiredSum;
  }

  void registerSolution() override {
    for (auto i : currentElements())
      cout << i << " ";
    cout << endl;
  }
  void elementUpdate(const Number &n) override { _currentSum += n; }
  void elementUnupdate(const Number &n) override { _currentSum -= n; }
  int _desiredSum;
  int _currentSum;
};

int main() {
  vector<int> v;
  v.push_back(1);
  cout << v.size() << endl;

  NQueens2 board(8);
  board.solve();
  cout << board.report() << endl;

  //    SubSetSumEfficient s1({2, 3, 5, 6, 8, 10},10);
  //    s1.solve();
  //    cout << s1.report() << endl;
  //
  //    SubSetSumEfficient s2({-1,-1,-1,1,1,1},0);
  //    s2.solve();
  //    cout << s2.report() << endl;

  //    Knapsack k({{4,40},{7,42},{5,25},{3,12}},10);
  //    k.solve();
  //    k.printBestSolution();
  return 0;
}

/*
Explain about how to write partial specializations needs to specify base class
usings

 How to handle whether should prune after a full solution or not?

 Template parameter for type of collection of choices?

 */
