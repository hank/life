from django.conf.urls.defaults import *
urlpatterns = patterns('',
    (r'^$', 'dingodjango.posts.views.index'),
    (r'^(.*)', 'dingodjango.posts.views.single_post'),
)
