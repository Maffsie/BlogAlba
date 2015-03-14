		<TMPL_IF NAME="PAGINATED">
		<div class='col col-sm-9'><div id='pagination'>
			<TMPL_IF NAME="prevlink"><p style='float: left'><a href="/page/<TMPL_VAR NAME="prevpage">">Go forth in time (page <TMPL_VAR NAME="prevpage">)</a></p></TMPL_IF>
			<TMPL_IF NAME="nextlink"><p style='float: right'><a href="/page/<TMPL_VAR NAME="nextpage">">Plunge further into posts of yore (page <TMPL_VAR NAME="nextpage">)</a></p></TMPL_IF>
		</div></div>
		</TMPL_IF>
		</div>
	</div>
	<footer>
		<a href="https://github.com/MaffC/BlogAlba">BlogAlba</a> + <a href="http://nginx.org">nginx</a> + <a href="http://freebsd.org">freebsd</a> + <a href="http://digitalocean.com">digitalocean</a><br />
		<span id="small">Served by <TMPL_VAR NAME="host">, site generated at <TMPL_VAR NAME="gentime"> (took <TMPL_VAR NAME="genworktime">)</span>
	</footer>
	<!-- Code block syntax highlighting. -->
	<script src="//cdnjs.cloudflare.com/ajax/libs/highlight.js/8.4/highlight.min.js"></script>
	<script>hljs.initHighlightingOnLoad();</script>
	</body>
</html>
