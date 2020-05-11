#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchersInternal.h"
#include "clang/ASTMatchers/ASTMatchersMacros.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/CommandLine.h"
#include "clang/Rewrite/Frontend/Rewriters.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "info.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <fstream>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include "matchers.h"


#ifndef EXECUTE_H
#define EXECUTE_H

class execute : public MatchFinder::MatchCallback, public ASTConsumer, public RecursiveASTVisitor<execute>{

// ----------------------- General ---------------------
	public:
		virtual void run(const MatchFinder::MatchResult &Result);
		void postRun();
		bool check_same_decl_canonical(const Decl *c1, const Decl *c2);

	private:
		ASTContext *Context;
		Rewriter Rewrite;
		typedef std::multimap<string, Info> A;
		typedef A::iterator AI;

/*
**
** GENERAL METHODS
**
*/

	public:
		bool foundAll(A a);
		bool foundAny(A a);
		bool anyFoundAndInvalid(A a);
		bool allFoundAndValid(A a);
		void getMessagesOfNotFound(A a);
		void getMessagesOfNotFoundOrInvalid(A a);
		void getMessagesOfFound(A a);
		void getMessagesCheckingExplicitSpecified(A a);
		bool existClass(const CXXRecordDecl *foundClass);
		bool existConstructor(const CXXConstructorDecl *foundConstructor);
		bool existDestructor(const CXXDestructorDecl *foundDestructor);
		bool existDeleteExpression(const CXXDeleteExpr *foundDeleteExpression);
		bool existMethod(const CXXMethodDecl *foundMethod);
		bool existFunction(const FunctionDecl *foundFunction);
		bool existMember(const FieldDecl *foundMember);
		bool existVariable(const VarDecl *foundVariable);

/*
**
** GENERAL CHECK PARAMS
**
*/

	public:
		bool checkInitializersConstructor(const CXXConstructorDecl *foundConstructor, vector<string> parameters);
		bool checkParams(const FunctionDecl *foundFunction, vector<string> parameters);
		bool checkParamsFunction(const FunctionDecl *foundFunction, vector<string> parameters);
		bool checkWithoutParams(vector<string> params);
		bool markedConst(string c1, bool c2);
		bool markedDefault(string c1, bool c2);
		bool checkDefArgs(const FunctionDecl* function, unsigned int numDefArgs, vector<string> defArgs);
		bool checkRegularExpresion(string str1, string str2);

/*
**
** CLASSES
**
*/


// ----------------------- CLASSES ---------------------
	public:
		void setClasses(string className, string message);

	private:
		void classWithName(const MatchFinder::MatchResult &Result);
		void hasClass();
		A classes;

/*
**
** CONSTRUCTORS
**
*/




// ----------------------- DEFAULT CONSTRUCTOR ---------------------

	public:
		void setDefaultConstructors(string className, bool exist, string notFoundMessage);

	private:
		void classWithDefaultConstructor(const MatchFinder::MatchResult &Result);
		void hasDefaultConstructor();
		A defaultConstructors;

// ----------------------- COPY CONSTRUCTOR ---------------------

	public:
		void setCopyConstructors(string className, bool exist, string notFoundMessage);

	private:
		void classWithCopyConstructor(const MatchFinder::MatchResult &Result);
		void hasCopyConstructor();
		A copyConstructors;

// ----------------------- MOVE CONSTRUCTORS ---------------------

	public:
		void setMoveConstructors(string className, bool exist, string notFoundMessage);

	private:
		void classWithMoveConstructor(const MatchFinder::MatchResult &Result);
		void hasMoveConstructor();
		A moveConstructors;

// ----------------------- DESTRUCTOR ---------------------

	public:
		void setDestructors(string className, bool exist, string message);

	private:
		void classWithDestructor(const MatchFinder::MatchResult &Result);
		void hasDestructor();
		A destructors;

// ----------------------- DELETE MEMBERS ---------------------

	public:
		void setDeleteMembers(string className, string memberName, string message);

	private:
		void deleteMember(const MatchFinder::MatchResult &Result);
		void hasDeleteMember();
		A deleteMembers;

// ----------------------- CLASS WITH CONSTRUCTOR WITH INITIALIZERS ---------------------

	public:
		void setInitializers(string className, vector<string> parameters, vector<string> inits, string message);

	private:
		void classWithListInitializerConstructor(const MatchFinder::MatchResult &Result);
		A initializers;
		void hasInitializer();

// ----------------------- NUMBER OF CONSTRUCTORS ---------------------

	public:
		void setConstructors(string className, unsigned int constructors, bool lenient, string message);

	private:
		void numberOfConstructor(const MatchFinder::MatchResult &Result);
		void howManyConstructors();
		A constructors;

// ----------------------- EXPLICIT SPECIFIED CONSTRUCTORS ---------------------

	public:
		void setExplicitSpecifiedConstructors(string className, vector<string> parameters, string message);

	private:
		void explicitSpecifiedConstructor(const MatchFinder::MatchResult &Result);
		void hasExplicitSpecifiedConstructor();
		A explicitSpecifiedConstructors;

// ----------------------- CATCHING EXCEPTIONS ---------------------

	public:
		void setTakeExceptions(string exceptionClass, string message);

	private:
		void takeException(const MatchFinder::MatchResult &Result);
		void hasTakeException();
		A takeExceptions;




/*
**
** VARIABLES
**
*/

// ----------------------- MEMBER ---------------------

	public:
		void setMembers(string className, string memberName, string constant, bool exist, string message);

	private:
		void classWithMember(const MatchFinder::MatchResult &Result);
		A members;
		void hasMember();

// ----------------------- STATIC VARIABLE ---------------------

	public:
		void setStaticVariables(string className, string variableName, string constant, string message);

	private:
		void classWithStaticVariable(const MatchFinder::MatchResult &Result);
		A staticVariables;
		void hasStaticVariable();

// ----------------------- RELEASED VARIABLE ---------------------

	public:
		void setReleasedVariables(string message);
		bool allReleasedVariables();

	private:
		void releaseVariable(const MatchFinder::MatchResult &Result);
		map<const VarDecl*, bool> variables_new;
		string releasedVariableMessage;
		void hasReleasedVariable();

// ----------------------- PRIVATE MEMBERS ---------------------

	public:
		void setClassWithAllPrivateMembers(string className, string message);

	private:
		void classWithAllPrivateMember(const MatchFinder::MatchResult &Result);
		void hasAllPrivateMember();
		A classWithAllPrivateMembers;

// ----------------------- ACCESS LEVEL VARIABLE MEMBERS ----------

	public:
                void setMembersAccessLevel(string className, string memberName, string level, string message);

        private:
                void classWithVariableMembersAccessLevel(const MatchFinder::MatchResult &Result);
                void hasVariableMembersAccessLevel();
                A variableMembersAccessLevel;




/*
**
** METHODS
**
*/

// ----------------------- METHODS WITH NAME---------------------

	public:
		void setMethodsWithName(string methodName, string className, vector<string> params, string constant, string message);

	private:
		void methodWithName(const MatchFinder::MatchResult &Result);
		A methodsWithName;
		void hasMethodWithName();

// -------------------- METHODS WITH DEFAULT ARG------------------

	public:
		void setMethodsWithDefaultArg(string methodName, string className, vector<string> params, vector<string> defaults, string constant, string message);

	private:
		void methodWithDefaultArg(const MatchFinder::MatchResult &Result);
		A methodsWithDefaultArg;
		void hasMethodWithDefaultArg();

// ----------------------- METHODS WITH REFERENCED VARIABLE---------------------

	public:
		void setMethodsWithReferencedVariable(string methodName, string className, vector<string> params, string constant, string memberVariable, string message);

	private:
		void methodWithReferencedVariable(const MatchFinder::MatchResult &Result);
		A methodsWithReferencedVariable;
		void hasMethodWithReferencedVariable();

// ----------------------- METHODS WITH REFERENCED METHOD---------------------

	public:
		void setMethodsWithReferencedMethod(string mainMethodName, vector<string> mainMethodParams, string mainClassName, string mainConstant, string usedMethodName, vector<string> usedMethodParams, string usedClasName, string usedConstant, string message);

	private:
		void methodWithReferencedMethod(const MatchFinder::MatchResult &Result);
		A methodsWithReferencedMethod;
		void hasMethodWithReferencedMethod();

// ----------------------- METHODS NO EXCEPT---------------------

	public:
		void setNoExceptMethods(string methodName, vector<string> params, string className, string constant, string message);

	private:
		void noExceptMethod(const MatchFinder::MatchResult &Result);
		A noExceptMethods;
		void hasNoExceptMethod();

// ----------------------- METHODS INLINE---------------------

	public:
		void setInlineMethods(string methodName, vector<string> params, string className, string constant, string message);

	private:
		void inlineMethod(const MatchFinder::MatchResult &Result);
		A inlineMethods;
		void hasInlineMethod();


// ----------------------- DEFAULT ARGUMENTS IN METHODS ---------------------

	public:
		void setDefaultArgumentsInMethod(string methodName, vector<string> params, string className, string constant, unsigned int numDefaultArgs, vector<string> defaultArgs, string message);

	private:
		void defaultArgumentsInMethod(const MatchFinder::MatchResult &Result);
		A defaultArgumentsInMethods;
		void hasDefaultArgumentsInMethod();


// ----------------------- METHODS DELETED ---------------------

	public:
		void setDeletedMethods(string methodName, string className, vector<string> params, string constant, string message);
	private:
		void deletedMethod(const MatchFinder::MatchResult &Result);
		void hasDeletedMethod();
		A deletedMethods;

// ----------------------- METHODS DEFAULT ---------------------

	public:
		void setDefaultedMethods(string methodName, string className, vector<string> params, string constant, string message);
	private:
		void defaultedMethod(const MatchFinder::MatchResult &Result);
		void hasDefaultedMethod();
		A defaultedMethods;


// ----------------------- METHODS VIRTUAL ---------------------
	public:
		void setVirtualMethods(string methodName, string className, vector<string> params, string constant, string message);
	private:
		void virtualMethod(const MatchFinder::MatchResult &Result);
		void hasVirtualMethod();
		A virtualMethods;

/*
**
** OPERATORS
**
*/

// ----------------------- COPY ASSIGNMENT OPERATOR ---------------------

	public:
		void setCopyAssignmentOperators(string className, bool exist, string message);

	private:
		void classWithCopyAssignmentOperator(const MatchFinder::MatchResult &Result);
		void hasCopyAssignmentOperator();
		A copyAssignmentOperators;

// ----------------------- MOVE ASSIGNMENT OPERATOR ---------------------

	public:
		void setMoveAssignmentOperators(string className, bool exist, string message);

	private:
		void classWithMoveAssignmentOperator(const MatchFinder::MatchResult &Result);
		void hasMoveAssignmentOperator();
		A moveAssignmentOperators;

// ----------------------- FUNCTIONS WITH REFERENCED FUNCTIONS ---------------------

	public:
		void setFunctionsWithReferencedFunction(string mainFunctionName, vector<string> mainFunctionParameters, string usedFuncionName, vector<string> usedFunctionParameters, string message);

	private:
		void functionWithReferencedFunction(const MatchFinder::MatchResult &Result);
		A functionsWithReferencedFunction;
		void hasFunctionWithReferencedFunction();

// ----------------------- METHODS WITH REFERENCED FUNCTIONS ---------------------

	public:
		void setMethodsWithReferencedFunction(string mainMethodName, vector<string> mainMethodParameters, string mainClassName, string mainConstant, string usedFuncionName, vector<string> usedFunctionParameters, string message);

	private:
		void methodWithReferencedFunction(const MatchFinder::MatchResult &Result);
		A methodsWithReferencedFunction;
		void hasMethodWithReferencedFunction();

// ----------------------- FUNCTIONS WITH REFERENCED METHODS ---------------------

	public:
		void setFunctionsWithReferencedMethod(string mainFunctionName, vector<string> mainFunctionParameters, string usedMethodName, vector<string> usedMethodParameters, string usedConstant, string usedClass, string message);

	private:
		void functionWithReferencedMethod(const MatchFinder::MatchResult &Result);
		A functionsWithReferencedMethod;
		void hasFunctionWithReferencedMethod();

// ----------------------- FUNCTIONS WITH NAME ---------------------

	public:
		void setFunctionsWithName(string functionName, vector<string> params, string message);

	private:
		void functionWithName(const MatchFinder::MatchResult &Result);
		void hasFunctionWithName();
		A functionsWithName;





/*
**
** HEADERS
**
*/

// ----------------------- INCLUDED HEADER---------------------

	public:
		void setInvocationsFromHeader(string functionNames, string headerName, bool exist, string message);

	private:
		void invocationsFromHeader(const MatchFinder::MatchResult &Result);
		A invocationsFromHeaders;
		void hasInvocationsFromHeader();

// --------------------- FILE INCLUDE HEADER ------------------
	public:
		void setFileIncludeHeader(vector<string> fileName, string headerName, string message);
	private:
		A fileIncludedHeader;
		void hasFileIncludedHeader();

/*
**
** PREPROCESSOR
**
*/

// ----------------------- PREPROCESSOR ---------------------
	public:
		void setGuardClauses(string fileName, string message);
	private:
		A guardClauses;
		void hasGuardClauses();



/*
**
** FRIEND MEMBERS
**
*/

// ----------------------- NOT FRIEND MEMBERS---------------------

	public:
		void setNotFriendMembers(string className, string message);

	private:
		void classWithNotFriendMember(const MatchFinder::MatchResult &Result);
		A notFriendMembers;
		void hasNotFriendMember();


// ----------------------- FRIEND FUNCTION ------------------------

	public:
		void setFriendFunction(string functionName, string className, vector<string> params, string message);

	private:
		void classWithFriendFunction(const MatchFinder::MatchResult &Result);
		A friendFunctions;
		void hasFriendFunction();


//------------------------ FRIEND CLASS --------------------------

        public:
                void setFriendClass(string className, string friendClassName, string message);

        private:
                void classWithFriendClass(const MatchFinder::MatchResult &Result);
                A friendClasses;
                void hasFriendClass();
		bool friend_class(const CXXRecordDecl* c1, string c2);

//------------------------ DYNAMIC CAST --------------------------
	public:
		void setDynamicCast(string methodName, vector<string> parameters, string constant, string className, string originType, string dstType, string message);
	private:
		void methodWithDynamicCast(const MatchFinder::MatchResult &Result);
		A dynamicCast;
		void hasDynamicCast();



/*
**
** FINAL CHECK
**
*/

// ----------------------- FINAL CHECK ---------------------

	public:
		void setCorrectMessage(string message);
		string getCorrectMessage();
		void setIncorrectMessage(string message);
		string getIncorrectMessage();

	private:
		bool correct = true;
		string correctMessage, incorrectMessage;
		void isCorrect();
		void showMessages();
		set<string> messages;
};



#endif //EXECUTE_H
