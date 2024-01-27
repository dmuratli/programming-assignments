#include <iostream>
#include <string>

using namespace std;

void getInput(string exercise, int &reps, double &mins, double &liftedWeight){
    if (exercise=="lunges"){
        cout << "Lunges: ";
        cin >> mins >> reps;
        liftedWeight=0;
    }else if (exercise=="pushups"){
        cout << "Push Ups: ";
        cin >> mins >> reps;
        liftedWeight=0;
    }else if (exercise=="pullups"){
        cout << "Pull Ups: ";
        cin >> mins >> reps;
        liftedWeight=0;
    }else{
        cout << "Weight Lifting: ";
        cin >> mins >> reps >> liftedWeight;
    }
}

bool inputCheck(double weight, int reps, double mins, double liftedWeight){
    if (weight>=30){
        if (liftedWeight>0 && liftedWeight<=35){
            if (reps>=0 && reps<=50){
                if (mins>=0 && mins<=2000){
                    return true;
                }else{
                    cout << "Minute out of range!" << endl;
                    return false;
                }
            }else{
                cout << "Reps out of range!" << endl;
                return false;
            }
        }else{
            cout << "Lifted weight out of range!" << endl;
            return false;
        }
    }else{
        cout << "Weight out of range!" << endl;
        return false;
    }
}

void calculateMET(int reps, string exercise, double &MET){
    if (exercise=="lunges"){
        if (reps<15){
            MET+=3;
        }else if (reps>=15 && reps<30){
            MET+=6.5;
        }else{
            MET+=10.5;
        }
    }else if (exercise=="pushups"){
        if (reps<15){
            MET+=4;
        }else{
            MET+=7.5;
        }
    }else{
        if (reps<25){
            MET+=5;
        }else{
            MET+=9;
        }
    }
}

void calculateWeightLiftMET(int reps, double liftedWeight, double &MET){
    if (liftedWeight<5 && reps<20){
        MET+=3;
    }else if (liftedWeight<5 && reps>=20 && reps<40){
        MET+=5.5;
    }else if (liftedWeight<5 && reps>=40){
        MET+=10;
    }else if (liftedWeight>=5 && liftedWeight<15 && reps<20){
        MET+=4;
    }else if (liftedWeight>=5 && liftedWeight<15 && reps>=20 && reps<40){
        MET+=7.5;
    }else if (liftedWeight>=5 && liftedWeight<15 && reps >=40){
        MET+=12;
    }else if (liftedWeight>=15 && reps<20){
        MET+=5;
    }else if (liftedWeight>=15 && reps>=20 && reps<40){
        MET+=9;
    }else{
        MET+=13.5;
    }

}

void displayResults(double difference, double total, double weight, double lungeMET, double pushupMET,
double pullupMET, double weightliftMET, double lungeCalorie, double pushupCalorie,
double pullupCalorie, double weightliftCalorie){
    double allowedCalorie, neededLunge, neededPushup, neededPullup, neededWeightlift;
    cout << "From lunges, you burned " << lungeCalorie << " calories." << endl;
    cout << "From push ups, you burned " << pushupCalorie << " calories." << endl;
    cout << "From pull ups, you burned " << pullupCalorie << " calories." << endl;
    cout << "From weight lifting, you burned " << weightliftCalorie << " calories." << endl;
    cout << "You burned " << total << " calories." << endl << endl;
    if (difference>0){
        neededLunge=(difference*200)/(lungeMET*3.5*weight);
        neededPushup=(difference*200)/(pushupMET*3.5*weight);
        neededPullup=(difference*200)/(pullupMET*3.5*weight);
        neededWeightlift=(difference*200)/(weightliftMET*3.5*weight);
        cout << "You did not reach your goal by " << difference << " calories." << endl;
        cout << "You need to do lunges " << neededLunge << " minutes more to reach your goal or," << endl;
        cout << "You need to do push ups " << neededPushup << " minutes more to reach your goal or," << endl;
        cout << "You need to do pull ups " << neededPullup << " minutes more to reach your goal or," << endl;
        cout << "You need to do weight lifting " << neededWeightlift << " minutes more to reach your goal." << endl;
    }else if (difference<0){
        allowedCalorie=-difference;
        cout << "You have surpassed your goal! You can eat something worth " << allowedCalorie << " calories :)" << endl;
    }else{
        cout << "Congratulations! You have reached your goal!" << endl;
    }
}

void computeResults(double weight, double goal, int repsLunge, int repsPushUp, int repsPullUp,
int repsWeightLift, double minLunge, double minPushUp, double minPullUp, double minWeightLift,
double liftedWeight){
    double lunges_met=0, pushups_met=0, pullups_met=0, weightlifts_met=0, burnedcalories,
    lungeCalorie, pushupCalorie, pullupCalorie, weightliftCalorie, difference;
    calculateMET(repsLunge, "lunges", lunges_met);
    calculateMET(repsPushUp, "pushups", pushups_met);
    calculateMET(repsPullUp, "pullups", pullups_met);
    calculateWeightLiftMET(repsWeightLift, liftedWeight, weightlifts_met);
    lungeCalorie=(minLunge*(lunges_met*3.5*weight))/200;
    pushupCalorie=(minPushUp*(pushups_met*3.5*weight))/200;
    pullupCalorie=(minPullUp*(pullups_met*3.5*weight))/200;
    weightliftCalorie=(minWeightLift*(weightlifts_met*3.5*weight))/200;
    burnedcalories=lungeCalorie+pushupCalorie+pullupCalorie+weightliftCalorie;
    difference=goal-burnedcalories;
    displayResults(difference, burnedcalories, weight, lunges_met, pushups_met, pullups_met, weightlifts_met, lungeCalorie, pushupCalorie, pullupCalorie, weightliftCalorie);
}

int main(){
    string name;
    int lunges_reps, pushups_reps, pullups_reps, weightlifts_reps;
    double weight, lunges_mins, pushups_mins, pullups_mins, weightlifts_mins, 
    weightlifts_weight, goal;
    bool validity;
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Welcome " << name << ", please enter your weight(kg): ";
    cin >> weight;
    cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl;
    getInput("lunges", lunges_reps, lunges_mins, weightlifts_weight);
    getInput("pushups", pushups_reps, pushups_mins, weightlifts_weight);
    getInput("pullups", pullups_reps, pullups_mins, weightlifts_weight);
    cout << name << ", please enter minutes, repetitions and lifted weight in a week for the activities below." << endl;   
    getInput("weightlifting", weightlifts_reps, weightlifts_mins, weightlifts_weight);
    cout << name << ", please enter your weekly calorie burn goal: ";
    cin >> goal;
    validity=inputCheck(weight, lunges_reps, lunges_mins, weightlifts_weight);
    if (validity==true){
        validity=inputCheck(weight, pushups_reps, pushups_mins, weightlifts_weight);
        if (validity==true){
            validity=inputCheck(weight, pullups_reps, pullups_mins, weightlifts_weight);
            if (validity==true){
                validity=inputCheck(weight, weightlifts_reps, weightlifts_mins, weightlifts_weight);
                if (validity==true){
                    computeResults(weight, goal, lunges_reps, pushups_reps, pullups_reps, weightlifts_reps, lunges_mins, pushups_mins, pullups_mins, weightlifts_mins, weightlifts_weight);
                }else{
                    ;
                }
            }else{
                ;
            }
        }else{
            ;
        }
    }else{
        ;
    }
    return 0;
}

//Deniz Muratli