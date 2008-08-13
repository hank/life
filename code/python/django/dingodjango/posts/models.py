from django.db import models
from django.db.models import permalink
from django.contrib import admin
from django.contrib.auth.models import User
from dingodjango.authors.models import Author
from django.template.defaultfilters import slugify
from django import forms
import textile
import markdown

MARKUP_CHOICES=(
  ('textile', 'Textile'),
  ('markdown', 'Markdown',),
)

class Post(models.Model):
  slug = models.SlugField(
    primary_key=True,
    editable=False,
  )
  title = models.CharField("Post Title", max_length=200)
  author = models.ForeignKey(Author)
  date_created = models.DateTimeField(auto_now=True, editable=False)
  date_updated = models.DateTimeField(auto_now_add=True, 
    blank=False, editable=False)
  body = models.TextField("Content")
  renderedbody = models.TextField(editable=False, blank=True, null=True)
  markup = models.CharField(max_length=30, choices=MARKUP_CHOICES)
  class Meta:
    ordering = ['-date_created', 'title']
  def __unicode__(self):
    return self.title
  def save(self):
    if(self.markup == "textile"):
      self.renderedbody = textile.textile(str(self.body))
    elif(self.markup == "markdown"):
      self.renderedbody = markdown.markdown(str(self.body))
    else:
      self.renderedbody = self.body
    self.slug = slugify(self.title)
    super(Post, self).save()

  @permalink
  def get_absolute_url(self):
    return ('single-post', (), {'slug': self.slug})


class Tag(models.Model):
  slug = models.SlugField(
    primary_key=True,
    editable=False,
  )
  name = models.CharField(max_length=35)
  posts = models.ManyToManyField(Post)
  description = models.TextField()
  class Meta:
    ordering = ['name']
  def __unicode__(self):
    return self.name
  def save(self):
    self.slug = slugify(self.name)
    super(Tag, self).save()

