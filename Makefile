CC=gcc
VERSION=1.0
INS		= install
PROGRAM		= progress
DESTDIR		=
PREFIX		= /usr/local
INSDIR		= $(PREFIX)/bin
MANDIR		= $(PREFIX)/man/man1
MANPAGE		= progress.1

progress: progress.c
	$(CC) progress.c -o progress


install:
	$(INS) -d $(DESTDIR)$(INSDIR)
	$(INS) -d $(DESTDIR)$(MANDIR)

	$(INS) -s -m 755 $(PROGRAM) $(DESTDIR)$(INSDIR)
	$(INS) -m 644 $(MANPAGE) $(DESTDIR)$(MANDIR)

clean:
	rm -f progress


release:
	cp progress.spec /usr/src/redhat/SPECS
	(cd ..; tar czvf /usr/src/redhat/SOURCES/progress-${VERSION}.tar.gz progress-${VERSION})



.phony:	release
