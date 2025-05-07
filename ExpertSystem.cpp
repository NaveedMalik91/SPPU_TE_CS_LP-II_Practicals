#include <iostream>
#include <vector>
using namespace std;

bool askQuestion(const string &question)
{
    char response;
    cout << question << "(Y/N)";
    cin >> response;
    return (response == 'Y' || response == 'y');
}

void explainDiagnosis(const string &diagnosis)
{
    if (diagnosis == "allergies")
    {
        cout << "You may have Allergy because of symptoms like red watery eyes, itching, swelling, throat itching etc."<<endl;
    }
    else if (diagnosis == "flu")
    {
        cout << "You may have covid-19 flu because of symptoms like loss of smell and taste, fever, shortness of breath etc."<<endl;
    }
    else if (diagnosis == "fever")
    {
        cout << "You may have Fever because of symptoms like body ache, high body temperature, headache, chills etc."<<endl;
    }
    else if (diagnosis == "cold")
    {
        cout << "You may have Cold because of symptoms like runny and stuffy nose, sneezing, cough etc."<<endl;
    }
    else if (diagnosis == "appendicitis")
    {
        cout << "You may have Appendicitis because of symptoms like pain the lower right abdominal region, loss of appetite etc."<<endl;
    }
    else if (diagnosis == "foodpoisioning")
    {
        cout << "You may have Food Posioning because of symptoms like Stomach ache, Diarrhea, vomitting etc."<<endl;
    }
    else if (diagnosis == "strepthroat")
    {
        cout << "You may have Strep Throat because of symptoms like Tonsils, neck and thoat pain, sore throat, etc."<<endl;
        
    }
    else if (diagnosis == "Diabetes")
    {
        cout << "You may have Diabetes because of symptoms like Frequent Urination, weight loss, tiredness and weekness, etc"<<endl;
    }
    else{
        cout<<"No Relevant Diagnosis found"<<endl;
    }
}
bool diagnoseAllergies()
{
    bool symptom1 = askQuestion("Do you experience red watery eyes");
    bool symptom2 = askQuestion("Do you experience itching or swelling in the body?");
    bool symptom3 = askQuestion("Do you have redness in the body?");
    bool symptom4 = askQuestion("Are you experiencing itching in the throat?");
    return symptom1 || symptom2 || symptom4 || symptom3;
}

bool diagnosefever()
{
    bool symptom1 = askQuestion("Do you experience body chills?");
    bool symptom2 = askQuestion("Do you have temperature higher than 37.5 deg celsius?");
    bool symptom3 = askQuestion("Do you have headache?");
    bool symptom4 = askQuestion("Dou you have body ache?");
    return symptom1 || symptom2 || symptom3 || symptom4;
}
bool diagnoseflu()
{
    bool symptom1 = askQuestion("Dou have the sense of smell and taste");
    bool symptom2 = askQuestion("Do you have sore throat?");
    bool symptom3 = askQuestion("Do you have cough, body and muscle ache?");
    bool symptom4 = askQuestion("Do you experience shortness of breath?");
    return symptom1 || symptom2 || symptom4 || symptom3;
}
bool diagnosecold()
{
    bool symptom1 = askQuestion("Do you have runny or stuffy nose?");
    bool symptom2 = askQuestion("Do you have headache?");
    bool symptom3 = askQuestion("Are you sneezing frequently");
    return symptom1 || symptom2 || symptom3;
}
bool diagnoseappendicitis()
{
    bool symptom1 = askQuestion("Do you experience pain in lower right part of your Abdomin?");
    bool symptom2 = askQuestion("Are you feeling nauseous?");
    bool symptom3 = askQuestion("Are you experiencing loss of appetite?");
    return symptom1 || symptom2 || symptom3;
}
bool diagnosestrepthroat()
{
    bool symptom1 = askQuestion("Do you have tonsils?");
    bool symptom2 = askQuestion("Do you experience pain in the throat, neck and head?");
    bool symptom3 = askQuestion("Do you have sore throat?");
    return symptom1 || symptom2 || symptom3;
}

bool diagnosefoodpoisoning()
{
    bool symptom1 = askQuestion("Do you experience stomach ache?");
    bool symptom2 = askQuestion("Are you feeling nauseous?");
    bool symptom3 = askQuestion("Are you vomitting frequently?");
    bool symptom4 = askQuestion("Do you have any symptoms of Diarrhea?");
    return symptom1 || symptom2 || symptom3 || symptom4;
}

bool diagnoseDiabetes()
{
    bool symptom1 = askQuestion("Are you feeling thirsty frequently?");
    bool symptom2 = askQuestion("Dou you experience frequent urination?");
    bool symptom3 = askQuestion("Did you have unexpected weight loss;");
    bool symptom4 = askQuestion("Are you feeling tired and week?");
    return symptom1 || symptom2 || symptom3||symptom4;
}

int main()
{
    vector<string> diagnoses;
    bool hasallergies = diagnoseAllergies();
    bool hasappendicitis = diagnoseappendicitis();
    bool hasflu = diagnoseflu();
    bool hascold = diagnosecold();
    bool hasfever = diagnosefever();
    bool hasstrepthroat = diagnosestrepthroat();
    bool hasfoodpoisoning = diagnosefoodpoisoning();
    bool hasDiabetes = diagnoseDiabetes();


    if (hasallergies)
    {
        diagnoses.push_back("allergies");
    }
    if (hasappendicitis)
    {
        diagnoses.push_back("appendicitis");
    }
    if (hasflu)
    {
        diagnoses.push_back("flu");
    }
    if (hascold)
    {
        diagnoses.push_back("cold");
    }
    if (hasfoodpoisoning)
    {
        diagnoses.push_back("foodpoisioning");
    }
    if (hasstrepthroat)
    {
        diagnoses.push_back("strepthroat");
    }
    if (hasfever)
    {
        diagnoses.push_back("fever");
    }
    if (hasDiabetes)
    {
        diagnoses.push_back("Diabetes");
    }

    if (!diagnoses.empty())
    {
        for(const auto diagnosis : diagnoses){
            explainDiagnosis(diagnosis);
        }
    }

    else
    {
        cout << "No diagnosis found for the symptoms";
    }
    return 0;
}