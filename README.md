BoostComp
=========

BoostComp is a Waveshaper VST plug-in

- - -

It can be use for distortion, boosting and compressing an input stereo signal.

VST source code is provided for making the plug-in working under DAW software running on both Windows and Linux.

Faust source code is included in order to obtain the source code of other plug-in formats such as lv2, ladspa, au and many more.

A copy of the VST 2.4 SDK is not included because it is not compatible with the GPL license of this plug-in.

To compile the plug-in the files adopted in the `Makefile` must be adjusted. In particular, folders are expressed in a Linux-like standards, and cross compilation of the Windows plug-in is set by default. From a termial session, type the following code
```
make all cleanobj
```
to get the shared object file of the **BoostComp** plug-in.

- - -

Win32 BoostComp.dll - KVR Audio Developer Challenge 2014

https://drive.google.com/file/d/0B4OdwW0QnH7IakIzQ3lRVGVNYUk/edit?usp=sharing

=================================================================================
LxVST 64bit BoostComp.so - KVR Audio Developer Challenge 2014

https://drive.google.com/file/d/0B4OdwW0QnH7IVFJnd00wUTdFRDg/edit?usp=sharing

=================================================================================

Luca Sartore - July 2014

