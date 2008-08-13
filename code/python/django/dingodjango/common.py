from django.shortcuts import render_to_response
from django.conf import settings

DEFAULTS = {
  'posts_per_page': 5,
}

#
# Utility Functions
#
def settings_or_default(key):
  if settings.DINGO_DJANGO_SETTINGS.has_key(key):
    return settings.DINGO_DJANGO_SETTINGS[key]
  elif DEFAULTS.has_key(key):
    return DEFAULTS[key]
  else:
    raise KeyError

def render_to_response_with_settings(*args, **kwargs):
  """Renders a response including the custom settings for DingoDjango."""
  if args[-1].has_key('settings'):
    raise KeyError
  args[-1]['settings'] = settings.DINGO_DJANGO_SETTINGS
  return render_to_response(*args, **kwargs)

