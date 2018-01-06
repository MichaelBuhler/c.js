import test from 'ava';
import executor from './executor';

test.cb('Empty Program', executor(function () {
}, ''));

test.cb('Empty Block', executor(function () {
    {}
}, ''));

test.cb('Hello World', executor(function () {
    console.log('Hello, World!');
}, 'Hello, World!\n'));
