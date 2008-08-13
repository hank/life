from models import Post, Tag, Author
from dingodjango.common import *
from django.core.paginator import Paginator, InvalidPage


#
# Pages
#
def index(request):
  authors = Author.objects.all()
  page = request.GET.get('page', 1)
  per_page = settings_or_default('posts_per_page')
  paginator = Paginator(Post.objects.all(), per_page)
  try:
    posts = paginator.page(page)
  except InvalidPage:
    posts = paginator.page(1)

  return render_to_response_with_settings('posts/index.html', locals())

def single_post(request, slug, year=0, month=0, day=0):
  authors = Author.objects.find_all()
  try:
    post = Post.objects.filter(slug__iexact=slug)[0:1].get()
  except Post.DoesNotExist:
    pass
  return render_to_response_with_settings('posts/single.html', locals())

