import test from 'ava';
import runner from './runner';

test.cb('Empty Block', runner(function () {
    {}
}));

test.cb('Function Definition', runner(function () {
    function buhler () {
    }
}));

test.cb('Function Definitions', runner(function () {
    function michael () {}
    function buhler () {
    }
}));

test.cb('Empty Statement', runner(function () {
    ;
}));

test.cb('Empty Statements', runner(function () {
    ;
    ;;
    ;;;
}));

test.cb('Variable Declaration', runner(function () {
    var buhler;
}));

test.cb('Variable Declaration List', runner(function () {
    var michael, buhler;
}));

test.cb('Single Line Comment', runner(function () {
    // this is a comment
}));

test.cb('Multi Line Comment', runner(function () {
    var michael;
    /* this is a
     * multiline comment
     */
    var buhler;
}));
