from django.contrib import admin
from dingodjango.authors.models import Author

class AuthorAdmin(admin.ModelAdmin):
  pass
admin.site.register(Author, AuthorAdmin)
