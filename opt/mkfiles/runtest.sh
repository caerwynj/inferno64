#!/bin/bash -i
# This script designed to be executed from host os in any way:
#	cd /…/project;	prove -r; mk test; appl/lib/t/smoke.t
#	cd appl/lib;	prove -r; mk test; t/smoke.t
#	cd t;		prove -r; mk test; ./smoke.t
# It require PKGDIR, EMUPKGDIR and EMUCMD variables set in mkfile.

# When this script executed not by mk (i.e. by prove or manually) it won't
# have variables from mkfile in environment and will need to fetch them.
function getvar() {
	echo -e "<mkfile\ngetvar:VQ:\n\techo \$$1" |
		mk -f /proc/self/fd/0 getvar
}

SUBDIR=$(pwd)
cd $(getvar PKGDIR)
PKGDIR=$(pwd)
DIS=$(getvar EMUPKGDIR)${SUBDIR:${#PKGDIR}}/$(dirname $0)/$(basename $0 .t).dis

eval "$(getvar EMUCMD) \$DIS"
