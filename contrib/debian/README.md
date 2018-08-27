
Debian
====================
This directory contains files used to package bitcoin5000d/bitcoin5000-qt
for Debian-based Linux systems. If you compile bitcoin5000d/bitcoin5000-qt yourself, there are some useful files here.

## bitcoin5000: URI support ##


bitcoin5000-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoin5000-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoin5000-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin5000128.png` to `/usr/share/pixmaps`

bitcoin5000-qt.protocol (KDE)

