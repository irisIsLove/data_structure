#include "SqList.hpp"

int main()
{
    std::cout << "SqList test begin:\n\n";
    SqList<int> list;
    std::cout << "List is empty: " << list.isEmpty() << '\n';

    for (auto i = 0; i < 123; ++i)
    {
        list.insertElem(i + 1, static_cast<int>(i));
    }
    list.traverse();
    std::cout << "List's size: " << list.size() << '\n';
    std::cout << "List is empty: " << list.isEmpty() << '\n';

    auto index = list.locateElem(55);
    std::cout << "Locate The element 55 in list: " << index << '\n';
    std::cout << "The element 55's prior element is " << list.priorElem(55) << '\n';
    std::cout << "The element 55's next element is " << list.nextElem(55) << '\n';

    std::cout << "Delete the element 55" << '\n';
    list.deleteElem(index);
    list.traverse();
    std::cout << "\nSqList test end!\n";
}