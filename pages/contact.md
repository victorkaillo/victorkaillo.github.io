---
layout: page
permalink: /contact/
title: Contact
show_meta: false
published: true
description: "Contact victorkaillo@ufrn.edu.br"
comments: false
mathjax: false
noindex: false
sitemap:
    priority: 0.5
    changefreq: 'monthly'
    lastmod: 2016-02-13
tags:
  - "victor kaillo"
  - "driving directions"
  - address
---

| <i class="fa fa-twitter"></i> | [@victorkaillo](https://twitter.com/victor_kaillo)  | 
| - | :- |
| <i class="fa fa-envelope"></i> | Victor<br>Kaillo<br>1808<br>Natal, RN    | 
| - | :- |
| <i class="fa fa-car"></i>  | [Driving directions]({{ site.url }}/directions) | 
| - | :- |
| <i class="fa fa-paper-plane">  | victorkaillo@ufrn.edu.br | 
| - | :- |

<a href="https://twitter.com/share" class="twitter-share-button" data-via="{{ site.owner.twitter }}" data-size="small" data-dnt="true">Tweet</a> <a href="javascript:window.print()" class="social-icons" title="Printer friendly format"><i class="fa fa-print"></i></a>

<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>

{% if site.twitter_widget_id %}
<div class="text-tweets">
<div class="tweets">
<a class="twitter-timeline"
  data-dnt="true"
  width="600"
  height="250"
  href="https://twitter.com/victor_kaillo"
  data-widget-id="{{ site.twitter_widget_id }}"
  data-tweet-limit="2"
  data-chrome="noheader nofooter noborders noscrollbar transparent">
  Recent Tweets</a>
 </div>
<script>
    !function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+"://platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");
</script>
</div>
{% else %}
Twitter stream will show up here if `twitter_widget_id` is present is `_config.yml`
{% endif %}
