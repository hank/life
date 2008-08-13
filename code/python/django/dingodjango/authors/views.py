from dingodjango.common import *
from django.contrib.admin.models import User
from dingodjango.authors.models import Author
from dingodjango.posts.models import Post

def bio(request, username):
  try:
    author = Author.objects.filter(user__username__exact=username)[0:1].get()
    posts = Post.objects.filter(author=author.id)[:5]
  except Author.DoesNotExist:
    pass
  return render_to_response_with_settings('authors/bio.html', locals())
