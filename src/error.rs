use thiserror::Error;

#[derive(Debug, Error)]
pub enum AppError {
    #[error("failed to create udev context")]
    UdevContext,

    #[error("no device name satisfies pattern `TPPS/2.*TrackPoint`")]
    TrackpointNotFound,

    #[error("failed to open {path}: {source}\nMake sure to provide sufficient rights: sudo chmod a+r {path}")]
    DeviceOpen {
        path: String,
        #[source]
        source: std::io::Error,
    },

    #[error("directory {path} does not contain any audio files")]
    EmptyAudioFolder { path: String },

    #[error("failed to load sample from {path}: {source}")]
    LoadSample {
        path: String,
        #[source]
        source: rodio::decoder::DecoderError,
    },

    #[error("failed to open default audio output: {0}")]
    AudioOutput(String),

    #[error("{0}")]
    Other(#[from] Box<dyn std::error::Error + Send + Sync>),
}

pub type Result<T> = std::result::Result<T, AppError>;
