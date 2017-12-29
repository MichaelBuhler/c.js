#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "string_utils.h"

char* Identifier_toString(Identifier_node* identifier) {
    char* string = new_string("Identifier ");
    string = concat(string, identifier->name);
    return string;
}

Identifier_node* createIdentifier(char* name) {
    Identifier_node* identifier = (Identifier_node*) calloc(1, sizeof(Identifier_node));
    identifier->name = new_string(name);
    identifier->toString = Identifier_toString;
    return identifier;
}

char* Statement_toString(Statement_node* statement) {
    switch (statement->type) {
        case BLOCK_STATEMENT_TYPE:
            return statement->statementUnion.block->toString(statement->statementUnion.block);
        case VARIABLE_STATEMENT_TYPE:
            return statement->statementUnion.variableStatement->toString(statement->statementUnion.variableStatement);
        case EMPTY_STATEMENT_TYPE:
            return statement->statementUnion.emptyStatement->toString(statement->statementUnion.emptyStatement);
        case EXPRESSION_STATEMENT_TYPE:
            return statement->statementUnion.expressionStatement->toString(statement->statementUnion.expressionStatement);
    }
}

Statement_node* createStatement(StatementType_enum type, void* untypedStatement) {
    Statement_node* statement = (Statement_node*) calloc(1, sizeof(Statement_node));
    statement->type = type;
    statement->statementUnion.any = untypedStatement; // TODO do we need .any ?
    statement->toString = Statement_toString;
    return statement;
}

void StatementList_append(StatementList_node* statementList, Statement_node* statement) {
    statementList->statements = (Statement_node**) realloc(statementList->statements, ( statementList->count + 1 ) * sizeof(Statement_node*) );
    statementList->statements[statementList->count] = statement;
    statementList->count += 1;
}

char* StatementList_toString(StatementList_node* statementList) {
    char* string = new_string("StatementList");
    if ( statementList->count == 0 ) {
        string = concat(string, " (empty)");
        return string;
    }
    for ( int i = 0 ; i < statementList->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp = statementList->statements[i]->toString(statementList->statements[i]);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

StatementList_node* createStatementList(Statement_node* statement) {
    StatementList_node* statementList = (StatementList_node*) calloc(1, sizeof(StatementList_node));
    statementList->count = 0;
    statementList->statements = NULL;
    statementList->append = StatementList_append;
    statementList->toString = StatementList_toString;
    statementList->append(statementList, statement);
    return statementList;
}

char* Block_toString(Block_node* block) {
    char* string = new_string("Block");
    if ( block->statementList == NULL ) {
        string = concat(string, " (empty)");
    } else {
        string = concat(string, "\n");
        char* tmp = block->statementList->toString(block->statementList);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

Block_node* createBlock() {
    Block_node* block = (Block_node*) calloc(1, sizeof(Block_node));
    block->statementList = NULL;
    block->toString = Block_toString;
    return block;
}

void FormalParameterList_append(FormalParameterList_node* formalParameterList, Identifier_node* parameter) {
    formalParameterList->parameters = (Identifier_node**) realloc(formalParameterList->parameters, ( formalParameterList->count + 1 ) * sizeof(Identifier_node*) );
    formalParameterList->parameters[formalParameterList->count] = parameter;
    formalParameterList->count += 1;
}

char* FormalParameterList_toString(FormalParameterList_node* formalParameterList) {
    char* string = new_string("FormalParameterList");
    if ( formalParameterList->count == 0 ) {
        string = concat(string, " (empty)");
        return string;
    }
    for ( int i = 0 ; i < formalParameterList->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp = formalParameterList->parameters[i]->toString(formalParameterList->parameters[i]);
        char* tmp2 = indent(tmp);
        free(tmp);
        string = concat(string, tmp2);
        free(tmp2);
    }
    return string;
}

FormalParameterList_node* createFormalParameterList(Identifier_node* parameter) {
    FormalParameterList_node* formalParameterList = (FormalParameterList_node*) calloc(1, sizeof(FormalParameterList_node));
    formalParameterList->count = 0;
    formalParameterList->parameters = NULL;
    formalParameterList->append = FormalParameterList_append;
    formalParameterList->toString = FormalParameterList_toString;
    formalParameterList->append(formalParameterList, parameter);
    return formalParameterList;
}

char* FunctionDeclaration_toString(FunctionDeclaration_node* functionDeclaration) {
    char* string = new_string("FunctionDeclaration\n");
    char* tmp1 = functionDeclaration->identifier->toString(functionDeclaration->identifier);
    tmp1 = concat(tmp1, "\n");
    if ( functionDeclaration->formalParameterList == NULL ) {
        tmp1 = concat(tmp1, "FormalParameterList (empty)");
    } else {
        char* tmp2 = functionDeclaration->formalParameterList->toString(functionDeclaration->formalParameterList);
        tmp1 = concat(tmp1, tmp2);
        free(tmp2);
    }
    tmp1 = concat(tmp1, "\n");
    char* tmp2 = functionDeclaration->block->toString(functionDeclaration->block);
    tmp1 = concat(tmp1, tmp2);
    free(tmp2);
    tmp2 = indent(tmp1);
    free(tmp1);
    string = concat(string, tmp2);
    free(tmp2);
    return string;
}

FunctionDeclaration_node* createFunctionDeclaration(Identifier_node* identifier, FormalParameterList_node* formalParameterList, Block_node* block) {
    FunctionDeclaration_node* functionDeclaration = (FunctionDeclaration_node*) calloc(1, sizeof(FunctionDeclaration_node));
    functionDeclaration->identifier = identifier;
    functionDeclaration->formalParameterList = formalParameterList;
    functionDeclaration->block = block;
    functionDeclaration->toString = FunctionDeclaration_toString;
    return functionDeclaration;
}

char* SourceElement_toString(SourceElement_node* sourceElement) {
    switch (sourceElement->type) {
        case STATEMENT_SOURCE_ELEMENT_TYPE:
            return sourceElement->sourceElementUnion.statement->toString(sourceElement->sourceElementUnion.statement);
        case FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE:
            return sourceElement->sourceElementUnion.functionDeclaration->toString(sourceElement->sourceElementUnion.functionDeclaration);
    }
}

SourceElement_node* createSourceElement(SourceElementType_enum type, void* untypedSourceElement) {
    SourceElement_node* sourceElement = (SourceElement_node*) calloc(1, sizeof(SourceElement_node));
    sourceElement->type = type;
    sourceElement->sourceElementUnion.any = untypedSourceElement; // TODO do we need .any ?
    sourceElement->toString = SourceElement_toString;
    return sourceElement;
}

void SourceElements_append(SourceElements_node* sourceElements, SourceElement_node* sourceElement) {
    sourceElements->elements = (SourceElement_node**) realloc(sourceElements->elements, ( sourceElements->count + 1 ) * sizeof(SourceElement_node*) );
    sourceElements->elements[sourceElements->count] = sourceElement;
    sourceElements->count += 1;
}

char* SourceElements_toString(SourceElements_node* sourceElements) {
    char* string = new_string("SourceElements");
    for ( int i = 0 ; i < sourceElements->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp = sourceElements->elements[i]->toString(sourceElements->elements[i]);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

SourceElements_node* createSourceElements(SourceElement_node* sourceElement) {
    SourceElements_node* sourceElements = (SourceElements_node*) calloc(1, sizeof(SourceElements_node));
    sourceElements->count = 0;
    sourceElements->elements = NULL;
    sourceElements->append = SourceElements_append;
    sourceElements->toString = SourceElements_toString;
    sourceElements->append(sourceElements, sourceElement);
    return sourceElements;
}

char* Program_toString(Program_node* program) {
    char* string = new_string("Program");
    if ( program->sourceElements != NULL ) {
        string = concat(string, "\n");
        char* tmp = program->sourceElements->toString(program->sourceElements);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

Program_node* createProgram() {
    Program_node* program = (Program_node*) calloc(1, sizeof(Program_node));
    program->sourceElements = NULL;
    program->toString = Program_toString;
    return program;
}

char* VariableStatement_toString(VariableStatement_node* variableStatement) {
    char* string = new_string("VariableStatement\n");
    char* tmp = variableStatement->variableDeclarationList->toString(variableStatement->variableDeclarationList);
    string = concat(string, indent(tmp));
    free(tmp);
    return string;
}

VariableStatement_node* createVariableStatement(VariableDeclarationList_node* variableDeclarationList) {
    VariableStatement_node* variableStatement = (VariableStatement_node*) calloc(1, sizeof(VariableStatement_node));
    variableStatement->variableDeclarationList = variableDeclarationList;
    variableStatement->toString = VariableStatement_toString;
    return variableStatement;
}

char* VariableDeclaration_toString(VariableDeclaration_node* variableDeclaration) {
    char* string = new_string("VariableDeclaration\n");
    char* tmp1 = variableDeclaration->identifier->toString(variableDeclaration->identifier);
    if ( variableDeclaration->initializer != NULL ) {
        tmp1 = concat(tmp1, "\n");
        char* tmp2 = variableDeclaration->initializer->toString(variableDeclaration->initializer);
        tmp1 = concat(tmp1, tmp2);
        free(tmp2);
    }
    char* tmp2 = indent(tmp1);
    free(tmp1);
    string = concat(string, tmp2);
    free(tmp2);
    return string;
}

VariableDeclaration_node*  createVariableDeclaration(Identifier_node* identifier, Initializer_node* initializer) {
    VariableDeclaration_node* variableDeclaration = (VariableDeclaration_node*) calloc(1, sizeof(VariableDeclaration_node));
    variableDeclaration->identifier = identifier;
    variableDeclaration->initializer = initializer;
    variableDeclaration->toString = VariableDeclaration_toString;
    return variableDeclaration;
}

void VariableDeclarationList_append(VariableDeclarationList_node* variableDeclarationList, VariableDeclaration_node* variableDeclaration) {
    variableDeclarationList->variableDeclarations = (VariableDeclaration_node**) realloc(variableDeclarationList->variableDeclarations, ( variableDeclarationList->count + 1 ) * sizeof(VariableDeclaration_node*) );
    variableDeclarationList->variableDeclarations[variableDeclarationList->count] = variableDeclaration;
    variableDeclarationList->count += 1;
}

char* VariableDeclarationList_toString(VariableDeclarationList_node* variableDeclarationList) {
    char* string = new_string("VariableDeclarationList");
    for ( int i = 0 ; i < variableDeclarationList->count ; i++ ) {
        string = concat(string, "\n");
        string = concat(string, indent(variableDeclarationList->variableDeclarations[i]->toString(variableDeclarationList->variableDeclarations[i])));
    }
    return string;
}

VariableDeclarationList_node* createVariableDeclarationList(VariableDeclaration_node* variableDeclaration) {
    VariableDeclarationList_node* variableDeclarationList = (VariableDeclarationList_node*) calloc(1, sizeof(VariableDeclarationList_node));
    variableDeclarationList->count = 0;
    variableDeclarationList->variableDeclarations = NULL;
    variableDeclarationList->append = VariableDeclarationList_append;
    variableDeclarationList->toString = VariableDeclarationList_toString;
    variableDeclarationList->append(variableDeclarationList, variableDeclaration);
    return variableDeclarationList;
}

char* Initializer_toString(Initializer_node* initializer) {
    char* string = new_string("Initializer\n");
    char* tmp = initializer->expression->toString(initializer->expression);
    string = concat(string, indent(tmp));
    free(tmp);
    return string;
}

Initializer_node* createInitializer(Expression_node* expression) {
    Initializer_node* initializer = (Initializer_node*) calloc(1, sizeof(Initializer_node));
    initializer->expression = expression;
    initializer->toString = Initializer_toString;
    return initializer;
}

char* EmptyStatement_toString(EmptyStatement_node* emptyStatement) {
    return new_string("EmptyStatement");
}

EmptyStatement_node* createEmptyStatement() {
    EmptyStatement_node* emptyStatement = (EmptyStatement_node*) calloc(1, sizeof(EmptyStatement_node));
    emptyStatement->toString = EmptyStatement_toString;
    return emptyStatement;
}

char* ExpressionStatement_toString(ExpressionStatement_node* expressionStatement) {
    char* string = new_string("ExpressionStatement\n");
    char* tmp = expressionStatement->expression->toString(expressionStatement->expression);
    string = concat(string, indent(tmp));
    free(tmp);
    return string;
}

ExpressionStatement_node* createExpressionStatement(Expression_node* expression) {
    ExpressionStatement_node* expressionStatement = (ExpressionStatement_node*) calloc(1, sizeof(ExpressionStatement_node));
    expressionStatement->expression = expression;
    expressionStatement->toString = ExpressionStatement_toString;
    return expressionStatement;
}

char* Expression_toString(Expression_node* expression) {
    switch (expression->type) {
        case THIS_EXPRESSION_TYPE:
            return new_string("this");
        case IDENTIFIER_EXPRESSION_TYPE:
            return expression->expressionUnion.identifier->toString(expression->expressionUnion.identifier);
        case ASSIGNMENT_EXPRESSION_TYPE:
            return expression->expressionUnion.assignmentExpression->toString(expression->expressionUnion.assignmentExpression);
        case LITERAL_EXPRESSION_TYPE:
            return expression->expressionUnion.literal->toString(expression->expressionUnion.literal);
        case CALL_EXPRESSION_TYPE:
            return expression->expressionUnion.callExpression->toString(expression->expressionUnion.callExpression);
    }
}

Expression_node* createExpression(ExpressionType_enum type, void* untypedExpression) {
    Expression_node* expression = (Expression_node*) calloc(1, sizeof(Expression_node));
    expression->type = type;
    expression->expressionUnion.any = untypedExpression; // TODO do we need .any ?
    expression->toString = Expression_toString;
    return expression;
}

char* AssignmentExpression_toString(AssignmentExpression_node* assignmentExpression) {
    char* string = new_string("AssignmentExpression\n");
    char* tmp1 = assignmentExpression->identifier->toString(assignmentExpression->identifier);
    tmp1 = concat(tmp1, "\n");
    switch (assignmentExpression->assignmentOperator) {
        case EQUALS_ASSIGNMENT_OPERATOR:
            tmp1 = concat(tmp1, "=");
            break;
    }
    tmp1 = concat(tmp1, "\n");
    char* tmp2 = assignmentExpression->expression->toString(assignmentExpression->expression);
    tmp1 = concat(tmp1, tmp2);
    free(tmp2);
    tmp2 = indent(tmp1);
    free(tmp1);
    string = concat(string, tmp2);
    free(tmp2);
    return string;
}

AssignmentExpression_node* createAssignmentExpression(Identifier_node* identifier/* TODO needs to be LeftHandSideExpression_node */, AssignmentOperator_enum assignmentOperator, Expression_node* expression) {
    AssignmentExpression_node* assignmentExpression = (AssignmentExpression_node*) calloc(1, sizeof(AssignmentExpression_node));
    assignmentExpression->identifier = identifier;
    assignmentExpression->assignmentOperator = assignmentOperator;
    assignmentExpression->expression = expression;
    assignmentExpression->toString = AssignmentExpression_toString;
    return assignmentExpression;
}

char* CallExpression_toString(CallExpression_node* callExpression) {
    char* string = new_string("CallExpression\n");
    char* tmp = new_string("Function\n");
    tmp = concat(tmp, indent(callExpression->function->toString(callExpression->function)));
    char* tmp2 = indent(tmp);
    string = concat(string, tmp2);
    free(tmp2);
    free(tmp);
    string = concat(string, "\n");
    if ( callExpression->argumentList == NULL ) {
        char* tmp = indent("ArgumentList (empty)");
        string = concat(string, tmp);
        free(tmp);
    } else {
        char* tmp1 = callExpression->argumentList->toString(callExpression->argumentList);
        char* tmp2 = indent(tmp1);
        free(tmp1);
        string = concat(string, tmp2);
        free(tmp2);
    }
    return string;
}

CallExpression_node* createCallExpression(Expression_node* function, ArgumentList_node* argumentList) {
    CallExpression_node* callExpression = (CallExpression_node*) calloc(1, sizeof(CallExpression_node));
    callExpression->function = function;
    callExpression->argumentList = argumentList;
    callExpression->toString = CallExpression_toString;
    return callExpression;
}

void ArgumentList_append(ArgumentList_node* argumentList, Expression_node* argument) {
    argumentList->arguments = (Expression_node**) realloc(argumentList->arguments, ( argumentList->count + 1 ) * sizeof(Expression_node*) );
    argumentList->arguments[argumentList->count] = argument;
    argumentList->count += 1;
}

char* ArgumentList_toString(ArgumentList_node* argumentList) {
    char* string = new_string("ArgumentList");
    for ( int i = 0 ; i < argumentList->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp1 = argumentList->arguments[i]->toString(argumentList->arguments[i]);
        char* tmp2 = indent(tmp1);
        free(tmp1);
        string = concat(string, tmp2);
        free(tmp2);
    }
    return string;
}

ArgumentList_node* createArgumentList(Expression_node* argument) {
    ArgumentList_node* argumentList = (ArgumentList_node*) calloc(1, sizeof(ArgumentList_node));
    argumentList->count = 0;
    argumentList->arguments = NULL;
    argumentList->append = ArgumentList_append;
    argumentList->toString = ArgumentList_toString;
    argumentList->append(argumentList, argument);
    return argumentList;
}

char* Literal_toString(Literal_node* literal) {
    switch (literal->type) {
        case NULL_LITERAL_TYPE:
            return literal->literalUnion.nullLiteral->toString(literal->literalUnion.nullLiteral);
        case BOOLEAN_LITERAL_TYPE:
            return literal->literalUnion.booleanLiteral->toString(literal->literalUnion.booleanLiteral);
        case NUMBER_LITERAL_TYPE:
            return literal->literalUnion.numberLiteral->toString(literal->literalUnion.numberLiteral);
        case STRING_LITERAL_TYPE:
            return literal->literalUnion.stringLiteral->toString(literal->literalUnion.stringLiteral);
    }
}

Literal_node* createLiteral(LiteralType_enum type, void* untypedLiteral) {
    Literal_node* literal = (Literal_node*) calloc(1, sizeof(Literal_node));
    literal->type = type;
    literal->literalUnion.any = untypedLiteral; // TODO do we need .any ?
    literal->toString = Literal_toString;
    return literal;
}

char* NullLiteral_toString(NullLiteral_node* nullLiteral) {
    return new_string("null");
}

NullLiteral_node* createNullLiteral() {
    NullLiteral_node* nullLiteral = (NullLiteral_node*) calloc(1, sizeof(NullLiteral_node));
    nullLiteral->toString = NullLiteral_toString;
    return nullLiteral;
}

char* BooleanLiteral_toString(BooleanLiteral_node* booleanLiteral) {
    if (booleanLiteral->boolean) {
        return new_string("BooleanLiteral true");
    } else {
        return new_string("BooleanLiteral false");
    }
}

BooleanLiteral_node* createBooleanLiteral(char boolean) {
    BooleanLiteral_node* booleanLiteral = (BooleanLiteral_node*) calloc(1, sizeof(BooleanLiteral_node));
    booleanLiteral->boolean = boolean;
    booleanLiteral->toString = BooleanLiteral_toString;
    return booleanLiteral;
}

char* NumberLiteral_toString(NumberLiteral_node* numberLiteral) {
    char* string = new_string("NumberLiteral ");
    char* tmp = (char*) calloc(100, sizeof(char));
    sprintf(tmp, "%.18e", numberLiteral->number);
    tmp = (char*) realloc(tmp, strlen(tmp)+1);
    string = concat(string, tmp);
    free(tmp);
    return string;
}

NumberLiteral_node* createNumberLiteral(double number) {
    NumberLiteral_node* numberLiteral = (NumberLiteral_node*) calloc(1, sizeof(NumberLiteral_node));
    numberLiteral->number = number;
    numberLiteral->toString = NumberLiteral_toString;
    return numberLiteral;
}

char* StringLiteral_toString(StringLiteral_node* stringLiteral) {
    char* string = new_string("\"");
    for ( int i =  0 ; i < strlen(stringLiteral->string) ; i++ ) {
        switch (stringLiteral->string[i]) {
            case '\b': string = concat(string, "\\b");  break; // \b backspace
            case '\f': string = concat(string, "\\f");  break; // \f form feed
            case '\n': string = concat(string, "\\n");  break; // \n line feed (new line)
            case '\r': string = concat(string, "\\r");  break; // \r carriage return
            case '\t': string = concat(string, "\\t");  break; // \t horizontal tab
            case '"':  string = concat(string, "\\\""); break; // \" double quotation mark
            default:   string = concatc(string, stringLiteral->string[i]);
        }
    }
    string = concat(string, "\"");
    return string;
}

StringLiteral_node* createStringLiteral(char* string) {
    StringLiteral_node* stringLiteral = (StringLiteral_node*) calloc(1, sizeof(StringLiteral_node));
    stringLiteral->string = new_string(string);
    stringLiteral->toString = StringLiteral_toString;
    return stringLiteral;
}
