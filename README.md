# TrackPoint Sound

## Description
This project is a more serious implementation of a comic program for playing sound when touching a trackpoint
## dependencies
* sfml == 2.6.2-1 (or less than 3.0) CHECK THE SFML VERSION
  
  Ubuntu
  ```bash
  sudo apt install libsfml-dev libudev-dev 
  ```
CHECK THE SFML VERSION
  
  Arch-based
  
  *   Will be installed with the aur package

## Installation
* Arch(btw)-based 
  ```bash
  yay -S trackpointsound
  ```
* Ubuntu-based (manual installing)
```
git clone https://github.com/WindowsKonon1337/TrackPointSound.git
cd TrackPointSound
cmake -B ./build -S .
cd build/TrackpointSound && make
sudo cp TrackpointSound /usr/bin/trackpointsound
sudo chmod +x /usr/bin/trackpointsound
mkdir -p ~/.trackpointsound
cp -r ./audio ~/.trackpointsound
```

## possible problems
1. For Ubuntu 22.04 and below, the apt repository contains a version of sfml that does not support mp3 playback. It is recommended that when adding your audio, use a supported format, or manually compile a more recent version of the library



## Configuration

configuration folder is locates at ~/.trackpointsound

At the moment it only contains the audio folder, from which samples are taken for playback
