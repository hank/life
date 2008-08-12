from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

from dingodjango.feeds import LatestEntries
from django.http import HttpResponse

feeds = {
    'latest': LatestEntries,
#    'tags': LatestEntriesByTag,
}


urlpatterns = patterns('',
    # Example:
    # (r'^dingodjango/', include('dingodjango.foo.urls')),

    # Uncomment the next line to enable admin documentation:
    #(r'^dingodjango/admin/doc/', include('django.contrib.admindocs.urls')),
    (r'^dingodjango/$', 'dingodjango.posts.views.index'),
    (r'^dingodjango/posts/', include('dingodjango.posts.urls')),

    # Uncomment the next line for to enable the admin:
    (r'^dingodjango/admin/(.*)', admin.site.root),
    (r'^dingodjango/feeds/(?P<url>.*)/$', 'django.contrib.syndication.views.feed', 
      {'feed_dict': feeds}),
)
