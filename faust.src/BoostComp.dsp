declare name "BoostComp";
declare author "Wolf Sound";
declare version "0.01";
declare copyright "2014";

//define the boostcomp from an header file
boostcomp = ffunction(float boostcomp(float, float, float, float, float, float, float), "BoostComp.h", "-lm");

// set the agrument of the filter
drive = hslider("Drive", 1, 1e-6, 4, 1e-6);
threshold = hslider("Threshold", 1, 1e-6, 4, 1e-6);
gain = hslider("Gain", 1, 0, 4, 1e-6);
linearity = hslider("Linearity", 0, -4, 4, 1e-6);
asymmetry = hslider("Asymmetry", 0, -1, 1, 1e-6);
wet = hslider("Wet", 1, 0, 1, 1e-6);

// Signal processing
psig(x) = boostcomp(x, drive, threshold, gain, linearity, asymmetry, wet);

// return the signal process
process(l, r) = psig(l), psig(r);
