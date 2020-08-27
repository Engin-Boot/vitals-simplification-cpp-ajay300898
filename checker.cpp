#include <assert.h>

// enum Range
bool bool isBPOk(float bpm);
bool isSpoOk(float spo2);
bool isRespOk(float respRate);
const int bp_limits[] = {70,150};
const int resp_limits[] = {30,95};

bool isBPOk(float bpm){
  if(bpm >= bp_limits[0] && bpm <= bp_limits[1] ){
    return true;
  }
  return false;
}

bool isSpoOk(float spo2){
  if(spo2>=90){
    return true;
  }
  return false;
}

bool isRespOk(float respRate){
  if(respRate >= resp_limits[0] && respRate <= resp_limits[1] ){
    return true;
  }
  return false;
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return isBPOk(bpm) && isSpoOk(spo2) && isRespOk(respRate);
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
