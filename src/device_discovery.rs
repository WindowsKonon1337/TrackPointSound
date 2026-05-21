use crate::error::{AppError, Result};
use std::path::PathBuf;

#[derive(Debug, Clone)]
pub struct InputDevice {
    pub name: String,
    pub event_path: PathBuf,
}

pub struct DeviceDiscovery {
    cache: Option<String>,
}

impl DeviceDiscovery {
    pub fn new() -> Self {
        Self { cache: None }
    }

    pub fn trackpoint_event_path(&mut self, use_cache: bool) -> Result<String> {
        if use_cache {
            if let Some(path) = &self.cache {
                return Ok(path.clone());
            }
        }

        let devices = discover_devices()?;
        let trackpoint = devices
            .into_iter()
            .find(is_trackpoint)
            .ok_or(AppError::TrackpointNotFound)?;

        self.cache = Some(trackpoint.event_path.display().to_string());
        Ok(self.cache.clone().unwrap())
    }
}

fn is_trackpoint(device: &InputDevice) -> bool {
    device.name.starts_with("TPPS/2") && device.name.ends_with("TrackPoint")
}

fn discover_devices() -> Result<Vec<InputDevice>> {
    let mut enumerator = udev::Enumerator::new().map_err(|_| AppError::UdevContext)?;
    enumerator
        .match_subsystem("input")
        .map_err(|_| AppError::UdevContext)?;

    let mut result = Vec::new();

    for device in enumerator
        .scan_devices()
        .map_err(|_| AppError::UdevContext)?
    {
        let Some(name) = device_name(&device) else {
            continue;
        };
        let Some(event_path) = device_event_path(&device) else {
            continue;
        };

        result.push(InputDevice { name, event_path });
    }

    Ok(result)
}

fn device_event_path(device: &udev::Device) -> Option<PathBuf> {
    let devnode = device.devnode()?;
    let path = devnode.to_str()?;
    path.starts_with("/dev/input/event")
        .then(|| PathBuf::from(path))
}

fn device_name(device: &udev::Device) -> Option<String> {
    let parent = device.parent()?;
    let name = parent.attribute_value("name")?;
    Some(name.to_string_lossy().into_owned())
}
