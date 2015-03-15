---
title: UnrealIRCd and SANICK
date: 2012-07-22 03:17:00
tags: C, development, irc, servers, unrealircd
---

I know, I still haven't done that mail server post. It's coming.

I just wanted to quickly write a post about a module I've just finished working on for UnrealIRCd 3.2.x.

Unreal has the `m_svsnick` module, which is specifically meant to be used by U-lined servers, such as IRC services. This module facilitates the forced changing of nicks. Other IRCd's have a command like that built-in and usable by regular opers, but not Unreal. The reasoning for this is that such a command could easily be abused, and the management of nicks is Services' job anyway. This is all fine and dandy as some IRC services packages such as Anope come with an SVSNICK command available in operserv by default, and other services packages may have 3rd-party modules to add such a command. However, what if you're running UnrealIRCd and Atheme 6.x? Unreal has no user-accessable SVSNICK command, and atheme doesn't have such a command either. That's where the subject of this post comes in.

I've just finished working on `m_sanick.c`, a module which adds a SANICK command, accessible by IRC opers, which force-changes a given user's nick.

### Download

You can download the module source here: [m_sanick.c][1]

Source is licensed under the GPL, original code by Mouse, some code used by this module was pulled from `m_svsnick.c`.

### Installation

* Download the module to `src/modules/m_sanick.c` in the Unreal3.2 source directory
* `./Config` and `make` unreal as normal, if you haven't already done so or if the source directory is completely clean
* Run `make custommodule MODULEFILE="m_sanick"`
* Copy the resulting .so (which will be at `src/modules/m_sanick.so`) to the Unreal modules directory. If you installed unreal as a package, it'll probably be `/usr/lib/unrealircd/modules`. If you compiled unreal yourself, the modules directory will be in the unreal configuration directory you set during configuration. This is usually inside the source directory or at `/etc/unrealircd/modules`.
* Add `loadmodule "/your/module/directory/m_sanick.so";` to your unrealircd.conf
* `unreal rehash` your server.

If you run an Unreal-based network with multiple servers, you'll need to repeat this process in full on every server.

### Usage

Once installed, run `/sanick TargetNick NewNick` where TargetNick is the nick you wish to change, and NewNick is the nick you wish to change the user's nick to.

If this does not work, `/quote sanick TargetNick NewNick` should work. In irssi, you will have to use this command instead. Alternatively, in irssi, you can use [dispatch.pl][2] or add sanick as an alias with the following command: `/alias sanick quote sanick`

### Disclaimer

The original source was written by Mouse, and was modified by myself in order for it to compile and function correctly. The "CHGNICK" function was removed. Parts of this module are copyright to Mouse and the UnrealIRCd dev team. I am not liable under any circumstance for any damage, service disruption or any other issues that may arise during the installation or use of this module. This module contains no malicious code and is freely downloadable and may be modified by anyone. This module is in use on at least one production IRC network, however no guarantees are made as to the module's stability. Use at your own risk. This module will not work on other IRCd's and may not work on older (3.2.8 or older) versions of UnrealIRCd.

This module is an unofficial third-party module and is unsupported. However if you experience issues while compiling or using this module, please [email me](/about) and I'll try to help as best I can.

[1]: https://pub.maff.scot/code/m_sanick.c
[2]: http://scripts.irssi.org/scripts/dispatch.pl
