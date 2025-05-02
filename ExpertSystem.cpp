#include <iostream>
#include <string>
using namespace std;

// Function to ask yes/no questions
bool askQuestion(const string& question) {
    char response;
    cout << question << " (y/n): ";
    cin >> response;
    return (response == 'y' || response == 'Y');
}



// Function to explain the diagnosis based on symptoms
void explainDiagnosis(const string& diagnosis) {
    if (diagnosis == "flu") {
        cout << "Flu is diagnosed because you have high fever, fatigue, and body aches.\n";
    } else if (diagnosis == "cold") {
        cout << "You may have a cold because you have a runny nose and frequent sneezing.\n";
    } else if (diagnosis == "food poisoning") {
        cout << "Food poisoning is suspected due to symptoms like nausea, vomiting, and diarrhea.\n";
    } else if (diagnosis == "appendicitis") {
        cout << "Appendicitis may be diagnosed because of severe abdominal pain and loss of appetite.\n";
    } else if (diagnosis == "strep throat") {
        cout << "Strep throat is diagnosed because of a sore throat and swollen tonsils.\n";
    } else if (diagnosis == "fever") {
        cout << "You may have a fever because of high body temperature and chills.\n";
    } else if (diagnosis == "allergies") {
        cout << "You may have allergies due to symptoms like itching or swelling, and watery eyes.\n";
    }
}

// Function to diagnose allergies
bool diagnoseAllergies() {
    bool itchingOrSwelling = askQuestion("Do you experience any itching or swelling?");
    bool redness = askQuestion("Do you have red, watery eyes?");
    return (itchingOrSwelling || redness);
}

// Function to diagnose fever
bool diagnoseFever() {
    bool highTemperature = askQuestion("Do you have a temperature above 37.5 deg Celsius?");
    bool chills = askQuestion("Do you experience chills?");
    return (highTemperature || chills);
}

// Function to diagnose cold
bool diagnoseCold() {
    bool runnyOrStuffyNose = askQuestion("Do you have a runny or stuffy nose?");
    bool sneezing = askQuestion("Are you sneezing frequently?");
    return (runnyOrStuffyNose || sneezing);
}

// Function to diagnose flu
bool diagnoseFlu() {
    bool bodyAches = askQuestion("Do you have body aches?");
    bool fatigue = askQuestion("Do you feel tired or fatigued?");
    bool highTemperature = askQuestion("Do you have a temperature above 38 deg Celsius?");
    return (bodyAches && fatigue && highTemperature);
}

// Function to diagnose strep throat
bool diagnoseStrepThroat() {
    bool soreThroat = askQuestion("Do you have a sore throat?");
    bool swollenTonsils = askQuestion("Are your tonsils swollen?");
    return (soreThroat && swollenTonsils);
}

// Function to diagnose food poisoning
bool diagnoseFoodPoisoning() {
    bool nausea = askQuestion("Do you feel nauseous?");
    bool vomiting = askQuestion("Have you been vomiting?");
    bool diarrhea = askQuestion("Do you have diarrhea?");
    return (nausea && vomiting && diarrhea);
}

// Function to diagnose appendicitis
bool diagnoseAppendicitis() {
    bool severeAbdominalPain = askQuestion("Do you have severe abdominal pain?");
    bool lossOfAppetite = askQuestion("Have you lost your appetite?");
    return (severeAbdominalPain && lossOfAppetite);
}

int main() {
    cout << "Welcome to the Expert System for Medical Diagnosis\n";

    // Asking about symptoms for various diseases
    bool hasAllergies = diagnoseAllergies();
    bool hasFever = diagnoseFever();
    bool hasCold = diagnoseCold();
    bool hasFlu = diagnoseFlu();
    bool hasStrepThroat = diagnoseStrepThroat();
    bool hasFoodPoisoning = diagnoseFoodPoisoning();
    bool hasAppendicitis = diagnoseAppendicitis();

    // Output the diagnosis
    string diagnosis = "";

    if (hasAllergies) {
        diagnosis = "allergies";
    } else if (hasFever) {
        diagnosis = "fever";
    } else if (hasCold) {
        diagnosis = "cold";
    } else if (hasFlu) {
        diagnosis = "flu";
    } else if (hasStrepThroat) {
        diagnosis = "strep throat";
    } else if (hasFoodPoisoning) {
        diagnosis = "food poisoning";
    } else if (hasAppendicitis) {
        diagnosis = "appendicitis";
    }

    if (!diagnosis.empty()) {
        cout << "\nDiagnosis: You may have " << diagnosis << ".\n";
        explainDiagnosis(diagnosis);
    } else {
        cout << "\nNo specific diagnosis could be made based on the provided symptoms.\n";
    }

   
    cout << endl;

    return 0;
}
