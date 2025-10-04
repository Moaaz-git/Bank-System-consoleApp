#pragma once

#include <string>
#include <iostream>
using namespace std;

class clsPerson
{

private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _PhoneNumber;

public:
    clsPerson(string FirstName, string LastName, string Email, string PhoneNumber)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _PhoneNumber = PhoneNumber;
    }

    // Getters
    string FirstName() const
    {
        return _FirstName;
    }

    string LastName() const
    {
        return _LastName;
    }

    string Email() const
    {
        return _Email;
    }

    string PhoneNumber() const
    {
        return _PhoneNumber;
    }

    string FullName() const
    {
        return _FirstName + " " + _LastName;
    }

    // Setters
    void SetFirstName(const string &FirstName)
    {
        _FirstName = FirstName;
    }

    void SetLastName(const string &LastName)
    {
        _LastName = LastName;
    }

    void SetEmail(const string &Email)
    {
        _Email = Email;
    }

    void SetPhoneNumber(const string &PhoneNumber)
    {
        _PhoneNumber = PhoneNumber;
    }

    void SendEmail(string Title, string Body)
    {
    }
    void SendFax(string Title, string Body)
    {
    }
    void SendSMS(string Title, string Body)
    {
    }
};