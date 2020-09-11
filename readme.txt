These are rewrites of various utilities I've found on Linux, BSD and Unix
systems.

With the exception of signames.c/h (in the "kill" folder) and setmode.c (in
the "mkdir" folder) - which come from the BSDs - the rest of the code is
ground-up rewrites.  The goal is for them to be lightweight and to Do The
Right Thing, whatever that may be.  I do accept submissions via the github
page.

The default license for all code not otherwise specified is the UIUC or NCSA
license.  The exceptions are some library functions borrowed from the BSDs.
Obviously BSD code is under the BSD license.

Thoughts:

I need to write manuals for everything and properly implement make install.

Maybe I could primp up the output of dmesg.

Not all these tools are very well tested.

mount is very basic.

I'd like to reimplement sh just to have a cleaner implementation...

I left who(1) out of the actual Lunaris core because it's kind-of braindead.
