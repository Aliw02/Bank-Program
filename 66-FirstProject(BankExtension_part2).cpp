// 66-FirstProject(BankExtension_part2).cpp : This file contains the 'main' function. Program execution begins and ends there.






#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";


// -------------- Start Of The Program Functions -------------- // 

enum enManageUsersMenuOption
{

   eListUser    = 1,
   eAddUser     = 2,
   eDeleteUser  = 3,
   eUpdateUser  = 4,
   eFindUser    = 5,
   eMainMenu    = 6,

};

enum enTransactionsMenuOptions 
{

    eDeposit = 1,
    eWithdraw = 2, 
    eShowTotalBalance = 3,
    eShowMainMenu = 4 

};

enum enMainMenuOptions 
{ 
    
    eListClients = 1,
    eAddNewClient = 2, 
    eDeleteClient = 3, 
    eUpdateClient = 4, 
    eFindClient = 5, 
    eShowTransactionsMenu = 6, 
    eManageUsers = 7, 
    eLogout = 8 

};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

struct stUsers
{

    string UserName = "";
    string Password = "";
    short  FullPermissions = 0;
    short  showClientsListPermission = 0;
    short  addClientPermission = 0;
    short  deleteClientPermission = 0;
    short  updateClientPermission = 0;
    short  findClientPermission = 0;
    short  transactionPermission = 0;
    short  manageUsersPermission = 0;
    bool   MarkForDelete = false;

};

void ShowMainMenu(stUsers);             // Declaration for the Main Menu Function        ---> (Definition) At Main Functions Part
void ShowTransactionsMenu(stUsers);    // Declaration for the Transactions Menu Function ---> (Definition) At Main Functions Part
void ShowManageUsersMenu(stUsers);    // Declaration for the Manage Menu Function        ---> (Definition) At Main Functions Part
void Login();                        // Declaration for the Login Function               ---> (Definition) At Main Functions Part

void PrintScreenName(string ScrName)
{

    cout << "\n-----------------------------------\n";
    cout << "\t" << ScrName << " Screen";
    cout << "\n-----------------------------------\n";

}


// -------------- Start Of The Client Part -------------- // 

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {

        sWord = S1.substr(0, pos); // store the word 

        if (sWord != "")
        {

            vString.push_back(sWord);

        }

        S1.erase(0, pos + Delim.length());  /* erase() until position and move to next word. */
    }

    if (S1 != "")
    {

        vString.push_back(S1); // it adds last word of the string.
    
    }

    return vString;

}

stClient ConvertLineToRecord(string Line, string Separator = "#//#")
{

    stClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Separator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(stClient Client, string Separator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);

        }

        MyFile.close();

    }

    return false;


}

stClient ReadNewClient()
{
    stClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract all the whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {

        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);

    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <stClient> LoadClientsDataFromFile(string FileName)
{

    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowTotalBalances()
{

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else

        for (stClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(stClient Client)
{

    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPin Code        : " << Client.PinCode;
    cout << "\nName            : " << Client.Name;
    cout << "\nPhone           : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{

    for (stClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }

    return false;

}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    for (stClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{

    stClient Client;
    Client = ReadNewClient();
    
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";

            return true;

        }

    }
    
    else
    {

        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
       
        return false;

    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient& C : vClients)
            {

                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);

                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";

            return true;
        
        }

    }

    else
    {

        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        
        return false;

    }

}

bool EditBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{

    char Answer = 'n';

    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient& C : vClients)
        {

            if (C.AccountNumber == AccountNumber)
            {

                C.AccountBalance += Amount;

                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;

            }

        }

        return false;
    }

}

string ReadClientAccountNumber()
{

    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;

}

// -------------- End Of The Client Part -------------- // 



// -------------- Start Of The Users Part -------------- // 

stUsers ConvertLineToRecordOfUsers(string Line, string Separator = "#//#")
{

    stUsers User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Separator);

    User.UserName = vUserData[0];
    User.Password = vUserData[1];
    User.FullPermissions = stoi(vUserData[2]);

    return User;

}

string ConvertRecordToLineOfUsers(stUsers User, string Separator = "#//#")
{

    string stUserRecord = "";

    stUserRecord += User.UserName + Separator;
    stUserRecord += User.Password + Separator;
    stUserRecord += to_string(User.FullPermissions);

    return stUserRecord;

}

vector <stUsers> LoadUsersDataFromFile(string FileName)
{

    vector <stUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUsers User;

        while (getline(MyFile, Line))
        {

            User = ConvertLineToRecordOfUsers(Line);

            vUsers.push_back(User);

        }

        MyFile.close();

    }

    return vUsers;

}

string ReadUserInfo(string Message)
{

    string Info = "";

    cout << Message;
    getline(cin >> ws, Info);

    return Info;

}

bool UserExistsByUsername(string Username, string FileName)
{

    vector <stUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUsers User;

        while (getline(MyFile, Line))
        {

            User = ConvertLineToRecordOfUsers(Line);

            if (User.UserName == Username)
            {

                MyFile.close();
                return true;

            }

            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return false;


}

bool FindUsersByUsernameAndPassword(vector <stUsers> vUsers, string Username, string Pass, stUsers& User)
{

    for (stUsers& U : vUsers)
    {

        if (U.UserName == Username && U.Password == Pass)
        {
            User = U;
            return true;

        }

    }

    return false;

}

bool FindUserByUsername(string Username, vector <stUsers> vUsers, stUsers& User)
{

    for (stUsers U : vUsers)
    {

        if (U.UserName == Username)
        {
            User = U;
            return true;
        }

    }

    return false;

}

void PrintUserRecordLine(stUsers User)
{


    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.FullPermissions;


}

stUsers PermissionsAllowed(stUsers& User)
{

    cout << "Do you Want To Give Access To: \n\n";
    

    char ShowClientListPermission = 'Y';
    cout << "Show Client List? Y/N? ";
    cin >> ShowClientListPermission;

    if (ShowClientListPermission == 'Y' || ShowClientListPermission == 'y')
    {

        User.showClientsListPermission = 1;

    }


    char AddNewClientPermission = 'Y';
    cout << "Add New Client? Y/N? ";
    cin >> AddNewClientPermission;

    if (AddNewClientPermission == 'Y' || AddNewClientPermission == 'y')
    {

        User.addClientPermission = 2;

    }



    char DeleteClientPermission = 'Y';
    cout << "Delete Client? Y/N? ";
    cin >> DeleteClientPermission;

    if (DeleteClientPermission == 'Y' || DeleteClientPermission == 'y')
    {

        User.deleteClientPermission = 4;

    }



    char UpdateClientInfoPermission = 'Y';

    cout << "Update Client Info? Y/N? ";
    cin >> UpdateClientInfoPermission;


    if (UpdateClientInfoPermission == 'Y' || UpdateClientInfoPermission == 'y')
    {

        User.updateClientPermission = 8;

    }



    char FindClientPermission = 'Y';

    cout << "Find Client? Y/N? ";
    cin >> FindClientPermission;


    if (FindClientPermission == 'Y' || FindClientPermission == 'y')
    {

        User.findClientPermission = 16;

    }
    

    char TransactionPermission = 'Y';

    cout << "Transaction? Y/N? ";
    cin >> TransactionPermission;


    if (TransactionPermission == 'Y' || TransactionPermission == 'y')
    {

        User.transactionPermission = 32;

    }
    

    char ManageUsersPermission = 'Y';

    cout << "Manage Users? Y/N? ";
    cin >> ManageUsersPermission;


    if (ManageUsersPermission == 'Y' || ManageUsersPermission == 'y')
    {

        User.manageUsersPermission = 64;

    }


    int result = (User.showClientsListPermission | User.addClientPermission | User.deleteClientPermission 
                 | User.updateClientPermission | User.findClientPermission | User.transactionPermission | User.manageUsersPermission);

    User.FullPermissions = result;

    return User;

}

stUsers ReadNewUser()
{

    stUsers User;
    char fullPermission = 'Y';

    cout << "Enter UserName? ";

    // Usage of std::ws will extract all the whitespace character
    getline(cin >> ws, User.UserName);

    while (UserExistsByUsername(User.UserName, UsersFileName))
    {

        cout << "\n\nUser with [" << User.UserName << "] already exists, Enter another User Name? ";
        getline(cin >> ws, User.UserName);

    }


    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);


    cout << "\nDo You want to give the user Full Permission on the system: Y/N? ";
    cin >> fullPermission;

    if (fullPermission == 'Y' || fullPermission == 'y')
    {

        User.FullPermissions = -1;
        

    }

    else
    {

        User = PermissionsAllowed(User);

    }

    return User;

}

void AddDataLineToFileOfUsers(string FileName, string  stDataLine)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewUser()
{

    stUsers User;

    User = ReadNewUser();

    AddDataLineToFileOfUsers(UsersFileName, ConvertRecordToLineOfUsers(User));

}

void AddNewUsers()
{

    char AddMore = 'Y';

    do
    {

        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool MarkUserForDeleteByUserName(string Username, vector <stUsers>& vUsers)
{

    for (stUsers & User : vUsers)
    {

        if (User.UserName == Username)
        {
            User.MarkForDelete = true;

            return true;
        
        }

    }

    return false;

}

vector <stUsers> SaveUsersDataToFile(string FileName, vector <stUsers> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stUsers User : vUsers)
        {

            if (User.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLineOfUsers(User);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vUsers;

}

void PrintUserCard(stUsers User)
{

    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername    : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermission  : " << User.FullPermissions;
    cout << "\n-----------------------------------\n";

}

bool DeleteUserByUsername(string Username, vector <stUsers>& vUsers)
{

    stUsers User;
    char Answer = 'n';

    if (Username == "Admin")
    {

        cout << "\n\nYou Can't Delete this User. \n\n";
        return true;

    }

    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkUserForDeleteByUserName(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            //Refresh User 
            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.";

            return true;

        }

        else
        {

            cout << "\n\nUser not Deleted\n\n";

        }

    }

    else
    {

        cout << "\nUser with Username (" << Username << ") is Not Found!";

        return false;

    }

}

stUsers ChangeUserRecord(string Username)
{
    stUsers User;

    User.UserName = Username;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    cout << "Enter Permission? ";
    cin >> User.FullPermissions;

    return User; 

}

bool UpdateUserByUsername(string Username, vector <stUsers>& vUsers)
{

    stUsers User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stUsers& U : vUsers)
            {

                if (U.UserName == Username)
                {

                    U = ChangeUserRecord(Username);

                    break;
                }

            }

            SaveUsersDataToFile(UsersFileName, vUsers);

            cout << "\n\nUser Updated Successfully.";

            return true;

        }

        else
        {

            cout << "\nUser with Username (" << Username << ") is Not Updated!";
            return true;

        }

    }

    else
    {

        cout << "\nUser with Username (" << Username << ") is Not Found!";

        return false;

    }

}

stUsers CheckThePermissions(stUsers& User)
{

    short fullPermission = User.FullPermissions;

    if (User.FullPermissions == 127 || User.FullPermissions == -1)
    {

        User.FullPermissions = -1;
        return User;

    }

    if (User.FullPermissions % 2 != 0)
    {

        fullPermission--;
        User.showClientsListPermission = 1;

    }

    if (fullPermission >= 64 && fullPermission <= 126)
    {

        fullPermission -= 64;
        User.manageUsersPermission = 1;

    }

    if (fullPermission >= 32)
    {

        fullPermission -= 32;
        User.transactionPermission = 1;

    }

    if (fullPermission >= 16)
    {

        fullPermission -= 16;
        User.findClientPermission = 1;

    }

    if (fullPermission >= 8)
    {

        fullPermission -= 8;
        User.updateClientPermission = 1;

    }

    if (fullPermission >= 4)
    {

        fullPermission -= 4;
        User.deleteClientPermission = 1;

    }

    if (fullPermission >= 2)
    {

        fullPermission -= 2;
        User.addClientPermission = 1;

    }

    if (fullPermission == 0)
    {

        return User;

    }

}


// -------------- End Of The Users Part -------------- // 



// -------------- End Of The Program Functions -------------- // 



// -------------- Start Of The Main Screen Functions -------------- // 

void ShowAllClientsScreen()
{


    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else

        for (stClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowAddNewClientsScreen()
{

    PrintScreenName("Add Client");

    AddNewClients();

}

void ShowDeleteClientScreen()
{

    PrintScreenName("Delete Client");

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{

    PrintScreenName("Update Client Info");

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowFindClientScreen()
{

    PrintScreenName("Find Client");

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;

    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);

    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

// -------------- Start Of The Extension 1 Functions -------------- //

void ShowDepositScreen()
{

    PrintScreenName("Deposit Client");


    stClient Client;

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";

        AccountNumber = ReadClientAccountNumber();

    }


    PrintClientCard(Client);

    double Amount = 0;

    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    EditBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{

    PrintScreenName("Withdraw Client");

    stClient Client;

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";

        AccountNumber = ReadClientAccountNumber();

    }

    PrintClientCard(Client);

    double Amount = 0;

    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {

        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        
        cout << "Please enter another amount? ";
        cin >> Amount;
    
    }

    EditBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

// -------------- End Of The Extension 1 Functions -------------- //

// -------------- Start Of The Extension 2 Functions -------------- //

void ShowUsersList()
{

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "FullPermissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";

    else

        for (stUsers User : vUsers)
        {

            PrintUserRecordLine(User);
            cout << endl;

        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowAddNewUserScreen()
{

    PrintScreenName("Add New User");

    AddNewUsers();

}

void ShowDeleteUserScreen()
{

    PrintScreenName("Delete User");

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUserInfo("Please, Enter UserName: ");
    DeleteUserByUsername(Username, vUsers);

}

void ShowUpdateUserScreen()
{

    PrintScreenName("Update User Info");

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUserInfo("Please, Enter UserName: ");
    UpdateUserByUsername(Username, vUsers);

}

void ShowFindUserScreen()
{

    PrintScreenName("Find User");

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUsers User;

    string Username = ReadUserInfo("Please, Enter UserName: ");


    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserCard(User);

    }

    else
    {
    
        cout << "\nUser with Username [" << Username << "] is not found!";
    
    }

}

void ShowAccessDeniedScreen()
{

    system("cls");
    cout << "\n\nAccess Denied, You haven't Permission :(\n\n";

}

// -------------- End Of The Extension 2 Functions -------------- //




// -------------- End Of The Main Screen Functions -------------- // 



// -------------- Start Of Manage Users Menu Functions -------------- // 

void GoBackToManageUsersMenu(stUsers User)
{

    cout << "\n\nPress any key to go back to Manage Users Menu...";

    system("pause>0");
    ShowManageUsersMenu(User);

}

short ReadManageUsersMenuOption()
{

    short Choice = 0;

    do
    {

        cout << "Choose what do you want to do? [1 to 6]? ";

        cin >> Choice;

    } while (Choice <= 0 || Choice >= 7);

    return Choice;

}

void PerformManageUsersMenuOption(enManageUsersMenuOption ManageUsersMenueOption, stUsers User)
{

    switch (ManageUsersMenueOption)
    {

    case enManageUsersMenuOption::eListUser:
    {

        system("cls");
        ShowUsersList();
        GoBackToManageUsersMenu(User);
        break;

    }

    case enManageUsersMenuOption::eAddUser:
    {

        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUsersMenu(User);
        break;

    }

    case enManageUsersMenuOption::eDeleteUser:
    {

        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenu(User);
        break;

    }

    case enManageUsersMenuOption::eUpdateUser:
    {

        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenu(User);
        break;

    }

    case enManageUsersMenuOption::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenu(User);
        break;

    }

    case enManageUsersMenuOption::eMainMenu:
    {

        system("cls");
        ShowMainMenu(User);
        break;

    }

    }

}

// -------------- End Of Manage Users Menu Functions -------------- // 


// -------------- Start Of Transactions Menu Functions -------------- // 

void GoBackToTransactionsMenu(stUsers User)
{

    cout << "\n\nPress any key to go back to Transactions Menu...";

    system("pause>0");
    ShowTransactionsMenu(User);

}

short ReadTransactionsMenuOption()
{    
    
    short Choice = 0;

    do
    {

        cout << "Choose what do you want to do? [1 to 4]? ";

        cin >> Choice;

    } while (Choice <= 0 || Choice >= 5);

    return Choice;

}

void PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionMenuOption, stUsers User)
{

    switch (TransactionMenuOption)
    {

        case enTransactionsMenuOptions::eDeposit:
        {

            system("cls");

            ShowDepositScreen();
            GoBackToTransactionsMenu(User);
           
            break;

        }

        case enTransactionsMenuOptions::eWithdraw:
        {

            system("cls");
            ShowWithDrawScreen();
            GoBackToTransactionsMenu(User);
            break;

        }

        case enTransactionsMenuOptions::eShowTotalBalance:
        {

            system("cls");
            ShowTotalBalancesScreen();
            GoBackToTransactionsMenu(User);
            break;

        }

        case enTransactionsMenuOptions::eShowMainMenu:
        {

            ShowMainMenu(User);

        }

    }

}

// -------------- End Of Transactions Menu Functions -------------- // 


// -------------- Start Of Main Menu Functions -------------- // 

void GoBackToMainMenu(stUsers User)
{

    cout << "\n\nPress any key to go back to Main Menu...";

    system("pause>0");
    ShowMainMenu(User);

}

short ReadMainMenuOption()
{

    short Choice = 0;

    do 
    {
      
        cout << "Choose what do you want to do? [1 to 8]? ";

        cin >> Choice;

    } while (Choice <= 0 || Choice >= 9);

    return Choice;

}

void PerformMainMenuOption(enMainMenuOptions MainMenuOption, stUsers User)
{

    User = CheckThePermissions(User);

    switch (MainMenuOption)
    {

    case enMainMenuOptions::eListClients:
    {
        if (User.FullPermissions == -1 || User.showClientsListPermission == 1)
        {

            system("cls");

            ShowAllClientsScreen();
            GoBackToMainMenu(User);
            break;
        }

        else
        {
            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;

        }

    }

    case enMainMenuOptions::eAddNewClient:
    {
        if (User.FullPermissions == -1 || User.addClientPermission == 1)
        {
            system("cls");

            ShowAddNewClientsScreen();
            GoBackToMainMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;
        }

    }

    case enMainMenuOptions::eDeleteClient:
    {

        if (User.FullPermissions == -1 || User.deleteClientPermission == 1)
        {
            system("cls");

            ShowDeleteClientScreen();
            GoBackToMainMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;
        }

    }

    case enMainMenuOptions::eUpdateClient:
    {
        if (User.FullPermissions == -1 || User.updateClientPermission == 1)
        {
            system("cls");

            ShowUpdateClientScreen();
            GoBackToMainMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;

        }

    }

    case enMainMenuOptions::eFindClient:
    {
        if (User.FullPermissions == -1 || User.findClientPermission == 1)
        {
            system("cls");

            ShowFindClientScreen();
            GoBackToMainMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User); 
            break;

        }
    }

    case enMainMenuOptions::eShowTransactionsMenu:
    {
        if (User.FullPermissions == -1 || User.transactionPermission == 1)
        {
            system("cls");

            ShowTransactionsMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;
        }

    }

    case enMainMenuOptions::eManageUsers:
    {

        if (User.FullPermissions == -1 || User.manageUsersPermission == 1)
        {
            system("cls");

            ShowManageUsersMenu(User);
            break;

        }

        else
        {

            ShowAccessDeniedScreen();
            GoBackToMainMenu(User);
            break;

        }

    }

    case enMainMenuOptions::eLogout:
    {

        system("cls");
        Login();

        break;

    }

    }

}

// -------------- End Of Main Menu Functions -------------- // 




// -------------- Start Of The Main Functions -------------- // 

void ShowManageUsersMenu(stUsers User)
{

    system("cls");

    cout << "===========================================\n";
    cout << "\t\Manage User Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Users List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";

    PerformManageUsersMenuOption((enManageUsersMenuOption)ReadManageUsersMenuOption(), User);

}

void ShowTransactionsMenu(stUsers User)
{

    system("cls");

    cout << "===========================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "===========================================\n";
    
    PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption(), User);

}

void ShowMainMenu(stUsers User)
{
    system("cls");

    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption(), User);

}

void Login()
{

    vector <stUsers> vUsers ;
    stUsers User;

    string Username ;
    string Pass ;
    bool LoginFaild = false;


    do
    {

        system("cls");

        PrintScreenName("Login");

        if (LoginFaild)
        {

            cout << "\nInvalid Username/Password!\n\n";

        }

        vUsers = LoadUsersDataFromFile(UsersFileName);

        Username = ReadUserInfo("Please, Enter UserName: ");
        Pass = ReadUserInfo("Please, Enter Password: ");
        
        LoginFaild = !FindUsersByUsernameAndPassword(vUsers, Username, Pass, User);



    } while (LoginFaild);

    ShowMainMenu(User);

}

// -------------- End Of The Main Functions -------------- // 

int main()
{

    Login();

    return 0;

}