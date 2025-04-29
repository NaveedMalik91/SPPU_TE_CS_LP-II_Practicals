#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Symptom {
    string question;
    bool response = false;
};

struct Disease {
    string name;
    string explanation;
    vector<int> symptomIndices; 
};

bool askQuestion(const string& question) {
    char response;
    cout << question << " (y/n): ";
    cin >> response;
    return (response == 'y' || response == 'Y');
}

int main() {
    cout << "Welcome to the DSA-based Expert System for Medical Diagnosis\n\n";

    vector<Symptom> symptoms = {
        {"Do you experience any itching or swelling?"},
        {"Do you have red, watery eyes?"},
        {"Do you have a temperature above 37.5°C?"},
        {"Do you experience chills?"},
        {"Do you have a runny or stuffy nose?"},
        {"Are you sneezing frequently?"},
        {"Do you have body aches?"},
        {"Do you feel tired or fatigued?"},
        {"Do you have a temperature above 38°C?"},
        {"Do you have a sore throat?"},
        {"Are your tonsils swollen?"},
        {"Do you feel nauseous?"},
        {"Have you been vomiting?"},
        {"Do you have diarrhea?"},
        {"Do you have severe abdominal pain?"},
        {"Have you lost your appetite?"}
    };

    vector<Disease> diseases = {
        {"allergies", "You may have allergies due to symptoms like itching or swelling, and watery eyes.", {0, 1}},
        {"fever", "You may have a fever because of high body temperature and chills.", {2, 3}},
        {"cold", "You may have a cold because you have a runny nose and frequent sneezing.", {4, 5}},
        {"flu", "Flu is diagnosed because you have high fever, fatigue, and body aches.", {6, 7, 8}},
        {"strep throat", "Strep throat is diagnosed because of a sore throat and swollen tonsils.", {9, 10}},
        {"food poisoning", "Food poisoning is suspected due to symptoms like nausea, vomiting, and diarrhea.", {11, 12, 13}},
        {"appendicitis", "Appendicitis may be diagnosed because of severe abdominal pain and loss of appetite.", {14, 15}}
    };

    for (auto& symptom : symptoms) {
        symptom.response = askQuestion(symptom.question);
    }

    string bestDiagnosis = "";
    string explanation = "";
    int maxMatch = 0;

    for (const auto& disease : diseases) {
        int matchCount = 0;
        for (int index : disease.symptomIndices) {
            if (symptoms[index].response) matchCount++;
        }

        if (matchCount > maxMatch) {
            maxMatch = matchCount;
            bestDiagnosis = disease.name;
            explanation = disease.explanation;
        }
    }

    if (!bestDiagnosis.empty()) {
        cout << "\nDiagnosis: You may have " << bestDiagnosis << ".\n";
        cout << explanation << endl;
    } else {
        cout << "\nNo specific diagnosis could be made based on the provided symptoms.\n";
    } return 0;
}