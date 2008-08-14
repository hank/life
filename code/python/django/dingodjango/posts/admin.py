from django.contrib import admin
from dingodjango.posts.models import Post, Tag

class TagAdmin(admin.ModelAdmin):
  pass
admin.site.register(Tag, TagAdmin)

class PostAdmin(admin.ModelAdmin):
  pass
admin.site.register(Post, PostAdmin)

