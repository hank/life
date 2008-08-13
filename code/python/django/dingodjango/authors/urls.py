from django.conf.urls.defaults import *
urlpatterns = patterns('dingodjango.authors.views',
    url(r'(?P<username>[-\w_]+)', 'bio', name="bio"),
)
