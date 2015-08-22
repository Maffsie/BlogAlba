		<TMPL_IF NAME="PAGINATED">
		<div class='col col-sm-9'><div id='pagination'>
			<TMPL_IF NAME="prevlink"><p style='float: left'><a href="/page/<TMPL_VAR NAME="prevpage">">Go forth in time (page <TMPL_VAR NAME="prevpage">)</a></p></TMPL_IF>
			<TMPL_IF NAME="nextlink"><p style='float: right'><a href="/page/<TMPL_VAR NAME="nextpage">">Plunge further into posts of yore (page <TMPL_VAR NAME="nextpage">)</a></p></TMPL_IF>
		</div></div>
		</TMPL_IF>
		</div>
	</div>
	<footer>
		<a href="https://github.com/MaffC/BlogAlba">BlogAlba</a> + <a href="http://nginx.org">nginx</a> + <a href="http://freebsd.org">freebsd</a> + <a href="https://ip-projects.de">ip-projects servers</a><br />
		<span id="small">Served by <TMPL_VAR NAME="host">, site generated at <TMPL_VAR NAME="gentime"> (took <TMPL_VAR NAME="genworktime">)</span>
	</footer>
	<!-- Code block syntax highlighting. -->
	<script src="//cdnjs.cloudflare.com/ajax/libs/highlight.js/8.4/highlight.min.js"></script>
	<script>hljs.initHighlightingOnLoad();</script>
	<!--Begin google analytics-->
	<script>
		(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
		(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
		m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
		})(window,document,'script','//www.google-analytics.com/analytics.js','ga');
		ga('create', 'UA-30268654-2', 'auto');
		ga('require', 'displayfeatures');
		ga('send', 'pageview');
	</script>
	<!--End google analytics-->
	</body>
</html>
