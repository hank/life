from django.conf.urls.defaults import *
urlpatterns = patterns('dingodjango.posts.views',
    (r'^$', 'index'),
    (r'^random', 'random'),
    (r'^tag/(?P<tagslug>[-\w]+)', 'tag'),
    url(r'^(?P<year>\d{4})/(?P<month>\d{1,2})/(?P<day>\d+)/(?P<slug>[-\w]+)', 
        'single_post', 
        name="single-post"),
)
