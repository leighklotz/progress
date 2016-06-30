# Progress

Progress is a Linux utility I wrote to print progress of pipe IO to stderr.

At the time (2002-2003) there were no such utilities.  As of 2016, pv and the status=progress flag for dd make progress less interesting.

Progress is mostly for historical interest.

## Example
````
$ tar czf - *.pdf | progress -m1 > my-pdfs.tar.gz
......................................................................................................................................................................................................................................................................................................................................................
$ 
````

## Alternatives

- [pipebench](http://www.habets.pp.se/synscan/programs.php?prog=pipebench)
- [Progress Bar](https://pypi.python.org/pypi/Pbar)
- [Command Line Progress Bar](http://clpbar.sourceforge.net/)
- [Pipeline Viewer](http://linux.die.net/man/1/pv)
- dd status=progress

## Download
You can download some precompiled versions here: [progress](https://software.graflex.org/progress)

## INSTALL
````$ make install PREFIX=/usr/local/````

## Make debian package
````$ dpkg-buildpackage -us -uc````

## Make RPM package
This may be wrong:

````$ rpmbuild -ba progress.spec````

----

# Contact
Leigh L. Klotz, Jr. <klotz@graflex.org>
