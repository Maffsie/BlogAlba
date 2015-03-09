			<div class="col col-sm-9">
				<div class="panel">
					<a href="<TMPL_VAR NAME="permaurl">"><h1><TMPL_VAR NAME="title"></h1></a>
					<TMPL_IF NAME="INDEX">
					<p class="lead"><TMPL_VAR NAME="fancy"></p>
					<TMPL_VAR NAME="excerpt">
					<p><a href="<TMPL_VAR NAME="permaurl">">Read more</a></p>
					<TMPL_ELSE>
					<TMPL_VAR NAME="body">
					</TMPL_IF>
				</div>
			</div>
