#include "Bank.hpp"
#include "UnitTest.hpp"
#include <iostream>
#include <vector> 

int getIntInput()
{
    int output;
    std::cin >> output;
    while(std::cin.fail()) {
        std::cout << "Error, please enter an integer value" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> output;
    }
    return output;
}

float getFloatInput()
{
    float output;
    std::cin >> output;
    while(std::cin.fail()) {
        std::cout << "Error, please enter a float value" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> output;
    }
    return output;
}

int main(int argc, char *argv[]) 
{

    if(argc == 2 && std::string("test") == argv[1])
    {
        auto testResult = runTests();
        if(testResult == false)
        {
            std::cout << "The tests returned with a failure\n";
        }
        
    }
    else if(argc == 2 && std::string("bank") == argv[1])
    {
        int choice;
        Bank<int> myBank;

        while(1)
        {
            std::cout << "Welcome to the bank \n 1) Create new Account \n 2) Get the details of an existing account \n 3) Deposit \n 4) Withdraw \n 5) Leave\n";
            choice = getIntInput();
    
            int accountNum;
            switch(choice)
            {
                case 1:            
                    std::cout << "Would you like to create an enterprise or customer account ? Type 1 for customer and 2 for enterprise...\n";
                    choice = getIntInput();

                    std::cout << "Please give account id for the new account\n";

                    accountNum = getIntInput();

                    if(choice == 2)
                    {
                        std::string companyName;
                        std::string yTunnus;
                        std::cout << "Please give company name:\n";
                        std::cin >> companyName;
                        std::cout << "Please give ytunnus:\n";
                        std::cin >> yTunnus;
                        std::vector<std::string> inputData;
                        inputData.push_back(companyName);
                        inputData.push_back(yTunnus);
                        AccountID<int> id(accountNum);
                        myBank.createNewAccount(id, inputData, 2);
                    }
                    else if( choice == 1)
                    {
                        std::string firstName;
                        std::string lastName;
                        std::cout << "Please give first name:\n";
                        std::cin >> firstName;
                        std::cout << "Please give last name:\n";
                        std::cin >> lastName;
                        std::vector<std::string> inputData;
                        inputData.push_back(firstName);
                        inputData.push_back(lastName);
                        AccountID<int> id(accountNum);
                        myBank.createNewAccount(id, inputData, 1);          
                    }
                    break;

                case 2:
                    {
                        std::cout << "Give id number for the Account to get the information for: \n";
                        accountNum = getIntInput();
                        AccountID<int> tmpID(accountNum);
                        std::cout << myBank.getAccountDetails(tmpID);
                    }

                    break; 
                    
                case 3:
                    {
                        std::cout << "Give an account to which to make the deposit to:\n";
                        accountNum = getIntInput();
                        std::cout << "Give an amount to deposit:\n";
                        float depositAmount;
                        depositAmount = getFloatInput();

                        std::cout << "Trying to deposit " + std::to_string(depositAmount) + " eur\n";
                        AccountID<int> tmpID(accountNum);
                        auto result  = myBank.deposit(depositAmount, tmpID);
                        std::cout << "Deposit with amount " + std::to_string(result) + "eur made\n";
                    }
                    break;
                
                case 4:
                    {
                        std::cout << "Give an account from which to withdraw:\n";
                        accountNum = getIntInput();
                        std::cout << "Give an amount to withdraw:\n";
                        float withdrawAmount;
                        withdrawAmount = getFloatInput();

                        std::cout << "Trying to withdraw " + std::to_string(withdrawAmount) + " eur\n";
                        AccountID<int> tmpID(accountNum);
                        auto result  = myBank.withdraw(withdrawAmount, tmpID);
                        std::cout << "Withdrew " + std::to_string(result) + "eur\n";
                    }
                    break;

                case 5:
                    break;
                default:
                    break;
            }

            if(choice  == 5)
            {
                break;
            }
        }
    }
    else
    {
        std::cout << "Usage: " << std::endl << "Run tests: "+ std::string(argv[0]) + " test" << std::endl << "Use bank: " + std::string(argv[0]) + " bank" << std::endl;
    }

    return 0;
}