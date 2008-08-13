from django.db import models
from django.db.models import permalink
from django.contrib import admin
from django.contrib.auth.models import User

class Author(models.Model):
  user = models.ForeignKey(User, unique=True)
  first_name = models.CharField(max_length=40)
  last_name = models.CharField(max_length=60, blank=True)
  bio = models.TextField(blank=True)
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

  @permalink
  def get_absolute_url(self):
    return ('bio', (), {'user': self.user})

