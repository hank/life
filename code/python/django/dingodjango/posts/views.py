from django.shortcuts import render_to_response
import django.http
from models import Post, Tag, Author
from django.conf import settings
from django.core.paginator import Paginator, InvalidPage

DEFAULTS = {
  'posts_per_page': 5,
}

#
# Pages
#
def index(request):
  page = request.GET.get('page', 1)
  per_page = settings_or_default('posts_per_page'):
  paginator = Paginator(Post.objects.all(), per_page)
  try:
    posts = paginator.page(page)
  except InvalidPage:
    posts = paginator.page(1)

  return render_to_response_with_settings('posts/index.html', locals())

def single_post(request, slug, year=0, month=0, day=0):
  try:
    posts = {'object_list': Post.objects.filter(slug__iexact=slug)}
  except Post.DoesNotExist:
    pass
  return render_to_response_with_settings('posts/single.html', locals())

#
# Utility Functions
#
def settings_or_default(key):
  if settings.DINGO_DJANGO_SETTINGS.has_key(key):
    return settings.DINGO_DJANGO_SETTINGS[key]
  elif DEFAULTS.has_key(key):
    return DEFAULTS['key']
  else:
    raise KeyError

def render_to_response_with_settings(*args, **kwargs):
  """Renders a response including the custom settings for DingoDjango."""
  if args[-1].has_key('settings'):
    raise KeyError
  args[-1]['settings'] = settings.DINGO_DJANGO_SETTINGS
  return render_to_response(*args, **kwargs)

