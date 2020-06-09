LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

DEPENDS = "qtbase qtcharts"

SRC_URI = "git://github.com/JoaoPagotto/ControllerPID;protocol=https"

PV = "1.0+git${SRCPV}"
SRCREV = "56eecfdfff6bc03b6fe641692e258a2c1d81c6f2"

S = "${WORKDIR}/git"

inherit qmake5
