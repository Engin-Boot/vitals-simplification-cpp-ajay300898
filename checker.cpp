#include <assert.h>
#include <iostream>
using namespace std;
// enum Range
bool isBPOk(float bpm);
bool isSpoOk(float spo2);
bool isRespOk(float respRate);
bool isVitalOk(float value, float low, float high);
const int bp_limits[] = {70,150};
const int resp_limits[] = {30,95};

class Alert{
  public:
  virtual void raiseAnAlert(const char* vital, const char *message) = 0;
  
};

class AlertInSMS : public Alert{
  public:
  virtual void raiseAnAlert(const char* vital, const char *message) override{
    cout << "send SMS :" << endl;
  }
};

class AlertInSoung : public Alert{
  public:
  virtual void raiseAnAlert(const char* vital, const char *message) override{
    cout << "Make Alert sound :" << endl;
  }
};
class CheckVitals{
  private:
    Alert* alert;
  public:
  CheckVitals(): alert(0){}
  void setAlert(Alert* alert_requested){
    alert = alert_requested;
  }
  
  bool isVitalOk(float value, float low, float high){
    return (value >= low && value <= high);
  }
  bool isBPOk(float bpm){
    if(isVitalOk(bpm,bp_limits[0],bp_limits[1])){
      return true;
    }
    alert->raiseAnAlert("bpm","BP ");
    return false;
  }

  bool isSpoOk(float spo2){
    if(isVitalOk(spo2,90,100)){
      return true;
    }
    alert->raiseAnAlert("spo2","SPO2");
    return false;
  }

  bool isRespOk(float respRate){
    if(isVitalOk(respRate,resp_limits[0],resp_limits[1])){
      return true;
    }
    alert->raiseAnAlert("respRate","RESP");
    return false;
  }

  bool vitalsAreOk(float bpm, float spo2, float respRate) {
    bool res1,res2,res3;
    res1 = isBPOk(bpm);
    res2 = isSpoOk(spo2);
    res3 = isRespOk(respRate);
    return res1 && res2 && res3;
  }
};

int main() {
  CheckVitals x;
  x.setAlert(new AlertInSMS);
  
  assert(x.isVitalOk(10,50,100) == false);
  assert(x.isVitalOk(1000,50,100) == false);
  assert(x.isVitalOk(70,50,100) == true);
  assert(x.vitalsAreOk(80, 95, 60) == true);
  assert(x.vitalsAreOk(60, 90, 40) == false);  // test bp low
  assert(x.vitalsAreOk(160, 90, 40) == false); // test bp high
  assert(x.vitalsAreOk(80, 99, 25) == false);  // test resp low
  assert(x.vitalsAreOk(80, 99, 100) == false); // test resp low
  assert(x.vitalsAreOk(80, 85, 60) == false); // test spo2 low

}
