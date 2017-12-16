const child_process = require('child_process');

const tests = [{
    name: 'Variable Definition',
    code: 'var buhler;'
},{
    name: 'Variable Definition and Assignment',
    code: 'var buhler = michael;'
},{
    name: 'Function Definition',
    code: 'function buhler() {}'
},{
    name: 'MemberExpression',
    code: 'buhler();'
}];

const formatWidth = tests.reduce(function (currentValue, test) {
    return Math.max(currentValue, test.name.length);
}, -1) + 3;

tests.forEach(function (test) {
    const child = child_process.spawn('out/transpiler');
    child.stdin.end(test.code);
    let stdout = '';
    child.stdout.on('data', function (data) {
        stdout += String(data);
    });
    let stderr = '';
    child.stderr.on('data', function (data) {
        stderr += String(data);
    });
    child.on('close', function (code) {
        let output = 'test \'' + test.name + '\':';
        for (let i = formatWidth - test.name.length ; i ; i-- ) output += ' ';
        console.log( output + ( code === 0 ? '\x1b[1;32mPass\x1b[0m' : '\x1b[1;31mFail\x1b[0m' ));
        if ( code !== 0 ) {
            //console.error(stdout);
            console.error(stderr);
        }
    });
});
