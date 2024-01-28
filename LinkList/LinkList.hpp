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

    /// @brief ������Ա��е�����
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

    /// @brief �ж����Ա��Ƿ�Ϊ��
    /// @return Ϊ�շ���true����֮����false
    bool isEmpty() { return _nSize == 0; }

    /// @brief
    /// @return �������Ա��С
    size_t size() const { return _nSize; }

    /// @brief ������ͷ������һ��Ԫ��
    /// @param e ����Ԫ��
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

    /// @brief ɾ��ͷ��Ԫ��
    /// @return ���ر�ɾ��Ԫ��
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

    /// @brief ������β������µ�Ԫ��
    /// @param e ����Ԫ��
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

    /// @brief ɾ��β��Ԫ��
    /// @return ���ر�ɾ��Ԫ��
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

    /// @brief ��ָ��λ�ò���Ԫ��
    /// @param index ����Ԫ��λ��
    /// @param e ����Ԫ��
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

    /// @brief ɾ��ָ��λ�õ�Ԫ��
    /// @param index ɾ��λ��
    /// @return ���ر�ɾ��Ԫ��
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

    /// @brief ��ȡָ��λ�õ�Ԫ��
    /// @param index λ��
    /// @return ָ��λ�õ�Ԫ��
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

    /// @brief �������������ĵ�һ��Ԫ�ص�λ��
    /// @param e ���ڶ�λ��Ԫ��
    /// @param funcCompare ��λ�ķ���
    /// @return λ��
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

    /// @brief �����б�
    /// @param funcVisit �����б�ĺ���
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
