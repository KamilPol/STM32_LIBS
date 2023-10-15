int __errno;
void *__dso_handle = (void *)&__dso_handle;

void _init(void) {}
void _fini(void) {}
void _kill(void) {}
void _close(void) {}
void _lseek(void) {}
void _read(void) {}
void _write(void) {}

int _getpid(void)
{
	return 0;
}

void _exit(void)
{
	while (1);
}