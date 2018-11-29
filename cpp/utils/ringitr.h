#pragma once
#include <vector>

template <typename T, typename Container = std::vector<T>, typename Iterator = Container::iterator>
class RingIterator
{
public:
    using difference_type = size_t;
    using value_type = T;
    using pointer = T * ;
    using reference = T & ;
    using iterator_category = std::bidirectional_iterator_tag;

private:
    const Container& data;
    Iterator   cursor;
    Iterator   begin;
    Iterator   end;


public:
    RingIterator(Container& v) : data(v), cursor(v.begin()), begin(v.begin()), end(v.end()) {}
    RingIterator(Container& v, const Iterator& i) : data(v), cursor(i), begin(v.begin()), end(v.end()) {}
    RingIterator(Container& v, const Iterator& i, const Iterator& j) : data(v), cursor(i), begin(i), end(j) {}
    RingIterator(Container& v, size_t i) : data(v), cursor(v.begin() + i % v.size()), begin(v.begin()), end(v.end()) {}
    RingIterator(const RingIterator& r)
        : data(r.data)
    {
        *this = r;
    }


    const RingIterator& operator = (const RingIterator& rhs) 
    {
        assert(&rhs.data == &data);
        cursor = rhs.cursor;
        begin = rhs.begin;
        end = rhs.end;
        return *this;
    }
    
    bool operator == (const RingIterator& x) const { return cursor == x.cursor; }
    bool operator != (const RingIterator& x) const { return !(*this == x); }
    reference operator*() const { return *cursor; }
    RingIterator& operator++() { ++cursor; if (cursor == end) cursor = begin; return *this; }
    RingIterator& operator+(size_t count) { while (count-- > 0) { (*this)++; } return *this; }
    RingIterator& operator-(size_t count) { while (count-- > 0) { (*this)--; } return *this; }
    RingIterator operator++(int) { RingIterator ring = *this; ++*this; return ring; }
    RingIterator& operator--() { if (cursor == begin) cursor = end; --cursor; return *this; }
    RingIterator operator--(int) { RingIterator ring = *this; --*this; return ring; }
    RingIterator insert(const T& x) { return RingIterator(data, data.insert(cursor, x)); }
    RingIterator erase() { return RingIterator(data, data.erase(cursor)); }
};

