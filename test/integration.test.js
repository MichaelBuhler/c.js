import test from 'ava';
import executor from './executor';

test.cb('Empty Program', executor(function () {
}, ''));

test.cb('Empty Block', executor(function () {
    {}
}, ''));

