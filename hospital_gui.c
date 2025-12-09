#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
using namespace std;

#define RED     "\033[31m"
#define ORANGE  "\033[33m"
#define YELLOW  "\033[93m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

struct Patient {
    string token;
    string name;
    string department;
    string severityText;
    string severityColor;
    int severity;
    time_t arrival;
};


struct Compare {
    bool operator()(Patient const &p1, Patient const &p2) {
        if(p1.severity == p2.severity)
            return p1.arrival > p2.arrival;
        return p1.severity > p2.severity; // 1 highest priority
    }
};

priority_queue<Patient, vector<Patient>, Compare> pq;
int tokenNo = 1000;


string getTime(time_t t) {
    char buf[30];
    strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));
    return string(buf);
}


void setSeverity(Patient &p) {
    switch(p.severity) {
        case 1: 
            p.severityText = "Immediate Attention";
            p.severityColor = RED;
            break;
        case 2: 
            p.severityText = "Very Urgent";
            p.severityColor = ORANGE;
            break;
        case 3: 
            p.severityText = "Urgent";
            p.severityColor = YELLOW;
            break;
        case 4: 
            p.severityText = "Less Urgent";
            p.severityColor = GREEN;
            break;
        case 5:
            p.severityText = "Non-Urgent";
            p.severityColor = BLUE;
            break;
        default:
            p.severityText = "Unknown";
            p.severityColor = RESET;
    }
}


string getDepartment(int choice) {
    switch(choice) {
        case 1: return "Cardiology";
        case 2: return "Neurology";
        case 3: return "Orthopedics";
        case 4: return "Emergency";
        case 5: return "Pediatrics";
        case 6: return "Trauma";
        case 7: return "ICU";
        case 8: return "Others";
        default: return "Others";
    }
}


void addPatient() {
    Patient p;
    cout << "\nEnter Patient Name: ";
    cin >> ws;
    getline(cin, p.name);

    cout << "\nSelect Department:\n";
    cout << "1. Cardiology\n";
    cout << "2. Neurology\n";
    cout << "3. Orthopedics\n";
    cout << "4. Emergency\n";
    cout << "5. Pediatrics\n";
    cout << "6. Trauma Care\n";
    cout << "7. ICU\n";
    cout << "8. Others\n";
    cout << "Enter choice: ";

    int d;
    cin >> d;
    p.department = getDepartment(d);

    cout << "\nEnter Severity Level (1-5):\n";
    cout << "1. Needs Immediate Attention " << RED << "(Red - Critical)" << RESET << "\n";
    cout << "2. Very Urgent " << ORANGE << "(Orange - High Risk)" << RESET << "\n";
    cout << "3. Urgent " << YELLOW << "(Yellow - Moderate)" << RESET << "\n";
    cout << "4. Less Urgent " << GREEN << "(Green - Stable)" << RESET << "\n";
    cout << "5. Non-Urgent " << BLUE << "(Blue - Can Wait)" << RESET << "\n";
    cout << "Select severity: ";
    cin >> p.severity;

    p.arrival = time(0);
    p.token = "ER" + to_string(tokenNo++);
    setSeverity(p);

    pq.push(p);

    cout << "\nPatient Registered Successfully!\n";
    cout << "Token Number: " << p.token << "\n";
}


void callNext() {
    if(pq.empty()) {
        cout << "\nNo patients in queue.\n";
        return;
    }

    Patient p = pq.top();
    pq.pop();

    cout << "\n========== NEXT PATIENT ==========\n";
    cout << "Token       : " << p.token << "\n";
    cout << "Name        : " << p.name << "\n";
    cout << "Department  : " << p.department << "\n";
    cout << "Severity    : " 
         << p.severityColor << p.severityText << RESET 
         << " (" << p.severity << ")\n";
    cout << "Arrival     : " << getTime(p.arrival) << "\n";
    cout << "==================================\n";
}


void displayQueue() {
    if(pq.empty()) {
        cout << "\nNo patients waiting.\n";
        return;
    }

    priority_queue<Patient, vector<Patient>, Compare> temp = pq;

    cout << "\n================= EMERGENCY QUEUE =================\n";
    cout << left
         << setw(8) << "Token"
         << setw(14) << "Name"
         << setw(14) << "Department"
         << setw(6) << "Sev"
         << setw(26) << "Severity"
         << setw(10) << "Arrival"
         << endl;

    cout << "--------------------------------------------------------------\n";
    
    while(!temp.empty()) {
        Patient p = temp.top();
        temp.pop();
        cout << setw(8) << p.token
             << setw(14) << p.name
             << setw(14) << p.department
             << setw(6) << p.severity
             << setw(26) << (p.severityColor + p.severityText + RESET)
             << setw(10) << getTime(p.arrival)
             << endl;
    }
    cout << "--------------------------------------------------------------\n";
}

int main() {
    int choice;
    while(true) {
        cout << "\n=============== HOSPITAL EMERGENCY ===============\n";
        cout << "1. Add Patient\n";
        cout << "2. Call Next Patient\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "===================================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addPatient(); break;
            case 2: callNext(); break;
            case 3: displayQueue(); break;
            case 4: return 0;
            default: cout << "\nInvalid choice.\n";
        }
    }

}
