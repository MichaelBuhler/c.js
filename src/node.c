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

char* Identifier_toCode(Identifier_node* identifier) {
    return new_string(identifier->name);
}

Identifier_node* createIdentifier(char* name) {
    Identifier_node* identifier = (Identifier_node*) calloc(1, sizeof(Identifier_node));
    identifier->name = new_string(name);
    identifier->toString = Identifier_toString;
    identifier->toCode = Identifier_toCode;
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
        case RETURN_STATEMENT_TYPE:
            return statement->statementUnion.returnStatement->toString(statement->statementUnion.returnStatement);
    }
}

char* Statement_toCode(Statement_node* statement) {
    switch (statement->type) {
        case BLOCK_STATEMENT_TYPE:
            return statement->statementUnion.block->toCode(statement->statementUnion.block, 0);
        case VARIABLE_STATEMENT_TYPE:
            return statement->statementUnion.variableStatement->toCode(statement->statementUnion.variableStatement);
        case EMPTY_STATEMENT_TYPE:
            return statement->statementUnion.emptyStatement->toCode(statement->statementUnion.emptyStatement);
        case EXPRESSION_STATEMENT_TYPE:
            return statement->statementUnion.expressionStatement->toCode(statement->statementUnion.expressionStatement);
        case RETURN_STATEMENT_TYPE:
            return statement->statementUnion.returnStatement->toCode(statement->statementUnion.returnStatement);
    }
}

Statement_node* createStatement(StatementType_enum type, void* untypedStatement) {
    Statement_node* statement = (Statement_node*) calloc(1, sizeof(Statement_node));
    statement->type = type;
    statement->statementUnion.any = untypedStatement; // TODO do we need .any ?
    statement->toString = Statement_toString;
    statement->toCode = Statement_toCode;
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
        string = concat_indent(string, tmp);
        free(tmp);
    }
    return string;
}

char* StatementList_toCode(StatementList_node* statementList) {
    char* code = new_string("");
    for ( int i = 0 ; i < statementList->count ; i++ ) {
        Statement_node* statement = statementList->statements[i];
        if ( i > 0 ) code = concat(code, "\n");
        char* tmp = statement->toCode(statement);
        code = concat(code, tmp);
        free(tmp);
    }
    return code;
}

StatementList_node* createStatementList(Statement_node* statement) {
    StatementList_node* statementList = (StatementList_node*) calloc(1, sizeof(StatementList_node));
    statementList->count = 0;
    statementList->statements = NULL;
    statementList->append = StatementList_append;
    statementList->toString = StatementList_toString;
    statementList->toCode = StatementList_toCode;
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
        string = concat_indent(string, tmp);
        free(tmp);
    }
    return string;
}

char* Block_toCode(Block_node* block, char isFunction) {
    char* code = new_string("{\n");
    if ( block->statementList == NULL ) {
        code = concat_indent(code, "// empty block");
    } else {
        char* tmp = block->statementList->toCode(block->statementList);
        code = concat_indent(code, tmp);
        free(tmp);
    }
    if (isFunction) {
        code = concat(code, "\n");
        ReturnStatement_node* returnStatement = createReturnStatement(NULL);
        char* tmp = returnStatement->toCode(returnStatement);
        free(returnStatement);
        code = concat_indent(code, tmp);
        free(tmp);
    }
    code = concat(code, "\n}");
    return code;
}

Block_node* createBlock() {
    Block_node* block = (Block_node*) calloc(1, sizeof(Block_node));
    block->statementList = NULL;
    block->toString = Block_toString;
    block->toCode = Block_toCode;
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
        string = concat_indent(string, tmp);
        free(tmp);
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
    string = concat_indent(string, tmp1);
    free(tmp1);
    return string;
}

char* FunctionDeclaration_toCode(FunctionDeclaration_node* functionDeclaration) {
    char* code = new_string("static return_t ");
    code = concat(code, functionDeclaration->identifier->toCode(functionDeclaration->identifier));
    code = concat(code, "(");
    if ( functionDeclaration->formalParameterList != NULL ) {
        // TODO move this to formalParameterList->toCode()
        Identifier_node** parameters = functionDeclaration->formalParameterList->parameters;
        code = concat(code, "variable ");
        code = concat(code, parameters[0]->name);
        for ( int j = 1; j < functionDeclaration->formalParameterList->count; j++ ) {
            code = concat(code, ", variable ");
            code = concat(code, parameters[j]->name);
        }
    }
    code = concat(code, ") ");
    char* tmp = functionDeclaration->block->toCode(functionDeclaration->block, 1);
    code = concat(code, tmp);
    free(tmp);
    code = concat(code, "\n\n");
    return code;
}

FunctionDeclaration_node* createFunctionDeclaration(Identifier_node* identifier, FormalParameterList_node* formalParameterList, Block_node* block) {
    FunctionDeclaration_node* functionDeclaration = (FunctionDeclaration_node*) calloc(1, sizeof(FunctionDeclaration_node));
    functionDeclaration->identifier = identifier;
    functionDeclaration->formalParameterList = formalParameterList;
    functionDeclaration->block = block;
    functionDeclaration->toString = FunctionDeclaration_toString;
    functionDeclaration->toCode = FunctionDeclaration_toCode;
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
        string = concat_indent(string, tmp);
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
        string = concat_indent(string, tmp);
        free(tmp);
    }
    return string;
}

char* Program_toCode(Program_node* program) {
    if ( program->sourceElements == NULL || program->sourceElements->count == 0 ) {
        return new_string("// empty program");
    }
    char* code = new_string("");
    code = concat(code, "#include <stdlib.h>                                                             \n");
    code = concat(code, "#include \"runtime.h\"                                                          \n");
    code = concat(code, "                                                                                \n");
    code = concat(code, "////////////////////////////////////////////////////////////////////////////////\n");
    code = concat(code, "// function definitions                                                         \n");
    code = concat(code, "                                                                                \n");
    for ( int i = 0 ; i < program->sourceElements->count ; i++ ) {
        if ( program->sourceElements->elements[i]->type == FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE ) {
            FunctionDeclaration_node* functionDeclaration = program->sourceElements->elements[i]->sourceElementUnion.functionDeclaration;
            char* tmp = functionDeclaration->toCode(functionDeclaration);
            code = concat(code, tmp);
            free(tmp);
        }
    }
    code = concat(code, "////////////////////////////////////////////////////////////////////////////////\n");
    code = concat(code, "// main program                                                                 \n");
    code = concat(code, "                                                                                \n");
    code = concat(code, "int main(int argc, char** argv) {");
    char* tmp1 = new_string("");
    for ( int i = 0 ; i < program->sourceElements->count ; i++ ) {
        if ( program->sourceElements->elements[i]->type == STATEMENT_SOURCE_ELEMENT_TYPE ) {
            tmp1 = concat(tmp1, "\n");
            Statement_node* statement = program->sourceElements->elements[i]->sourceElementUnion.statement;
            char* tmp2 = statement->toCode(statement);
            tmp1 = concat(tmp1, tmp2);
            free(tmp2);
        }
    }
    tmp1 = concat(tmp1, "\nreturn 0;");
    code = concat_indent(code, tmp1);
    free(tmp1);
    code = concat(code, "\n}");
    return code;
}

Program_node* createProgram(SourceElements_node* sourceElements) {
    Program_node* program = (Program_node*) calloc(1, sizeof(Program_node));
    program->sourceElements = sourceElements;
    program->toString = Program_toString;
    program->toCode = Program_toCode;
    return program;
}

char* VariableStatement_toString(VariableStatement_node* variableStatement) {
    char* string = new_string("VariableStatement\n");
    char* tmp = variableStatement->variableDeclarationList->toString(variableStatement->variableDeclarationList);
    string = concat_indent(string, tmp);
    free(tmp);
    return string;
}

char* VariableStatement_toCode(VariableStatement_node* variableStatement) {
    return variableStatement->variableDeclarationList->toCode(variableStatement->variableDeclarationList);
}

VariableStatement_node* createVariableStatement(VariableDeclarationList_node* variableDeclarationList) {
    VariableStatement_node* variableStatement = (VariableStatement_node*) calloc(1, sizeof(VariableStatement_node));
    variableStatement->variableDeclarationList = variableDeclarationList;
    variableStatement->toString = VariableStatement_toString;
    variableStatement->toCode = VariableStatement_toCode;
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
    string = concat_indent(string, tmp1);
    free(tmp1);
    return string;
}

char* VariableDeclaration_toCode(VariableDeclaration_node* variableDeclaration) {
    char* code = new_string("variable* ");
    code = concat(code, variableDeclaration->identifier->toCode(variableDeclaration->identifier));
    code = concat(code, " = new_undefined();");
    if ( variableDeclaration->initializer != NULL ) {
        code = concat(code, "\n");
        code = concat(code, variableDeclaration->identifier->toCode(variableDeclaration->identifier));
        code = concat(code, "->value = ");
        char* tmp = variableDeclaration->initializer->toCode(variableDeclaration->initializer);
        code = concat(code, tmp);
        free(tmp);
        code = concat(code, ";");
    }
    return code;
}

VariableDeclaration_node* createVariableDeclaration(Identifier_node* identifier, Initializer_node* initializer) {
    VariableDeclaration_node* variableDeclaration = (VariableDeclaration_node*) calloc(1, sizeof(VariableDeclaration_node));
    variableDeclaration->identifier = identifier;
    variableDeclaration->initializer = initializer;
    variableDeclaration->toString = VariableDeclaration_toString;
    variableDeclaration->toCode = VariableDeclaration_toCode;
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
        char* tmp = variableDeclarationList->variableDeclarations[i]->toString(variableDeclarationList->variableDeclarations[i]);
        string = concat_indent(string, tmp);
        free(tmp);
    }
    return string;
}

char* VariableDeclarationList_toCode(VariableDeclarationList_node* variableDeclarationList) {
    char* code = new_string("");
    for ( int i = 0 ; i < variableDeclarationList->count ; i++ ) {
        VariableDeclaration_node* variableDeclaration = variableDeclarationList->variableDeclarations[i];
        if ( i > 0 ) code = concat(code, "\n");
        char* tmp = variableDeclaration->toCode(variableDeclaration);
        code = concat(code, tmp);
        free(tmp);
    }
    return code;
}

VariableDeclarationList_node* createVariableDeclarationList(VariableDeclaration_node* variableDeclaration) {
    VariableDeclarationList_node* variableDeclarationList = (VariableDeclarationList_node*) calloc(1, sizeof(VariableDeclarationList_node));
    variableDeclarationList->count = 0;
    variableDeclarationList->variableDeclarations = NULL;
    variableDeclarationList->append = VariableDeclarationList_append;
    variableDeclarationList->toString = VariableDeclarationList_toString;
    variableDeclarationList->toCode = VariableDeclarationList_toCode;
    variableDeclarationList->append(variableDeclarationList, variableDeclaration);
    return variableDeclarationList;
}

char* Initializer_toString(Initializer_node* initializer) {
    char* string = new_string("Initializer\n");
    char* tmp = initializer->expression->toString(initializer->expression);
    string = concat_indent(string, tmp);
    free(tmp);
    return string;
}

char* Initializer_toCode(Initializer_node* initializer) {
    return initializer->expression->toCode(initializer->expression);
}

Initializer_node* createInitializer(Expression_node* expression) {
    Initializer_node* initializer = (Initializer_node*) calloc(1, sizeof(Initializer_node));
    initializer->expression = expression;
    initializer->toString = Initializer_toString;
    initializer->toCode = Initializer_toCode;
    return initializer;
}

char* EmptyStatement_toString(EmptyStatement_node* emptyStatement) {
    return new_string("EmptyStatement");
}

char* EmptyStatement_toCode(EmptyStatement_node* emptyStatement) {
    return new_string("// empty statement");
}

EmptyStatement_node* createEmptyStatement() {
    EmptyStatement_node* emptyStatement = (EmptyStatement_node*) calloc(1, sizeof(EmptyStatement_node));
    emptyStatement->toString = EmptyStatement_toString;
    emptyStatement->toCode = EmptyStatement_toCode;
    return emptyStatement;
}

char* ExpressionStatement_toString(ExpressionStatement_node* expressionStatement) {
    char* string = new_string("ExpressionStatement\n");
    char* tmp = expressionStatement->expression->toString(expressionStatement->expression);
    string = concat_indent(string, tmp);
    free(tmp);
    return string;
}

char* ExpressionStatement_toCode(ExpressionStatement_node* expressionStatement) {
    char* code = expressionStatement->expression->toCode(expressionStatement->expression);
    return concat(code, ";");
}

ExpressionStatement_node* createExpressionStatement(Expression_node* expression) {
    ExpressionStatement_node* expressionStatement = (ExpressionStatement_node*) calloc(1, sizeof(ExpressionStatement_node));
    expressionStatement->expression = expression;
    expressionStatement->toString = ExpressionStatement_toString;
    expressionStatement->toCode = ExpressionStatement_toCode;
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
        case MEMBER_EXPRESSION_TYPE:
            return expression->expressionUnion.memberExpression->toString(expression->expressionUnion.memberExpression);
    }
}

char* Expression_toCode(Expression_node* expression) {
    switch (expression->type) {
        case IDENTIFIER_EXPRESSION_TYPE:
            return expression->expressionUnion.identifier->toCode(expression->expressionUnion.identifier);
        case LITERAL_EXPRESSION_TYPE:
            return expression->expressionUnion.literal->toCode(expression->expressionUnion.literal);
        case MEMBER_EXPRESSION_TYPE:
            return expression->expressionUnion.memberExpression->toCode(expression->expressionUnion.memberExpression);
        default:
            return new_string("(/* Unsupported Expression */)");
    }
}

Expression_node* createExpression(ExpressionType_enum type, void* untypedExpression) {
    Expression_node* expression = (Expression_node*) calloc(1, sizeof(Expression_node));
    expression->type = type;
    expression->expressionUnion.any = untypedExpression; // TODO do we need .any ?
    expression->toString = Expression_toString;
    expression->toCode = Expression_toCode;
    return expression;
}

char* MemberExpression_toString(MemberExpression_node* memberExpression) {
    char* string = new_string("MemberExpression\n");
    char* tmp1 = new_string("Parent\n");
    char* tmp2 = memberExpression->parent->toString(memberExpression->parent);
    tmp1 = concat_indent(tmp1, tmp2);
    free(tmp2);
    tmp1 = concat(tmp1, "\nChild\n");
    switch (memberExpression->type) {
        case DOT_MEMBER_EXPRESSION_TYPE:
            tmp2 = memberExpression->child.identifier->toString(memberExpression->child.identifier);
            break;
        case BRACKET_MEMBER_EXPRESSION_TYPE:
            tmp2 = memberExpression->child.expression->toString(memberExpression->child.expression);
            break;
    }
    tmp1 = concat_indent(tmp1, tmp2);
    free(tmp2);
    string = concat_indent(string, tmp1);
    free(tmp1);
    return string;
}

char* MemberExpression_toCode(MemberExpression_node* memberExpression) {
    char* code = memberExpression->parent->toCode(memberExpression->parent);
    code = concat(code, "->getMember(");
    char* tmp1;
    char* tmp2;
    switch (memberExpression->type) {
        case DOT_MEMBER_EXPRESSION_TYPE:
            tmp1 = new_string("\"");
            tmp2 = memberExpression->child.identifier->toCode(memberExpression->child.identifier);
            tmp1 = concat(tmp1, tmp2);
            free(tmp2);
            tmp1 = concat(tmp1, "\"");
            break;
        case BRACKET_MEMBER_EXPRESSION_TYPE:
            tmp1 = new_string("native_toString(");
            tmp2 = memberExpression->child.expression->toCode(memberExpression->child.expression);
            tmp1 = concat(tmp1, tmp2);
            free(tmp2);
            tmp1 = concat(tmp1, ")");
            break;
    }
    code = concat(code, tmp1);
    free(tmp1);
    code = concat(code, ")");
    return code;
}

MemberExpression_node* createMemberExpression(Expression_node* parent, MemberExpressionType_enum type, void* child) {
    MemberExpression_node* memberExpression = (MemberExpression_node*) calloc(1, sizeof(MemberExpression_node));
    memberExpression->type = type;
    memberExpression->parent = parent;
    memberExpression->child.any = child;
    memberExpression->toString = MemberExpression_toString;
    memberExpression->toCode = MemberExpression_toCode;
    return memberExpression;
}

char* LeftHandSideExpression_toString(LeftHandSideExpression_node* leftHandSideExpression) {
    char* string = new_string("LeftHandSideExpression\n");
    char* tmp;
    switch (leftHandSideExpression->type) {
        case IDENTIFIER_LEFT_HAND_SIDE_EXPRESSION_TYPE:
            tmp = leftHandSideExpression->leftHandSideExpressionUnion.identifier->toString(leftHandSideExpression->leftHandSideExpressionUnion.identifier);
            break;
        case MEMBER_EXPRESSION_LEFT_HAND_SIDE_EXPRESSION_TYPE:
            tmp = leftHandSideExpression->leftHandSideExpressionUnion.memberExpression->toString(leftHandSideExpression->leftHandSideExpressionUnion.memberExpression);
            break;
    }
    string = concat_indent(string, tmp);
    free(tmp);
    return string;
}

LeftHandSideExpression_node* createLeftHandSideExpression(LeftHandSideExpressionType_enum type, void* expression) {
    LeftHandSideExpression_node* leftHandSideExpression = (LeftHandSideExpression_node*) calloc(1, sizeof(LeftHandSideExpression_node));
    leftHandSideExpression->type = type;
    leftHandSideExpression->leftHandSideExpressionUnion.any = expression;
    leftHandSideExpression->toString = LeftHandSideExpression_toString;
    return leftHandSideExpression;
}

char* AssignmentExpression_toString(AssignmentExpression_node* assignmentExpression) {
    char* string = new_string("AssignmentExpression\n");
    char* tmp1 = assignmentExpression->leftHandSideExpression->toString(assignmentExpression->leftHandSideExpression);
    tmp1 = concat(tmp1, "\nAssignmentOperator\n");
    switch (assignmentExpression->assignmentOperator) {
        case EQUALS_ASSIGNMENT_OPERATOR:
            tmp1 = concat_indent(tmp1, "=");
            break;
    }
    tmp1 = concat(tmp1, "\nRightHandSideExpression\n");
    char* tmp2 = assignmentExpression->expression->toString(assignmentExpression->expression);
    tmp1 = concat_indent(tmp1, tmp2);
    free(tmp2);
    string = concat_indent(string, tmp1);
    free(tmp1);
    return string;
}

AssignmentExpression_node* createAssignmentExpression(LeftHandSideExpression_node* leftHandSideExpression, AssignmentOperator_enum assignmentOperator, Expression_node* expression) {
    AssignmentExpression_node* assignmentExpression = (AssignmentExpression_node*) calloc(1, sizeof(AssignmentExpression_node));
    assignmentExpression->leftHandSideExpression = leftHandSideExpression;
    assignmentExpression->assignmentOperator = assignmentOperator;
    assignmentExpression->expression = expression;
    assignmentExpression->toString = AssignmentExpression_toString;
    return assignmentExpression;
}

char* CallExpression_toString(CallExpression_node* callExpression) {
    char* string = new_string("CallExpression\n");
    char* tmp1 = new_string("Function\n");
    char* tmp2 = callExpression->function->toString(callExpression->function);
    tmp1 = concat_indent(tmp1, tmp2);
    free(tmp2);
    string = concat_indent(string, tmp1);
    free(tmp1);
    string = concat(string, "\n");
    if ( callExpression->argumentList == NULL ) {
        string = concat_indent(string, "ArgumentList (empty)");
    } else {
        char* tmp = callExpression->argumentList->toString(callExpression->argumentList);
        string = concat_indent(string, tmp);
        free(tmp);
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
        char* tmp = argumentList->arguments[i]->toString(argumentList->arguments[i]);
        string = concat_indent(string, tmp);
        free(tmp);
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

char* ReturnStatement_toString(ReturnStatement_node* returnStatement) {
    char* string = new_string("ReturnStatement");
    if ( returnStatement->expression == NULL ) {
        string = concat(string, " (undefined)");
    } else {
        string = concat(string, "\n");
        char* tmp = returnStatement->expression->toString(returnStatement->expression);
        string = concat_indent(string, tmp);
        free(tmp);
    }
    return string;
}

char* ReturnStatement_toCode(ReturnStatement_node* returnStatement) {
    char* code = new_string("{\n");
    char* tmp1 = new_string("return_t ret;\n");
    if ( returnStatement->expression == NULL ) {
        tmp1 = concat(tmp1, "ret.value = new_undefined();");
    } else {
        char* tmp2 = new_string("evaluate this expression:\n");
        char* tmp3 = returnStatement->expression->toString(returnStatement->expression);
        tmp2 = concat(tmp2, tmp3);
        free(tmp3);
        tmp1 = concat_comment(tmp1, tmp2);
        free(tmp2);
        tmp1 = concat(tmp1, "\nret.value = new_undefined(); // not really\nret.value = NULL; // result of expression");
    }
    tmp1 = concat(tmp1, "\nreturn ret;");
    code = concat_indent(code, tmp1);
    free(tmp1);
    code = concat(code, "\n}");
    return code;
}

ReturnStatement_node* createReturnStatement(Expression_node* expression) {
    ReturnStatement_node* returnStatement = (ReturnStatement_node*) calloc(1, sizeof(ReturnStatement_node));
    returnStatement->expression = expression;
    returnStatement->toString = ReturnStatement_toString;
    returnStatement->toCode = ReturnStatement_toCode;
    return returnStatement;
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

char* Literal_toCode(Literal_node* literal) {
    switch (literal->type) {
        case NULL_LITERAL_TYPE:
            return literal->literalUnion.nullLiteral->toCode(literal->literalUnion.nullLiteral);
        case BOOLEAN_LITERAL_TYPE:
            return literal->literalUnion.booleanLiteral->toCode(literal->literalUnion.booleanLiteral);
        case STRING_LITERAL_TYPE:
            return literal->literalUnion.stringLiteral->toCode(literal->literalUnion.stringLiteral);
        default:
            return new_string("/* Unsupported Literal */");
    }
}

Literal_node* createLiteral(LiteralType_enum type, void* untypedLiteral) {
    Literal_node* literal = (Literal_node*) calloc(1, sizeof(Literal_node));
    literal->type = type;
    literal->literalUnion.any = untypedLiteral; // TODO do we need .any ?
    literal->toString = Literal_toString;
    literal->toCode = Literal_toCode;
    return literal;
}

char* NullLiteral_toString(NullLiteral_node* nullLiteral) {
    return new_string("null");
}

char* NullLiteral_toCode(NullLiteral_node* nullLiteral) {
    return new_string("new_null()");
}

NullLiteral_node* createNullLiteral() {
    NullLiteral_node* nullLiteral = (NullLiteral_node*) calloc(1, sizeof(NullLiteral_node));
    nullLiteral->toString = NullLiteral_toString;
    nullLiteral->toCode = NullLiteral_toCode;
    return nullLiteral;
}

char* BooleanLiteral_toString(BooleanLiteral_node* booleanLiteral) {
    if (booleanLiteral->boolean) {
        return new_string("BooleanLiteral true");
    } else {
        return new_string("BooleanLiteral false");
    }
}

char* BooleanLiteral_toCode(BooleanLiteral_node* booleanLiteral) {
    if (booleanLiteral->boolean) {
        return new_string("new_boolean(true)");
    } else {
        return new_string("new_boolean(false)");
    }
}

BooleanLiteral_node* createBooleanLiteral(char boolean) {
    BooleanLiteral_node* booleanLiteral = (BooleanLiteral_node*) calloc(1, sizeof(BooleanLiteral_node));
    booleanLiteral->boolean = boolean;
    booleanLiteral->toString = BooleanLiteral_toString;
    booleanLiteral->toCode = BooleanLiteral_toCode;
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
            default:   string = concat_char(string, stringLiteral->string[i]);
        }
    }
    string = concat(string, "\"");
    return string;
}

char* StringLiteral_toCode(StringLiteral_node* stringLiteral) {
    char* code = new_string("new_string(");
    char* tmp = stringLiteral->toString(stringLiteral);
    code = concat(code, tmp);
    free(tmp);
    code = concat(code, ")");
    return code;
}

StringLiteral_node* createStringLiteral(char* string) {
    StringLiteral_node* stringLiteral = (StringLiteral_node*) calloc(1, sizeof(StringLiteral_node));
    stringLiteral->string = new_string(string);
    stringLiteral->toString = StringLiteral_toString;
    stringLiteral->toCode = StringLiteral_toCode;
    return stringLiteral;
}
