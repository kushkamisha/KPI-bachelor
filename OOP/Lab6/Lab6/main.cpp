//
//  main.cpp
//  Lab6
//
//  Created by Kushka Misha on 12/5/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "prototypes.hpp"

int main() {
    
    Doctor doctors[] = {Doctor(0, "Nicola", "Tesla"), Doctor(1, "Franz", "Kafka")};
    
//    Group<Patient, Disease, DoctorId> arr[] = {
//        Group<Patient, Disease, DoctorId> (
//            {"Mark", "Twein", 60, 'm'},
//            {"Caries", "filling", 300},
//            {0}
//        ),
//        Group<Patient, Disease, DoctorId> (
//            {"Sebastian", "Pingo", 45, 'm'},
//            {"Crack in the tooth", "Remove the tooth", 600},
//            {0}
//        ),
//        Group<Patient, Disease, DoctorId> (
//            {"Angelina", "Jolie", 37, 'f'},
//            {"Caries", "filling", 500},
//            {1}
//        )
//    };
    
    vector<Group<Patient, Disease, DoctorId>> arr;
    string cont = "y";
    
    string name, surname;
    int age;
    char sex;
    int id;
    
    string disease, treatment;
    float cost;
    
    while(cont == "y") {
        cout << endl << "Enter patient's:" << endl;
        cout << "\tName\n\t> ";
        cin >> name;
        cout << "Surname\n\t> ";
        cin >> surname;
        cout << "Age\n\t> ";
        cin >> age;
        cout << "Sex\n\t> ";
        cin >> sex;
        
        cout << "Disease\n\t> ";
        cin >> disease;
        cout << "Treatment\n\t> ";
        cin >> treatment;
        cout << "Cost\n\t> ";
        cin >> cost;
        
        cout << "Enter doctor id\n> ";
        cin >> id;
        
        arr.push_back(Group<Patient, Disease, DoctorId> ({name, surname, age, sex}, {disease, treatment, cost}, {id}));
        
        cout << endl << endl << "Continue? (y / n)\n> ";
        cin >> cont;
    }

    // Calculate profit and number of patients of every doctor
    int n = arr.size();
    int doctor_id = 0;

    for (int i = 0; i < n; i++) {
        cost = arr[i].getCost();
        doctor_id = arr[i].getDoctorId();
        
        doctors[doctor_id].increaseNumberOfPatients();
        doctors[doctor_id].increaseProfit(cost);
        doctors[doctor_id].getDoctorInfo();
    }
    
    return 0;
}
