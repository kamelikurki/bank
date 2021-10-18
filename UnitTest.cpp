#include "UnitTest.hpp"
#include "Bank.hpp"
#include <vector> 
#include <string> 
#include <climits>
#include <iostream>
bool runTests()
{
    Bank<int> testBank;
    
    // Create test accounts
    AccountID<int> customerID(123);
    std::vector<std::string> customerTestData;
    customerTestData.push_back("ville");
    customerTestData.push_back("saari");
    
    AccountID<int> enterpriseID(1234);
    std::vector<std::string> enterpriseTestData;
    enterpriseTestData.push_back("company");
    enterpriseTestData.push_back("ytunnus");
    
    // Test creating customer account
    auto success = testBank.createNewAccount(customerID, customerTestData, 1);
    if(!success) 
    {
        std::cout << "Failed to create customer account"<< std::endl;
        return false;
    }

    // Test creating account with existing ID
    success = testBank.createNewAccount(customerID, customerTestData, 1);
    if(success) 
    {
        std::cout << "Failed to block creating customer account with the same id again"<< std::endl;
        return false;
    }

    // Test creating enterprise account
    success = testBank.createNewAccount(enterpriseID, enterpriseTestData, 2);
    if(!success) 
    {
        std::cout << "Failed to create enterprise account"<< std::endl;
        return false;
    }

    // Test that created customer account exists
    bool accountExists;
    auto balance = testBank.getBalance(customerID,accountExists);

    if(!accountExists)
    {
        std::cout << "Created customer account doesn't exist"<< std::endl;
        return false;
    }

    // Test that account balance is initialized to 0
    if(balance < 0.0f || balance > 0.0f)
    {
        std::cout << "Customer account balance is not initialized to 0"<< std::endl;
        return false;
    }

    // Test that created enterprise account exists 
    balance = testBank.getBalance(enterpriseID,accountExists);
    if(!accountExists)
    {
        std::cout << "Created enterprise account doesn't exist"<< std::endl;
        return false;
    }

    // Test that balance is initialized to 0
    if(balance < 0.0f || balance > 0.0f)
    {
        std::cout << "Enterprise account balance is not initialized to 0"<< std::endl;
        return false;
    }

    // Test deposit
    auto initialBalance = testBank.getBalance(enterpriseID, accountExists);
    float depositAmount = 100.0f;
    testBank.deposit(depositAmount,enterpriseID);
    auto newBalance =  testBank.getBalance(enterpriseID, accountExists);
    if(!(newBalance - (initialBalance + depositAmount) < 0.01f))
    {
        std::cout << "balance after deposit does not match."<< std::endl;
        return false;
    }


    // Test withdraw
     initialBalance = testBank.getBalance(enterpriseID, accountExists);
    float withdrawAmount = 50.0f;
    testBank.withdraw(withdrawAmount,enterpriseID);
    newBalance =  testBank.getBalance(enterpriseID, accountExists);
    if(!(newBalance - (initialBalance - withdrawAmount) < 0.01f))
    {
        std::cout << "balance after withdraw does not match."<< std::endl;
        return false;
    }

    // Test withdrawing negative amount 

    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.withdraw(-10.0f, accountExists);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Withdrawing a negative amount changed the account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // Test depositing negative amount 

    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.deposit(-10.0f, accountExists);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Depositing a negative amount changed the account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // Test withdrawing too much 

    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.withdraw(initialBalance+1.0f, accountExists);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Withdrawing too much changed the account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // test overflowing account 
    testBank.deposit(10.f,enterpriseID);
    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.deposit((float) UINT_MAX,enterpriseID);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Depositing over the maximum account value changed the the account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // test depositing NaN
    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.deposit(std::numeric_limits<float>::quiet_NaN(),enterpriseID);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Depositing NaN changed account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // Test depositing infinity
    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.deposit(std::numeric_limits<float>::infinity(),enterpriseID);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Depositing infinity changed account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // test withdrawing NaN
    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.withdraw(std::numeric_limits<float>::quiet_NaN(),enterpriseID);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Withdrawing NaN changed account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    // Test withdrawing infinity
    initialBalance = testBank.getBalance(customerID,accountExists);
    testBank.withdraw(std::numeric_limits<float>::infinity(),enterpriseID);
    newBalance =  testBank.getBalance(customerID,accountExists);
    if(!((initialBalance - newBalance) < 0.01))
    {
        std::cout << "Withdrawing infinity changed account balance. The balance should stay the same."<< std::endl;
        return false;
    }

    std::cout << "success" << std::endl;

    return true;
}