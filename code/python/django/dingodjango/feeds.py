from django.contrib.syndication.feeds import Feed
from dingodjango.posts.models import Post
from django.conf import settings

class LatestEntries(Feed):
    title = settings.DINGO_DJANGO_SETTINGS['title']
    description = settings.DINGO_DJANGO_SETTINGS['subtitle']
    link = "/"

    def items(self):
        return Post.objects.order_by('-date_created')[:5]

#class LatestEntriesByTag(Feed):
#    title = "DingoDjango Blog Feed"
#    link = "/"
#    description = "New posts on this DingoDjango blog!"
#
#    def items(self):
#        return Post.objects.order_by('-date_created')[:5]
