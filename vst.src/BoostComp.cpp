#include "BoostComp.h"

#include <math.h>
#include <float.h>
#include <stdio.h>

void int2strng(VstInt32 value, char *string) { sprintf(string, "%d", value); }
void float2strng(float value, char *string) { sprintf(string, "%.2f", value); }
float linear2dB(float signal) { return 10.f * (float) log10(fabs(signal)); }

AudioEffect *createEffectInstance(audioMasterCallback audioMaster) {
  return new wolfBoostComp(audioMaster);
}

wolfBoostComp::wolfBoostComp(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, 1, 6) // programs, parameters
{
  //inits here!
  fParam1 = (float) 0.25f; // Drive
  fParam2 = (float) 0.25f; // Threshold
  fParam3 = (float) 0.25f; // Gain  
  fParam4 = (float) 0.50f; // Linearity
  fParam5 = (float) 0.50f; // Asymmetry
  fParam6 = (float) 1.00f; // Wet

  setNumInputs(2);
  setNumOutputs(2);
  setUniqueID('wlBC');    // identify here
  DECLARE_VST_DEPRECATED(canMono) ();
  canProcessReplacing();
  strcpy(programName, "Boost-Compressor Fx");

  adj1 = 1.f;
  adj2 = 1.f;
  adj3 = 1.f;
  adj4 = 0.f;
  adj5 = 0.f;
  asymKonst = boostcomp(adj5, adj1, adj2, adj3, adj4, fParam6);
}

bool wolfBoostComp::getProductString(char* text) { strcpy(text, "BoostComp"); return true; }
bool wolfBoostComp::getVendorString(char* text)  { strcpy(text, "Wolf Sound"); return true; }
bool wolfBoostComp::getEffectName(char* name)    { strcpy(name, "BoostComp"); return true; }

void wolfBoostComp::setProgramName(char *name) { strcpy(programName, name); }
void wolfBoostComp::getProgramName(char *name) { strcpy(name, programName); }
bool wolfBoostComp::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* name) {
  if (index == 0) { strcpy(name, programName); return true; }
  return false;
}

float wolfBoostComp::getParameter(VstInt32 index) {
  float v = 0;
  switch(index) {
    case 0: v = fParam1; break;
    case 1: v = fParam2; break;
    case 2: v = fParam3; break;
    case 3: v = fParam4; break;
    case 4: v = fParam5; break;
    case 5: v = fParam6; break;
  }
  return v;
}

void wolfBoostComp::getParameterName(VstInt32 index, char *label) {
  switch(index) {
    case 0: strcpy(label, "Drive"); break;
    case 1: strcpy(label, "Threshold"); break;
    case 2: strcpy(label, "Gain"); break;
    case 3: strcpy(label, "Linearity"); break;
    case 4: strcpy(label, "Asymmetry"); break;
    case 5: strcpy(label, "Wet"); break;
  }
}

void wolfBoostComp::setParameter(VstInt32 index, float value) {
  switch(index)
  {
    case 0: fParam1 = value; break;
    case 1: fParam2 = value; break;
    case 2: fParam3 = value; break;
    case 3: fParam4 = value; break;
    case 4: fParam5 = value; break;
    case 5: fParam6 = value; break;
  }
  adj1 = fParam1 * 4.f; // Drive
  adj2 = fParam2 * 4.f; // Threshold
  adj3 = fParam3 * 4.f; // Gain  
  if (adj1 < 1.e-6f) adj1 = 1.e-6f;
  if (adj2 < 1.e-6f) adj2 = 1.e-6f;
  adj4 = fParam4 * 8.f - 4.f; // Linearity
  adj5 = fParam5 * 2.f - 1.f  ; // Asymmetry
  asymKonst = boostcomp(adj5, adj1, adj2, adj3, adj4, fParam6);
}

void wolfBoostComp::getParameterDisplay(VstInt32 index, char *text) {
  switch(index) {
    case 0:
      if (adj1 > 1.e-6f) {
        float2strng(linear2dB(adj1), text);
      } 
      else {
        strcpy(text, "-Inf");
      }
      break;
    case 1:
      if (adj2 > 1.e-6f) {
        float2strng(linear2dB(adj2), text);
      } 
      else {
        strcpy(text, "-Inf");
      }
      break;
    case 2:
      if (adj3 > 0.f) {
        float2strng(linear2dB(adj3), text);
      } 
      else {
        strcpy(text, "-Inf");
      }
      break;
    case 3:
      float2strng(adj4 * 100.f, text);
      break;
    case 4:
      float2strng(adj5 * 100.f, text);
      break;
    case 5:
      float2strng(fParam6 * 100.f, text);
      break;
  }
}

void wolfBoostComp::getParameterLabel(VstInt32 index, char *label) {
  switch(index) {
    case 0: strcpy(label, "dB"); break;
    case 1: strcpy(label, "dB"); break;
    case 2: strcpy(label, "dB"); break;
    case 3: strcpy(label, "%"); break;
    case 4: strcpy(label, "%"); break;
    case 5: strcpy(label, "%"); break;
  }
}

float wolfBoostComp::boostcomp(float signal, float drive, float threshold, 
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

//--------------------------------------------------------------------------------
// process

void wolfBoostComp::process(float **inputs, float **outputs, VstInt32 sampleFrames) {
  float *in1 = inputs[0];
  float *in2 = inputs[1];
  float *out1 = outputs[0];
  float *out2 = outputs[1];

  while(--sampleFrames >= 0) {
    *out1++ += boostcomp(adj5 + *in1++, adj1, adj2, adj3, adj4, fParam6) - asymKonst;
    *out2++ += boostcomp(adj5 + *in2++, adj1, adj2, adj3, adj4, fParam6) - asymKonst;
  }
}

void wolfBoostComp::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
  float *in1 = inputs[0];
  float *in2 = inputs[1];
  float *out1 = outputs[0];
  float *out2 = outputs[1];

  while(--sampleFrames >= 0) {
    *out1++ = boostcomp(adj5 + *in1++, adj1, adj2, adj3, adj4, fParam6) - asymKonst;
    *out2++ = boostcomp(adj5 + *in2++, adj1, adj2, adj3, adj4, fParam6) - asymKonst;
  }
}
