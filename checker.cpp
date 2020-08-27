#include <assert.h>

// enum Range
bool isBPOk(float bpm);
bool isSpoOk(float spo2);
bool isRespOk(float respRate);
bool isVitalOk(float value, float low, float high);
const int bp_limits[] = {70,150};
const int resp_limits[] = {30,95};

bool isVitalOk(float value, float low, float high){
  return (value >= low && value <= high);
}
bool isBPOk(float bpm){
  return isVitalOk(bpm,bp_limits[0],bp_limits[1]);
}

bool isSpoOk(float spo2){
  return isVitalOk(spo2,90,100);
}

bool isRespOk(float respRate){
  return isVitalOk(respRate,resp_limits[0],resp_limits[1]);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return isBPOk(bpm) && isSpoOk(spo2) && isRespOk(respRate);
}

int main() {
  assert(isVitalOk(10,50,100) == false);
  assert(isVitalOk(1000,50,100) == false);
  assert(isVitalOk(70,50,100) == true);
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);  // test bp low
  assert(vitalsAreOk(160, 90, 40) == false); // test bp high
  assert(vitalsAreOk(80, 99, 25) == false);  // test resp low
  assert(vitalsAreOk(80, 99, 100) == false); // test resp low
  assert(vitalsAreOk(80, 85, 60) == false); // test spo2 low

}
