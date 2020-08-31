#include <assert.h>
#include <iostream>
#include <map>
#include<string>
#include<vector>
using namespace std;
class Alert {
public:
    virtual void raiseAnAlert( string message) = 0;

};

class AlertInSMS : public Alert {
public:
    virtual void raiseAnAlert(string message) override {
        cout << "send SMS :" << message << endl;
    }
};

class AlertInSound : public Alert {
public:
    virtual void raiseAnAlert(string message) override {
        cout << "Make Alert sound :" << message << endl;
    }
};

class Range {
public:
    static bool isInRange(float value, float low, float high) {
        return value >= low && value <= high;
    }
    static bool isLessThan(float value, float low) {
        return value < low;
    }
    static bool isGreaterThan(float value, float high) {
        return value > high;
    }
};


struct Vital {
    string vital_name;
    float value;
};

class Vitals {
public:
    static map<string, pair<int, int>> vitals_information;
    vector<Vital> vitals;
    Vitals() {
        
    }
    void addVitalInfo(Vital v) {
        vitals.push_back(v);
    }
    void addVitalInfo(string vital_name, float value ) {
        struct Vital v = {vital_name, value};
        vitals.push_back(v);
    }
    void addVitalInfo(vector<Vital> v) {
        vitals = v;
    }
    bool addNewVital(string v_name, float low, float high) {
        if (vitals_information.find(v_name) == vitals_information.end()) {
            vitals_information[v_name] = { low , high };
            return true;
        }
        return false;
    }
};
map<string, pair<int, int>> Vitals::vitals_information;

class CheckVitals {
private:
    Alert* alert;
public:
    CheckVitals() : alert(new AlertInSMS) {}   // default is Alert in SMS.
    CheckVitals(Alert* alert_requested) : alert(alert_requested) {}
    void setAlert(Alert* alert_requested) {
        alert = alert_requested;
    }

    bool AreVitalsOk(vector<Vital> vital_info) {
        bool result = true;
        for (int i = 0; i < vital_info.size(); i++) {
            
            result &= isVitalOk(vital_info[i].vital_name, vital_info[i].value);
        }
        if (result == true) {
            cout << "All vitals are in Normal " << endl;
        }
        
        return result;
    }

    bool isVitalOk(string v_name, float value) {
        string msg;
        if (!Range::isInRange(value, Vitals::vitals_information[v_name].first, Vitals::vitals_information[v_name].second)) {
            if (Range::isLessThan(value, Vitals::vitals_information[v_name].first)) {
                msg = v_name + " of the patient is " + to_string(value) + " which is less than the normal\n";
                alert->raiseAnAlert(msg);
                return false;
            }
            msg = v_name + " of the patient is " + to_string(value) + " which is high than the normal\n";
            alert->raiseAnAlert(msg);
            return false;
        }
        return true;
    }
};

int main() {
    CheckVitals x;
    x.setAlert(new AlertInSMS);
    Vitals::vitals_information["bp"] = { 70,150 };   // added values manually
    Vitals::vitals_information["spo2"] = { 90,100 }; // we can also call addNewVital();
    Vitals::vitals_information["resp"] = { 30,95 };
    vector<Vital> vital_info = { {"bp",60},{"spo2",90},{"resp",40} };
    Vitals patient_vital_info;
    patient_vital_info.addVitalInfo(vital_info);
   
    assert(x.AreVitalsOk({ {"bp",60},{"spo2",90},{"resp",40} }) == false); // test bp low
    assert(x.AreVitalsOk({ {"bp",160},{"spo2",90},{"resp",40} }) == false); // test bp high
    assert(x.AreVitalsOk({ {"bp",80},{"spo2",99},{"resp",25} }) == false); // test resp low
    x.setAlert(new AlertInSound);
    assert(x.AreVitalsOk({ {"bp",80},{"spo2",99},{"resp",100} }) == false); // test resp high
    assert(x.AreVitalsOk({ {"bp",80},{"spo2",85},{"resp",60} }) == false); // test spo2 low
    assert(x.AreVitalsOk({ {"bp",90},{"spo2",95},{"resp",40} }) == true); // all true
    
}
