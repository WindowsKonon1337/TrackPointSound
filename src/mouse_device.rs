use crate::error::{AppError, Result};
use evdev::{Device, InputEventKind, RelativeAxisType};

pub struct MouseDevice {
    device: Device,
}

impl MouseDevice {
    pub fn open(path: &str) -> Result<Self> {
        let device = Device::open(path).map_err(|source| AppError::DeviceOpen {
            path: path.to_owned(),
            source,
        })?;
        Ok(Self { device })
    }

    pub fn is_moved(&mut self) -> Result<bool> {
        for event in self.device.fetch_events().map_err(|source| AppError::DeviceOpen {
            path: "trackpoint event device".to_owned(),
            source,
        })? {
            if let InputEventKind::RelAxis(axis) = event.kind() {
                if matches!(axis, RelativeAxisType::REL_X | RelativeAxisType::REL_Y)
                    && event.value() != 0
                {
                    return Ok(true);
                }
            }
        }
        Ok(false)
    }
}
