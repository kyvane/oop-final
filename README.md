# Two-Deck DJ Player

A DJ application built with JUCE and C++. Two independent decks play at the same time and are mixed to stereo output. Each deck has transport controls, a waveform, a three-band EQ, and a reverb section.

## Features

Each deck can:

- Load an audio file with **LOAD**, or by dragging a file onto the deck
- Play and stop the loaded track
- Scrub position with the position knob
- Adjust volume and playback speed
- Shape the tone with **HIGH**, **MID**, and **LOW** EQ knobs
- Shape space with reverb: wet level, dry level, damping, room size, freeze, and width
- Show the waveform and a moving playhead

Both decks share one mixer, so they play together through the same output.

## Requirements

This folder is source code. There is no `NewProject.exe` until you compile it.

- JUCE
- Visual Studio 2022 (Windows), Xcode (macOS)

## How to use

1. Launch the app. The window is split into a left deck and a right deck.
2. Click **LOAD** on a deck and choose a file, or drop a file onto that deck. The waveform appears when the file loads.
3. Click **PLAY** to start. The button label switches to **STOP**. Pressing play with nothing loaded shows a warning.
4. Turn **VOL** and **SPEED**, and drag the position knob to jump through the track. The position knob follows playback.
5. Use the EQ and reverb knobs on that deck. The other deck is independent, so you can mix two tracks.