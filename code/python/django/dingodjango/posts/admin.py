from django.contrib import admin
from dingodjango.posts.models import Post, Tag

class PostAdmin(admin.ModelAdmin):
  pass
admin.site.register(Post, PostAdmin)

class TagAdmin(admin.ModelAdmin):
  pass
admin.site.register(Tag, TagAdmin)
