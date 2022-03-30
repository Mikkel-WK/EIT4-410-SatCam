FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://bsp.cfg"
SRC_URI += "file://QSPI-s25fl127_8-2020_2.patch \
            file://user_2022-03-05-22-08-00.cfg \
            file://user_2022-03-07-19-09-00.cfg \
            file://user_2022-03-09-12-26-00.cfg \
            file://user_2022-03-10-15-00-00.cfg \
            "
KERNEL_FEATURES_append = " bsp.cfg"
SRC_URI += "file://user_2022-03-05-14-15-00.cfg"

