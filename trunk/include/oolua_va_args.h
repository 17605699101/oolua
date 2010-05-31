#ifndef OOLUA_VA_ARGS_H_
#	define OOLUA_VA_ARGS_H_



#ifdef __GNUC__
//	SShhhhhhhhh stops gcc generating warnings about the variadic macros
#	pragma GCC system_header
#endif


//any other compilers use the _MSC_VER define?
#if defined _MSC_VER && !defined __INTEL_COMPILER
#	if _MSC_VER >= 1400 && _MSC_VER <= 1600
//		vs8(2005) vs9(2008) and vs10(2010) should all be fine with the work around their __VA_ARGS__ bug
//		https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
//		Taken from the above bug report url and the proposed workaround
#		define OOLUA_ARG_N(\
			_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,\
			_10, _11, _12, _13, _14, _15, _16, _17, _18, _19,\
			_20, _21, _22, _23, _24, _25, _26, _27, _28, _29,\
			_30, _31, _32, _33, _34, _35, _36, _37, _38, _39,\
			_40, _41, _42, _43, _44, _45, _46, _47, _48, _49,\
			_50, _51, _52, _53, _54, _55, _56, _57, _58, _59,\
			_60, _61, _62, ...)  _62

#		define OOLUA_RSEQ_N \
			62,61,60,\
			59,58,57,56,55,54,53,52,51,50,\
			49,48,47,46,45,44,43,42,41,40,\
			39,38,37,36,35,34,33,32,31,30,\
			29,28,27,26,25,24,23,22,21,20,\
			19,18,17,16,15,14,13,12,11,10,\
			9,8,7,6,5,4,3,2,1,0

#		define OOLUA_LEFT_PAREN (
#		define OOLUA_RIGHT_PAREN )
#		define OOLUA_NARG(...)\
			OOLUA_ARG_N OOLUA_LEFT_PAREN __VA_ARGS__, OOLUA_RSEQ_N OOLUA_RIGHT_PAREN

#		define OOLUA_NARG_ALLOW_ZERO(DontCare,...) \
				OOLUA_NARG OOLUA_LEFT_PAREN DontCare , ##  __VA_ARGS__ OOLUA_RIGHT_PAREN -1

#		define OOLUA_MEM_FUNC(return_type,func_name,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN return_type,func_name,__VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__))( return_type,func_name,__VA_ARGS__ )*/

#		define OOLUA_MEM_FUNC_CONST(return_value,func,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN ,_CONST OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN return_type,func_name,__VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST)(return_type,func_name,__VA_ARGS__) */

#		define OOLUA_MEM_FUNC_RENAME(new_name,return_value,func_name,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN ,_RENAME OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN new_name,return_type,func_name,__VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_RENAME)(new_name,return_type,func_name,__VA_ARGS__)*/

#		define OOLUA_MEM_FUNC_CONST_RENAME(new_name,return_value,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_MEM_FUNC_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN ,_CONST_RENAME OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN new_name,return_type,func_name,__VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST_RENAME)(new_name,return_type,func_name,__VA_ARGS__)*/

#		define EXPORT_OOLUA_FUNCTIONS_NON_CONST(ClassType,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN TEST_CONCAT OOLUA_LEFT_PAREN EXPORT_OOLUA_FUNCTIONS_ , OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN , _NON_CONST OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN ClassType , __VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_NON_CONST)(ClassType, GET_ARGS_2 LEFT_PAREN __VA_ARGS__ RIGHT_PAREN )*/

#		define OOLUA_FUNCTIONS_CONST(ClassType,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN TEST_CONCAT OOLUA_LEFT_PAREN EXPORT_OOLUA_FUNCTIONS_ , OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN , _CONST OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN ClassType , __VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_CONST)(ClassType,__VA_ARGS__)*/

#		define OOLUA_PUBLIC_INHERIT(...) \
			TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_PUBLIC_INHERIT_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(OOLUA_PUBLIC_INHERIT_,OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)*/

#		define OOLUA_C_FUNCTION(return_type,func,...)\
			TEST_CONCAT OOLUA_LEFT_PAREN OOLUA_C_FUNCTION_,OOLUA_NARG OOLUA_LEFT_PAREN __VA_ARGS__ OOLUA_RIGHT_PAREN OOLUA_RIGHT_PAREN OOLUA_LEFT_PAREN return_type,func,__VA_ARGS__ OOLUA_RIGHT_PAREN
			/*TEST_CONCAT(OOLUA_C_FUNCTION_,OOLUA_NARG(__VA_ARGS__))(return_type,func,__VA_ARGS__)*/

#	endif

#elif defined __GNUC__ && __GNUC__ < 3 
#	warning if you are using a version of g++ less than 3.0 and want to use \
		__VA_ARGS__ please send a message to the mailing list @ \
		http:\/\/groups.google.com\/group\/oolua-user \
		and I will provide a work around using named variadic arguments.

#elif defined __GNUC__

//	Assume the compiler supports __VA_ARGS__ and uses the standard implementation.
//The only difference between the code at the following URL and used below, is
//that macro names got an OOLUA prefix as per all macros in the library
//http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5

#	define OOLUA_NARG(...)\
		OOLUA_NARG_DO(__VA_ARGS__,OOLUA_RSEQ_N())

#	define OOLUA_NARG_DO(...)\
		OOLUA_ARG_N(__VA_ARGS__)

#	define OOLUA_ARG_N(\
		_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,\
		_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,\
		_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,\
		_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,\
		_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,\
		_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,\
		_61,_62,_63,N,...) N

#	define OOLUA_RSEQ_N()\
		63,62,61,60,\
		59,58,57,56,55,54,53,52,51,50,\
		49,48,47,46,45,44,43,42,41,40,\
		39,38,37,36,35,34,33,32,31,30,\
		29,28,27,26,25,24,23,22,21,20,\
		19,18,17,16,15,14,13,12,11,10,\
		9,8,7,6,5,4,3,2,1,0


/*
GCC comma-deletion extension
The token preceding the special `##' must be a comma, and there must be white space 
 between that comma and whatever comes immediately before it.
 */

#	define OOLUA_NARG_ALLOW_ZERO(DontCare , ...) \
	OOLUA_NARG_DO( DontCare , ##__VA_ARGS__ ,OOLUA_RSEQ_N_ALLOW_ZERO()) 
	//OOLUA_NARG_ALLOW_ZERO_DO( DontCare , ##__VA_ARGS__ ,OOLUA_RSEQ_N_ALLOW_ZERO()) 
/*
#	define OOLUA_NARG_ALLOW_ZERO_DO(...)\
		OOLUA_ARG_N_ALLOW_ZERO (__VA_ARGS__)

#	define OOLUA_ARG_N_ALLOW_ZERO(\
_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,\
_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,\
_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,\
_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,\
_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,\
_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,\
_61,_62,_63,N,...) N

*/

#	define OOLUA_RSEQ_N_ALLOW_ZERO()\
		62,61,60,\
		59,58,57,56,55,54,53,52,51,50,\
		49,48,47,46,45,44,43,42,41,40,\
		39,38,37,36,35,34,33,32,31,30,\
		29,28,27,26,25,24,23,22,21,20,\
		19,18,17,16,15,14,13,12,11,10,\
		9,8,7,6,5,4,3,2,1,0


#	define OOLUA_PUBLIC_INHERIT_0(...)

#	define OOLUA_MEM_FUNC(return_type,func_name,...)\
TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG_ALLOW_ZERO(1 , ##__VA_ARGS__))( return_type,func_name ,##__VA_ARGS__ )

#	define OOLUA_MEM_FUNC_CONST(return_value,func,...)\
TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG_ALLOW_ZERO(1 ,##__VA_ARGS__)),_CONST)(return_type,func_name ,##__VA_ARGS__)

#	define OOLUA_MEM_FUNC_RENAME(new_name,return_value,func_name,...)\
TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG_ALLOW_ZERO(1 ,##__VA_ARGS__)),_RENAME)(new_name,return_type,func_name ,##__VA_ARGS__)

#	define OOLUA_MEM_FUNC_CONST_RENAME(new_name,return_value,...)\
TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG_ALLOW_ZERO(1 ,##__VA_ARGS__)),_CONST_RENAME)(new_name,return_type,func_name ,##__VA_ARGS__)

#	define OOLUA_PUBLIC_INHERIT(...) \
	: TEST_CONCAT(OOLUA_PUBLIC_INHERIT_,OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)

#	define EXPORT_OOLUA_FUNCTIONS_NON_CONST(ClassType,...)\
TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG_ALLOW_ZERO(1 ,##__VA_ARGS__)),_NON_CONST) (ClassType ,##__VA_ARGS__)

#	define EXPORT_OOLUA_FUNCTIONS_CONST(ClassType,...)\
TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG_ALLOW_ZERO(1 ,##__VA_ARGS__)),_CONST) (ClassType ,##__VA_ARGS__)

#	define OOLUA_C_FUNCTION(return_type,func,...)\
TEST_CONCAT(OOLUA_C_FUNCTION_,OOLUA_NARG(__VA_ARGS__))(return_type,func ,##__VA_ARGS__)


#else
//	Assume the compiler supports __VA_ARGS__ and uses the standard implementation.
//The only difference between the code at the following URL and used below, is
//that macro names got an OOLUA prefix as per all macros in the library
//http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5

#	define OOLUA_NARG(...)\
		OOLUA_NARG_DO(__VA_ARGS__,OOLUA_RSEQ_N())

#	define OOLUA_NARG_DO(...)\
		OOLUA_ARG_N(__VA_ARGS__)

#	define OOLUA_ARG_N(\
		_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,\
		_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,\
		_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,\
		_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,\
		_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,\
		_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,\
		_61,_62,_63,N,...) N

#	define OOLUA_RSEQ_N()\
		63,62,61,60,\
		59,58,57,56,55,54,53,52,51,50,\
		49,48,47,46,45,44,43,42,41,40,\
		39,38,37,36,35,34,33,32,31,30,\
		29,28,27,26,25,24,23,22,21,20,\
		19,18,17,16,15,14,13,12,11,10,\
		9,8,7,6,5,4,3,2,1,0

#	define OOLUA_MEM_FUNC(return_type,func_name,...)\
		TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__))( return_type,func_name,__VA_ARGS__ )

#	define OOLUA_MEM_FUNC_CONST(return_value,func,...)\
		TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST)(return_type,func_name,__VA_ARGS__)

#	define OOLUA_MEM_FUNC_RENAME(new_name,return_value,func_name,...)\
		TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_RENAME)(new_name,return_type,func_name,__VA_ARGS__)

#	define OOLUA_MEM_FUNC_CONST_RENAME(new_name,return_value,...)\
		TEST_CONCAT(TEST_CONCAT(OOLUA_MEM_FUNC_,OOLUA_NARG(__VA_ARGS__)),_CONST_RENAME)(new_name,return_type,func_name,__VA_ARGS__)

#	define OOLUA_PUBLIC_INHERIT(...) \
		TEST_CONCAT(OOLUA_PUBLIC_INHERIT_,OOLUA_NARG(__VA_ARGS__))(__VA_ARGS__)

#	define EXPORT_OOLUA_FUNCTIONS_NON_CONST(ClassType,...)\
		TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_NON_CONST)(ClassType,__VA_ARGS__)

#	define TEXPORT_OOLUA_FUNCTIONS_CONST(ClassType,...)\
		TEST_CONCAT(TEST_CONCAT(EXPORT_OOLUA_FUNCTIONS_,OOLUA_NARG(__VA_ARGS__)),_CONST)(ClassType,__VA_ARGS__)

#	define OOLUA_C_FUNCTION(return_type,func,...)\
		TEST_CONCAT(OOLUA_C_FUNCTION_,OOLUA_NARG(__VA_ARGS__))(return_type,func,__VA_ARGS__)

#endif


//Concating using OOLUA_NARG with Visual Studio fails, unless we go through a further macro to expand it
#define DO_TEST_CONCAT2(A,B)A##B
#define DO_TEST_CONCAT(A,B) DO_TEST_CONCAT2(A,B)
#define TEST_CONCAT(A,B) DO_TEST_CONCAT(A,B)


#define OOLUA_PUBLIC_INHERIT_1(ClassType) \
			public Proxy_class<ClassType> 

#define OOLUA_PUBLIC_INHERIT_2(ClassType1,ClassType2) \
			OOLUA_PUBLIC_INHERIT_1(ClassType1)\
			,OOLUA_PUBLIC_INHERIT_1(ClassType2)

#define OOLUA_PUBLIC_INHERIT_3(ClassType1,ClassType2,ClassType3) \
			OOLUA_PUBLIC_INHERIT_2(ClassType1,ClassType2)\
			,OOLUA_PUBLIC_INHERIT_1(ClassType3)

#define OOLUA_PUBLIC_INHERIT_4(ClassType1,ClassType2,ClassType3,ClassType4) \
			OOLUA_PUBLIC_INHERIT_3(ClassType1,ClassType2,ClassType3)\
			,OOLUA_PUBLIC_INHERIT_1(ClassType4)

#define OOLUA_PUBLIC_INHERIT_5(ClassType1,ClassType2,ClassType3,ClassType4,ClassType5) \
			OOLUA_PUBLIC_INHERIT_4(ClassType1,ClassType2,ClassType3,ClassType4)\
			,OOLUA_PUBLIC_INHERIT_1(ClassType4)

#define OOLUA_PUBLIC_INHERIT_6(ClassType1,ClassType2,ClassType3,ClassType4,ClassType5,ClassType6) \
			OOLUA_PUBLIC_INHERIT_5(ClassType1,ClassType2,ClassType3,ClassType4,ClassType5)\
			,OOLUA_PUBLIC_INHERIT_1(ClassType6)

#define OOLUA_CLASS_WITH_BASES(ClassType,...) \
			OOLUA_CLASS(ClassType) OOLUA_PUBLIC_INHERIT(__VA_ARGS__) \
			OOLUA_BASIC\
			OOLUA_BASES_START __VA_ARGS__ OOLUA_BASES_END


#endif
