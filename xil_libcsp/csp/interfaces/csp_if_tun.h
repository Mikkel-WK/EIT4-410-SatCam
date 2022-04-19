#pragma once

#include "../csp.h"

typedef struct {
	/* Should be set before calling if_tun_init */
	int tun_src;
	int tun_dst;
} csp_if_tun_conf_t;

void csp_if_tun_init(csp_iface_t * iface, csp_if_tun_conf_t * ifconf);
