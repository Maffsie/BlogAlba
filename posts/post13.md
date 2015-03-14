---
layout: post
title: Why I love lighttpd
date: 2012-09-04 00:35:00
---

It's a well-known fact that I absolutely adore lighttpd. Why, you ask?

I run lighttpd on a small cluster of web servers that serve a mix of static and dynamic content. One web server is dedicated to serving static content, and the other two are dedicated to serving dynamic content. The average memory use across all three is around 3.5MB. Average CPU use is almost zero.

But it's not just the low resource usage that I love about lighttpd. It's the downright gorgeous configuration syntax.

We recently began rolling out proper SSL to all of our client-accessable services at work. We're primarily an Apache shop at work, but one server runs lighttpd. Forcing all connections to run over SSL was as simple as:

```
server.modules += ("mod_redirect")
$HTTP["scheme"] == "http" {
	$HTTP["host"] =~ "(.*)" {
		url.redirect = ("^/(.*)" => "https://%1/$1")
	}
}
```

And then there's the fact that managing vhosts is just brilliant. Adding a new vhost is as simple as `mkdir /var/www/new-vhost` and adding the following to my lighttpd config file:

```
$HTTP["host"] =~ "^new\.vhost\.net$" {
	server.document-root        = var.basedir + "/new-vhost"
	accesslog.filename              = var.logdir  + "/access-new-vhost.log"
}
```

There's a lot more to love about lighttpd, though. I'll be updating this post with more tips and config snippets as I go.

Adding on to the earlier config snippet for forcing SSL across all vhosts, it might even be possible to have a single block for all vhosts (I haven't personally tested this, use at your own risk):

```
$HTTP["host"] =~ "(.*)" {
	server.document-root        = var.basedir + "/$1"
	accesslog.filename              = var.logdir + "/access-$1.log"
}
```

This would, in theory, accept any vhost as long as it has a corresponding folder in /var/www.
