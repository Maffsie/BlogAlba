<!doctype html>
<html lang="en">
	<head>
		<meta charset="utf-8" />
		<meta http-equiv="Content-Type" content="text/html;charset=UTF-8" />
		<meta name="keywords" content="<TMPL_VAR NAME="keywords">" />
		<meta name="author" content="<TMPL_VAR NAME="author">" />
		<meta name="description" content="<TMPL_VAR NAME="tagline">" />
		<meta property="og:title" content="<TMPL_VAR NAME="name">" />
		<meta property="og:site_name" content="<TMPL_VAR NAME="name">" />
		<meta property="og:description" content="<TMPL_VAR NAME="tagline">" />
		<title><TMPL_VAR NAME="pagetitle"></title>
		<TMPL_VAR NAME="robots">
		<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
		<link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/bootswatch/3.3.2/custom/bootstrap.min.css" />
		<link rel="stylesheet" href="/main.css" />
	</head>
	<body>
	<nav class="navbar navbar-static">
		<div class="container">
			<a class="navbar-toggle" data-toggle="collapse" data-target=".nav-collapse">
			</a>
			<div class="nav-collapse collase">
				<ul class="nav navbar-nav">
					<li><a href="<TMPL_VAR NAME="url">">Home</a></li>
					<TMPL_LOOP NAME="NAV">
					<li><a href="<TMPL_VAR NAME="navurl">"><TMPL_VAR NAME="navname"></a></li>
					</TMPL_LOOP>
				</ul>
				<ul class="nav navbar-right navbar-nav">
				</ul>
			</div>
		</div>
	</nav>

	<header class="masthead">
		<div class="container">
			<div class="row">
				<div class="col col-sm-6">
					<h1><a href="<TMPL_VAR NAME="url">" title="<TMPL_VAR NAME="name">"><TMPL_VAR NAME="name"></a>
						<p class="lead"><TMPL_VAR NAME="tagline"></p></h1>
				</div>
			</div>
		</div>
	</header>
	<div class="container">
		<div class="row">
			<div class="col col-sm-3">
				<div id="sidebar">
					<ul class="nav nav-stacked">
						<TMPL_IF NAME="ISPOST">
						<li><h3 class="highlight">This Post</h3></li>
						<li>Published: <TMPL_VAR NAME="fancy"></li>
						<TMPL_IF NAME="hastags">
						<li>Tags: <TMPL_VAR NAME="tags"></li>
						</TMPL_IF>
						</TMPL_IF>
						<li><h3 class="highlight">Posts</h3></li>
						<TMPL_LOOP NAME="recent">
						<li><a href="<TMPL_VAR NAME="permaurl">"><TMPL_VAR NAME="title"></a></li>
						</TMPL_LOOP>
					</ul>
				</div>
			</div>
