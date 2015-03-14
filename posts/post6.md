---
layout: post
title: Virtual Servers and their providers
date: 2012-04-28 02:48:00
tags: benchmarks, bhost, rant, review, servers, simplexwebs, thrustvps, VPS
---

Since I figure it's bad form to have a blog and /only/ use it for ranting, here's a somewhat useful post. I've been with [a][1] [number][2] [of][3] [different][4] [hosts][5] over the past year or two, and I figure it'd be useful for others to know why I like or don't like them.

### **[SimplexWebs][6]**

SimplexWebs has been in the hosting business for quite a while now, and do enterprise webhosting, online radio hosting and domains, as well as VPS (Xen, powered by OnApp) hosting. I was lucky enough to grab one of their limited birthday sale servers, which gave you 256MB RAM, decent CPU speed, 20GB disk and 100GB monthly bandwidth, for £25 a year.

This server's basically been my primary server/main workhorse - despite initially purchasing it to run a VPN server, and has held up ridiculously well. Uptime has been fantastic - my server's only been down a few times over the last half a year or so, including migrations between their old SolusVM platform to their new OnApp platform, and including the recent downtime when they moved datacentres.

Server and network speed are _really_ good. I think this is one of the fastest servers I've ever used, and that includes the brief time I was with Linode. Support is fantastic, their team is always quick to respond and very helpful, and you definitely get the feeling that they actually care about their customers. Overall, they're one of the best hosts I've ever been with, and I don't feel I'll ever need to move to another host.

Here's some benchmarks:

Network speed:

```nohilight
~ wget cachefly.cachefly.net/100mb.test -O /dev/null
--2012-04-28 02:34:32--  http://cachefly.cachefly.net/100mb.test
Resolving cachefly.cachefly.net... 140.99.94.175
Connecting to cachefly.cachefly.net|140.99.94.175|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 104857600 (100M) [application/octet-stream]
Saving to: `/dev/null'

100%[======>] 104,857,600 11.8M/s   in 8.7s

2012-04-28 02:34:41 (11.5 MB/s) - `/dev/null' saved [104857600/104857600]
```

Disk I/O:

```nohilight
~ dd if=/dev/zero of=/tmp/disktest bs=64k count=16k
16384+0 records in
16384+0 records out
1073741824 bytes (1.1 GB) copied, 4.52632 s, 237 MB/s
```

### **[Bhost][7]**

Bhost are a UK-centric VPS provider, primarily dealing with OpenVZ servers although they've recently launched Xen PV plans. I should mention their servers are some of the cheapest you can get, the cheapest OpenVZ server being £4.70 (before VAT) and including 512MB RAM and 512MB burst RAM.

Their support is pretty great, considering they're a budget host, and the servers themselves are quite speedy. I do have some issues with the OS templates they have available - their Arch images are broken due to the host kernel being too old, although I'd say that's an Arch issue, and their Gentoo image is too old to actually use. Debian works fine though, so that's what I'm using. Overall, network and server speed is _really_ good. Uptime is fantastic, in the entire time I've been with them (a number of months now), my server's almost never been down. Definitely one of the most reliable hosts I've been with.

Here's some benchmarks, since I still have a server with them: Network speed:

```nohilight
# wget cachefly.cachefly.net/100mb.test -O /dev/null
--2012-04-28 02:30:40--  http://cachefly.cachefly.net/100mb.test
Resolving cachefly.cachefly.net... 205.234.175.175
Connecting to cachefly.cachefly.net|205.234.175.175|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 104857600 (100M) [application/octet-stream]
Saving to: `/dev/null'

100%[======>] 104,857,600 10.2M/s   in 9.8s

2012-04-28 02:30:49 (10.2 MB/s) - `/dev/null' saved [104857600/104857600]
```

Disk I/O:

```nohilight
# dd if=/dev/zero of=/tmp/disktest bs=64k count=16k
16384+0 records in
16384+0 records out
1073741824 bytes (1.1 GB) copied, 8.31944 s, 129 MB/s
```

### **[ThrustVPS][8]**

This was actually the first VPS host I'd ever been with. I found them after browsing [LowEndBox][9], and was interested by their very low pricing. Their website design made me feel like they were a good host, and so I bought a server there (Xen HVM, 512MB RAM, 1TB bandwidth, four cores). The setup time really should've indicated something, though, as it took somewhere between a day or two before my server actually got provisioned.

The speed of the server itself was reasonably good - network speed was great (Less ThrustVPS's doing and more that it's just a good datacentre in general), disk I/O and general performance was good. It never felt _speedy_, but it got the job done without delay. Uptime was, for the most part, good. It wasn't often down, and when it was, it was down for less than an hour at most. I quickly learned (through talking with others in their IRC channel - #thrustvps on OFTC) that this was a rarity, and that I was on one of their "good" nodes. Complaints of servers being down were oddly common. Their support was nothing really to write home about. It was neither good nor bad. Your issues did get resolved (eventually - by someone who usually had less than stellar english skills), but you never got the feel that they actually cared.

My main issues with ThrustVPS started in September, when I got an email stating that the node my server was on, had experienced some issues and they were investigating it. After it came back online, my server was left without internet connectivity. Nothing was wrong as far as I could see, so I emailed their support asking what was wrong. Eventually I was told that the connectivity issue had been resolved, though no explanation about what happened was ever given. 9 days later, the same thing happened again - Node went down, my server had no connectivity when it came back. I emailed support again, and was eventually told that I'd been DDOSed and that my server's IP had been null-routed. I explained to them that I had done nothing to warrant an attack, and asked if they were sure - as I could find absolutely no evidence that this was actually the case. Their support claimed that what they were saying was true, and refused to restore connectivity until I reinstalled my server's operating system. So I backed up the data on my server to a separate drive, quick-installed Debian, got them to restore connectivity and then sent my backup to another server.

In summary, while the servers and prices themselves are good, uptime is a bit unpredictable, support is unpleasant and they seem to have a habit of restricting your server without explanation, or without supplying any actual evidence to back up their claims. I wouldn't recommend them to anyone.

[1]: http://thrustvps.com
[2]: http://linode.com
[3]: http://bhost.net
[4]: http://simplexwebs.com
[5]: http://vps6.net
[6]: http://www.simplexwebs.com
[7]: http://www.bhost.net
[8]: http://www.thrustvps.com
[9]: http://lowendbox.com
