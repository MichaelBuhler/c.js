const child_process = require('child_process');

import test from 'ava';
const chalk = require('chalk');

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
            else t.fail(chalk.red.bold(stderr));
            t.end();
        });
    });
});
