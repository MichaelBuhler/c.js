transpiler: out/transpiler

out/transpiler: out out/bison.c out/flex.c
	gcc out/bison.c out/flex.c -o out/transpiler

out/flex.c: out src/flex.l out/bison.h
	flex --outfile out/flex.c src/flex.l

out:
	mkdir out

out/bison.c: out src/bison.y
	bison --defines --output-file out/bison.c src/bison.y

clean:
	rm -fr out

test: transpiler
	node_modules/.bin/ava

test-verbose: transpiler
	node_modules/.bin/ava --verbose

.PHONY: all test test-verbose clean
