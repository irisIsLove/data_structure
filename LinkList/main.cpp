#include "LinkList.hpp"

int main()
{
    std::cout << "LinkList test begin:\n\n";

    LinkList<int> list;
    for (auto i = 0; i < 10; ++i)
    {
        list.pushFront(i);
    }
    std::cout << "pushFront test: ";
    list.traverse();

    for (auto i = 10; i < 20; ++i)
    {
        list.insertElem(i + 1, i);
    }
    std::cout << "insertElem test: ";
    list.traverse();

    for (auto i = 20; i < 30; ++i)
    {
        list.pushBack(i);
    }
    std::cout << "pushBack test: ";
    list.traverse();

    auto index = list.locateElem(15);
    std::cout << "Locate The element 15 in list: " << index << '\n';

    std::cout << "Delete the element 15: ";
    list.deleteElem(index);
    list.traverse();

    std::cout << "popFront test: ";
    list.popFront();
    list.traverse();

    std::cout << "popBack test: ";
    list.popBack();
    list.traverse();

    std::cout << "\nLinkList test end!\n";
}