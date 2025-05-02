#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct symptom{
    string question;
    bool response = false;
};
struct disease{
    string name;
    string explanation;
    vector<vector<pair<int,int>>> symptomWeight;
};

bool askQuestion(const string& symptom){
    char ans;
    cout<<symptom<<" y/n: ";
    cin>>ans;
    while (ans != 'n' && ans == 'N' && ans != 'Y' && ans != 'y')
    {
        cout<<"Invalid choice, please enter y/n";
        cin>>ans;
    }
    return(ans == 'y' ||ans == 'Y');
    

}
bool askFeedback(){
    char feedback;
    cout<<"Were you satisfied (y/n)?";
    cin>>feedback;
    if (feedback == 'N'||feedback == 'n')
    {
        cout<<"Please try again";
        cin>>feedback;
        return(feedback == 'Y' || feedback == 'y');
    }
    return false;
    
}

string diagnose(vector<string>&symptoms, vector<string>&diseases){

}
int main(int argc, char const *argv[])
{
    
    return 0;
}
