#pragma once
#define	htobe32(_x)	__htonl(_x)		// __bswap32(_x)
#define	htobe16(_x)	__htons(_x)		// __bswap16(_x)
#define	be32toh(_x)	__ntohl(_x)		//__bswap32(_x)
#define	be16toh(_x)	__ntohs(_x)		//__bswap16(_x)
#define htobe64(_x)	__bswap64(_x)
#define be64toh(_x) __bswap64(_x)
