from django import template
from dingodjango.posts.models import Author

register = template.Library()

@register.inclusion_tag('authors/author_posts.html')
def author_posts(author):
  posts = author.post_set.all()[:10]
  return {'posts':posts}

@register.inclusion_tag('authors/author_sidebar.html')
def author_sidebar():
  authors = Author.objects.all()
  return {'authors':authors}
