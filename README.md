# Void - Public Code Release
### Preface
Void is an internal cheat made for VRChat in C++. Void was discontinued in August of 2022 due to the implementation of Easy Anti-Cheat. I decided it would be smarter to focus more on my education and University work rather than playing cat-and-mouse with EAC. 
### Notes
* This code is licensed under the GNU GPLv3 license, meaning you can do anything you want with the code, but it ***cannot be closed source***. Please contact me for permission if you would like to use some of this code in a closed source project at a@uwu.me.
* If you open this in Visual Studio, do not use VS's filters, instead make sure you click to "Show All Files" box.
* Authentication & server communication is omitted.
* VMProtect SDK is omitted.
#### Credits
* [autumn](https://github.com/autumncpp) - developing void
* [ocornut](https://github.com/ocornut) - imgui maintainer
* [rollraw](https://github.com/rollraw) - imgui styles, color class, & a couple memory related classes
* [stellar](https://github.com/ImStellar) - emotional support & helped with some photon related stuff
* darktrix, josh, poison, regan, unixian, jordan - best staff team i could've asked for

## Information
Void is a massive code-base, navigating it can be confusing.

Client functionality can be found inside *core/hooks/events.cpp*\
Engine anti-crash implementation can be found inside *core/hooks/patches.cpp*\
Non-Engine anti-crash implementation can be found inside *core/hooks/helpers/assetbundle_processor.cpp*\
Photon anti-crash implementation can be found inside *core/hooks/events.cpp* & *core/hooks/eventmap.cpp*

Game & Engine class reflection can be found inside *core/assembler/*\
Mono reflection can be found inside *core/assembler/mono/*\
Mono Dumper can be found inside *core/assembler/mono/mono.cpp*\
IL2CPP reflection can be found inside *core/assembler/il2cpp/*

QuickMenu implementation can be found inside *core/assembler/vrc/modules/*\
Desktop Menu implementation can be found inside *core/menu.cpp*

## Final Words
It's been real. Enjoy.
