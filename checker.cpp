#include <assert.h>

// enum Range
bool bool isBPOk(float bpm);
bool isSpoOk(float spo2);
bool isRespOk(float respRate);
bool isVitalOk(float value, float low, float high);
const int bp_limits[] = {70,150};
const int resp_limits[] = {30,95};

bool isVitalOk(float value, float low, float high){
  if(value < low || value > high){
    return false;
  }
  else return true;
}
bool isBPOk(float bpm){
  return isVitalOk(bpm,bp_limits[0],bp_limits[1]);
}

bool isSpoOk(float spo2){
  if(spo2>=90){
    return true;
  }
  return false;
}

bool isRespOk(float respRate){
  return isVitalOk(respRate,resp_limits[0],resp_limits[1]);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return isBPOk(bpm) && isSpoOk(spo2) && isRespOk(respRate);
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
