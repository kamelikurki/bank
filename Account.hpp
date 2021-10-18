#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <climits>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "AccountID.hpp"

template <typename T>
class Account
{
public:

    Account(AccountID<T> id) : accountID(id), balanceCents(0) {}
    ~Account() {};

    float withdraw(const float amountToWithdraw)
    {
        float actualWithdraw = 0.0f;
        // Check for NaN or Inf and that the amount is not negative
        if(std::isfinite(amountToWithdraw) && !(amountToWithdraw < 0.0f))
        {
            // Convert to cents and remove decimals after. Only do so if there will be no overflow 
            if ((amountToWithdraw*100.0f) < UINT_MAX) 
            {
                unsigned int centsToWithdraw = static_cast<unsigned int>(amountToWithdraw*100.0f);

                // If there's enough balance, withdraw
                if(balanceCents >= centsToWithdraw)
                {
                    balanceCents -= centsToWithdraw;
                    actualWithdraw = static_cast<float>(centsToWithdraw) / 100.0f;
                }
            }          
        }

        return actualWithdraw;
    }

    float deposit(const float amountToDeposit)
    {
        float actualDeposit = 0.0f;

        // Check for NaN or Inf and that the amount is not negative
        if(std::isfinite(amountToDeposit) && !(amountToDeposit < 0.0f))
        {
            if ((amountToDeposit*100.0f) < UINT_MAX) 
            {
                // Truncate to 2 digits and transform to cents
                unsigned int centsToDeposit = static_cast<unsigned int>(amountToDeposit*100.0f);
                
                // If the deposit won't exceed the maximum balance of the account, deposit
                if(UINT_MAX - centsToDeposit >= balanceCents)
                {
                    balanceCents += centsToDeposit;
                    actualDeposit = static_cast<float>(centsToDeposit) / 100.0f;   
                }
            }
        }
        return actualDeposit;
    }

    AccountID<T> getAccountID()
    {
        return accountID;
    }

    std::string idAsString(AccountID<int> id)
    {
        return std::to_string(id.getID());
    }

    std::string idAsString(AccountID<std::string> id)
    {
        return id.getID();
    }

    std::string getFullAccountData()
    {
        std::string output("\nAccount ID: ");
        output += idAsString(accountID);
        output += "\nDate Created: ";
        std::time_t t_c = std::chrono::system_clock::to_time_t(accountID.getDate());
        struct tm * timeinfo = localtime (&t_c);

        char buffer[80];
        strftime (buffer,80,"%c",timeinfo);

        output += buffer;
        output += "\n";
        output += getAccountData();

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << static_cast<float>(balanceCents) / 100.f;
        std::string s = stream.str();

        output += "Account balance: " + s + "\n\n";
        return output;
    }
    
    float getBalance()
    {
        return static_cast<float>(balanceCents) / 100.0f;
    }

    virtual std::string getAccountData() = 0;

private:
    AccountID<T> accountID;
    unsigned int balanceCents;
};