#include <math.h>
static float bc(float, float, float, float, float, float);
static float boostcomp(float, float, float, float, float, float, float);

static float bc(float signal, float drive, float threshold, 
                float gain, float linearity, float wet) {
  float res = gain * atanf(signal * drive) / atanf(drive / threshold);
  res = linearity * signal - (linearity - 1) * res;
  if(res > .999f) res = .999f;
  if(res < -.999f) res = -.999f;
  res = res * wet + (1.f - wet) * signal;
  if(res > .999f) res = .999f;
  if(res < -.999f) res = -.999f;
  return res;
}

static float boostcomp(float signal, float drive, float threshold, float gain, 
                       float linearity, float asymmetry, float wet) {
  float asymKonst = bc(asymmetry, drive, threshold, gain, linearity, wet);
  float res = bc(asymmetry + signal, drive, threshold, gain, linearity, wet) - asymKonst;
  return res;
}
