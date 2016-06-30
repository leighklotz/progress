%define name    progress
%define version 1.0
%define release 1
%define serial  1
%define prefix  /usr/local/

Summary:        Progress -- report progress of data through a pipe
Name:           %{name}
Version:        %{version}
Release:        %{release}
Serial:         %{serial}
Group:          Utilities
License:        MIT
Url:            http://www.graflex.org/klotz/software/progress
Vendor:         Leigh L. Klotz, Jr. <klotz@graflex.org>
Source:         %{name}-%{version}.tar.gz
Buildroot:      /var/tmp/%{name}-%{version}-root

%description
Progress is a utility used in a pipe to report progress of data transfer to standard error.
Command-line arguments specify how frequently to report, what character to use to report,
and how much buffering to do.

%prep

%setup -q

%build
make progress install DESTDIR=$RPM_BUILD_ROOT

%install
[ "$RPM_BUILD_ROOT" != "/" ] && [ -d $RPM_BUILD_ROOT ] && rm -r $RPM_BUILD_ROOT
echo HELLO $RPM_BUILD_ROOT/
mkdir -p $RPM_BUILD_ROOT/%{prefix}/bin/
mkdir -p $RPM_BUILD_ROOT/%{prefix}/man/man1
cp progress $RPM_BUILD_ROOT/%{prefix}/bin/progress
cp progress.1 $RPM_BUILD_ROOT/%{prefix}/man/man1/progress.1

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && [ -d $RPM_BUILD_ROOT ] && rm -r $RPM_BUILD_ROOT;

%files
%defattr(-,root,root)
%{prefix}/bin/progress
%{prefix}/man/man1/progress.1
