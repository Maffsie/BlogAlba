---
layout: post
title: The Journey of a Thousand Frustrations Begins with a Single Step
date: 2012-04-16 13:45:00
tags: bash, gentoo, linux, one-liners, rant
---

There are times when linux frustrates me. Not with issues specific to one distro, but software packages in general which are written for linux.

My prime example here is Watch. In Gentoo, it's included in the [procps package][1]. I recently was confused to find that my ident daemon, which I keep running because I'm an avid IRC user, was being flooded with traffic near constantly. Netstat told me it was because of two IRC servers I ran. So I logged in, checked netstat there, and sure enough, it was them. But I had no idea what process on the servers was actually creating the connections.

I assumed it would be the ircd itself, but I wanted proof before investigating further. No problem, I thought, I'll just run `watch --differences=cumulative -n 0.1 'lsof +M -i4|grep auth'`, which according to watch's manpage, would show what's changed in a command's output, rather than clearing the screen and displaying the output every .1 seconds. It did do this, in a way, however, because the program creating the connection to my ident server only kept that connection for a fraction of a second, the output vanished, and thanks to the unhelpful way that watch handles output which only shows up once, all I got was some white blocks showing that there had at one point been text there.

My solution? Throw together a bash one-liner which looped infinitely until the offending program was identified: `while true; do UNR=$(lsof -M -i4|grep auth); if [ -n "$UNR" ]; then echo "$UNR"; break; fi; done`

This did eventually work, and it turned out to be a runaway process on my personal box constantly creating connections to both IRC servers.

[1]: http://packages.gentoo.org/package/sys-process/procps
