#include "Bank.hpp"
#include "Account.hpp"
#include "EnterpriseAccount.hpp"
#include "CustomerAccount.hpp"
#include <memory>

template<typename T>
class Bank<T>::bankImplementation
{
public:

    bool createNewAccount(AccountID<T> id, std::vector<std::string> data, int type)
    {
        bool accountCreated = false;
        if(getAccountByID(id) == nullptr && data.size() == 2)
        {
            if(type == 1)
            {
                accounts.push_back(std::make_shared<CustomerAccount<T>>(id, data[0], data[1]));
                accountCreated =  true;
            }
            else if(type == 2)
            {
                accounts.push_back(std::make_shared<EnterpriseAccount<T>>(id, data[0], data[1]));
                accountCreated =  true;
            }
        }

        return accountCreated;
    }


    float withdraw(const float amountToWithdraw, const AccountID<T> id)
    {
        auto acc = getAccountByID(id);
        float amountWithdrawn = 0.0f;
        if(acc != nullptr)
        {
            amountWithdrawn =  acc->withdraw(amountToWithdraw);
        }
        return amountWithdrawn;
    }

    float deposit(const float amountToDeposit, const AccountID<T> id)
    {
        auto acc = getAccountByID(id);
        float amountDeposit = 0.0f;
        if(acc != nullptr)
        {
            amountDeposit = acc->deposit(amountToDeposit);
        }
        return amountDeposit;     
    }

    std::string getAccountDetails(AccountID<T> idToGet)  
    {
        auto acc = getAccountByID(idToGet);
        std::string output("");
        if(acc != nullptr)
        {
            output = acc->getFullAccountData();
        }

        return output;
    }

    float getBalance(const AccountID<T> accountToGetBalanceFor, bool& accountExists)
    {
        auto acc = getAccountByID(accountToGetBalanceFor);
        float balance = 0.0f;
        if(acc != nullptr)
        {
            balance =  acc->getBalance();
            accountExists = true;
        }
        else
        {
            accountExists = false;
        }

        return balance;
    }

private:

    std::vector<std::shared_ptr<Account<T>>> accounts;

    std::shared_ptr<Account<T>> getAccountByID(AccountID<T> id)
    {
        std::shared_ptr<Account<T>> selectedAccount = nullptr;
  
        for(auto &acc : accounts)
        {
            if(acc->getAccountID().getID() == id.getID())
            selectedAccount = acc;
        }


        return selectedAccount;
    }
};


template<typename T>
Bank<T>::Bank() : pimpl(std::make_unique<bankImplementation>())
{

}

template<typename T>
Bank<T>::~Bank()
{

}

template<typename T>
bool Bank<T>::createNewAccount(AccountID<T> id, std::vector<std::string> data, int type)
{
    return pimpl->createNewAccount(id,data,type);
}

template<typename T>
float Bank<T>::withdraw(const float amountToWithdraw, const AccountID<T> id)
{
    return pimpl->withdraw(amountToWithdraw, id);
}

template<typename T>
float Bank<T>::deposit(const float amountToDeposit, const AccountID<T> id)
{
    return pimpl->deposit(amountToDeposit,id);
}

template<typename T>
std::string Bank<T>::getAccountDetails(AccountID<T> id)
{
    return pimpl->getAccountDetails(id);
}

template<typename T>
float Bank<T>::getBalance(const AccountID<T> accountToGetBalanceFor, bool& accountExists)
{
    return pimpl->getBalance(accountToGetBalanceFor, accountExists);
}

template class Bank<int>;
template class Bank<std::string>;