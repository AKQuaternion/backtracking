# backtracking


The most general form is the class `Backtracker<Choice, PartialSolution>`. The Choice template classes is a class (or type) indicating
the choice made at a particular step, and PartialSolution is a class representing a set of choices taken so far. For instance, if
implementing the standard N-Queens example, where we choose a column to put the queen in for each row, we would probably choose
`Choice = int`, and `PartialSolution = vector<int>`. To implement a Backtracking search, write a class that derives from
`Backtracker<Choice,PartialSolution> and implement the following (virtual) member functions:

`    virtual bool isFullSolution() const {return true;}
    virtual bool shouldExplore() const {return true;}
    virtual std::vector<Choice> choices() const=0;
    virtual void registerSolution()=0;
    virtual void applyChoice(const Choice &c)=0;
    virtual void unapplyChoice(const Choice &c)=0;
`
