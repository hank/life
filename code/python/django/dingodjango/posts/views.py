from django.shortcuts import render_to_response
import django.http
from models import Post, Tag, Author
from django.conf import settings

def render_to_response_with_settings(*args, **kwargs):
  """Renders a response including the custom settings for DingoDjango."""
  if args[-1].has_key('settings'):
    raise KeyError
  args[-1]['settings'] = settings.DINGO_DJANGO_SETTINGS
  return render_to_response(*args, **kwargs)

def index(request):
  posts = Post.objects.all()[:5]
  return render_to_response_with_settings('posts/index.html', {'posts':posts})

def single_post(request, slug):
  try:
    posts = Post.objects.filter(slug__iexact=slug)
  except Post.DoesNotExist:
    pass
  return render_to_response_with_settings('posts/single.html', {'posts':posts})
