#pragma once 
#include <ctime>
#include <chrono>

template<typename T>
class AccountID
{
public:
    AccountID(T initialID) : id(initialID), dateCreated(std::chrono::system_clock::now()) {}

    T getID() {return id;}

    const std::chrono::time_point<std::chrono::system_clock>  getDate() {return dateCreated;}

    bool operator==(const AccountID& id1) {return this->id == id1.id;}
    

private:
    T id;
    const std::chrono::time_point<std::chrono::system_clock>  dateCreated;
};