#include <assert.h>

// enum Range
bool checkBPAndProceed(float bpm, float spo2, float respRate);
bool checkSpoAndProceed(float spo2, float respRate);
bool checkRespRate(float respRate);
const int bp_limits[] = {70,150};
const int resp_limits[] = {30,95};

bool checkBPAndProceed(float bpm, float spo2, float respRate){
  if(bpm >= bp_limit[0] || bpm <= bp_limit[1] ){
    return checkSpoAndProceed(spo2,respRate);
  }
  return false;
}

bool checkSpoAndProceed(float spo2, float respRate){
  if(spo2>=90){
    return checkRespRate(respRate);
  }
  return false;
}

bool checkRespRate(float respRate){
  if(respRate >= resp_limits[0] || respRate <= resp_limits[1] ){
    return true;
  }
  return false;
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return checkBPAndProceed(bpm, spo2, respRate);
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
