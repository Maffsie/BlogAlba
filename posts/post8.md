---
layout: post
title: How to set up effective mail systems, pt. 1
date: 2012-06-11 00:31:00
tags: gentoo, guide, howto, linux, mail, postfix, servers, sysadmin
---

So a few months ago, I moved my primary mail hosting to my own VPS. Over the months since then, I've been tweaking and adding to my mail system, and I figure it'd help both myself and others if I documented what I've done, so I'll start with a list of all the software I use.

### Main Software

* **Gentoo** – My VPS runs **Gentoo**. I personally prefer it over other distros, as it's both lighter and less screwed up.
* **postfix** – I was originally going to use **Exim**, but found it strangely difficult to configure, plus **postfix** seems to universally have lower transaction times.
* **dovecot 2** – I'm switching away from **Gmail**, so obviously the things I would've missed most would be things like push email and mail filters. Dovecot supports IMAP IDLE, and has sieve/managesieve, so it was easy to port my Gmail filters over.
* **saslauthd** – While dovecot has its own SASL authentication, I prefer to use this when authenticating over SMTP. **EDIT:** I have since switched from **saslauthd** to Dovecot 2 for SASL authentication. Dovecot works well enough for it that I questioned why I actually needed **saslauthd**.
* **Mutt** – Mutt is my primary MUA. I'll also be discussing configuration changes I made to **Mutt**, and ways I made it work more like **Gmail**.

### Extra Software

* **Spamassassin** – This should be obvious. Does a great deal to cut down on spam. Plus, with a filter set up with **dovecot**'s sieve, I have a spam folder like before. **EDIT:** When I first published this post, I had only just set up **Postgrey** and had no idea what kind of impact it would have on incoming spam/junk mail. It had a massive impact – I haven't received a single spam email since. **Spamassassin** and **Amavisd** may actually be unnecessary when using **Postgrey** (Unless of course you plan to host mail for others, or if you receive a \*lot\* of spam).
* **Postgrey** – This does a fantastic job of cutting down on spam.
* **Amavisd** – Somewhat necessary for making **postfix** work with **SpamAssassin**, but also makes it easy to offload the antispam part of the mail system to another server. **Amavisd** can also be used for integrating antivirus systems into your mail scanning process, but I don't need that.
* **OpenDKIM** – Used for signing outgoing mail with my DKIM key, and for validating incoming signed mail. This does a good job of ensuring that mail sent from my domain is actually coming from one of my servers.
* **policyd-spf** – Originally, I used **pypolicyd-spf**, but it quite literally breaks every time there's an update to python, it's since been replaced with [this perl equivalent][1] which has never had any issues. This uses SPF to validate incoming mail, and ensure that the sending server is actually authorised to send mail for the given domain.
* **fail2ban** – This isn't strictly part of the process I go through when setting mail up, but **fail2ban** helps cut down load a lot when bots are trying (and failing) to use a server as an unauthenticated relay.

In the near future, I'll write a second post detailing how I linked all this together, including config excerpts, but in this post I'm just discussing the software I used, as well as why I use each package. I'll also leave you with a list of extremely good tips.

* **Get an SSL certificate.** This makes setting secure mail up a **lot** easier, especially if you plan to send or receive mail remotely with stuff like IMAP.
* If you do get an SSL certificate, **disable or firewall unencrypted mail ports**. Obviously leave port 25 in place, but if you're sending or receiving mail remotely, disable the unencrypted IMAP/POP3 ports (143 for IMAP and 110 for POP3), and set your MTA up to only accept submission mail through 465.
* **Set up SPF records for your domain appropriately**. SPF does a good job of telling other mail systems who is or is not allowed to send mail for your domain.
* **Generate a DKIM key, and add it to your domain's DNS**. As with SPF, DKIM (DomainKeys Identified Mail) does a fantastic job of indicating to other mail systems whether an email is actually legitimate or not.
* **Use blacklists**. There's a large number of DNS-based blacklists which indicate whether a given IP address is known for sending spam or for attempting to compromise servers. This can go a long way in preventing spam.
* **Report any spam you receive.** Reporting received spam to places like **SpamCop** not only reduces the chance of you receiving similar spam in the future, but it helps others too. It helps identify servers that send spam (Contributing to blacklists), helps identify possible domains used for spam (again, contributing to blacklists), and can contribute to the accuracy of antispam systems like **SpamAssassin**.
* **Monitor your services extensively**. This is definitely a big one. It's not easy to monitor your server by looking at logs, and often unless you've got systems set up to email you when anything out of the ordinary happens, you just plain don't know what's happening with your server. Packages like [**Monitorix**][2] (disclaimer: I'm the package maintainer for **monitorix** on **Gentoo**), do a fantastic job of showing you at-a-glance whether anything abnormal is happening, so it's easy to see if and when your mail server is rejecting mail. This can also be great for indicating when you've misconfigured something.
* **Use external monitoring services**. Services like [**MXToolbox**][3] have free accounts, and you can use them to set up checks so that you get an email if your server's IP is on any IP blacklists. Services like [**Pingdom**][4] are also great for monitoring both uptime and external availability.
* **Make sure your forward and reverse DNS match** and that your reverse DNS is your primary mail domain (or what your server actually identifies itself as). This is definitely a good way of ensuring your mail isn't identified as spam.

One final thing to note, the guide and so on will discuss **my** current mail setup. This means it assumes you'll be using sockets for things like **Postgrey**. Please read everything carefully before making configuration changes to your own mail setup, as what works for me may not work for you.

That's all for now, but I'll be adding to this list, and writing a second post documenting how I actually set my mail system up, very soon. **EDIT:** Disregard that. Second part of this post will arrive _eventually_ but I am tremendously lazy.

[1]: https://launchpad.net/postfix-policyd-spf-perl/
[2]: http://www.monitorix.org/
[3]: http://mxtoolbox.com/
[4]: http://www.pingdom.com/
