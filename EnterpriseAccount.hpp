#include "Account.hpp"    

template<typename T>
class EnterpriseAccount : public Account<T>
{
public:
    EnterpriseAccount(AccountID<T> id, std::string companyNameForAccount, std::string ytunnusForAccount): Account<T>(id), ytunnus(ytunnusForAccount),companyName(companyNameForAccount) {}

    std::string getAccountData()
    {
        std::string output = "Account type: Enterprise Account\nCompany: " + companyName + "\nYtunnus: " + ytunnus + "\n";  
        return output;
    }

private:
    std::string ytunnus;
    std::string companyName;
};
