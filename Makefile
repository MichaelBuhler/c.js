transpiler: out/flex.c out/bison.c src/main.c src/args.c src/node.c src/string_utils.c
	gcc -o transpiler -I src out/flex.c out/bison.c src/main.c src/args.c src/node.c src/string_utils.c

out:
	mkdir out

out/flex.c: out src/flex.l
	flex --outfile out/flex.c src/flex.l

out/bison.c: out src/bison.y
	bison --verbose --defines --output-file out/bison.c src/bison.y

test: transpiler node_modules/.bin/ava
	node_modules/.bin/ava test/**/*.test.js --verbose

node_modules/.bin/ava:
	npm install

clean:
	rm -frv out transpiler

.PHONY: test clean
