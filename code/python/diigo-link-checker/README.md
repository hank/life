= Diigo Link Checker
== Usage
Make a password file with your password in it and no newlines.  I call this PW
below in the examples.  Alternatively, you should be prompted.

Now run the script:

    python checklinks.py --user yourUSERNAME --passwordfile PW

If for some reason it crashes, you can start around where you left off, which is periodically
printed to the screen:

    python checklinks.py --user yourUSERNAME --passwordfile PW --offset 200
