# -*- coding: utf8 -*-
import sys
try:
  from urllib.parse import urlencode
except ImportError:
  from urllib import urlencode
try:
  from http import client
except ImportError:
  import httplib as client
try:
  import json
except ImportError:
  import simplejson as json
from base64 import b64encode

import logging

logger = logging.getLogger('pydiigo')

if isinstance(sys.version_info, tuple):
  PY_MAJOR_VERSION = sys.version_info[0]
else:
  PY_MAJOR_VERSION = sys.version_info.major

def parametalize(params_candidate={}) :
  if 'self' in params_candidate :
    del params_candidate['self']
  return set_data(params_candidate)

def set_data(params_candidate) :
  param = {}
  for key, value in params_candidate.items() :
    if value == None or value == '' or value == []:
      pass
    else:
        param[key] = value
  return param

class DiigoBookmark(dict) :
  """
  Diigo Bookmark model.
  "title":"Diigo API Help",
  "url":"http:\/\/www.diigo.com\/help\/api.html",
  "user":"foo",
  "desc":"",
  "tags":"test,diigo help",
  "shared":"yes",
  "created_at":"2008/04/30 06:28:54 +0800",
  "updated_at":"2008/04/30 06:28:54 +0800",
  "comments":[],
  "annotations":[]
  """
  def __init__(self, d) :
    for key, value in d.items() :
      self[key] = value

  def __getattr__(self, name):
    try: return self[name]
    except: object.__getattribute__(self, name)

class DiigoApi(object) :
  """
Requirements
=======================
* `pit`_ **optional**. See diigotest.py. You might love it ;)

.. _`pit`: http://pypi.python.org/pypi?:action=display&name=pit

instllation
=======================
$ pip install pydiigo

  or 

Download pydiigo and extract it, then

$ sudo python setup.py install

Notes
=======================
You might get 503 Error, because of Diigo's API limit.

v.0.5
--------------------
api needs diigo **API KEY** generate api key via https://www.diigo.com/api_keys/new/

required python version 2.6, 2.7, 3.2, 3.3

v.0.2
--------------------
**Update Bookmark** is deprecated and raise DeprecationWarning.

Usage
=======================

Initialize API 
--------------------
::

  >>> from pydiigo import DiigoApi
  >>> api = DiigoApi(user='YOUR_DIIGO_USERNAME', password='YOUR_DIIGO_PASSWORD', apikey='YOUR API KEY')

Search Bookmarks
--------------------
::

  >>> bookmarks = api.bookmarks_find(user='DIIGO_USER_NAME')
  >>> for bookmark in bookmarks:
  ...   print(bookmark.title)
  ...   print(bookmark.url)
  ...   print(bookmark.tags)
  ...   print(bookmark.desc)
  ...   print('-' * 10)

* Bookmark Structure

  * title (string)

  * url (string)

  * user (string)

  * desc (string: description)

  * tags (string: Seperated by comma with multiple tags.)

  * shared (string: yes or no)

  * created_at (string: eg.2009/03/04 02:57:09 +0000)

  * updated_at (string: eg.2009/03/04 02:57:09 +0000)

  * comments (string array)

  * annotations (string array)

Add Bookmark
--------------------
::

  >>> result = api.bookmark_add(title='', description='',url='', shared='yes', tags='')
  >>> print(result['message'])
  added 1 bookmark

* required arguments

  * url

Delete Bookmark
--------------------
::

  >>> result = api.bookmark_delete(url='')
  >>> print(result['message'])
  updated 1 bookmark

* required arguments

  * url

  """
  server = 'secure.diigo.com:443'
  
  def __init__(self, user='', password='', apikey='', debug=False) :
    self.user = user
    self.password = password
    self.apikey = apikey
    self.debug = debug
    if not self.user:
      raise ValueError('You must pass your username, password and apikey.')
    if PY_MAJOR_VERSION == 2:
      auth_header = b64encode("{0}:{1}".format(self.user, self.password))
    else:
      auth_header = b64encode(bytes("{0}:{1}".format(self.user, self.password), 'utf8')).decode('utf8')
    self.headers = {"Content-type": "application/x-www-form-urlencoded",
               "Accept"      : "text/plain",
               "Authorization": "Basic {0}==".format(auth_header),
               "User-agent"  : "pydiigo/{0}".format(VERSION)}

  def bookmarks_find(self, start=0, rows=50, sort=0,
                           user=None, tags='', filter='public',
                           list=None, site=None,
                           ft=None, url=None) :
    '''
      Diigo deleted some options(site, ft, url).
      rows fallback to count.
    '''
    count = rows
    del rows
    if site or ft or url:
      logger.error('Diigo removed some options(site, ft, url).')
    return self._handle_bookmark(parametalize(locals()), 'GET')

  def bookmark_add(self, title='', description='',url='',
                         shared='yes', tags=''):
    if url == None or len(url) == 0:
      raise ValueError('url must specified')
    desc = description
    return self._handle_bookmark(parametalize(locals()), 'POST')

  def bookmark_update(self, title='', description='',url='',
                         shared='yes', tags=''):
    raise DeprecationWarning('''Doese this API work?''')
    # if url == None or len(url) == 0:
    #   raise ValueError, 'url must specified'
    # return self._handle_bookmark(parametalize(locals()), 'POST')

  def bookmark_delete(self, url=''):
    if url == None or len(url) == 0:
      raise ValueError('url must specified')
    return self._handle_bookmark(parametalize(locals()), 'DELETE')
  
  def _load_json(self, response):
    body = response.read()
    logger.debug(body)
    if PY_MAJOR_VERSION == 2:
      return json.loads(body)
    else:
      return json.loads(body.decode('utf8'))

  def _handle_bookmark(self, param={}, method='GET') :
    logger.debug('{0}._handle_bookmark->{1}'.format(self.__class__, method))
    logger.debug(' ARGS:{0}\n'.format(param))
    param['key'] = self.apikey
    params = urlencode(param)
    conn = client.HTTPSConnection(self.server)
    try:
      if method == 'GET':
        urlpath = "/api/v2/bookmarks?{0}".format(params)
        conn.request(method, urlpath, "", self.headers)
        response = conn.getresponse()
        if response.status >= 400:
          logger.debug("ERROR: STATUS:{0}\n       {1}".format(response.status, response.read()))
          raise PyDiigoError(response.status,
                            'Bad Status',
                            method,
                            urlpath)
        bookmarks = [DiigoBookmark(d) for d in self._load_json(response)]
        return bookmarks
      else :
        urlpath = "/api/v2/bookmarks" 
        conn.request(method, urlpath, params, self.headers)
        response = conn.getresponse()
        if response.status >= 400:
          logger.debug("ERROR: STATUS:{0}\n       {1}".format(response.status, response.read()))
          raise PyDiigoError(response.status,
                            'Bad Status',
                            method,
                            params)
        return self._load_json(response)
    finally:
      conn.close()

class PyDiigoError(Exception) :
  STATUS = {'301':'Not Modified',
                '400':'Bad Request',
                '401':'Not Authorized',
                '403':'Forbidden',
                '404':'Not Found',
                '500':'Internal Server Error',
                '502':'Bad Gateway',
                '503':'Service Unavailable'}
  def __init__(self, status, message, method='', param={}):
    self.status = status
    self.message = message
    self.method = method
    self.param = param

  def __str__(self) :
    return self.__repr__()

  def __repr__(self) :
    return '[{0}:{1}] {2} when {3} called with {4}'.format(self.status, PyDiigoError.STATUS[str(self.status)],
                                                  self.message, self.method, self.param)


VERSION = '0.5'
AUTHOR = 'makoto tsuyuki'
AUTHOR_EMAIL = 'mtsuyuki_at_gmail_dot_com'
PROJECT_URL = 'http://www.tsuyukimakoto.com/project/pydiigo/'

CONTACT = '{0} or {1}'.format(PROJECT_URL, AUTHOR_EMAIL)
DESCRIPTION = '''Python wrapper for www.diigo.com's API'''
LONG_DESCRIPTION = DiigoApi.__doc__

