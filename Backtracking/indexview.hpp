//
//  indexview.hpp
//  Playground
//
//  Created by Chris Hartman on 12/10/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef indexview_h
#define indexview_h
#include <vector>
namespace indexview {

template<typename Element, typename Index>
class ConstIndexViewIterator {
public:
    ConstIndexViewIterator(const std::vector<Element> &baseSet, const std::vector<Index> &indices, Index i)
    :_baseSet(baseSet),_indices(indices),_i(i)
    {}
    
    ConstIndexViewIterator & operator++()
    {
        _i++;
        return *this;
    }
    
    const Element & operator*()
    {
        return _baseSet[_indices[_i]];
    }
    
    friend bool operator!=(const ConstIndexViewIterator &lhs, const ConstIndexViewIterator &rhs)
    {
        return lhs._i != rhs._i;
    }
    
    const std::vector<Element> &_baseSet;
    const std::vector<Index> &_indices;
    Index _i;
};

template<typename Element, typename Index>
class IndexViewIterator {
public:
    IndexViewIterator(std::vector<Element> &baseSet, const std::vector<Index> &indices, Index i)
    :_baseSet(baseSet),_indices(indices),_i(i)
    {}
    
    IndexViewIterator & operator++()
    {
        _i++;
        return *this;
    }
    
    Element & operator*()
    {
        return _baseSet[_indices[_i]];
    }
    
    friend bool operator!=(const IndexViewIterator &lhs, const IndexViewIterator &rhs)
    {
        return lhs._i != rhs._i;
    }
    
    std::vector<Element> &_baseSet;
    const std::vector<Index> &_indices;
    Index _i;
};

template<typename Element, typename Index>
class ConstIndexView {
public:
    ConstIndexView(const std::vector<Element> &baseSet, const std::vector<Index> &indices)
    :_baseSet(baseSet),_indices(indices)
    {}
    
    ConstIndexViewIterator<Element,Index> begin() const
    {
        return ConstIndexViewIterator<Element,Index>(_baseSet,_indices,0);
    }
    ConstIndexViewIterator<Element,Index> end() const
    {
        return ConstIndexViewIterator<Element,Index>(_baseSet,_indices,Index(_indices.size()));
    }
    const std::vector<Element> &_baseSet;
    const std::vector<Index> &_indices;
};

template<typename Element, typename Index>
class IndexView {
public:
    IndexView(std::vector<Element> &baseSet, const std::vector<Index> &indices)
    :_baseSet(baseSet),_indices(indices)
    {}
    
    IndexViewIterator<Element,Index> begin() const
    {
        return IndexViewIterator<Element,Index>(_baseSet,_indices,0);
    }
    IndexViewIterator<Element,Index> end() const
    {
        return IndexViewIterator<Element,Index>(_baseSet,_indices,Index(_indices.size()));
    }
    std::vector<Element> &_baseSet;
    const std::vector<Index> &_indices;
};

template <typename Element, typename Index>
ConstIndexView<Element,Index> makeIndexView(const std::vector<Element> &baseSet, const std::vector<Index> &indices)
{
    return ConstIndexView<Element,Index>(baseSet,indices);
}

template <typename Element, typename Index>
IndexView<Element,Index> makeIndexView(std::vector<Element> &baseSet, const std::vector<Index> &indices)
{
    return IndexView<Element,Index>(baseSet,indices);
}
}

#endif /* indexview_h */
