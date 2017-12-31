import test from 'ava';
import runner from './runner';

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

test.cb('Empty Block', runner(function () {
    {}
}));

test.cb('Function Definition, Zero Arguments, Empty Block', runner(function () {
    function buhler () {
    }
}));

test.cb('Function Definition, One Argument, Empty Block', runner(function () {
    function buhler (michael) {
    }
}));

test.cb('Function Definition, Multiple Arguments, Empty Block', runner(function () {
    function buhler (michael, other, another) {
    }
}));

test.cb('Function Definition, Zero Arguments, Non-Empty Block', runner(function () {
    function buhler () {
        var michael;
        var other;
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

test.cb('Variable Declaration, Initialize to Single Quote String, with Escape Characters', runner(function () {
    var buhler = 'mi\nc\'h\tae"l';
}));

test.cb('Variable Declaration, Initialize to Double Quote String', runner(function () {
    var buhler = "michael";
}));

test.cb('Variable Declaration, Initialize to Double Quote String, with Escape Characters', runner(function () {
    var buhler = "mi\nc\"h\tae'l";
}));

test.cb('Variable Declaration, Initialize to Call Expression, Zero Arguments', runner(function () {
    var buhler = michael();
}));

test.cb('Variable Declaration, Initialize to Call Expression, One Argument', runner(function () {
    var buhler = michael(buhler);
}));

test.cb('Variable Declaration, Initialize to Call Expression, Multiple Arguments', runner(function () {
    var buhler = michael(buhler, other);
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

test.cb('Variable Assignment, to Single Quote String', runner(function () {
    var buhler;
    buhler = 'michael';
}));

test.cb('Variable Assignment, to Single Quote String, with Escape Characters', runner(function () {
    var buhler;
    buhler = 'mi\nc\'h\tae"l';
}));

test.cb('Variable Assignment, to Double Quote String', runner(function () {
    var buhler;
    buhler = "michael";
}));

test.cb('Variable Assignment, to Double Quote String, with Escape Characters', runner(function () {
    var buhler;
    buhler = "mi\nc\"h\tae'l";
}));

test.cb('Variable Assignment, to Call Expression, Zero Arguments', runner(function () {
    var buhler;
    buhler = michael();
}));

test.cb('Variable Assignment, to Call Expression, One Argument', runner(function () {
    var buhler;
    buhler = michael(buhler);
}));

test.cb('Variable Assignment, to Call Expression, Multiple Arguments', runner(function () {
    var buhler;
    buhle = michael(buhler, other);
}));

test.cb('Parenthesis', runner(function () {
    (true);
    var buhler = (null);
}));

test.cb('Multiple Variable Declaration', runner(function () {
    var buhler, michael;
}));

test.cb('Multiple Variable Declaration, Mixed Initialization', runner(function () {
    var buhler = michael, other = true, another;
}));

test.cb('Return Statement', runner(function () {
    return;
}));

test.cb('Return Statement, with Expression', runner(function () {
    return buhler;
}));
