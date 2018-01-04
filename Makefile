transpiler: out/transpiler

out/transpiler: out/flex.c out/bison.c src/main.c src/args.c src/node.c src/string_utils.c
	gcc -o out/transpiler -I src out/flex.c out/bison.c src/main.c src/args.c src/node.c src/string_utils.c

out/flex.c: src/flex.l
	flex --outfile out/flex.c src/flex.l

out/bison.c: src/bison.y
	bison --verbose --defines --output-file out/bison.c src/bison.y

test: out/transpiler node_modules/.bin/ava
	node_modules/.bin/ava test/**/*.test.js --verbose

node_modules/.bin/ava:
	npm install

clean:
	rm -frv out/*

sample: out/sample
	out/sample

out/sample: out/sample.c src/runtime.h src/runtime.c
	gcc -o out/sample -I src out/sample.c src/runtime.c

out/sample.c: sample.js out/transpiler
	cat sample.js | out/transpiler --stdin > out/sample.c

.PHONY: test sample clean
