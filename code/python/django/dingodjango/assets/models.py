from django.db import models
from django.conf import settings

class Asset(models.Model):
  filename = models.FilePathField(settings.ASSET_PATH, max_length=1000, recursive=True)

