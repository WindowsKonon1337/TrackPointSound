mod device_discovery;
mod error;
mod mouse_device;
mod sound_player;

use device_discovery::DeviceDiscovery;
use error::Result;
use mouse_device::MouseDevice;
use sound_player::SoundPlayer;
use std::process;

fn main() {
    if let Err(err) = run() {
        eprintln!("trackpointsound: {err}");
        process::exit(1);
    }
}

fn run() -> Result<()> {
    let audio_dir = sound_player::resolve_audio_dir();
    let mut player = SoundPlayer::new(&audio_dir)?;
    let event_path = DeviceDiscovery::new().trackpoint_event_path(true)?;
    let mut device = MouseDevice::open(&event_path)?;

    loop {
        if device.is_moved()? && !player.is_playing() {
            player.play_random()?;
        }
    }
}
