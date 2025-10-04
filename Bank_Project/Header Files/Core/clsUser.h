#pragma once

#include <iostream>
#include <string>
#include "../Lib/clsString.h"
#include "clsPerson.h"
#include "../Lib/clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;



class clsUser : public clsPerson
{
private:
    short Key = 2;
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkForDelete = false;

    
    string _ConvertDataToLine(string Delim = "#//#")
    {
        string Line = "";
        string EncryptedPassword = clsUtil::EncryptText(Password(),Key);
        Line += clsDate::GetSystemDateTimeString() + Delim;
        Line += UserName() + Delim;
        Line += EncryptedPassword + Delim;
        Line += to_string(Permissions());
        
        return Line;
    }
    
    static clsUser _ConvertLineToUserObject(string Line, string Delim = "#//#")
    {
        vector<string> vSplitLine = clsString::Split(Line, Delim);
        
        return clsUser(enMode::UpdateMode, vSplitLine[0], vSplitLine[1], vSplitLine[2], vSplitLine[3], vSplitLine[4], clsUtil::DecryptText(vSplitLine[5]), stoi(vSplitLine[6]));
    }
    
    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        string EncryptedPassword = clsUtil::EncryptText(User.Password(),User.Key);
        UserRecord += User.FirstName() + Seperator;
        UserRecord += User.LastName() + Seperator;
        UserRecord += User.Email() + Seperator;
        UserRecord += User.PhoneNumber() + Seperator;
        UserRecord += User.UserName() + Seperator;
        UserRecord += EncryptedPassword + Seperator;
        UserRecord += to_string(User.Permissions());
        
        return UserRecord;
    }
    
    static clsUser _GetEmptyObject()
    {
        return clsUser(enMode::EmptyMode, " ", " ", " ", " ", " ", " ", 0);
    }
    
    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        
        fstream MyFile;
        MyFile.open("Users.txt", ios::in); // read Mode
        
        if (MyFile.is_open())
        {
            
            string Line;
            
            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLineToUserObject(Line);

                vUsers.push_back(User);
            }
            
            MyFile.close();
        }
        
        return vUsers;
    }
    
    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out); // overwrite
        
        string DataLine;
        
        if (MyFile.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (U.MarkForDeleted() == false)
                {
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }
    
    void _Update()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();
        
        for (clsUser &U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U = *this;
                break;
            }
        }
        
        _SaveUsersDataToFile(_vUsers);
    }
    
    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }
    
    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);
        
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            
            MyFile.close();
        }
    }
    
    public:
    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pLoginRegisters = 128,
        pCurrency = 256
    };
    
    struct stLoginRegisterRecord
    {
        string DateTime = "";
        string LoginUser = "";
        string Password= "";
        int Permissions = 0;
    };

    static stLoginRegisterRecord _ConvertRegisterLineToRecord(string line,string Delim="#//#")
    {
        vector<string> vString = clsString::Split(line,Delim);

        stLoginRegisterRecord stLogin;
        stLogin.DateTime = vString[0];
        stLogin.LoginUser = vString[1];
        stLogin.Password = vString[2];
        stLogin.Permissions = stoi(vString[3]);

        return stLogin;
    }
    
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber,
        string UserName, string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, PhoneNumber)
        
        {
            _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkForDeleted()
    {
        return _MarkForDelete;
    }

    // Getters
    string UserName() const
    {
        return _UserName;
    }

    string Password() const
    {
        return _Password;
    }

    int Permissions() const
    {
        return _Permissions;
    }

    // Setters
    void SetUserName(const string &UserName)
    {
        _UserName = UserName;
    }

    void SetPassword(const string &Password)
    {
        _Password = Password;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        string line = "";
        if (MyFile.is_open())
        {
            while (getline(MyFile, line))
            {
                clsUser User = _ConvertLineToUserObject(line);
                if (User.UserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        string line = "";
        if (MyFile.is_open())
        {
            while (getline(MyFile, line))
            {
                clsUser User = _ConvertLineToUserObject(line);
                if (User.UserName() == UserName && User.Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
            break;
        }
        case enMode::UpdateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsUser::IsUserExsists(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::AddNewMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
    }

    static bool IsUserExsists(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U._MarkForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Required)
    {
        if (this->Permissions() == enPermissions::eAll)
            return true;

        if ((Required & this->Permissions()) == Required)
            return true;
        else
            return false;
    }

    void RegisterLogIn()
    {
        fstream MyFile;
        MyFile.open("LogFile.txt", ios::out | ios::app);

        string Line = "";
        if (MyFile.is_open())
        {
            Line = _ConvertDataToLine();
            MyFile << Line << endl;
        }

        MyFile.close();
    }

    static vector<stLoginRegisterRecord>  GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLogInfo;

        fstream MyFile;
        MyFile.open("LogFile.txt" ,ios::in);

        string Line = "";
        if(MyFile.is_open())
        {
            stLoginRegisterRecord stLogRegister;
            while (getline(MyFile,Line))
            {
                stLogRegister = _ConvertRegisterLineToRecord(Line);
                vLogInfo.push_back(stLogRegister);
            }
            MyFile.close();
        }

        return vLogInfo;
    }
};