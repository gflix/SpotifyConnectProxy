# SpotifyConnectProxy

## Purpose

A lot of network attached media players, audio-video receivers and loudspeakers offer a service called
"Spotify Connect" which allows smartphone, tablet or PC based Spotify clients to use such a device for
playback. The Spotify client discovers capabable devices by using multicast DNS (mDNS) queries.

As a matter of fact the mDNS messages are bound to a single network section and are not routeable. If a network
is split up into several segments (i.e. using VLANs) Spotify clients in one segment could not connect to
devices located in an other segment.

This is where this proxy came in. It queries for Spotify Connect capable devices in one network segment and
proxies the information to one or more other network segments. Clients are now able to discover these devices
and if firewall configuration permits may connect to them to use them as playback devices.

## What it is not

This proxy does not interfer with Spotify internal information, does not connect to any Spotify services nor
does it try to break any security related features.

## Build instruction

To build the Debian package (Debian, Ubuntu and its derivatives) do the following after checking out the sources
and entering the directory to which the sources have been checked out:

```
$ sudo apt install debhelper cmake libsystemd-dev pkg-config
$ dpkg-buildpackage -uc -us -b
```

The package can then be installed by using the following command:

```
$ sudo dpkg -i ../spotify-connect-proxy*.deb
```

## Configuration

The service is configured through a file located at `/etc/default/spotify-connect-proxy`. See the
comments within that file for configuration.

## Tested environment

- AVR receiver: Denon AVR-X1800H

- Spotify clients: Android app, Linux desktop app

## To do

Google Chromecast seems to use similar information and could be integrated as well; actually discovery works but
no connection could be established and needs further investigation.
