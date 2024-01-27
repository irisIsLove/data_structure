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

    /// @brief ������Ա��е�����
    void clear()
    {
        _nSize = 0;
    }

    /// @brief �ж����Ա��Ƿ�Ϊ��
    /// @return Ϊ�շ���true����֮����false
    bool isEmpty()
    {
        return _nSize == 0 ? true : false;
    }

    /// @brief
    /// @return �������Ա��С
    size_t size() const
    {
        return _nSize;
    }

    /// @brief
    /// @param index ����ֵ
    /// @return ��������ֵΪ��i��Ԫ�ص�����
    T& getElem(size_t index)
    {
        assert(((index > 0 && index <= _nSize) && _pElems != nullptr) && "Error: out of range!");
        return _pElems[index - 1];
    }

    /// @brief �ж����Ա��е�һ��e����funcCompare��Ԫ���λ��
    /// @param e ����Ԫ��
    /// @param funcCompare �ȽϺ�����Ĭ���ǱȽ��Ƿ����
    /// @return ��Ԫ�ش��ڷ����������������ڷ���0
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
    /// @param curElem ��ǰԪ�أ�����Ϊ��һ��Ԫ��
    /// @return ���ص�ǰԪ�ص�ǰһ��Ԫ��
    T& priorElem(const T& curElem)
    {
        assert((_nSize > 0) && "Error: List is empty!");
        assert((locateElem(curElem) != 1) && "Error: The first element have no prior element!");
        auto nCurIndex = locateElem(curElem);
        return getElem(nCurIndex - 1);
    }

    /// @brief
    /// @param curElem ��ǰԪ�أ�����Ϊ���һ��Ԫ��
    /// @return ���ص�ǰԪ�صĺ�һ��Ԫ��
    T& nextElem(const T& curElem)
    {
        assert((_nSize > 0) && "Error: List is empty!");
        assert((locateElem(curElem) != _nSize) && "Error: The last element have no next element!");
        auto nCurIndex = locateElem(curElem);
        return getElem(nCurIndex + 1);
    }

    /// @brief ��index��λ���ϲ���Ԫ��e
    /// @param index ����λ��
    /// @param e ����Ԫ��
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

    /// @brief ɾ��λ��Ϊindex��Ԫ��
    /// @param index ��Ҫɾ��Ԫ�ص�λ��
    /// @return ���ر�ɾ����ֵ
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

    /// @brief ͨ��funcVisit�������Ա�
    /// @param funcVisit
    void traverse(const Visit<T>& funcVisit = selfVisit<T>)
    {
        funcVisit(this);
    }

private:
    T* _pElems;
    size_t _nCapacity;
    size_t _nSize;
};