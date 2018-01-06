const child_process = require('child_process');
const fs = require('fs');

const chalk = require('chalk');

if (!fs.existsSync('out/test')) fs.mkdirSync('out/test');

module.exports = function (wrappedCode, expectedOutput) {
    wrappedCode = wrappedCode.toString();
    const code = wrappedCode.substring(wrappedCode.indexOf('{')+1, wrappedCode.lastIndexOf('}'));
    const filename = 'test' + Math.floor(Math.random()*100000000);

    function execute(t) {
        const child = child_process.spawn('out/test/'+filename);
        child.stdin.end(code);

        let stdout = '';
        child.stdout.on('data', function (data) {
            return stdout += String(data);
        });

        let stderr = '';
        child.stderr.on('data', function (data) {
            return stderr += String(data);
        });

        child.on('close', function (code) {
            if ( code === 0 ) {
                if ( stdout === expectedOutput) {
                    t.pass();
                } else {
                    console.error(chalk.red('expected: '+JSON.stringify(expectedOutput)));
                    console.error(chalk.red('actual:   '+JSON.stringify(stdout)));
                    t.fail(chalk.red.bold('output did not match expectations'));
                }
            } else {
                const message = chalk.red.bold(stderr);
                console.error(chalk.red(stdout));
                console.error(message);
                t.fail(message);
            }
            t.end();
        });
    }

    function compile(t) {
        const child = child_process.spawn('gcc', [
            '-I', 'src',
            '-o', 'out/test/'+filename,
            'out/test/'+filename+'.c',
            'src/runtime.c',
            'src/hashtable.c'
        ]);
        child.stdin.end(code);

        let stdout = '';
        child.stdout.on('data', function (data) {
            return stdout += String(data);
        });

        let stderr = '';
        child.stderr.on('data', function (data) {
            return stderr += String(data);
        });

        child.on('close', function (code) {
            if ( code === 0 ) {
                execute(t);
            } else {
                const message = chalk.red.bold(stderr);
                console.error(chalk.red(stdout));
                console.error(message);
                t.fail(message);
            }
        });

    }

    return function (t) {
        t.plan(1);

        const child = child_process.spawn('out/transpiler', ['--stdin']);
        child.stdin.end(code);

        let stdout = '';
        child.stdout.on('data', function (data) {
            return stdout += String(data);
        });

        let stderr = '';
        child.stderr.on('data', function (data) {
            return stderr += String(data);
        });

        child.on('close', function (code) {
            if ( code === 0 ) {
                fs.writeFileSync('out/test/'+filename+'.c', stdout);
                compile(t);
            } else {
                const message = chalk.red.bold(stderr);
                console.error(chalk.red(stdout));
                console.error(message);
                t.fail(message);
            }
        });
    }
};
