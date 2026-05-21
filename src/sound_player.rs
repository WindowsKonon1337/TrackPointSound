use crate::error::{AppError, Result};
use rand::prelude::IndexedRandom;
use rodio::{Decoder, OutputStream, OutputStreamHandle, Sink};
use std::fs::{self, File};
use std::io::BufReader;
use std::path::{Path, PathBuf};

const AUDIO_EXTENSIONS: &[&str] = &["mp3", "wav", "ogg", "flac", "aac", "m4a"];

const SYSTEM_AUDIO_DIR: &str = "/usr/share/trackpointsound/audio";

pub fn resolve_audio_dir() -> PathBuf {
    if let Ok(home) = std::env::var("HOME") {
        let user_dir = PathBuf::from(home).join(".trackpointsound/audio");
        if has_samples(&user_dir) {
            return user_dir;
        }
    }
    let system_dir = PathBuf::from(SYSTEM_AUDIO_DIR);
    if has_samples(&system_dir) {
        return system_dir;
    }
    std::env::var("HOME")
        .map(|home| PathBuf::from(home).join(".trackpointsound/audio"))
        .unwrap_or(system_dir)
}

pub fn has_samples(dir: &Path) -> bool {
    collect_samples(dir)
        .map(|samples| !samples.is_empty())
        .unwrap_or(false)
}

pub struct SoundPlayer {
    _stream: OutputStream,
    stream_handle: OutputStreamHandle,
    samples: Vec<PathBuf>,
    current_sink: Option<Sink>,
}

impl SoundPlayer {
    pub fn new(audio_folder: impl AsRef<Path>) -> Result<Self> {
        let audio_folder = audio_folder.as_ref();
        let samples = collect_samples(audio_folder)?;

        if samples.is_empty() {
            return Err(AppError::EmptyAudioFolder {
                path: audio_folder.display().to_string(),
            });
        }

        let (_stream, stream_handle) =
            OutputStream::try_default().map_err(|e| AppError::AudioOutput(e.to_string()))?;

        Ok(Self {
            _stream,
            stream_handle,
            samples,
            current_sink: None,
        })
    }

    pub fn is_playing(&self) -> bool {
        self.current_sink
            .as_ref()
            .is_some_and(|sink| !sink.empty())
    }

    pub fn play_random(&mut self) -> Result<()> {
        let path = self
            .samples
            .choose(&mut rand::rng())
            .expect("samples checked non-empty in constructor")
            .clone();

        let file = File::open(&path).map_err(|e| AppError::Other(e.into()))?;

        let source = Decoder::new(BufReader::new(file)).map_err(|source| AppError::LoadSample {
            path: path.display().to_string(),
            source,
        })?;

        let sink = Sink::try_new(&self.stream_handle)
            .map_err(|e| AppError::AudioOutput(e.to_string()))?;
        sink.append(source);
        self.current_sink = Some(sink);

        Ok(())
    }
}

fn collect_samples(dir: &Path) -> Result<Vec<PathBuf>> {
    let mut samples = Vec::new();

    for entry in fs::read_dir(dir).map_err(|e| AppError::Other(e.into()))? {
        let entry = entry.map_err(|e| AppError::Other(e.into()))?;
        let path = entry.path();
        if !path.is_file() {
            continue;
        }
        if let Some(ext) = path.extension().and_then(|e| e.to_str()) {
            if AUDIO_EXTENSIONS
                .iter()
                .any(|supported| ext.eq_ignore_ascii_case(supported))
            {
                samples.push(path);
            }
        }
    }

    samples.sort();
    Ok(samples)
}
