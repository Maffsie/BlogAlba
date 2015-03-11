		<TMPL_IF NAME="PAGINATED">
		<div class='col col-sm-9'><div id='pagination'>
			<TMPL_IF NAME="prevlink"><p style='float: left'><a href="/page/<TMPL_VAR NAME="prevpage">">Go forth in time (page <TMPL_VAR NAME="prevpage">)</a></p></TMPL_IF>
			<TMPL_IF NAME="nextlink"><p style='float: right'><a href="/page/<TMPL_VAR NAME="nextpage">">Plunge further into posts of yore (page <TMPL_VAR NAME="nextpage">)</a></p></TMPL_IF>
		</div></div>
		</TMPL_IF>
		</div>
	</div>
	<footer>
		<a href="https://github.com/MaffC/BlogAlba">BlogAlba</a> + <a href="http://lighttpd.net">lighttpd</a> + <a href="http://freebsd.org">freebsd</a> + <a href="http://digitalocean.com">digitalocean</a><br />
		Served by <TMPL_VAR NAME="host">, site generated at <TMPL_VAR NAME="gentime"> (took <TMPL_VAR NAME="genworktime">)
	</footer>
	<!--
	<script src="//cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
	<script src="//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.2/js/bootstrap.min.js"></script>
	-->
	</body>
</html>
