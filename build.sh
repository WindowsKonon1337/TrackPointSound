#!/bin/sh
set -eu

PREFIX="${PREFIX:-/usr/local}"
DESTDIR="${DESTDIR:-}"

cargo build --release

install_files() {
    install -Dm755 target/release/trackpointsound "$DESTDIR$PREFIX/bin/trackpointsound"
    install -dm755 "$DESTDIR$PREFIX/share/trackpointsound/audio"
    install -m644 audio/* "$DESTDIR$PREFIX/share/trackpointsound/audio/"

    if [ -z "$DESTDIR" ] && [ -n "${HOME:-}" ] && [ "$PREFIX" = "/usr/local" ]; then
        mkdir -p "$HOME/.trackpointsound"
        cp -rn audio "$HOME/.trackpointsound/"
    fi
}

case "${1:-build}" in
    build) ;;
    install) install_files ;;
    *)
        echo "usage: $0 [build|install]" >&2
        echo "  build   — compile release binary (default)" >&2
        echo "  install — install binary and audio (PREFIX=$PREFIX)" >&2
        exit 1
        ;;
esac
