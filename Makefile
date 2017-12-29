transpiler: out/transpiler

out/transpiler: out src/main.c src/node.c out/bison.c out/flex.c
	gcc -o out/transpiler -I src src/main.c src/node.c out/bison.c out/flex.c

out/flex.c: out src/flex.l
	flex --outfile out/flex.c src/flex.l

out:
	mkdir out

out/bison.c: out src/bison.y
	bison --verbose --defines --output-file out/bison.c src/bison.y

clean:
	rm -fr out

test: transpiler
	node_modules/.bin/ava test/**/*.test.js

test-verbose: transpiler
	node_modules/.bin/ava test/**/*.test.js --verbose

.PHONY: test test-verbose clean
