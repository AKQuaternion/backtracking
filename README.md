# backtracking

##`Backtracker<Choice, PartialSolution>`
The most general form is the class `Backtracker<Choice, PartialSolution>`. The Choice template classes is a class (or type) indicating
the choice made at a particular step, and PartialSolution is a class representing a set of choices taken so far. For instance, if
implementing the standard N-Queens example, where we choose a column to put the queen in for each row, we would probably choose
`Choice = int`, and `PartialSolution = vector<int>`. To implement a Backtracking search, write a class that derives from
`Backtracker<Choice,PartialSolution> and implement the following (virtual) member functions:

```c++
    virtual bool isFullSolution() const {return true;}
    virtual bool shouldExplore() const {return true;}
    virtual std::vector<Choice> choices() const=0;
    virtual void registerSolution()=0;
    virtual void applyChoice(const Choice &c)=0;
    virtual void unapplyChoice(const Choice &c)=0;
```
You will probably want to call `currentPartialSolution()` which returns the current partial solution. 

`isFullSolution()` should return true if the current partial solution is actually a full solution to the problem.

`shouldExplore()` should return true if the most recent choice made should be explored. If doing something like branch and bound, you might also return false if the current partial solution has no chance of being extended to a better full solution than the best one found so far.

`choices()` should return a vector containing the possible choices that can be made from the current partial solution. Note that there is some redundancy with `choices()` and `shouldExplore()` - a choice may be pruned in either step. You may use this flexibility to make your code more readable.

`registerSolution()` will be called whenever a full solution is found. Note that the default implementation is to always return true, in which case *every* partial solution will be registered. 

`applyChoice(const Choice &c)` and `unapplyChoice(const Choice &c)` should apply (or unapply) the given choice to the current partial solution.

