#pragma once
#include <iterator>
#include <vector>

namespace toolbox
{
/** Fills a std::vector<Iterator>, which can then be
're-wound' with operator-- even in forward-only iterators like graph search */
template <typename Iterator>
class IteratorRecorder : public std::iterator<std::input_iterator_tag,
                                              typename Iterator::value_type>
{
public: /** Type Definitions */
    using reference = typename Iterator::reference;

private:                                              /** Data */
    std::vector<Iterator> recording_;                 /** Cache */
    typename std::vector<Iterator>::size_type index_; /** Current position */

public: /** Accessors */
    const Iterator& get() const;

public: /** Constructors */
    explicit IteratorRecorder(Iterator it);

public: /** Operators */
    IteratorRecorder& operator++();
    IteratorRecorder operator++(int dummy);
    IteratorRecorder& operator--();
    IteratorRecorder operator--(int dummy);
    auto& operator*();
    auto operator-> ();
    bool operator==(const IteratorRecorder& rhs) const;
    bool operator!=(const IteratorRecorder& rhs) const;
    bool operator==(const Iterator& rhs) const;
    bool operator!=(const Iterator& rhs) const;
    explicit operator Iterator() const;
};

/********************************IMPLEMENTATION********************************/

template <typename Iterator>
IteratorRecorder<Iterator>::IteratorRecorder(Iterator it)
    : recording_{it}, index_(0)
{
}

template <typename Iterator>
const Iterator& IteratorRecorder<Iterator>::get() const
{
    return recording_[index_];
}

template <typename Iterator>
IteratorRecorder<Iterator>& IteratorRecorder<Iterator>::operator++()
{
    ++index_;
    if (index_ == recording_.size())
    {
        auto it = recording_.back();
        recording_.emplace_back(++it);
    }
    return *this;
}

template <typename Iterator>
IteratorRecorder<Iterator> IteratorRecorder<Iterator>::operator++(int dummy)
{
    (void)dummy;
    auto result = *this;
    ++*this;
    return result;
}

template <typename Iterator>
IteratorRecorder<Iterator>& IteratorRecorder<Iterator>::operator--()
{
    --index_;
    return *this;
}

template <typename Iterator>
IteratorRecorder<Iterator> IteratorRecorder<Iterator>::operator--(int dummy)
{
    (void)dummy;
    auto result = *this;
    --*this;
    return result;
}

template <typename Iterator>
auto& IteratorRecorder<Iterator>::operator*()
{
    return get().operator*();
}

template <typename Iterator>
auto IteratorRecorder<Iterator>::operator-> ()
{
    return get().operator->();
}

template <typename Iterator>
bool IteratorRecorder<Iterator>::
operator==(const IteratorRecorder<Iterator>& rhs) const
{
    return get() == rhs.get();
}

template <typename Iterator>
bool IteratorRecorder<Iterator>::
operator!=(const IteratorRecorder<Iterator>& rhs) const
{
    return !(*this == rhs);
}

template <typename Iterator>
bool IteratorRecorder<Iterator>::operator==(const Iterator& rhs) const
{
    return get() == rhs;
}

template <typename Iterator>
bool IteratorRecorder<Iterator>::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

template <typename Iterator>
IteratorRecorder<Iterator>::operator Iterator() const
{
    return get();
}

} // namespace
