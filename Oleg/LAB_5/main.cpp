#include <cassert>
#include <iostream>
#include <list>

class theMostImportantList {
public:
    virtual ~theMostImportantList() = 0;
    virtual int &front() = 0;
    virtual int &back() = 0;
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual void popSecond(bool FirstNode) = 0;
    virtual void extend(const theMostImportantList &otherList) = 0;
    virtual unsigned int size() const = 0;
    virtual bool empty() const = 0;
    virtual bool length() const = 0;
};

inline theMostImportantList::~theMostImportantList() = default;

class NotTheMostImportantList : public theMostImportantList {
private:
    std::list<int> data;

public:
    NotTheMostImportantList(const int* arr, size_t size);
    int &front() override;
    int &back() override;
    void push(int value) override;
    void pop() override;
    void popSecond(bool FirstNode) override;
    void extend(const theMostImportantList &otherList) override;
    unsigned int size() const override;
    bool empty() const override;
    bool length() const override;
};

NotTheMostImportantList::NotTheMostImportantList(const int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        push(arr[i]);
    }
}

int &NotTheMostImportantList::front() {
    if(!data.empty())
        return data.front();
}

int &NotTheMostImportantList::back() {
    assert(!data.empty() && "List is empty");
    return data.back();
}

void NotTheMostImportantList::push(int value) {
    data.push_back(value);
}

void NotTheMostImportantList::pop() {
    if (!data.empty())
        data.pop_back();
}

void NotTheMostImportantList::popSecond(bool FirstNode) {
    if (!data.empty()) {
        if (FirstNode)
            data.pop_front();
        else
            data.pop_back();
    }
}

void NotTheMostImportantList::extend(const theMostImportantList &otherList) {

}


unsigned int NotTheMostImportantList::size() const {
    return data.size();
}

bool NotTheMostImportantList::empty() const {
    return data.empty();
}

bool NotTheMostImportantList::length() const
{
    return data.length();
}

