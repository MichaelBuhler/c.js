const child_process = require('child_process');
const chalk = require('chalk');

module.exports = function (wrappedCode) {
    wrappedCode = wrappedCode.toString();
    const code = wrappedCode.substring(wrappedCode.indexOf('{')+1, wrappedCode.lastIndexOf('}'));

    return function (t) {
        t.plan(1);

        const child = child_process.spawn('out/transpiler');
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
                t.pass();
            } else {
                const message = chalk.red.bold(stderr);
                console.error(chalk.red(stdout));
                console.error(message);
                t.fail(message);
            }
            t.end();
        });
    }
};
