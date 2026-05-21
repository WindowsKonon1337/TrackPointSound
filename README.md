# TrackPoint Sound

## Description
This project is a more serious implementation of a comic program for playing sound when touching a trackpoint.

Rust rewrite: device discovery via **libudev**, input events via **evdev**, playback via **rodio** (mp3, wav, ogg, flac, and more).

## dependencies

Arch-based (x86_64)

* `systemd-libs` (libudev) — trackpoint discovery
* `alsa-lib` — audio output (rodio/cpal)
* build: `rust`, `cargo`, `pkgconf`, `libudev`

```bash
sudo pacman -S systemd-libs alsa-lib rust cargo pkgconf libudev
```

* Will be installed with the AUR package

## Installation

* Arch(btw)-based

  ```bash
  yay -S trackpointsound
  ```

* manual (from source)

  ```bash
  git clone https://github.com/WindowsKonon1337/TrackPointSound.git
  cd TrackPointSound
  ./build.sh install          # PREFIX=/usr/local, copies audio to ~/.trackpointsound/
  # or system-wide:
  sudo ./build.sh install PREFIX=/usr
  ```

  Audio lookup order: `~/.trackpointsound/audio/` (if not empty), then `/usr/share/trackpointsound/audio/`.

  or:

  ```bash
  cargo install --path .
  mkdir -p ~/.trackpointsound && cp -r audio ~/.trackpointsound/
  ```

## possible problems

1. **No access to the trackpoint device** — you need read access to `/dev/input/event*`:

   ```bash
   sudo chmod a+r /dev/input/eventN   # N = your trackpoint event number
   ```

   or add your user to the `input` group (re-login required).

2. **Empty audio folder** — the program exits if `~/.trackpointsound/audio/` has no supported audio files.

3. **Trackpoint not found** — the device name must match `TPPS/2.*TrackPoint` (common on ThinkPads).

## Configuration

configuration folder is located at `~/.trackpointsound`

Put custom samples in `~/.trackpointsound/audio/` to override the package defaults from `/usr/share/trackpointsound/audio/`.

## AUR packaging

Draft [`aur/PKGBUILD`](aur/PKGBUILD) is included. Before publishing:

1. Create a git tag `v0.2.0` (version in `Cargo.toml`).
2. Update `sha256sums` in the PKGBUILD (`makepkg -g`).
3. Generate `.SRCINFO` (`makepkg --printsrcinfo > .SRCINFO`).
