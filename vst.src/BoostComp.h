#ifndef __BoostComp_H
#define __BoostComp_H

#include "audioeffectx.h"

class wolfBoostComp : public AudioEffectX
{
  public:
    wolfBoostComp(audioMasterCallback audioMaster);

    virtual bool getEffectName(char *name);
    virtual bool getVendorString(char *text);
    virtual bool getProductString(char *text);
    virtual VstInt32 getVendorVersion() { return 1000; }

    virtual void setProgramName(char *name);
    virtual void getProgramName(char *name);
    virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* name);

    virtual float getParameter(VstInt32 index);
    virtual void getParameterName(VstInt32 index, char *text);
    virtual void setParameter(VstInt32 index, float value);
    virtual void getParameterDisplay(VstInt32 index, char *text);
    virtual void getParameterLabel(VstInt32 index, char *label);

    virtual void process(float **inputs, float **outputs, VstInt32 sampleFrames);
    virtual void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
    virtual float boostcomp(float, float, float, float, float, float);



  protected:
    char programName[32];

    float fParam1;
    float fParam2;
    float fParam3;
    float fParam4;
    float fParam5;
    float fParam6;
    
    float adj1, adj2, adj3, adj4, adj5;
    float asymKonst;
};

#endif
