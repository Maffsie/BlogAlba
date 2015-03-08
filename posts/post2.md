---
layout: post
title: The case for not using Arch
date: 2012-02-28 17:04:00
tags: arch, arch linux, linux, rant, sysadmin
---

I run a number of different servers from a number of different providers. I also run servers for friends. In this post, I'll be discussing one server in particular, a friend's server that's primarily used for IRC, web hosting and minecraft. This server runs Arch.

Now I'm going to start by saying I don't always make fantastic decisions and I'm not always known for making sure everything's perfect before rebooting a server. I have, in the past, screwed servers up. But this case was a little different.

Yesterday I log into the server to update a firewall rule, and discover that, because I've never used the nat table in iptables before on that box, the module was never loaded. Of course, the box has fantastic uptime and hasn't been rebooted in over 160 days. Now I'll stop for a second to mention how Arch handles kernel upgrades. When the kernel's upgraded, the previous kernel is left on the system, and all kernels older than that are removed completely. This includes the currently running kernel, and all modules. And this box hadn't been rebooted since kernel 3 was released. I have the box set up to be as zero-maintenance as possible. Emails whenever anything happens, cronjobs taking care of updates and removal of old packages from the cache, scripts to reboot any services that have crashed, gone down or have stopped responding. But as I discovered during a routine check a week prior, the Arch box hadn't been upgrading any of its packages due to a [ recent change][1] to the filesystem package. I manually started the update process, it informed me that it couldn't upgrade the system because of a file conflict (as the news article mentioned). No problem, I force-installed the update to filesystem and then upgraded the rest of the system as usual.

Now fast-forward back to yesterday, I'm telling my friend I need to reboot his server to apply the firewall rule. He gives the okay, and I reboot the server. Emails flood in saying that various services are down and that the server's offline, as always. But then a few minutes pass, there's no email that everything's back online again. I ping the server, nothing. Log into the server host's control panel, it's listed as online, so I VNC into it to see what the issue is. It can't find the harddrive and has thrown itself into a recovery terminal. What.

I figure a kernel change has messed with the partitions, so I boot the server into my usual recovery system - the gentoo live CD. Nothing seems out of place with grub or the fstab, so I look at the next culprit - the config file for mkinitcpio. It's blank.

Somehow, pacman disregarded the usual rules about protecting config files against being overwritten and messed with the config file, so the initramfs Arch needs in order to boot up properly was completely broken. No problem, I'll just chroot in -- OH WAIT. The Gentoo LiveCD runs kernel 2.6.31, and arch refuses to do /absolutely anything/ unless the kernel is new enough (In this case it had to be 2.6.32 or newer). The server host isn't exactly good, and doesn't provide any recent install media. Cue ten minutes of me googling for the kernel versions of everything in the media list, eventually settling for a Fedora 13 disk that had a recent-enough kernel. I get chrooted in, fix the mkinitcpio config and start generating the images. It complains that /dev isn't mounted. Okay. I look at the source for mkinitcpio, discover it's trying to access /dev/fd, which somehow doesn't exist. I symlink it over from /proc/self/fd and start it again. Everything seems to work, so I reboot.

This time, it recognises the hard drive, but the partition device names have changed. It's now seeing the disk as /dev/xvda. Bizarre, but has happened before. I boot the gentoo livecd again, edit grub's menu.lst and fstab, reboot back into Arch. It boots! But doesn't have a network connection. By this point, I'm close to pulling out my hair. I google around and find that because I included a bunch of xen drivers that mkinitcpio forgot before, everything's working a little differently. Specifically, it now works closer with Xen, and is trying to unplug everything at boot. No problem, I'll put `xen-emul-unplug=none` in the kernel boot line. Reboot the server and the harddrive device name has changed again. I boot into gentoo, change menu.lst and fstab to use /dev/sda again, and reboot.

Finally, the server's booted and has a network connection. And this is why I no longer install arch on any of my boxen. I can't trust it to reboot without throwing a hissy fit and killing itself.

**TL;DR Arch package issue sends me on an hour-long crusade to make a box boot again.**

[1]: http://www.archlinux.org/news/filesystem-upgrade-manual-intervention-required/
