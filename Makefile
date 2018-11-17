ifndef OPT_LEVEL
	OPT_LEVEL = 2
endif

ifndef ARGS
	ARGS = abcdefgh foo bar baz beepboop "Nicolas Cage" Lit😂🔥
endif

run_test:
	[ -e build/ ] || mkdir build
	gcc -O${OPT_LEVEL} ${C_FLAGS} src/*.c test/*.c -o build/test
	${DB} ./build/test ${ARGS}
