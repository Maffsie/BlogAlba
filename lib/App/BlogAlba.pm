package App::BlogAlba;

use strict;
use warnings;

use App::BlogAlba::Article;
use Data::Paginated;

use Time::HiRes qw/gettimeofday tv_interval/;

use Sys::Hostname;
my $HOST = hostname; $HOST =~ s/\..*$//;

use Dancer2;
use Dancer2::Plugin::Feed;

#Sanitise our base URL
config->{url} =~ /\/$/ or config->{url} .= '/';

sub pagination_calc {
	my $rem=$nposts % config->{conf}->{per_page};
	$npages=($nposts-$rem)/config->{conf}->{per_page};
	$npages++ if $rem>0 or $npages<1;
}
sub get_index {
	my @iposts = @_;
	$page->param(pagetitle => config->{name}, INDEX => 1, POSTS => [@iposts]);
	return $page->output;
}
sub paginate {
	my $pagenum = shift; my $offset = ($pagenum-1)*config->{conf}->{per_page};
	my $offset_to = $offset+(config->{conf}->{per_page}-1); $offset_to = $#posts if $offset_to > $#posts;
	$page->param(PAGINATED => 1, prevlink => ($pagenum>1? 1 : 0), prevpage => $pagenum-1, nextlink => ($pagenum<$npages? 1 : 0), nextpage => $pagenum+1);
	return get_index @posts[$offset..(($offset+config->{conf}->{per_page})>$#posts? $#posts : ($offset+(config->{conf}->{per_page}-1)))];
}
sub get_post {
	my ($y,$m,$slug) = @_;
	for my $r (@posts) {
		my %post = %$r;
		next unless $post{slug} eq $slug and timefmt($post{time},'writepost') eq "$y-$m";
		$page->param(pagetitle => $post{title}." - ".config->{name},%post);
		return 1;
	}
	return undef;
}
sub get_page {
	my $pname = shift;
	for my $r (@pages) {
		my %cpage = %$r;
		next unless $cpage{filename} eq $pname;
		$page->param(pagetitle => $cpage{title}." - ".config->{name},%cpage);
		return 1;
	}
	return undef;
}
sub do_cache {
	return if $lastcache > (time - 3600);
	$lastcache = time;my $st=[gettimeofday];
	undef @posts;undef @pages;$nposts=0;
	opendir POSTS, "$basedir/posts/" or die "Couldn't open posts directory $basedir/posts/";
	while(readdir POSTS) {
		next unless /\.md$/;
		warn "Error reading post $_\n" and next unless readpost("$basedir/posts/$_",1);
		$nposts++;
	}
	closedir POSTS;
	@posts = map {$_->[1]} sort {$b->[0] <=> $a->[0]} map {[$_->{time},$_]} @posts;

	opendir PAGES, "$basedir/pages/" or die "Couldn't open pages directory $basedir/pages/";
	while(readdir PAGES) {
		next unless /\.md$/;
		warn "Error reading page $_\n" and next unless readpost("$basedir/pages/$_",2);
	}
	closedir PAGES;

	my @nav;
	push @nav, {navname => $_->{title}, navurl => config->{url}.$_->{filename},} for @pages;
	push @nav, {navname => $_, navurl => config->{links}->{$_},} for sort { $b cmp $a } keys config->{links};
	generate_feed;
	%defparams = (
		INDEX => 0, NAV => [@nav], url => config->{url}, recent => [@posts[0 .. ($#posts > (config->{conf}->{recent_posts}-1)? (config->{conf}->{recent_posts}-1) : $#posts)]],
		gentime => timefmt($lastcache, '%H:%M %e/%-m/%y %Z'), genworktime => sprintf("%.2f ms", tv_interval($st)*100), host => $HOST, rss_enabled => config->{rss_publish},
		about => config->{about}, author => config->{author}, name => config->{name}, tagline => config->{tagline}, keywords => config->{keywords},
		robots => config->{conf}->{indexable}? '<meta name="ROBOTS" content="INDEX, FOLLOW" />' : '<meta name="ROBOTS" content="NOINDEX, NOFOLLOW" />',
	);
	pagination_calc;
}

sub GetPost {
	my $params = shift or return undef;
	return undef unless
		$params->{year} =~ /^[0-9]{4}$/ and
		$params->{month} =~ /^(0[1-9]|1[0-2])$/ and
		$params->{slug};
	
	for my $article (@articles) {
		next unless
			$article->{slug} eq lc $params->{slug} and
			$article->{yyyymm} eq $params->{year}.$params->{month};
		return $article;
	}
	return undef;
}

hook 'before' => sub {
	do_cache;
	page_init;
};

#Indexes
get '/' => sub {
	return get_index @posts if $npages==1;
	return paginate 1;
};
get '/page/:num' => sub {
	pass unless params->{id} =~ /^[0-9]+$/ and params->{id} <= $npages;
	return redirect '/' unless $npages > 1 and params->{id} > 1;
	return paginate params->{id};
};

#Published articles
get '/:page' => sub {
	pass unless params->{extpage} =~ /^[a-z0-9\-]+(?:\.md)?$/i;
	if (params->{extpage} =~ s/\.md$//) { $page->param(SOURCEVIEW => 1); header('Content-Type' => 'text/plain'); }
	$page->param(ISPOST => 0);
	get_page params->{extpage} or pass;
	return $page->output;
};
get '/wrote/:yyyy/:mm/:slug' => sub {
	my $article = GetPost scalar params 'route';
	pass unless $article;
	content_tyle 'text/plain' and return $article->{raw}
		if params->{slug} =~ /\.md$/;
	
	return template 'post', { page => $article };
};

#Feeds
get '/feed/:type' => sub {
	pass unless params->{type} =~ /^(rss|atom)$/i;
	create_feed
		format => lc params->{type},
		title => config->{blogtitle},
		link => request->base,
		entries => \@articles;
}
get qr{/feed-(atom|rss2).xml} => sub { redirect '/feed/'.splat; }

# 404
any qr/.*/ => sub {
	redirect '/' if request->path =~ /index\.(html?|pl)$/;
	return send_error('The page you seek cannot be found.', 404);
};

1;
__END__
