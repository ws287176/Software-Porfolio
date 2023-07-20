#include <iostream>

#include <fstream> // Can add or read information from an existing file

#include <string> // include string library

#include <vector> // include vector library

#include <sstream>
// using namespace Patient;

using namespace std;

vector<vector<string>> diabetes_conditions = {
    {"Diabetes (Type 1)", "Insulin", "2 shots per day", "forever", "15.04"},
    {"Diabetes (Type 2)", "Insulin", "1 shot per day", "forever", "7.52"}};

vector<vector<string>> smoking_conditions = {
    {"Smoking (1 pack per month)", "Nicotine Tablets", "1 100mg pill a day",
     "6 months", "0.70"},
    {"Smoking (1 pack per week)", "Nicotine Tablets", "2 500mg pills a day",
     "12 months", "1.40"},
    {"Smoking (1 pack per day)", "Nicotine Patch", "One every 24 hours",
     "2 years", "3.64"}};

vector<vector<string>> cancer_conditions = {
    {"Lung Cancer (stage 1)", "Chemotherapy", "Once every 4 weeks", "6 months",
     "357.14"},
    {"Lung Cancer (stage 2)", "Chemotherapy", "Once every 2 weeks", "6 months",
     "714.29"},
    {"Lung Cancer (stage 3)", "Chemotherapy", "Once every week", "12 months",
     "1,428.57"},
    {"Lung Cancer(stage 4) ", "None", "None", "Nothing", "0"}};

struct User {
  string username;
  string first_name;
  string last_name;
  string password;
  string account_level;
};

// Function for reading account details
vector<User> read_account_details() {
  vector<User> users_vec;

  ifstream file("user details.csv");

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
        } else if (users.first_name.empty()) {
          users.first_name = token;
        } else if (users.last_name.empty()) {
          users.last_name = token;
        } else if (users.password.empty()) {
          users.password = token;
        } else if (users.account_level.empty()) {
          users.account_level = token;
        }
      }
      users_vec.push_back(users);
    }

    file.close();
  } else {
    cout << "Error opening file: "
         << "user details" << endl;
  }

  return users_vec;
}

void createAccount(string username, string first_name, string last_name,
                   string password, string account_level) {
  std::ofstream outfile;

  outfile.open("user details.csv",
               std::ios_base::app); // append instead of overwrite
  string string_for_file = username + "," + first_name + "," + last_name + "," +
                           password + "," + account_level + "\n";
  outfile << string_for_file;
  outfile.close();
}

struct Treatment {
  string patient_username; // Patient unique identifier
  string actual_condition; // Smoking, cancer or diabetes so that we can
                           // differentiate
  string ailment;          // condition the patient has
  string medication;       // Patient Medication
  string dosage;           // Patient treatment dosage
  string duration;         // How long (in months) of patient treatment
  string cost;             // Daily cost of patient treatment
};

// Function for reading patient treatment data from CSV file
vector<Treatment> read_treatment_data() {
  vector<Treatment> treatments_vec;

  ifstream file("treatments.csv");

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
        } else if (patients.actual_condition.empty()) {
          patients.actual_condition = token;
        } else if (patients.ailment.empty()) {
          patients.ailment = token;
        } else if (patients.medication.empty()) {
          patients.medication = token;
        } else if (patients.dosage.empty()) {
          patients.dosage = token;
        } else if (patients.duration.empty()) {
          patients.duration = token;
        } else if (patients.cost.empty()) {
          patients.cost = token;
        }
      }
      treatments_vec.push_back(patients);
    }

    file.close();
  } else {
    cout << "Error opening file: "
         << "treatments" << endl;
  }
  return treatments_vec;
}

void writeTreatmentsToFile(vector<Treatment> treatments) {
  string text = "";
  for (int i = 0; i < treatments.size(); i++) {
    text += treatments[i].patient_username;
    text += "," + treatments[i].actual_condition;
    text += "," + treatments[i].ailment;
    text += "," + treatments[i].medication;
    text += "," + treatments[i].dosage;
    text += "," + treatments[i].duration;
    text += "," + treatments[i].cost + "\n";
  }

  std::ofstream file("treatments.csv");
  file << text;
  file.close();
}

void writeAllUsersToFile(vector<User> users) {
  string text = "";
  for (int i = 0; i < users.size(); i++) {
    text += users[i].username;
    text += "," + users[i].first_name;
    text += "," + users[i].last_name;
    text += "," + users[i].password;
    text += "," + users[i].account_level + "\n";
  }

  std::ofstream file("user details.csv");
  file << text;
  file.close();
}

double calculateDailyCost(User user) {
  vector<Treatment> all_treatments = read_treatment_data();
  double daily_costs = 0;

  for (int i = 0; i < all_treatments.size(); i++) {
    if (all_treatments[i].patient_username == user.username) {
      daily_costs += stod(all_treatments[i].cost);
    }
  }

  return daily_costs;
}

string getTreatments(User user) {
  vector<Treatment> all_treatments = read_treatment_data();
  string text_for_user = "";

  for (int i = 0; i < all_treatments.size(); i++) {
    if (all_treatments[i].patient_username == user.username) {
      text_for_user += "You have: " + all_treatments[i].ailment +
                       " to treat that you are given " +
                       all_treatments[i].medication + " . Your dosage is " +
                       all_treatments[i].dosage + " You will have this for " +
                       all_treatments[i].duration + ".\n";
      break;
    }
  }

  return text_for_user;
}

void register_user() {

  string first_name;
  string last_name;
  string username;
  string password;

  cout << "Enter Patient First name: ";
  cin >> first_name;
  cout << "Enter Patient Last Name: ";
  cin >> last_name;
  bool found = true;
  vector<User> all_users = read_account_details();
  while (found) {
    found = false;
    cout << "Enter Patient username: ";
    cin >> username;
    for (int i = 0; i < all_users.size(); i++) {
      if (all_users[i].username == username) {
        found = true;
        cout << "Someone already has that username, please pick another\n";
      }
    }
  }
  cout << "Enter Patient password: ";
  cin >> password;
  createAccount(username, first_name, last_name, password, "1");
}

void patientMenu(User user) {
  bool loop = true;
  while (loop) {
    int c;

    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t           Welcome to the patient page            \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 to Get daily costs              |" << std::endl;

    cout << "\t Press 2 to get weekly costs             |" << std::endl;

    cout << "\t Press 3 to get monthly costs            |" << std::endl;

    cout << "\t Press 4 to get yearly costs             |" << std::endl;

    cout << "\t Press 5 to get treatments               |" << std::endl;

    // New number 6 change password
    // read user details using function || data type: vector<User>
    // use for statement to go through the vector then change that users
    // password to the new password
    // then save the vector of users to file using writeAllUsersToFile(the
    // vector name)

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

      cout << "Your treatments cost: " << calculateDailyCost(user) * 7
           << "per week";
      break;

    case 3:

      cout << "Your treatments cost: " << calculateDailyCost(user) * 28
           << "per month";
      break;

    case 4:

      cout << "Your treatments cost: " << calculateDailyCost(user) * 7 * 52
           << "per year";
      break;

    case 5:

      cout << getTreatments(user);
      break;

    case 6:

      loop = false;
      break;

    default:
      cout << "\t\t\t Please select from the options given above \n"
           << std::endl;
    }
  }
}

string listPatients() {
  vector<User> users = read_account_details();

  vector<User> patients;

  string all_patient_text = "Username, First Name, Last Name\n";

  for (int i = 0; i < users.size(); i++) {
    if (users[i].account_level == "1") {
      patients.push_back(users[i]);
    }
  }

  for (int i = 0; i < patients.size(); i++) {
    all_patient_text += patients[i].username + ", " + patients[i].first_name +
                        ", " + patients[i].last_name + "\n";
  }

  return all_patient_text;
}

string patientData(string username) {

  bool found = false;

  vector<User> users = read_account_details();

  vector<User> patients;

  for (int i = 0; i < users.size(); i++) {
    if (users[i].account_level == "1") {
      patients.push_back(users[i]);
    }
  }

  int user_index = 0;

  for (int i = 0; i < patients.size(); i++) {
    if (patients[i].username == username) {
      found = true;
      user_index = i;
      break;
    }
  }

  if (found == false) {
    return "Patient does not exist, please make sure you enter their username";
  }

  string patient_data = patients[user_index].username + ", " +
                        patients[user_index].first_name + ", " +
                        patients[user_index].last_name + "\n";

  patient_data += getTreatments(patients[user_index]);

  return patient_data;
}

void changeDiabetes(string username) {
  vector<Treatment> all_treatments = read_treatment_data();
  bool loop = true;
  int c;
  while (loop) {
    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t             Changing a Diabetes                 \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 if they do not have diabetes    |" << std::endl;

    cout << "\t Press 2 if they have diabetes type 1    |" << std::endl;

    cout << "\t Press 3 if they have diabetes type 2    |" << std::endl;

    cin >> c;

    switch (c) {
    case 1:
      loop = false;
      break;
    case 2:
      loop = false;
      break;
    case 3:
      loop = false;
      break;
    default:
      cout << "Please enter a correct value";
      break;
    }
  }
  bool found = false;
  for (int i = 0; i < all_treatments.size(); i++) {
    if (all_treatments[i].patient_username == username) {
      if (all_treatments[i].actual_condition == "Diabetes") {
        found = true;
        if (c - 2 >= 0) {
          all_treatments[i].ailment = diabetes_conditions[c - 2][0];
          all_treatments[i].medication = diabetes_conditions[c - 2][1];
          all_treatments[i].dosage = diabetes_conditions[c - 2][2];
          all_treatments[i].duration = diabetes_conditions[c - 2][3];
          all_treatments[i].cost = diabetes_conditions[c - 2][4];
        } else {
          all_treatments.erase(all_treatments.begin() + i);
        }
      }
    }
  }
  if (found == false && c - 2 >= 0) {
    Treatment new_condition;
    new_condition.patient_username = username;
    new_condition.actual_condition = "Diabetes";
    new_condition.ailment = diabetes_conditions[c - 2][0];
    new_condition.medication = diabetes_conditions[c - 2][1];
    new_condition.dosage = diabetes_conditions[c - 2][2];
    new_condition.duration = diabetes_conditions[c - 2][3];
    new_condition.cost = diabetes_conditions[c - 2][4];

    all_treatments.push_back(new_condition);
  }

  writeTreatmentsToFile(all_treatments);
}

void changeSmoking(string username) {
  vector<Treatment> all_treatments = read_treatment_data();
  bool loop = true;
  int c;
  while (loop) {
    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t             Changing a Smoking                 \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 if they do not smoke            |" << std::endl;

    cout << "\t Press 2 if they smoke 1 pack per month  |" << std::endl;

    cout << "\t Press 3 if they smoke 1 pack per week   |" << std::endl;

    cout << "\t Press 4 if they smoke 1 pack per day    |" << std::endl;

    cin >> c;

    switch (c) {
    case 1:
      loop = false;
      break;
    case 2:
      loop = false;
      break;
    case 3:
      loop = false;
      break;
    case 4:
      loop = false;
      break;
    default:
      cout << "Please enter a correct value";
      break;
    }
  }
  bool found = false;
  for (int i = 0; i < all_treatments.size(); i++) {
    if (all_treatments[i].patient_username == username) {
      if (all_treatments[i].actual_condition == "Smoking") {
        found = true;
        if (c - 2 >= 0) {
          all_treatments[i].ailment = smoking_conditions[c - 2][0];
          all_treatments[i].medication = smoking_conditions[c - 2][1];
          all_treatments[i].dosage = smoking_conditions[c - 2][2];
          all_treatments[i].duration = smoking_conditions[c - 2][3];
          all_treatments[i].cost = smoking_conditions[c - 2][4];
        } else {
          all_treatments.erase(all_treatments.begin() + i);
        }
      }
    }
  }
  if (found == false && c - 2 >= 0) {
    Treatment new_condition;
    new_condition.patient_username = username;
    new_condition.actual_condition = "Smoking";
    new_condition.ailment = smoking_conditions[c - 2][0];
    new_condition.medication = smoking_conditions[c - 2][1];
    new_condition.dosage = smoking_conditions[c - 2][2];
    new_condition.duration = smoking_conditions[c - 2][3];
    new_condition.cost = smoking_conditions[c - 2][4];

    all_treatments.push_back(new_condition);
  }

  writeTreatmentsToFile(all_treatments);
}

void changeCancer(string username) {
  vector<Treatment> all_treatments = read_treatment_data();
  bool loop = true;
  int c;
  while (loop) {
    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t             Changing Cancer diagnosis           \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 if they do not have cancer      |" << std::endl;

    cout << "\t Press 2 if they have Stage 1 Lung cancer|" << std::endl;

    cout << "\t Press 3 if they have Stage 2 Lung cancer|" << std::endl;

    cout << "\t Press 4 if they have Stage 3 Lung cancer|" << std::endl;

    cout << "\t Press 5 if they have Stage 4 Lung cancer|" << std::endl;

    cin >> c;

    switch (c) {
    case 1:
      loop = false;
      break;
    case 2:
      loop = false;
      break;
    case 3:
      loop = false;
      break;
    case 4:
      loop = false;
      break;
    case 5:
      loop = false;
      break;
    default:
      cout << "Please enter a correct value";
      break;
    }
  }
  bool found = false;
  for (int i = 0; i < all_treatments.size(); i++) {
    if (all_treatments[i].patient_username == username) {
      if (all_treatments[i].actual_condition == "Cancer") {
        found = true;
        if (c - 2 >= 0) {
          all_treatments[i].ailment = cancer_conditions[c - 2][0];
          all_treatments[i].medication = cancer_conditions[c - 2][1];
          all_treatments[i].dosage = cancer_conditions[c - 2][2];
          all_treatments[i].duration = cancer_conditions[c - 2][3];
          all_treatments[i].cost = cancer_conditions[c - 2][4];
        } else {
          all_treatments.erase(all_treatments.begin() + i);
        }
      }
    }
  }
  if (found == false && c - 2 >= 0) {
    Treatment new_condition;
    new_condition.patient_username = username;
    new_condition.actual_condition = "Cancer";
    new_condition.ailment = cancer_conditions[c - 2][0];
    new_condition.medication = cancer_conditions[c - 2][1];
    new_condition.dosage = cancer_conditions[c - 2][2];
    new_condition.duration = cancer_conditions[c - 2][3];
    new_condition.cost = cancer_conditions[c - 2][4];

    all_treatments.push_back(new_condition);
  }

  writeTreatmentsToFile(all_treatments);
}

void changePrescription(string username) {
  bool loop = true;
  while (loop) {
    int c;

    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t             Changing a Presription              \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 to change a diabetes condition  |" << std::endl;

    cout << "\t Press 2 to change a smoking condition   |" << std::endl;

    cout << "\t Press 3 to chnage a cancer condition    |" << std::endl;

    cout << "\t Press 4 to exit                         |" << std::endl;

    cin >> c;

    switch (c) {
    case 1:

      changeDiabetes(username);
      loop = false;
      break;

    case 2:

      changeSmoking(username);
      loop = false;
      break;

    case 3:

      changeCancer(username);
      loop = false;
      break;

    case 4:

      loop = false;
      break;

    default:

      cout << "Please choose a valid option";
      break;
    }
  }
}

void createNewDoctor() {
  string username;
  string first_name;
  string last_name;
  string password;

  cout << "Please enter the username for the account ";
  cin >> username;
  cout << "\nPlease enter their first name: ";
  cin >> first_name;
  cout << "\nPlease enter their last name: ";
  cin >> last_name;
  cout << "Please enter a generic password for them ";
  cin >> password;

  createAccount(username, first_name, last_name, password, "2");
}

void doctorMenu(User user) {
  bool loop = true;
  while (loop) {
    int c;

    cout << "\t\t\t_________________________________________________\n\n\n";

    cout << "\t\t\t           Welcome to the doctor page            \n\n\n";

    cout << "\t\t\t______________________MENU_______________________\n\n\n";

    cout << "                                                       \n\n";

    cout << "\t Press 1 to Get list of patients         |" << std::endl;

    cout << "\t Press 2 to get patient data             |" << std::endl;

    cout << "\t Press 3 to change patients treatments   |" << std::endl;

    cout << "\t Press 4 to create new Doctor            |" << std::endl;

    cout << "\t Press 5 to exit                         |" << std::endl;

    cout << "\n\t\t\t Please enter your choice : ";

    cin >> c;

    string username;

    cout << std::endl;

    switch (c)

    {

    case 1:

      cout << listPatients();
      break;

    case 2:

      cout << "What is the username of the patient: ";
      std::cin >> username;
      cout << patientData(username);
      break;

    case 3:

      cout << "What is the username of the patient: ";
      std::cin >> username;
      changePrescription(username);
      break;

    case 4:

      createNewDoctor();
      break;

    case 5:

      loop = false;
      break;

    default:
      cout << "\t\t\t Please select from the options given above \n"
           << std::endl;
    }
  }
}

void userMenu(User user) {
  int account_level = stoi(user.account_level);

  switch (account_level) {
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

void login(vector<User> users) {

  string userName = "";
  string userPassword = "";
  int loginAttempt = 0;

  while (loginAttempt <
         5) { // Showing that there must be only 5 login attempts before getting
              // locked out and having to try again later.

    std::cout << (" Please enter your username: ");
    std::cin >> userName;
    cout << (" Please enter your password: ");
    cin >> userPassword;

    bool found = false;

    for (int i = 0; i < users.size(); i++) {

      if (userName == users[i].username && found == false) {
        found = true;
        if (userPassword == users[i].password) {
          cout << "Welcome " + userName; // Says welcome if the correct
                                         // information is inputted and then
                                         // brings up the menu for that person
          loginAttempt = 5;
          userMenu(users[i]);
          break;
        } else {
          cout << "Invalid login attempt. Please try again.\n"
               << '\n'; // If you enter the wrong login name or password it will
                        // display an error message saying "invalid login
                        // attempt. please try again.
          loginAttempt++;
        }
      }
    }
    if (found == false) {
      cout << "Username not found. Please try again.\n";
      loginAttempt++;
    }
  }
  if (loginAttempt == 5) {
    cout << "Too many login attempts! Try again later!.";
  }
}

int main() {

  bool loop = true;

  while (loop) {
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

      // registration();
      register_user();
      break;

    case 3:

      // forgot();
      cout << "Forgot password";
      break;

    case 4:

      cout << "\t\t\t Thankyou! \n\n";
      loop = false;
      break;

    default:
      cout << "\t\t\t Please select from the options given above \n"
           << std::endl;
    }
  }
}