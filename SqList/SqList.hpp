#pragma once

#include <cassert>
#include <functional>
#include <iostream>

template <typename T>
class SqList;

template <typename T>
using Compare = std::function<bool(const T&, const T&)>;

template <typename T>
Compare<T> selfCompare = [](const T& e1, const T& e2) { return e1 == e2; };

template <typename T>
using Visit = std::function<void(SqList<T>*)>;

template <typename T>
Visit<T> selfVisit = [](SqList<T>* self) {
    for (auto i = 0; i < self->size(); ++i)
    {
        std::cout << self->getElem(i + 1) << ' ';
    }
    std::cout << '\n';
};

template <typename T>
class SqList
{
    enum : size_t
    {
        LIST_INCRESEMENT = 10,
        LIST_INIT_SIZE = 100,
    };

public:
    SqList()
        : _pElems(new T[LIST_INIT_SIZE])
        , _nCapacity(LIST_INIT_SIZE)
        , _nSize(0){};

    ~SqList() { delete[] _pElems; }

    /// @brief 清空线性表中的数据
    void clear()
    {
        _nSize = 0;
    }

    /// @brief 判断线性表是否为空
    /// @return 为空返回true，反之返回false
    bool isEmpty()
    {
        return _nSize == 0 ? true : false;
    }

    /// @brief
    /// @return 返回线性表大小
    size_t size() const
    {
        return _nSize;
    }

    /// @brief
    /// @param index 索引值
    /// @return 返回索引值为第i个元素的引用
    T getElem(size_t index) const
    {
        assert(((index > 0 && index <= _nSize) && _pElems != nullptr) && "Error: out of range!");
        return _pElems[index - 1];
    }

    /// @brief 判断线性表中第一个e满足funcCompare的元组的位置
    /// @param e 输入元素
    /// @param funcCompare 比较函数，默认是比较是否相等 函数类型：bool(const T&, const T&)
    /// @return 若元素存在返回索引，若不存在返回0
    size_t locateElem(const T& e, const Compare<T>& funcCompare = selfCompare<T>)
    {
        assert((_nSize > 0) && "Error: List is empty!");
        for (auto i = 0; i < _nSize; ++i)
        {
            if (funcCompare(e, _pElems[i]))
            {
                return i + 1;
            }
        }
        return 0;
    }

    /// @brief
    /// @param curElem 当前元素，不能为第一个元素
    /// @return 返回当前元素的前一个元素
    T priorElem(const T& curElem)
    {
        assert((_nSize > 0) && "Error: List is empty!");
        assert((locateElem(curElem) != 1) && "Error: The first element have no prior element!");
        auto nCurIndex = locateElem(curElem);
        return getElem(nCurIndex - 1);
    }

    /// @brief
    /// @param curElem 当前元素，不能为最后一个元素
    /// @return 返回当前元素的后一个元素
    T nextElem(const T& curElem)
    {
        assert((_nSize > 0) && "Error: List is empty!");
        assert((locateElem(curElem) != _nSize) && "Error: The last element have no next element!");
        auto nCurIndex = locateElem(curElem);
        return getElem(nCurIndex + 1);
    }

    /// @brief 在index的位置上插入元素e
    /// @param index 插入位置
    /// @param e 插入元素
    void insertElem(size_t index, const T& e)
    {
        assert((index > 0 && index <= _nSize + 1) && "Error: Index is out of range!");
        if (_nSize == _nCapacity)
        {
            auto nNewCapacity = _nCapacity + LIST_INCRESEMENT;
            T* pNewElems = new T[nNewCapacity];
            assert((pNewElems != nullptr) && "Error: Memory allocate failed!");
            for (auto i = 0; i < _nSize; ++i)
            {
                pNewElems[i] = _pElems[i];
            }
            delete[] _pElems;
            _pElems = pNewElems;
            _nCapacity = nNewCapacity;
        }

        for (auto i = _nSize; i > index; --i)
        {
            _pElems[i] = _pElems[i - 1];
        }
        _pElems[index - 1] = e;
        ++_nSize;
    }

    /// @brief 删除位置为index的元素
    /// @param index 需要删除元素的位置
    /// @return 返回被删除的值
    T deleteElem(size_t index)
    {
        assert((index > 0 && index <= _nSize) && "Error: Index is out of range!");
        T result = _pElems[index - 1];
        --_nSize;
        for (auto i = index - 1; i < _nSize; ++i)
        {
            _pElems[i] = _pElems[i + 1];
        }
        return result;
    }

    /// @brief 通过funcVisit遍历线性表
    /// @param funcVisit 为遍历函数 函数类型为 void(SqList<T>*)
    void traverse(const Visit<T>& funcVisit = selfVisit<T>)
    {
        funcVisit(this);
    }

    /// @brief 合并两个列表，合并的两个列表应为非递减排列的
    /// @param l1 输入的第一个列表
    /// @param l2 输入的第二个列表
    /// @param l3 输出的列表
    static void merge(const SqList<T>& listInput1, const SqList<T>& listInput2, SqList<T>& listOutput)
    {
        std::cout << "\nUse this function to ensure that the two lists are non-decreasing.\n";
        int i = 1, j = 1, k = 1;

        while (i <= listInput1.size() && j <= listInput2.size())
        {
            T elem1 = listInput1.getElem(i);
            T elem2 = listInput2.getElem(j);

            if (elem1 < elem2)
            {
                listOutput.insertElem(k, elem1);
                ++i;
            }
            else
            {
                listOutput.insertElem(k, elem2);
                ++j;
            }

            ++k;
        }

        while (i <= listInput1.size())
        {
            listOutput.insertElem(k, listInput1.getElem(i));
            ++i;
            ++k;
        }

        while (j <= listInput2.size())
        {
            listOutput.insertElem(k, listInput2.getElem(j));
            ++j;
            ++k;
        }
    }

private:
    T* _pElems;
    size_t _nCapacity;
    size_t _nSize;
};