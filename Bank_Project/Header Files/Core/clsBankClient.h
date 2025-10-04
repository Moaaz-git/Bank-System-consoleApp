#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "../Lib/clsString.h"
#include "clsPerson.h"
#include <ctime>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{

private:
    // state of object inside the class
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    string _PreapareTransferLogRecord(double Amount, clsBankClient DestinationClient, string Username, string Delim = "#//#")
    {
        string Line = "";

        Line += clsDate::GetSystemDateTimeString() + Delim;
        Line += AccountNumber() + Delim;
        Line += DestinationClient.AccountNumber() + Delim;
        Line += to_string(Amount) + Delim;
        Line += to_string(AccountBalance()) + Delim;
        Line += to_string(DestinationClient.AccountBalance()) + Delim;
        Line += Username;

        return Line;
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName() + Seperator;
        stClientRecord += Client.LastName() + Seperator;
        stClientRecord += Client.Email() + Seperator;
        stClientRecord += Client.PhoneNumber() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode() + Seperator;
        stClientRecord += to_string(Client.AccountBalance());

        return stClientRecord;
    }

    void _AddDataLineToFile(string stClientData)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stClientData << endl;
            MyFile.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C._MarkForDelete == false)
                {
                    string line = _ConverClientObjectToLine(C);
                    MyFile << line << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vBankCleints = _LoadDataFromFile();

        for (clsBankClient &C : vBankCleints)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(vBankCleints);
    }

    static clsBankClient _ConvertLineToRecord(string line, string Delim = "#//#")
    {
        vector<string> vSplitLine = clsString::Split(line, Delim);

        return clsBankClient(enMode::UpdateMode, vSplitLine[0], vSplitLine[1], vSplitLine[2], vSplitLine[3], vSplitLine[4], vSplitLine[5], stof(vSplitLine[6]));
    }

    static clsBankClient _GetEmptyObject()
    {
        return clsBankClient(enMode::EmptyMode, " ", " ", " ", " ", " ", " ", 0);
    }

    static vector<clsBankClient> _LoadDataFromFile()
    {

        vector<clsBankClient> vClients;
        fstream MyFille;
        MyFille.open("Clients.txt", ios::in);

        string line = "";
        if (MyFille.is_open())
        {
            while (getline(MyFille, line))
            {
                clsBankClient Client = _ConvertLineToRecord(line);
                vClients.push_back(Client);
            }
            MyFille.close();
        }

        return vClients;
    }

public:
    clsBankClient()
        : clsPerson("", "", "", "")
    {
        _Mode = enMode::EmptyMode;
        _AccountNumber = "";
        _PinCode = "";
        _AccountBalance = 0.0f;
    }

    struct stTransferInfo
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;
    };

    static stTransferInfo ConvertTransferLineToRecord(string Line, string Delim = "#//#")
    {
        vector<string> vSplitLineInfo = clsString::Split(Line, Delim);

        stTransferInfo TransferInfo;
        TransferInfo.DateTime = vSplitLineInfo[0];
        TransferInfo.SourceAccountNumber = vSplitLineInfo[1];
        TransferInfo.DestinationAccountNumber = vSplitLineInfo[2];
        TransferInfo.Amount = stof(vSplitLineInfo[3]);
        TransferInfo.srcBalanceAfter = stof(vSplitLineInfo[4]);
        TransferInfo.destBalanceAfter = stof(vSplitLineInfo[5]);
        TransferInfo.UserName = vSplitLineInfo[6];

        return TransferInfo;
    }

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber,
                  string AccountNumber, string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName, Email, PhoneNumber)
    {
        _Mode = Mode;
        _PinCode = PinCode;
        _AccountNumber = AccountNumber;
        _AccountBalance = AccountBalance;
    }

    // Getters
    string AccountNumber() const
    {
        return _AccountNumber;
    }

    string PinCode() const
    {
        return _PinCode;
    }

    float AccountBalance() const
    {
        return _AccountBalance;
    }

    enMode Mode() const
    {
        return _Mode;
    }

    // Setters
    void SetAccountNumber(const string &AccountNumber)
    {
        _AccountNumber = AccountNumber;
    }

    void SetPinCode(const string &PinCode)
    {
        _PinCode = PinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    void SetMode(enMode Mode)
    {
        _Mode = Mode;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsBankClient Find(string AccountNumber)
    {

        vector<clsBankClient> vBankClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line = "";
            while (getline(MyFile, line))
            {
                clsBankClient BankClient = _ConvertLineToRecord(line);
                if (BankClient.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return BankClient;
                }
                vBankClients.push_back(BankClient);
            }

            MyFile.close();
        }

        return _GetEmptyObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {

        vector<clsBankClient> vBankClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string line = "";
            while (getline(MyFile, line))
            {
                clsBankClient BankClient = _ConvertLineToRecord(line);
                if (BankClient.AccountNumber() == AccountNumber && BankClient.PinCode() == PinCode)
                {
                    MyFile.close();
                    return BankClient;
                }
                vBankClients.push_back(BankClient);
            }

            MyFile.close();
        }

        return _GetEmptyObject();
    }

    static bool IsClientExists(string AccountNumber)
    {
        clsBankClient BankClient = clsBankClient::Find(AccountNumber);
        return (!BankClient.IsEmpty());
    }

    enum enSaveResults
    {
        svFalidEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExists = 2
    };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFalidEmptyObject;
            }
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExists(_AccountNumber))
            {
                // This will add new record to file or database
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                // We need to set the mode to update after add new
                _Mode = enMode::AddNewMode;
                return enSaveResults::svSucceeded;
            }
        }
        }
    }

    bool DeleteClient()
    {
        vector<clsBankClient> vClients = _LoadDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyObject();

        return true;
    }

    static clsBankClient GetNewBankClientObject(string AccNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccNumber, "", 0);
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadDataFromFile();
    }

    static float GetTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadDataFromFile();

        float TotalBalance = 0;
        for (clsBankClient C : vClients)
        {
            TotalBalance += C.AccountBalance();
        }

        return TotalBalance;
    }

    // Transaction Functions::::

    void Deposit(double DepositAmount)
    {
        _AccountBalance += DepositAmount;
        Save();
    }

    bool WithDraw(double WithdrawAmount)
    {
        if (WithdrawAmount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= WithdrawAmount;
            Save();
        }
    }

    void SureWithDraw(double WithdrawAmount)
    {
        _AccountBalance -= WithdrawAmount;
        Save();
    }

    bool Transfer(double Amount, clsBankClient &DestinationClient, string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        SureWithDraw(Amount);
        DestinationClient.Deposit(Amount);
        this->RegisterTransferOperation(Amount, DestinationClient, UserName);
        return true;
    }

    void RegisterTransferOperation(double Amount, clsBankClient DestinationClient, string Username)
    {
        string Line = "";
        Line = this->_PreapareTransferLogRecord(Amount, DestinationClient, Username);

        fstream MyFile;
        MyFile.open("TranferOperations.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << Line << endl;

            MyFile.close();
        }
    }

    static vector<stTransferInfo> GetTransferInfoFromFile()
    {
        vector<stTransferInfo> vTransferInfo;
        fstream MyFile;
        MyFile.open("TranferOperations.txt", ios::in);

        string Line = "";
        stTransferInfo TransferInfo;
        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                TransferInfo = ConvertTransferLineToRecord(Line);
                vTransferInfo.push_back(TransferInfo);
            }
            MyFile.close();
        }

        return vTransferInfo;
    }
};