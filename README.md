BuskMagic - Live lighting control system
Copyright (C) 2019 Sauraen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

Art-Net™ Designed by and Copyright Artistic Licence Holdings Ltd.

# Overview

BuskMagic is an open-source program for Windows, Mac OSX, and Linux that lets
you control lighting effects live, in real time, during a show. It is designed
primarily for fully live performance--where you do not have the opportunity to
build specific looks or cue stacks ahead of time, but have to improvise the
lighting along with music or other performance. This is known as "busking".

# Input/Output

BuskMagic outputs lighting data over Art-Net, which is a UDP-based protocol
for carrying lighting data over networks (typically ethernet). The destinations
can be Art-Net nodes which you purchase or build, or other lighting controllers
or software. BuskMagic does not have any artificial limitations on the number
of universes addressed--it supports the same 32,768 universes Art-Net does. The
practical limit on the number of universes is your CPU power--and your budget
for buying Art-Net nodes (and fixtures)! BuskMagic is optionally Art-Net 4
compliant, supporting the handshaking and remote addressing schemes; or 
optionally non-compliant on a per-node basis, in which case it will skip the 
handshaking and just send DMX data to the selected IP address.

While BuskMagic may be fully controlled just from a computer, it is intended to
be controlled from one or more MIDI controllers, which can be mapped to virtual
"controllers" (buttons and knobs) in the interface. Any MIDI controllers which
are visible by your operating system's MIDI API are supported--this is typically
USB MIDI controllers/keyboards or dongles to convert to/from old-style MIDI.
Control is typically bidirectional, where buttons and knobs/faders set values in
BuskMagic, and BuskMagic sends the state of the controls back to the hardware
controller to set LEDs or move motorfaders. Unidirectional control is also
supported but you may run into issues using certain features.

# Design Philosophy

Typical lighting control systems are based on "cues", which contain states of
parameters for a subset of the fixtures. These cues are combined into cue
stacks, and hardware buttons/faders control the execution of these cue stacks.
While this model is perfect for theater situations and music performances which
are prepared for in advance, this model can be very restrictive when trying to
come up with effects live for a performance.

In contrast, BuskMagic allows you to map your hardware control elements
(buttons/knobs/faders/etc.) to parameters of groups of fixtures. There is no
"programmer" where parameters have to be carefully captured into--the state of
your buttons and knobs directly determines the stage output. Then, there is a
concept of "states", which are effectively "state saves" of the positions of all
your buttons and knobs. When you load a state, the states of all your
controllers change, and therefore the stage output changes too. You can directly
begin editing the state further from there. You can also use "blind" to cause
your control surface to switch to a different state for editing, while the stage
remains on the original state.

# A Dash of Magic

A show in any lighting software is full of "values"--e.g., press a button and
a certain set of dimmers get set to 0.5. In BuskMagic, a value like "0.5" here
is a "MagicValue". This means, the value may be a literal number such as 0.5,
or it may be the output of a channel. Normally, fixtures have channels, such as
dimmer or gobo, which you connect your controllers to. But, you can also create
"free channels", not associated with any fixture, which may be used as the
source for MagicValues throughout your showfile. This allows for an almost 
unlimited amount of controllable dependencies and metaparameters of the effects
you are creating--since these channels are driven by controllers, and those
controllers can have other MagicValues, and so on.

For example, suppose you create a modulator which fades a group of fixtures back
and forth between green and blue. You could enter 0.5 (hue green) and 0.75 (hue
blue) into the "HiValue" and "LoValue" of the modulator. However, if you then
wanted to change the green to yellow--so that the fade was now yellow to
blue--in this case you would have to manually change the 0.5 to 0.25 (hue
yellow). Instead, you could create two free channels, called "Color A" and
"Color B" or whatever you wanted to name them, and set the modulator's "HiValue"
to "Color A" and "LoValue" to "Color B". Then, you can set up additional buttons
or knobs to control what "Color A" and "Color B" are, which would allow you to
change "Color A" within the fading effect from green to yellow live. Of course
this also means you can have "Color A" be the output of another modulator--and
this can go as many layers deep as you like!
