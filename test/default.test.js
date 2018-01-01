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

test.cb('Empty Statement', runner(function () {
    ;
}));

test.cb('Parenthesis', runner(function () {
    (true);
    var buhler = (null);
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

test.cb('Variable Declaration', runner(function () {
    var buhler;
}));

test.cb('Multiple Variable Declaration', runner(function () {
    var buhler, michael;
}));

test.cb('Multiple Variable Declaration, Mixed Initialization', runner(function () {
    var buhler = michael, other = true, another;
}));

test.cb('Multiple Variable Declaration, Multiple Initialization', runner(function () {
    var buhler = michael, other = another;
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

test.cb('Variable Declaration, Initialize to Member Expression, with Dot Notation', runner(function () {
    var buhler = michael.other;
}));

test.cb('Variable Declaration, Initialize to Member Expression, with Chained Dot Notation', runner(function () {
    var buhler = michael.other.another;
}));

test.cb('Variable Declaration, Initialize to Member Expression, with Bracket Notation, with String Literal', runner(function () {
    var buhler = michael['other'];
}));

test.cb('Variable Declaration, Initialize to Member Expression, with Bracket Notation, with Expression', runner(function () {
    var buhler = michael[other];
}));

test.cb('Variable Declaration, Initialize to Member Expression, with Chained Bracket Notation, with String Literals', runner(function () {
    var buhler = michael['other']['another'];
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Other Variable', runner(function () {
    buhler = michael;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to This', runner(function () {
    buhler = this;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Null', runner(function () {
    buhler = null;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to True', runner(function () {
    buhler = true;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to False', runner(function () {
    buhler = false;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Integer', runner(function () {
    buhler = 123;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Floating Point', runner(function () {
    buhler = 123.456;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Single Quote String', runner(function () {
    buhler = 'michael';
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Single Quote String, with Escape Characters', runner(function () {
    buhler = 'mi\nc\'h\tae"l';
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Double Quote String', runner(function () {
    buhler = "michael";
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Double Quote String, with Escape Characters', runner(function () {
    buhler = "mi\nc\"h\tae'l";
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Call Expression, Zero Arguments', runner(function () {
    buhler = michael();
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Call Expression, One Argument', runner(function () {
    buhler = michael(buhler);
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Call Expression, Multiple Arguments', runner(function () {
    buhler = michael(buhler, other);
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Member Expression, with Dot Notation', runner(function () {
    buhler = michael.other;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Member Expression, with Chained Dot Notation', runner(function () {
    buhler = michael.other.another;
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Member Expression, with Bracket Notation, with String Literal', runner(function () {
    buhler = michael['other'];
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Member Expression, with Bracket Notation, with Expression', runner(function () {
    buhler = michael[other];
}));

test.cb('Assignment Expression, with Left Hand Identifier, to Member Expression, with Chained Bracket Notation, with String Literals', runner(function () {
    buhler = michael['other']['another'];
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Other Variable', runner(function () {
    buhler.member = michael;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to This', runner(function () {
    buhler.member = this;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Null', runner(function () {
    buhler.member = null;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to True', runner(function () {
    buhler.member = true;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to False', runner(function () {
    buhler.member = false;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Integer', runner(function () {
    buhler.member = 123;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Floating Point', runner(function () {
    buhler.member = 123.456;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Single Quote String', runner(function () {
    buhler.member = 'michael';
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Single Quote String, with Escape Characters', runner(function () {
    buhler.member = 'mi\nc\'h\tae"l';
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Double Quote String', runner(function () {
    buhler.member = "michael";
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Double Quote String, with Escape Characters', runner(function () {
    buhler.member = "mi\nc\"h\tae'l";
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Call Expression, Zero Arguments', runner(function () {
    buhler.member = michael();
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Call Expression, One Argument', runner(function () {
    buhler.member = michael(buhler);
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Call Expression, Multiple Arguments', runner(function () {
    buhler.member = michael(buhler, other);
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Member Expression, with Dot Notation', runner(function () {
    buhler.member = michael.other;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Member Expression, with Chained Dot Notation', runner(function () {
    buhler.member = michael.other.another;
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Member Expression, with Bracket Notation, with String Literal', runner(function () {
    buhler.member = michael['other'];
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Member Expression, with Bracket Notation, with Expression', runner(function () {
    buhler.member = michael[other];
}));

test.cb('Assignment Expression, with Left Hand Dot Member Expression, to Member Expression, with Chained Bracket Notation, with String Literals', runner(function () {
    buhler.member = michael['other']['another'];
}));

test.cb('Return Statement', runner(function () {
    return;
}));

test.cb('Return Statement, with Expression', runner(function () {
    return buhler;
}));
