import test from 'ava';

const child_process = require('child_process');

const scenarios = [{
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
    code: 'buhler();',
    failing: true
}];

scenarios.forEach(function (scenario) {
    (scenario.failing?test.cb.failing:test.cb)(scenario.name, function (t) {
        t.plan(1);

        const child = child_process.spawn('out/transpiler');
        child.stdin.end(scenario.code);

        let stderr = '';
        child.stderr.on('data', function (data) {
            return stderr += String(data);
        });

        child.on('close', function (code) {
            if ( code === 0 ) t.pass();
            else t.fail('\x1b[1;31m' + stderr + '\x1b[0m');
            t.end();
        });
    });
});
