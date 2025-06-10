#pragma once

// 所有容器的反向迭代器 -- 迭代器适配器
namespace sl
{
    template<class Iterator, class Ref, class Ptr>
    struct ReverseIterator
    {
        typedef ReverseIterator<Iterator, Ref, Ptr> Self;

        Iterator _it;

        ReverseIterator(Iterator it)
            :_it(it)
        {}

        Ref operator*()
        {
            Iterator tmp = _it;
            return *(--tmp);
        }

        Ptr operator->()
        {
            return &(operator*());
        }

        Self& operator++()
        {
            --it;
            return *this;
        }

        Self& operator--()
        {
            ++it;
            return *this;
        }

        bool operator!=(const Self& s)
        {
            return _it != s._it;
        }
    };
}