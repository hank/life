from django.db import models
from django.contrib import admin
from django.contrib.auth.models import User
from django.template.defaultfilters import slugify

class Author(models.Model):
  user = models.ForeignKey(User, unique=True)
  first_name = models.CharField(max_length=40)
  last_name = models.CharField(max_length=60, blank=True)
  email = models.EmailField()
  url = models.URLField(blank=True, verify_exists=False)
  date_created = models.DateField()
  active = models.BooleanField(default=True)
  class Meta:
    ordering = ['first_name']
  def __unicode__(self):
    return self.full_name()
  def full_name(self):
    return "%s %s" % (self.first_name, self.last_name,)

class AuthorAdmin(admin.ModelAdmin):
  pass
admin.site.register(Author, AuthorAdmin)

MARKUP_CHOICES=(
  ('textile', 'Textile'),
  ('markdown', 'Markdown',),
)

class Post(models.Model):
  slug = models.SlugField(
    primary_key=True,
    editable=False,
  )
  title = models.CharField(max_length=200)
  author = models.ForeignKey(Author)
  date_created = models.DateTimeField(auto_now=True, editable=False)
  date_updated = models.DateTimeField(auto_now_add=True, 
    blank=False, editable=False)
  body = models.TextField()
  markup = models.CharField(max_length=30, choices=MARKUP_CHOICES)
  class Meta:
    ordering = ['date_created', 'title']
  def __unicode__(self):
    return self.title
  def save(self):
    self.slug = slugify(self.title)
    super(Post, self).save()
  def get_absolute_url(self):
    return '/posts/%s' % self.slug

class PostAdmin(admin.ModelAdmin):
  pass
admin.site.register(Post, PostAdmin)

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

class TagAdmin(admin.ModelAdmin):
  pass
admin.site.register(Tag, TagAdmin)
