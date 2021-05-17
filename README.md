# D7049E-Game-Engine
A game engine created for the course Virtual Interactive Environments D7049E

## For the audio system
To be able to listen to the soundeffects you will need to download 2 libraries. The first one is openAL which is a 3D audio API and the second one is libsndfile which ables openAL to basically load the data into the sound file. The easiest way to do this is via a package manager vckpg. 

Step 1: Clone the repository in the desired directory

```
git clone https://github.com/Microsoft/vcpkg.git
```
Step 2: Run the bootstrap script to build vcpkg

```
.\vcpkg\bootstrap-vcpkg.bat
```
Step 3: Download the openAL library for 64-bit windows

```
vcpkg install openal-soft:x64-windows
```
Step 4: Download the libsndfile library for 64-bit windows

```
vcpkg install libsndfile:x64-windows
```
Step 5: Integrate vcpkg with Visual Studio

```
vcpkg integrate install
```
After this all installed libraries should already be discoverable by IntelliSense and usable in code without additional configuration.