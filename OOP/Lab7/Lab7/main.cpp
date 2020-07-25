//
//  main.cpp
//  Lab6
//
//  Created by Kushka Misha on 12/5/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "prototypes.hpp"

int main() {
    cout << "Hello" << endl;
    
    Doctor doctors[] = {Doctor(0, "Nicola", "Tesla"), Doctor(1, "Franz", "Kafka")};
    int num_of_doctors = 2;
    
    // Data to random generate patient and it's disease
    vector<vector<string>> names = {{"Adam", "m"}, {"Karl", "m"}, {"Lisa", "f"}, {"Gabbie", "f"}, {"David", "m"}};
    vector<string> surnames = {"Vozniak", "Jobs", "Karter", "Duglas", "Twein"};
    vector<vector<string>> disease_treatment = {{"Caries", "Filling"}, {"Crack in the tooth", "Remove the tooth"}};
    
    string cont = "y";
    
    string name, surname, sex, disease, treatment, str_n;
    int age, n, id, pos, doctor_id;
    float cost;
    
    // Init Mersenne-Twister random
    random_device rd;
    mt19937 rng(rd());
    
    while(cont == "y") {
        while (true) {
            try {
                cout << endl << "Enter number of patients\n> ";
                cin >> str_n;
                n = stoi(str_n);
                break;
            } catch (...) {
                cout << "Please enter a number, not string" << endl;
            }
        }
        
        unique_ptr<Group<Patient, Disease, DoctorId>> patient[n];
        for (int i = 0; i < n; i++) {
            // Patient's name and sex
            uniform_int_distribution<int> uni_name(0, names.size() - 1);
            pos = uni_name(rng);
            name = names[pos][0];
            sex = names[pos][1];
            
            // Patient's surname
            uniform_int_distribution<int> uni_surname(0, surnames.size() - 1);
            surname = surnames[uni_surname(rng)];
            
            // Patient's disease and treatment
            uniform_int_distribution<int> uni_disease(0, disease_treatment.size() - 1);
            pos = uni_disease(rng);
            disease = disease_treatment[pos][0];
            treatment = disease_treatment[pos][1];
            
            // Patient's age
            uniform_int_distribution<int> uni_age(5, 80);
            age = uni_age(rng);

            // Treatment cost
            uniform_int_distribution<int> uni_cost(100, 1000);
            cost = uni_cost(rng);
            
            // Doctor's id
            uniform_int_distribution<int> uni_id(0, num_of_doctors - 1);
            id = uni_id(rng);

            patient[i].reset(new Group<Patient, Disease, DoctorId> ({name, surname, age, sex, id}, {disease, treatment, cost}, {id}));
        }
        
        // Calculate profit and number of patients of every doctor
        for (int i = 0; i < n; i++) {
            cost = patient[i]->getCost();
            doctor_id = patient[i]->getDoctorId();
            doctors[doctor_id].increaseNumberOfPatients();
            doctors[doctor_id].increaseProfit(cost);
        }
        
        // Display patient's and disease data
        for (int i = 0; i < n; i++) {
            cout << "=========== Patient " << i + 1 << "===========" << endl;
            patient[i]->getPatientInfo();
            patient[i]->getDiseaseInfo();
        }
        
        // Display doctor's data
        for(int i = 0; i < num_of_doctors; i++) {
            doctors[i].getDoctorInfo();
        }
        
        // Restart program?
        cout << endl << endl << "Continue? (y / n)\n> ";
        cin >> cont;
    }

    return 0;
}

