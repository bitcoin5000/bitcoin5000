#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BITCOIN5000D=${BITCOIN5000D:-$SRCDIR/bitcoin5000d}
BITCOIN5000CLI=${BITCOIN5000CLI:-$SRCDIR/bitcoin5000-cli}
BITCOIN5000TX=${BITCOIN5000TX:-$SRCDIR/bitcoin5000-tx}
BITCOIN5000QT=${BITCOIN5000QT:-$SRCDIR/qt/bitcoin5000-qt}

[ ! -x $BITCOIN5000D ] && echo "$BITCOIN5000D not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BVKVER=($($BITCOIN5000CLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitcoin5000d if --version-string is not set,
# but has different outcomes for bitcoin5000-qt and bitcoin5000-cli.
echo "[COPYRIGHT]" > footer.h2m
$BITCOIN5000D --version | sed -n '1!p' >> footer.h2m

for cmd in $BITCOIN5000D $BITCOIN5000CLI $BITCOIN5000TX $BITCOIN5000QT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BVKVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BVKVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
