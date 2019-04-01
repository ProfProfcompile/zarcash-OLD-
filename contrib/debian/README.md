
Debian
====================
This directory contains files used to package zarcashd/zarcash-qt
for Debian-based Linux systems. If you compile zarcashd/zarcash-qt yourself, there are some useful files here.

## zarcash: URI support ##


zarcash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install zarcash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your zarcashqt binary to `/usr/bin`
and the `../../share/pixmaps/zarcash128.png` to `/usr/share/pixmaps`

zarcash-qt.protocol (KDE)

