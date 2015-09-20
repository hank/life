#!/usr/bin/env python
"""Simple script to names TV episode by episode name.
 
Files must be named as follows:
 
    ./ShowName - Episode Name.ext
 
For example:
 
    ./Scrubs - My First Day.avi
"""

import re
import os
import sys

from tvdb_api import Tvdb


def confirm(choicesize, question):
    while 1:
        numchs = "/".join([str(x) for x in range(1,choicesize+1)])
        ans = raw_input(question.format(numchs))
        if ans.isdigit():
            return ans
        elif ans in ['n', 'no']:
            return 'n'
        elif ans in ['q', 'quit']:
            sys.exit(1)


def nameByName(showname, episodename):
    """Searches for episode with correct name.
    The tvdb_api search is very simple, along the lines of:
    
        if searchterm in current_episodename:

    ..so the episode name must be accurate
    """
    try:
        show = Tvdb(interactive=True)[showname]
    except Exception as e:
        print e
        return None, []
    sr = show.search(episodename, key='episodename')
    if len(sr) == 0:
        another = " ".join(episodename.replace('_', ' ').split(" ")[0:2])
        print "Zero results, Searching for {} instead...".format(another)
        sr = show.search(another, key='episodename')
    if len(sr) != 1:
        print "Got %d search results for %s episode named %s" % (len(sr), showname, episodename)
    return show['seriesname'], sr
    

def main():
    for fname in sys.argv[1:]:
        print "Processing {}".format(fname)
        # Get absolute path to file
        fullpath = os.path.abspath(fname)

        # Get directory where file is, and extension
        dirname = os.path.split(fullpath)[0]
        fname, ext = os.path.splitext(fname)

        # Clean filename
        matchfname = fname.replace("_", " ").replace(".", " ")

        # Ignore filenames that have episode information already
        m = re.search('(\dx\d\d)', fname)
        if m:
            print "Already has episode info: {}".format(m.group(1))
            continue
        else:
            print "No match"

        # Pattern to match show/episode name
        m = re.match('^(.+?) - (.+?)$', fname)
        if m:
            # Show name is first group, episode name is second
            showname = m.group(1)
            epname = m.group(2)
            
            corrected_showname, eps = nameByName(showname, epname)
            if corrected_showname is None:
                continue
            if len(eps) == 0:
                continue
            # Construct new episode names
            newnames = []
            for ep in eps:
                newnames.append("%s - %02dx%02d - %s" % (
                    corrected_showname,
                    int(ep['seasonnumber']),
                    int(ep['episodenumber']),
                    ep['episodename']
                ))

            # Get full path to new episodes, for renaming
            newfullpaths = []
            for newname in newnames:
                newfullpaths.append(os.path.join(dirname, newname) + ext)

            # if the user confirms, rename the file
            print "Old filename:", fullpath
            i = 1
            for newfullpath in newfullpaths:
                print "{}: {}".format(i, newfullpath)
                i += 1
            choice = confirm(len(newfullpaths), "Choose? ({}/n/q) ")
            if choice.isdigit():
                # We picked one of the renames
                print "Renaming to:", newfullpaths[int(choice)-1]
                os.rename(fullpath, newfullpaths[int(choice)-1])
        else:
            print "Failed to match {}".format(fname)


if __name__ == '__main__':
    main()
