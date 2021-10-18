#include <string>
#include <vector>
#include <memory>
#include "AccountID.hpp"

template <typename T>
class Bank
{
public:
    Bank();
    ~Bank();
    /*
    \brief Creates a new bank account
    \param newID AccountID object for the new class
    \param data Account data, for customer account provide 2 strings firstName and lastName, for Enterprise acccount provide 2 strings Company name and Ytunnus
    \param type Account type, use 1 for customer account and 2 for enterprise account
    \return true if creation was successful, false otherwise
    */
    bool createNewAccount(AccountID<T> newID, std::vector<std::string> data, int type);

    /*
    \brief Withdraws from a given account
    \param amountToWithdraw Amount to withdraw in eur. Value will be truncated to 2 decimal places before withdrawing
    \param accountToWithdrawFrom AccountID of the account from which to withdraw
    \return float value of the actual amount withdrawn
    */
    float withdraw(const float amountToWithdraw, const AccountID<T> accountToWithdrawFrom);

    /*
    \brief Withdraws from a given account
    \param amountToDeposit Amount to deposit in eur. Value will be truncated to 2 decimal places before deposit
    \param accountToDepositTo AccountID of the account  to which to deposit to
    \return float value of the actual amount deposit
    */
    float deposit(const float amountToDeposit, const AccountID<T> accountToDepositTo);

    /*
    \brief Get the balance of a given account
    \param accountToGetBalanceFor AccountID of the account to get the balance for 
    \param accountExists reference to a boolean variable where to store data about if the account exists
    \return float value with the account balance
    */
    float getBalance(const AccountID<T> accountToGetBalanceFor, bool& accountExists);

    /*
    \brief Get the details of a given account
    \param id AccountID of the account to get the information for
    \return std::string with the account information
    */
    std::string getAccountDetails(AccountID<T> id);

private:
      
    class bankImplementation;
    std::unique_ptr<bankImplementation> pimpl;
};




