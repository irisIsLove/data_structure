#pragma once

#include <cassert>
#include <functional>
#include <iostream>

template <typename T>
class LinkList;

template <typename T>
using Compare = std::function<bool(const T&, const T&)>;

template <typename T>
using Visit = std::function<void(LinkList<T>*)>;

template <typename T>
class LinkList
{
    struct Node
    {
        T _data;
        Node* _pNext;
        Node* _pPrior;
    };

public:
    LinkList()
        : _pHead(nullptr)
        , _pTail(nullptr)
        , _nSize(0) {}

    ~LinkList()
    {
        for (auto i = 0; i < _nSize; ++i)
        {
            Node* pNext = _pHead->_pNext;
            if (nullptr != _pHead)
            {
                delete _pHead;
            }
            _pHead = pNext;
        }
    }

    /// @brief 清空线性表中的数据
    void clear()
    {
        for (auto i = 0; i < _nSize; ++i)
        {
            Node* pNext = _pHead->_pNext;
            if (nullptr != _pHead)
            {
                delete _pHead;
            }
            _pHead = pNext;
        }
    }

    /// @brief 判断线性表是否为空
    /// @return 为空返回true，反之返回false
    bool isEmpty() { return _nSize == 0; }

    /// @brief
    /// @return 返回线性表大小
    size_t size() const { return _nSize; }

    /// @brief 向链表头部插入一个元素
    /// @param e 插入元素
    void pushFront(const T& e)
    {
        Node* pNode = new Node;
        pNode->_data = e;
        pNode->_pNext = _pHead;
        pNode->_pPrior = nullptr;
        if (_pHead != nullptr)
        {
            _pHead->_pPrior = pNode;
        }
        _pHead = pNode;
        ++_nSize;

        if (_nSize == 1)
        {
            _pTail = _pHead;
        }
    }

    /// @brief 删除头部元素
    /// @return 返回被删除元素
    T popFront()
    {
        assert(_nSize != 0 && "The list is empty!");
        Node* pNode = _pHead;
        _pHead = pNode->_pNext;
        _pHead->_pPrior = nullptr;
        T res = pNode->_data;
        delete pNode;
        --_nSize;
        return res;
    }

    /// @brief 向链表尾部添加新的元素
    /// @param e 插入元素
    void pushBack(const T& e)
    {
        Node* pNode = new Node;
        pNode->_data = e;
        pNode->_pNext = nullptr;
        pNode->_pPrior = _pTail;
        if (_pTail != nullptr)
        {
            _pTail->_pNext = pNode;
        }
        _pTail = pNode;
        ++_nSize;

        if (_nSize == 1)
        {
            _pHead = _pTail;
        }
    }

    /// @brief 删除尾部元素
    /// @return 返回被删除元素
    T popBack()
    {
        assert(_nSize != 0 && "The list is empty!");
        T res = _pTail->_data;
        Node* pNode = _pTail;
        _pTail = pNode->_pPrior;
        _pTail->_pNext = nullptr;
        delete pNode;
        --_nSize;
        return res;
    }

    /// @brief 在指定位置插入元素
    /// @param index 插入元素位置
    /// @param e 插入元素
    void insertElem(size_t index, const T& e)
    {
        assert(index > 0 && index <= _nSize + 1 && "Error: out of range! The index should be [1..size + 1].");
        if (index == 1)
        {
            pushFront(e);
        }
        else if (index == _nSize + 1)
        {
            pushBack(e);
        }
        else
        {
            Node* pCur = new Node;
            pCur->_data = e;

            Node* pNext = _pHead;
            for (auto i = 0; i < index; ++i)
            {
                pNext = pNext->_pNext;
            }
            Node* pPrior = pNext->_pPrior;
            pCur->_pPrior = pPrior;
            pPrior->_pNext = pCur;
            pCur->_pNext = pNext;
            pNext->_pPrior = pCur;
            ++_nSize;
        }
    }

    /// @brief 删除指定位置的元素
    /// @param index 删除位置
    /// @return 返回被删除元素
    T deleteElem(size_t index)
    {
        assert(index > 0 && index <= _nSize + 1 && "Error: out of range! The index should be [1..size].");
        if (index == 1)
        {
            return popFront();
        }
        else if (index == _nSize)
        {
            return popBack();
        }
        else
        {
            Node* pNode = _pHead;
            for (auto i = 1; i < index; ++i)
            {
                pNode = pNode->_pNext;
            }

            Node* pPrior = pNode->_pPrior;
            Node* pNext = pNode->_pNext;
            pPrior->_pNext = pNext;
            pNext->_pPrior = pPrior;

            T res = pNode->_data;
            delete pNode;
            --_nSize;
            return res;
        }
    }

    /// @brief 获取指定位置的元素
    /// @param index 位置
    /// @return 指定位置的元素
    T getElem(size_t index)
    {
        assert(index > 0 && index <= _nSize && "Error: out of range, the index should be [1, size]!");
        Node* pNode = _pHead;
        for (auto i = 1; i < index; ++i)
        {
            pNode = pNode->_pNext;
        }
        return pNode->_data;
    }

    /// @brief 返回满足条件的第一个元素的位置
    /// @param e 用于定位的元素
    /// @param funcCompare 定位的方法
    /// @return 位置
    size_t locateElem(const T& e, const Compare<T>& funcCompare = selfCompare<T>)
    {
        Node* pNode = _pHead;
        for (auto i = 0; i < _nSize; ++i)
        {
            if (funcCompare(pNode->_data, e))
            {
                return i + 1;
            }
            pNode = pNode->_pNext;
        }
        return 0;
    }

    /// @brief 遍历列表
    /// @param funcVisit 遍历列表的函数
    void traverse(const Visit<T>& funcVisit = selfVisit<T>)
    {
        funcVisit(this);
    }

private:
    Node* _pHead;
    Node* _pTail;
    size_t _nSize;
};

template <typename T>
Compare<T> selfCompare = [](const T& e1, const T& e2) { return e1 == e2; };

template <typename T>
Visit<T> selfVisit = [](LinkList<T>* self) {
    for (auto i = 0; i < self->size(); ++i)
    {
        std::cout << self->getElem(i + 1) << ' ';
    }
    std::cout << '\n';
};
