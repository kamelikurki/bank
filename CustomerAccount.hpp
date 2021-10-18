#include "Account.hpp"

template<typename T>
class CustomerAccount : public Account<T>
{
public:
    CustomerAccount(AccountID<T> id, std::string ownerFirstName, std::string ownerLastName) : Account<T>(id), firstName(ownerFirstName), lastName(ownerLastName) {}

    std::string getAccountData()
    {
        std::string output = "Account type: Customer Account \nOwner:" + firstName + " " + lastName +"\n";  
        return output;
    }

private:
    std::string firstName;
    std::string lastName; 
};
