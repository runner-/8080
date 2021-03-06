#include	<stdio.h>
#include	<errno.h>
#include	<string.h>
#include	"i8080.h"

static	u8	mem[65536];

int	gethexfile(char *);

int	main(int argc, char **argv, char **env)
{
	int	i;
	i8080	*cpu;

	cpu = i8080_new();
	if(gethexfile(argv[1])) {
		return 1;
	}
	i8080_dump(NULL, NULL);
	for(i=0; i<64; i++) {
		i8080_dump(cpu, mem);
		if(i8080_run(cpu, mem)) break;
	}
	return 0;
}

int	gethexfile(char *fname)
{
	char	buf[256], tmp[8];
	int	i, len, adr, data;
	FILE	*fp;

	fp = fopen(fname, "r");
	if(fp == NULL) {
		printf("%s %s\n", fname, strerror(errno));
		return 1;
	}
	while(fgets(buf, sizeof(buf), fp)) {
		if(buf[0] != ':') {
			printf("illegal format %s", buf);
			return 1;
		}
		tmp[0] = buf[1];
		tmp[1] = buf[2];
		tmp[2] = '\0';
		sscanf(tmp, "%x", &len);
		tmp[0] = buf[3];
		tmp[1] = buf[4];
		tmp[2] = buf[5];
		tmp[3] = buf[6];
		tmp[4] = '\0';
		sscanf(tmp, "%x", &adr);
		for(i=0; i<len; i++) {
			tmp[0] = buf[i*2+9];
			tmp[1] = buf[i*2+10];
			tmp[2] = '\0';
			sscanf(tmp, "%x", &data);
			mem[adr+i] = (u8)data;
			/* printf("%04X %02X\n", adr+i, data); */
		}
	}
	return 0;
}

u8 i8080_in(u8 port)
{
 printf("IN %02X 1\n", port);
 return 1;
}

void i8080_out(u8 data, u8 port)
{
	printf("OUT %02X %02X\n", port, data);
}
