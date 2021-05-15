namespace io {
	const int size = 1e7 + 10;
	char buff[size];
	char *l, *r;
	inline void init() {
		l = buff;
		r = buff + fread(buff, 1, size, stdin);
	}
	inline char gc() {
		if(l == r) init();
		return (l != r) ? *(l ++) : EOF;
	}
	void read(int &n) {
		n = 0; char c = gc();
		while(!isdigit(c)) c = gc();
		while(isdigit(c)) n = n * 10 + c - '0', c = gc();
	}
} using io::read;
