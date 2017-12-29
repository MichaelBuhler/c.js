import test from 'ava';
import runner from './runner';

test.cb('Empty Block', runner(function () {
    {}
}));

test.cb('Zero Argument Function Definition Empty Block', runner(function () {
    function buhler () {
    }
}));

test.cb('Zero Argument Function Definition Block Statement List', runner(function () {
    function buhler () {
        var michael;
        var other;
    }
}));

test.cb('One Argument Function Definition Empty Block', runner(function () {
    function buhler (michael) {
    }
}));

test.cb('Multi Argument Function Definition Empty Block', runner(function () {
    function buhler (michael, other, another) {
    }
}));

test.cb('Empty Statement', runner(function () {
    ;
}));

test.cb('Variable Declaration', runner(function () {
    var buhler;
}));

test.cb('Variable Declaration, Initialize to Other Variable', runner(function () {
    var buhler = michael;
}));

test.cb('Variable Declaration, Initialize to This', runner(function () {
    var buhler = this;
}));

test.cb('Variable Declaration, Initialize to Null', runner(function () {
    var buhler = null;
}));

test.cb('Variable Declaration, Initialize to True', runner(function () {
    var buhler = null;
}));

test.cb('Variable Declaration, Initialize to False', runner(function () {
    var buhler = null;
}));

test.cb('Variable Declaration, Initialize to Integer', runner(function () {
    var buhler = 123;
}));

test.cb('Variable Declaration, Initialize to Floating Point', runner(function () {
    var buhler = 123.456;
}));

test.cb('Variable Declaration, Initialize to Single Quote String', runner(function () {
    var buhler = 'michael';
}));

test.cb('Variable Declaration, Initialize to Single Quote String, Escape Characters', runner(function () {
    var buhler = 'mi\nc\'h\tae"l';
}));

test.cb('Variable Declaration, Initialize to Double Quote String', runner(function () {
    var buhler = "michael";
}));

test.cb('Variable Declaration, Initialize to Double Quote String, Escape Characters', runner(function () {
    var buhler = "mi\nc\"h\tae'l";
}));

test.cb('Multiple Variable Declaration', runner(function () {
    var buhler, michael;
}));

test.cb('Multiple Variable Declaration, Multiple Initialization', runner(function () {
    var buhler = michael, other = another;
}));

test.cb('Variable Assignment, to Other Variable', runner(function () {
    var buhler;
    buhler = michael;
}));

test.cb('Variable Assignment, to This', runner(function () {
    var buhler;
    buhler = this;
}));

test.cb('Variable Assignment, to Null', runner(function () {
    var buhler;
    buhler = null;
}));

test.cb('Variable Assignment, to True', runner(function () {
    var buhler;
    buhler = true;
}));

test.cb('Variable Assignment, to False', runner(function () {
    var buhler;
    buhler = false;
}));

test.cb('Variable Assignment, to Integer', runner(function () {
    var buhler;
    buhler = 123;
}));

test.cb('Variable Assignment, to Floating Point', runner(function () {
    var buhler;
    buhler = 123.456;
}));

test.cb('Variable Assignment, Initialize to Single Quote String', runner(function () {
    var buhler;
    buhler = 'michael';
}));

test.cb('Variable Assignment, Initialize to Single Quote String, Escape Characters', runner(function () {
    var buhler;
    buhler = 'mi\nc\'h\tae"l';
}));

test.cb('Variable Assignment, Initialize to Double Quote String', runner(function () {
    var buhler;
    buhler = "michael";
}));

test.cb('Variable Assignment, Initialize to Double Quote String, Escape Characters', runner(function () {
    var buhler;
    buhler = "mi\nc\"h\tae'l";
}));

test.cb('Parenthesis', runner(function () {
    (true);
    var buhler = (null);
}));

test.cb('Multiple Variable Declaration, Mixed Initialization', runner(function () {
    var buhler = michael, other = true, another;
}));

test.cb('Single Line Comment', runner(function () {
    // this is a comment
}));

test.cb('Multi Line Comment', runner(function () {
    var buhler;
    /* this is a
     * multiline comment
     */
    var michael;
}));
