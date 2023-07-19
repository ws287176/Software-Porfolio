#include <iostream> 

#include <fstream> // Can add or read information from an existing file

#include <string> // include string library 

#include <vector> // include vector library 

#include <sstream>
//using namespace Patient;


using namespace std;



struct User {
    string username;
    string first_name;
    string last_name;
    string password;
    string account_level;
};

//Function for reading account details
vector<User> read_account_details() {
    vector<User> users_vec;

    ifstream file("\\\\svr-kn-file01\\homedrives$\\WS287176\\My Documents\\UCW Year 1\\Software\\Resit\\user details.csv");

    if (file) {
        string line;

        while (getline(file, line)) {
            User users;

            size_t pos = 0;
            string token;

            // Read patient treatment data from CSV file
            stringstream sep(line);
            while (getline(sep, token, ',')) {
                if (users.username.empty()) {
                    users.username = token;
                }
                else if (users.first_name.empty()) {
                    users.first_name = token;
                }
                else if (users.last_name.empty()) {
                    users.last_name = token;
                }
                else if (users.password.empty()) {
                    users.password = token;
                }
                else if (users.account_level.empty()) {
                    users.account_level = token;
                }
            }
            users_vec.push_back(users);
        }

        file.close();
    }
    else {
        cout << "Error opening file: " << "user details" << endl;
    }

    return users_vec;
}

struct Treatment {
    string patient_username; // Patient unique identifier
    string ailment; // condition the patient has
    string medication; // Patient Medication
    string dosage; // Patient treatment dosage
    string duration; // How long (in months) of patient treatment
    string cost; // Daily cost of patient treatment
};

// Function for reading patient treatment data from CSV file
vector<Treatment> read_treatment_data() {
    vector<Treatment> treatments_vec;

    ifstream file("\\\\svr-kn-file01\\homedrives$\\WS287176\\My Documents\\UCW Year 1\\Software\\Resit\\treatments.csv");

    if (file) {
        string line;

        while (getline(file, line)) {
            Treatment patients;

            size_t pos = 0;
            string token;

            // Read patient treatment data from CSV file
            stringstream sep(line);
            while (getline(sep, token, ',')) {
                if (patients.patient_username.empty()) {
                    patients.patient_username = token;
                }
                else if (patients.ailment.empty()) {
                    patients.ailment = token;
                }
                else if (patients.medication.empty()) {
                    patients.medication = token;
                }
                else if (patients.dosage.empty()) {
                    patients.dosage = token;
                }
                else if (patients.duration.empty()) {
                    patients.duration = token;
                }
                else if (patients.cost.empty()) {
                    patients.cost = token;
                }
            }
            treatments_vec.push_back(patients);
        }

        file.close();
    }
    else {
        cout << "Error opening file: " << "treatments" << endl;
    }

    return treatments_vec;
}

void writeTreatmentsToFile(vector<Treatment> treatments)
{
    string text = "";
    for (int i = 0; i < treatments.size(); i++)
    {
        text += treatments[i].patient_username;
        text += "," + treatments[i].ailment;
        text += "," + treatments[i].medication;
        text += "," + treatments[i].dosage;
        text += "," + treatments[i].duration;
        text += "," + treatments[i].cost + std::endl;
    }

    std::ofstream file(file_name);
    file << text;
    file.close();
}

double calculateDailyCost(User user) {
    vector<Treatment> all_treatments = read_treatment_data();
    double daily_costs = 0;

    for (int i = 0; i < all_treatments.size(); i++)
    {
        if (all_treatments[i].patient_username == user.username)
        {
            daily_costs += stod(all_treatments[i].cost);
        }
    }

    return daily_costs;
}

string getTreatments(User user)
{
    vector<Treatment> all_treatments = read_treatment_data();
    string text_for_user = "";

    for (int i = 0; i < all_treatments.size(); i++)
    {
        if (all_treatments[i].patient_username == user.username)
        {
            text_for_user += "You have: " + all_treatments[i].ailment + " to treat that you are given "
                + all_treatments[i].medication + " . Your dosage is " + all_treatments[i].dosage + " You will have this for " + all_treatments[i].duration + ".\n";
        }
    }

    return text_for_user;
}

Treatment register_user() {

    Treatment pUser;
    string first_name;
    string last_name;
    string date_of_birth;

    cout << "Enter Patient First name";
    cin >> first_name;
    cout << "Enter Patient Last Name";
    cin >> last_name;
    cout << "Enter Patient date of birth";
    cin >> date_of_birth;
    return pUser;
}

void patientMenu(User user)
{
    bool loop = true;
    while (loop)
    {
        int c;

        cout << "\t\t\t_________________________________________________\n\n\n";

        cout << "\t\t\t           Welcome to the patient page            \n\n\n";

        cout << "\t\t\t______________________MENU_______________________\n\n\n";



        cout << "                                                       \n\n";

        cout << "\t Press 1 to Get daily costs              |" << std::endl;

        cout << "\t Press 2 to get weekly costs            |" << std::endl;

        cout << "\t Press 3 to get monthly costs            |" << std::endl;

        cout << "\t Press 4 to get yearly costs             |" << std::endl;

        cout << "\t Press 5 to get treatments               |" << std::endl;

        cout << "\t Press 6 to EXIT                         |" << std::endl;


        cout << "\n\t\t\t Please enter your choice : ";

        cin >> c;

        cout << std::endl;

        switch (c)

        {

        case 1:

            cout << "Your treatments cost: " << calculateDailyCost(user) << "per day";
            break;

        case 2:

            cout << "Your treatments cost: " << calculateDailyCost(user) * 7 << "per week";
            break;

        case 3:

            cout << "Your treatments cost: " << calculateDailyCost(user) * 28 << "per month";
            break;

        case 4:

            cout << "Your treatments cost: " << calculateDailyCost(user) * 7 * 52 << "per year";
            break;

        case 5:

            cout << getTreatments(user);
            break;

        case 6:

            loop = false;
            break;

        default:
            cout << "\t\t\t Please select from the options given above \n" << std::endl;
        }
    }
}

void doctorMenu(User user)
{
    cout << "Hopefully back to main";
}

void userMenu(User user)
{
    int account_level = stoi(user.account_level);

    switch (account_level)
    {
    case 1:
        patientMenu(user);
        break;
    case 2:
        doctorMenu(user);
        break;
    default:
        cout << "Sorry there is an error with your account please talk to an admin";
        break;
    }
}

void login(vector <User> users)
{

    string userName = "";
    string userPassword = "";
    int loginAttempt = 0;

    while (loginAttempt < 5) { // Showing that there must be only 5 login attempts before getting locked out and having to try again later. 

        std::cout << (" Please enter your username: ");
        std::cin >> userName;
        cout << (" Please enter your password: ");
        cin >> userPassword;

        for (int i = 0; i < users.size(); i++) {

            if (userName == users[i].username && userPassword == users[i].password)
            {
                cout << "Welcome " + userName;              // Says welcome if the correct information is inputted and then brings up the menu for that person  
                userMenu(users[i]);
                break;
            }
            else {
                cout << "Invalid login attempt. Please try again.\n" << '\n';  // If you enter the wrong login name or password it will display an error message saying "invalid login attempt. please try again. 
                loginAttempt++;
            }
        }
    }
    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! Try again later!.";
    }
}

int main() {

    bool loop = true;

    while (loop)
    {
        int c;

        cout << "\t\t\t_________________________________________________\n\n\n";

        cout << "\t\t\t            Welcome to the login page            \n\n\n";

        cout << "\t\t\t______________________MENU_______________________\n\n\n";



        cout << "                                                       \n\n";

        cout << "\t Press 1 to LOGIN                       |" << std::endl;

        cout << "\t Press 2 to REGISTER                    |" << std::endl;

        cout << "\t Press 3 to if you forgot your PASSWORD |" << std::endl;

        cout << "\t Press 4 to EXIT                        |" << std::endl;


        cout << "\n\t\t\t Please enter your choice : ";

        cin >> c;

        cout << std::endl;

        switch (c)

        {

        case 1:

            login(read_account_details());
            break;

        case 2:

            //registration();
            register_user();
            break;

        case 3:

            //forgot();
            cout << "Forgot password";
            break;

        case 4:

            cout << "\t\t\t Thankyou! \n\n";
            loop = false;
            break;

        default:
            cout << "\t\t\t Please select from the options given above \n" << std::endl;
        }
    }
}