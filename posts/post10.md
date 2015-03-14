---
layout: post
title: File descriptor counting
date: 2012-07-01 04:03:00
tags: bash, linux, one-liners, servers
---

Yes I know I still haven't done part two of that mail server post. I'll get it done soon, I promise.

While chatting on IRC, someone mentioned that they were having a problem with a process going mental and creating a bunch of file descriptors in linux, eventually hitting the "max FD limit" linux has. They couldn't figure out which process it was and they couldn't find a program that would list a count of how many FDs a process has open. A few minutes later I'd thrown together this bash one-liner for him. I'm posting it here just in case someone else might find it useful.

```
echo "$(for pid in $(ls -a /proc|egrep '^([0-9])*$'|sort -n 2>/dev/null); do if [ -e /proc/$pid/fd ]; then FHC=$(ls -l /proc/$pid/fd|wc -l); if [ $FHC -gt 0 ]; then PNAME="$(cat /proc/$pid/comm)"; echo "$FHC files opened by $pid ($PNAME)"; fi; fi; done)"|sort -r -n|head -n4
```

To explain: It loops through every file/folder in /proc that is a process ID, then checks that there's a file descriptor folder. Then it gets a count of all the FDs that process currently holds, gets the process name and outputs how many file descriptors that process has open, as well as the process name. This is then reverse-sorted and cut down to only the four processes with the most FDs open.
