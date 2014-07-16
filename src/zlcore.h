/// @addtogroup GROUP_ZYLLIBC	zyllibc
/// @{
///

/// @addtogroup GROUP_ZLCORE	zlcore
/// zyl910's cross platform core library (跨平台核心库) .
///
/// @author	[zyl910](mailto:zyl910hero@gmail.com)
/// @version	1.0
/// @date	2013-12-01
///
/// Links:
///
/// * Git:	https://github.com/zyl910/zlcore
/// * Blog:	http://www.cnblogs.com/zyl910/tag/zlcore/
/// 
/// zlcore is a lightweight C library.
///
/// Features (特性):
/// * Check C/C++ environment (检测C/C++环境) .
/// 
/// ## Usage (用法)
/// 
/// Add `src/``*.*` to you project (将 `src/``*.*` 加入到您的项目).
/// 
///
/// Option before include(可选的之前引入文件):
/// 
/// guiddef.h	// or windows.h
/// 
/// Input config macro(输入配置型宏):
///
/// * __BYTE_ORDER__:	Host byte order (主机的字节序). 默认是 1234 小端方式.
/// * ZL_NOWIDE: stdc not support wide char (标准C库不支持宽字符) . 若设置此宏, 则 ZL_NOWIDECPP 也被设置.
/// * ZL_NOWIDECPP: stdcpp not support wide char (标准C++库不支持宽字符) . Used to improve the compatibility , e.g. bcb6 (用于提高兼容性, 例如bcb6).
/// 
///
/// ## Documentation (文档)
/// 
/// You can generate documentation with [doxygen](http://www.stack.nl/~dimitri/doxygen/index.html) (您可以用doxygen生成文档).
/// 
/// Use doxywizard to open *.doxygen file (使用doxywizard打开 *.doxygen).
/// 
/// * tcharall_doc.doxygen: Generates documentation from interface files (生成接口的文档) .
/// * tcharall_docfull.doxygen: Generates documentation from interface & implement and example files (生成接口、实现、示例等内容的详细文档).
/// 
/// You may need change INCLUDE_PATH in *.doxyfile with the actual location (您可能需要在 *.doxygen 中调整INCLUDE_PATH为实际路径).
/// 
/// 
/// ## MIT License (MIT许可证)
/// 
/// Copyright (c) 2000-2013 zyl910 \<zyl910hero@gmail.com\>
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
/// 
/// ## Tested compiler (测试过的编译器)
/// 
/// * Virtual C++: 6, 7.1(2003), 8(2005), 9(2008), 10(2010), 11(2012), 12(2013).
/// * Borland C++ Builder: 6.
/// * GCC(Linux): 4.7.0(Fedora 17),  4.7.2(Fedora 18),  4.8.1(Fedora 19).
/// * GCC(MinGW): 4.6.2(MinGW(20120426)), 4.7.1(TDM-GCC(MinGW-w64)).
/// * LLVM GCC: 4.2(Mac OS X Lion 10.7.4), 4.2.1(Mac OS X Mountain Lion 10.8.3).
/// 
/// 
/// 
/// ## Change history (变更日志)
/// 
/// [2013-12-01] v1.0:
/// 
/// * Release v1.0 (发布1.0版).
/// 
/// @{
///

///
/// @file	zlcore.h
/// @brief	zyl910's cross platform core library (跨平台核心库) .
/// @since	@ref GROUP_ZLCORE 1.0
///
///
///

#ifndef __ZLCORE_H_INCLUDED
#define __ZLCORE_H_INCLUDED

// Disable warning: UTF-8(No BOM).
#ifdef ZL_CRT_MSVC
#pragma warning(disable : 4819)
#endif

#if defined(ZL_NOWIDE) && !defined(ZL_NOWIDECPP)
/// stdcpp not support wide char (标准C++库不支持宽字符) . Used to improve the compatibility , e.g. bcb6 (用于提高兼容性, 例如bcb6).
#define ZL_NOWIDECPP	ZL_NOWIDE
#endif

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <memory.h>
#include <stddef.h>
#include <string.h>

#include "auto_stdint.h"
#if !defined(PTRDIFF_MAX) || !defined(INT32_MAX)
#error Need C99 marcos: __STDC_LIMIT_MACROS.
#endif
#if !defined(INT32_C)
#error Need C99 marcos: __STDC_CONSTANT_MACROS.
#endif

#ifndef ZL_NOWIDE
#include <wchar.h>

#ifndef WINT_MAX
#error Can not found WINT_MAX! No __STDC_CONSTANT_MACROS marcos?
#endif

#endif


#if defined __cplusplus
extern "C" {
#endif


////////////////////////////////////////
// C environment (C环境检查) .
////////////////////////////////////////


////////////////////////////////////////
// C++ environment (C++环境检查) .
////////////////////////////////////////


////////////////////////////////////////
// CRT: C runtime (CRT检查) .
////////////////////////////////////////

/// @def ZL_CRT_SECURE
/// Security Enhancements in the CRT (安全CRT). e.g. _snprintf_s .
///
#ifndef ZL_CRT_SECURE
#if defined(_MSC_VER) && (_MSC_VER>=1400)	// VC2005
	#define ZL_CRT_SECURE	1
#else
	#define ZL_CRT_SECURE	0
#endif	// #if defined(_MSC_VER) && (_MSC_VER>=1400)	// VC2005
#endif	// #ifndef ZL_CRT_SECURE

/// @def ZL_CRT_MSVC
/// Visual C++ extension CRT (VC扩展的CRT). e.g. _snprintf .
///
#ifndef ZL_CRT_MSVC
#if defined(_MSC_VER)||defined(_WIN32)||defined(_WIN64)||defined(__MINGW32__)||defined(__MINGW64__)	// 假定Windows平台的编译器均支持VC扩展的CRT.
	#define ZL_CRT_MSVC	1
#else
	#define ZL_CRT_MSVC	0
#endif
#endif	// #ifndef ZL_CRT_MSVC

// == C99 new functions == 
#ifndef ZL_CRT_vfscanf
#if defined(_MSC_VER)
	// 直至VC2012, VC仍不支持vfscanf/vfwscanf/vsscanf/vswscanf函数.
	#define ZL_CRT_vfscanf	0
	#define ZL_CRT_vfwscanf	0
	#define ZL_CRT_vsscanf	0
	#define ZL_CRT_vswscanf	0
#else
	// bcb和gcc 均支持vfscanf等函数. 假设其他编译器也支持.
	#define ZL_CRT_vfscanf	1
	#define ZL_CRT_vfwscanf	1
	#define ZL_CRT_vsscanf	1
	#define ZL_CRT_vswscanf	1
#endif
#endif	// #ifndef ZL_CRT_vfscanf


#ifndef ZL_CRT_strnlen
#if defined(_MSC_VER) && (_MSC_VER>=1400)	// VC2005
	#define ZL_CRT_strnlen	1
	#define ZL_CRT_wcsnlen	1
#elif defined(__GNUC__) && ((__GNUC__>4) || (__GNUC__==4 && __GNUC_MINOR__>=7))   // gcc 4.7 . Yes: TDM-GCC 4.7 ; No: MinGW 4.6.1 .
	#define ZL_CRT_strnlen	1
	#define ZL_CRT_wcsnlen	1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__>199901L) // C99 .
	#define ZL_CRT_strnlen	1
	#define ZL_CRT_wcsnlen	1
//#elif defined(__BORLANDC__)	// No: bcb6 .
#else
	#define ZL_CRT_strnlen	0
	#define ZL_CRT_wcsnlen	0
#endif
#endif	// #ifndef ZL_CRT_strnlen

/// @def ZL_CRT_mbstate
/// mbstate_t
///
#ifndef ZL_CRT_mbstate
#if defined(_MSC_VER)	// VC.
	#define ZL_CRT_mbstate	1
	# if (_MSC_VER==1200 || _MSC_VER>=1400)	// VC6, VC2005+
		#define ZL_CRT_mbrtowc	1
		#define ZL_CRT_wcrtomb	1
	#else
		// VC2003 虽然有 mbstate_t, 在链接时有时找不到 mbrtowc/wcrtomb (error LNK2019: 无法解析的外部符号 _mbrtowc ，该符号在函数 _ZLUtfGetChar_a@16 中被引用).
		#define ZL_CRT_mbrtowc	0
		#define ZL_CRT_wcrtomb	0
	#endif
#elif defined(__GNUC__)	// gcc: OK .
	#define ZL_CRT_mbstate	1
	#define ZL_CRT_mbrtowc	1
	#define ZL_CRT_wcrtomb	1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__>199901L) // C99 .
	#define ZL_CRT_mbstate	1
	#define ZL_CRT_mbrtowc	1
	#define ZL_CRT_wcrtomb	1
//#elif defined(__BORLANDC__)	// bcb6: no .
#else
	#define ZL_CRT_mbstate	0
	#define ZL_CRT_mbrtowc	0
	#define ZL_CRT_wcrtomb	0
#endif
#endif	// #ifndef ZL_CRT_mbstate


#ifndef ZL_CRT_fgetpos
#define ZL_CRT_fgetpos	1
#define ZL_CRT_fsetpos	1
#endif

#ifndef ZL_CRT__fseeki64
#if defined(_MSC_VER) && (_MSC_VER>=1400)	// VC2005
#define ZL_CRT__fseeki64	1
#define ZL_CRT__ftelli64	1
#else
#define ZL_CRT__fseeki64	0
#define ZL_CRT__ftelli64	0
#endif
#endif

/// @def ZL_CRT_fgetpos
/// Has fgetpos .

/// @def ZL_CRT_fsetpos
/// Has fsetpos .

/// @def ZL_CRT__fseeki64
/// Has _fseeki64 .

/// @def ZL_CRT__ftelli64
/// Has _ftelli64 .


////////////////////////////////////////
// Compatibility macro (兼容宏) .
////////////////////////////////////////

/// @def EXTERN_C
/// extern "C" .
///
#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C    extern
#endif
#endif

/// @def INLINE
/// inline (内联) .
///
#ifndef INLINE
#if defined(__STDC_VERSION__) && (__STDC_VERSION__>199901L) // C99 .
	#define INLINE	inline
#elif defined(_MSC_VER) || defined(__GNUC__) || defined(__BORLANDC__)   // vc, gcc, bcb .
	#define INLINE	__inline
#else
	#define INLINE
#endif
#endif	// #ifndef INLINE


////////////////////////////////////////
// Special macro (专用宏) .
////////////////////////////////////////

// == Usually (常用) ==

/// @def ZLCALL
/// Call convention (调用约定) .
///
/// 在Windows平台下默认是 `__stdcall`, 其他情况使用默认调用约定.
///
#ifndef ZLCALL
#if (defined(WIN32) || defined(WIN64))
#define ZLCALL	__stdcall
#else
#define ZLCALL
#endif
#endif	// #ifndef ZLCALL

#define ZL_MACTOSTR(x)	#x	//!< Macro name string (宏名字符串).
#define ZL_MACROVALUESTR(x)	ZL_MACTOSTR(x)	//!< Macro value string (宏值字符串).

/// @def ZL_COMPILER_NAME
/// Compiler name (编译器名称) .
///
#ifndef ZL_COMPILER_NAME
#if defined(__ICL)	// Intel C++
#  if defined(__VERSION__)
#    define ZL_COMPILER_NAME	"Intel C++ " __VERSION__
#  elif defined(__INTEL_COMPILER_BUILD_DATE)
#    define ZL_COMPILER_NAME	"Intel C++ (" ZL_MACROVALUESTR(__INTEL_COMPILER_BUILD_DATE) ")"
#  else
#    define ZL_COMPILER_NAME	"Intel C++"
#  endif	// #  if defined(__VERSION__)
#elif defined(_MSC_VER)	// Microsoft VC++
#  if defined(_MSC_FULL_VER)
#    define ZL_COMPILER_NAME	"Microsoft VC++ (" ZL_MACROVALUESTR(_MSC_FULL_VER) ")"
#  elif defined(_MSC_VER)
#    define ZL_COMPILER_NAME	"Microsoft VC++ (" ZL_MACROVALUESTR(_MSC_VER) ")"
#  else
#    define ZL_COMPILER_NAME	"Microsoft VC++"
#  endif	// #  if defined(_MSC_FULL_VER)
#elif defined(__GNUC__)	// GCC
#  if defined(__CYGWIN__)
#    define ZL_COMPILER_NAME	"GCC(Cygmin) " __VERSION__
#  elif defined(__MINGW32__)
#    define ZL_COMPILER_NAME	"GCC(MinGW) " __VERSION__
#  else
#    define ZL_COMPILER_NAME	"GCC " __VERSION__
#  endif	// #  if defined(_MSC_FULL_VER)
#elif defined(__BCPLUSPLUS__)	// Borland C++
#  define ZL_COMPILER_NAME	"Borland C++ (" ZL_MACROVALUESTR(__BCPLUSPLUS__) ")"
#elif defined(__BORLANDC__)	// Borland C
#  define ZL_COMPILER_NAME	"Borland C (" ZL_MACROVALUESTR(__BORLANDC__) ")"
#elif defined(__TCPLUSPLUS__)	// Turbo C++
#  define ZL_COMPILER_NAME	"Turbo C++ (" ZL_MACROVALUESTR(__TCPLUSPLUS__) ")"
#elif defined(__TURBOC__)	// Turbo C
#  define ZL_COMPILER_NAME	"Turbo C (" ZL_MACROVALUESTR(__TURBOC__) ")"
#else
#  define ZL_COMPILER_NAME	"Unknown Compiler"
#endif	// #if defined(__ICL)	// Intel C++
#endif	// #ifndef ZL_COMPILER_NAME

/// @def ZL_WORDSIZE
/// Word size(机器字长) .
///
#ifndef ZL_WORDSIZE
#if ( defined(INT64_MAX) && PTRDIFF_MAX >= INT64_MAX )
	#define ZL_WORDSIZE	64
#elif PTRDIFF_MAX >= INT32_MAX
	#define ZL_WORDSIZE	32
#else
	#define ZL_WORDSIZE	16
#endif
#endif	// #ifndef ZL_WORDSIZE

/// @def ZL_ALIGN
/// Alignment(对齐) .
///
#ifndef ZL_ALIGN
#if defined(__GNUC__)	// GCC
	#define ZL_ALIGN(n)	__attribute__((aligned(n)))
#else	// 否则使用VC格式.
	#define ZL_ALIGN(n)	__declspec(align(n))
#endif	// #if defined(__GNUC__)	// GCC
	// [TODO] C++11 alignas .
#endif	// #ifndef ZL_ALIGN


// == Memory (存储) ==

/// Allocates memory blocks.
///
/// @param[in]	sz	Bytes to allocate. 
/// @return	Returns a void pointer to the allocated space, or NULL if there is insufficient memory available. 
#define ZLALLOC(sz)	malloc(sz)

/// Deallocates or frees a memory block.
///
/// @param[in]	p	Previously allocated memory block to be freed. 
#define ZLFREE(p)	free(p)


// == Size (大小) ==

/// Array count (数组长度).
#define ZLCOUNT(arr)	(sizeof(arr)/sizeof(arr[0]))

/// Array element size (数组元素大小).
#define ZLESIZE(arr)	(sizeof(arr[0]))

/// Struct member (结构体成员).
#define ZLMEMBER(structtype, field)	( ((structtype *)0)->field )

/// Struct member size (结构体成员的总字节数).
#define ZLMSIZE(structtype, field)	(sizeof( ZLMEMBER(structtype, field) ))

/// Struct member ElementSize (结构体成员的元素大小). 或用于计算指针数据元素的大小.
#define ZLMESIZE(structtype, field)	(sizeof( ZLMEMBER(structtype, field[0]) ))

/// Struct member pointer data ElementSize (结构体成员的指针数据元素大小).
#define ZLMPESIZE(structtype, field)	(sizeof( ZLMEMBER(structtype, field[0][0]) ))

/// Struct member ArrayCount (结构体成员的数组长度).
#define ZLMCOUNT(structtype, field)	(ZLMSIZE(structtype,field)/ZLMSIZE(structtype,field[0]))


// == Char (字符) ==

/// @def ZLWCHAR_BITS
/// wchar_t bits (宽字符位数). 可为 0(未知), sizeof(char), 16, 32 .
#ifndef ZL_NOWIDE
	#if (WINT_MAX==UINT32_MAX) || (WINT_MAX==INT32_MAX)	// UTF-32
		#define ZLWCHAR_BITS	32
	#elif (WINT_MAX==UINT16_MAX) || (WINT_MAX==INT16_MAX)	// UTF-16
		#define ZLWCHAR_BITS	16
	#elif (WINT_MAX==UCHAR_MAX) || (WINT_MAX==SCHAR_MAX)	// UTF-16
		#define ZLWCHAR_BITS	CHAR_BIT
	#else
		#define ZLWCHAR_BITS	0
	#endif	// #if WINT_MAX
#else
	#define ZLWCHAR_BITS	0
#endif	// #ifndef ZL_NOWIDE

/// [internal] Alway narrow char - escape (仍是窄字符常量-转义).
#define ZL_ESCAPE_CHAR(x)	x

/// Alway narrow char (仍是窄字符常量).
#define _CA(x)	ZL_ESCAPE_CHAR(x)

/// [internal] Conv char to wchar_t - escape  (将窄字符常量转为宽字符常量-转义).
#define ZL_ESCAPE_WCHAR(x)	L ## x

/// Convert char to wchar_t (将窄字符常量转为宽字符常量).
#define _CW(x)	ZL_ESCAPE_WCHAR(x)


// == fpos (文件位置) ==

/// @def ZLFPOS_GETINT
/// Get fpos_t position integer (取得 fpos_t 的位置整数).
#ifdef _G_config_h
#define ZLFPOS_GETINT(fpos)	((intmax_t)((fpos).__pos))	
#else
#define ZLFPOS_GETINT(fpos)	((intmax_t)(fpos))	
#endif

/// @def ZLFPOS_SETINT
/// Set fpos_t position integer (设置 fpos_t 的位置整数).
#ifdef _G_config_h
	// gcc: stdio.h, _G_config.h
	#ifndef __USE_FILE_OFFSET64
		#define ZLFPOS_SETINT(fpos, posint)	(fpos).__pos=(__off_t)(posint)	
	#else
		#define ZLFPOS_SETINT(fpos, posint)	(fpos).__pos=(__off64_t)(posint)	
	#endif
#else
	#define ZLFPOS_SETINT(fpos, posint)	fpos=(fpos_t)(posint)
#endif



////////////////////////////////////////
// attribute (特性).
////////////////////////////////////////

#ifdef __GNUC__
#ifdef __MINGW32__
#define ZLATTRIBUTE_FORMAT_PRINTF(idxstr, idxcheck)	__attribute__((format(ms_printf, idxstr, idxcheck)))
#define ZLATTRIBUTE_FORMAT_SCANF(idxstr, idxcheck)	__attribute__((format(ms_scanf, idxstr, idxcheck)))
#else
#define ZLATTRIBUTE_FORMAT_PRINTF(idxstr, idxcheck)	__attribute__((format(printf, idxstr, idxcheck)))
#define ZLATTRIBUTE_FORMAT_SCANF(idxstr, idxcheck)	__attribute__((format(scanf, idxstr, idxcheck)))
#endif
#else	// #ifdef __GNUC__
#define ZLATTRIBUTE_FORMAT_PRINTF(idxstr, idxcheck)
#define ZLATTRIBUTE_FORMAT_SCANF(idxstr, idxcheck)
#endif	// #ifdef __GNUC__

#define ZLATTRIBUTE_FORMAT_WPRINTF(idxstr, idxcheck)
#define ZLATTRIBUTE_FORMAT_WSCANF(idxstr, idxcheck)

#ifdef UNICODE
	#define ZLATTRIBUTE_FORMAT_TPRINTF	ZLATTRIBUTE_FORMAT_WPRINTF
	#define ZLATTRIBUTE_FORMAT_TSCANF	ZLATTRIBUTE_FORMAT_WSCANF
#else	// #ifdef UNICODE
	#define ZLATTRIBUTE_FORMAT_TPRINTF	ZLATTRIBUTE_FORMAT_PRINTF
	#define ZLATTRIBUTE_FORMAT_TSCANF	ZLATTRIBUTE_FORMAT_SCANF
#endif	// #ifdef UNICODE

/// @def ZLATTRIBUTE_FORMAT_PRINTF
/// The format attribute specifies that a function takes printf style arguments that should be type-checked against a format string.
///

/// @def ZLATTRIBUTE_FORMAT_SCANF
/// The format attribute specifies that a function takes scanf style arguments that should be type-checked against a format string.
///

/// @def ZLATTRIBUTE_FORMAT_WPRINTF
/// The format attribute specifies that a function takes wprintf style arguments that should be type-checked against a format string.
///

/// @def ZLATTRIBUTE_FORMAT_WSCANF
/// The format attribute specifies that a function takes wscanf style arguments that should be type-checked against a format string.
///

/// @def ZLATTRIBUTE_FORMAT_TPRINTF
/// The format attribute specifies that a function takes _tprintf style arguments that should be type-checked against a format string.
///

/// @def ZLATTRIBUTE_FORMAT_TSCANF
/// The format attribute specifies that a function takes _tscanf style arguments that should be type-checked against a format string.
///


////////////////////////////////////////
// zlresult - Result (返回值).
////////////////////////////////////////

//#include <errno.h>
//#include <winerror.h>

/// Result (返回值).
///
/// Same as HRESULT (类似HRESULT). 大于等于0时成功，此时低16位可用于存放结果; 小于0时失败，整个32位均作为错误码. 找不到合适的错误码时, 可返回-1.
///
/// 	// winerror.h
/// 	// 
/// 	// HRESULTs are 32 bit values layed out as follows:
/// 	// 
/// 	//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
/// 	//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
/// 	// +-+-+-+-+-+---------------------+-------------------------------+
/// 	// |S|R|C|N|r|    Facility         |               Code            |
/// 	// +-+-+-+-+-+---------------------+-------------------------------+
/// 	// 
/// 	// where
/// 	// 
/// 	//     S - Severity - indicates success/fail
/// 	// 
/// 	//         0 - Success
/// 	//         1 - Fail (COERROR)
/// 	// 
/// 	//     R - reserved portion of the facility code, corresponds to NT's
/// 	//             second severity bit.
/// 	// 
/// 	//     C - reserved portion of the facility code, corresponds to NT's
/// 	//             C field.
/// 	// 
/// 	//     N - reserved portion of the facility code. Used to indicate a
/// 	//             mapped NT status value.
/// 	// 
/// 	//     r - reserved portion of the facility code. Reserved for internal
/// 	//             use. Used to indicate HRESULT values that are not status
/// 	//             values, but are instead message ids for display strings.
/// 	// 
/// 	//     Facility - is the facility code
/// 	// 
/// 	//     Code - is the facility's status code
///
///
typedef int32_t zlresult;

#define ZLSUCCEEDED(hr)	((zlresult)(hr) >= 0)	//!< success.
#define ZLFAILED(hr)	((zlresult)(hr) < 0)	//!< failure.
#define ZLISERROR(Status) ((uint32_t)(Status) >> 31 == 1)	//!< Generic test for error on any status value.
#define ZLRESULT_CODE(hr)    ((hr) & INT32_C(0xFFFF))	//!< Return the code.
#define ZLRESULT_FACILITY(hr)  (((zlresult)(hr) >> 16) & INT32_C(0xfff))	//!< Return the facility.
#define ZLRESULT_SEVERITY(hr)  (((zlresult)(hr) >> 31) & 0x1)	//!< Return the severity.

#define ZLFACILITY_NULL	0	//!< Same FACILITY_NULL .
#define ZLFACILITY_C	0x700	//!< C error.

/// Convert to zlresult type (转换为 zlresult 类型) .
#define ZLRESULT_CASE(x)    ((zlresult)(x))

/// Create an HRESULT value from component pieces.
///
/// @param[in]	sev	severity.
/// @param[in]	fac	facility.
/// @param[in]	code	code.
/// @return	zlresult.
///
#define ZLRESULT_MAKE(sev,fac,code) \
    ((zlresult) (((uint32_t)(sev)<<31) | (((uint32_t)(fac) & UINT32_C(0x1fff))<<16) | ((uint32_t)(code) & UINT32_C(0xFFFF))) )

/// Map an C errno into a zlresult.
///
/// @param[in]	x	C errno.
/// @return	zlresult.
///
#define ZLRESULT_FROM_C(x)      ZLRESULT_MAKE(1, ZLFACILITY_C, x)


// == Error Codes.
#define ZL_E_OK	0	//!< OK.
#define ZL_E_ERROR	-1	//!< Unknown error.

// == Error Codes: C.
#define ZL_EDOM	ZLRESULT_FROM_C(EDOM)	//!< EDOM .
#define ZL_EILSEQ	ZLRESULT_FROM_C(EILSEQ)	//!< EILSEQ .
#define ZL_ERANGE	ZLRESULT_FROM_C(ERANGE)	//!< ERANGE .


// == Error Codes: Windows.

/// Catastrophic failure
#define ZL_E_UNEXPECTED                     ZLRESULT_CASE(0x8000FFFFL)

/// Not implemented
#define ZL_E_NOTIMPL                        ZLRESULT_CASE(0x80004001L)

/// Ran out of memory
#define ZL_E_OUTOFMEMORY                    ZLRESULT_CASE(0x8007000EL)

/// One or more arguments are invalid
#define ZL_E_INVALIDARG                     ZLRESULT_CASE(0x80070057L)

/// No such interface supported
#define ZL_E_NOINTERFACE                    ZLRESULT_CASE(0x80004002L)

/// Invalid pointer
#define ZL_E_POINTER                        ZLRESULT_CASE(0x80004003L)

/// Invalid handle
#define ZL_E_HANDLE                         ZLRESULT_CASE(0x80070006L)

/// Operation aborted
#define ZL_E_ABORT                          ZLRESULT_CASE(0x80004004L)

/// Unspecified error
#define ZL_E_FAIL                           ZLRESULT_CASE(0x80004005L)

/// General access denied error
#define ZL_E_ACCESSDENIED                   ZLRESULT_CASE(0x80070005L)

/// The data necessary to complete this operation is not yet available.
#define ZL_E_PENDING                        ZLRESULT_CASE(0x8000000AL)


////////////////////////////////////////
// endian (端序)
////////////////////////////////////////

// == __BYTE_ORDER__ ==

// [GCC] 3.7.2 Common Predefined Macros: http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
//__BYTE_ORDER__	1234
//__ORDER_LITTLE_ENDIAN__	1234
//__ORDER_BIG_ENDIAN__	4321

/// @def __ORDER_BIG_ENDIAN__
/// Byte order - big endian (字节序-大端端序).
///
#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__	4321
#endif

/// @def __ORDER_LITTLE_ENDIAN__
/// Byte order - little endian (字节序-小端端序).
///
#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__	1234
#endif

/// @def __BYTE_ORDER__
/// Host byte order (主机的字节序). 默认是小端方式.
///
#ifndef __BYTE_ORDER__	// 若没有定义, 默认判定为小端方式.
#define __BYTE_ORDER__	__ORDER_LITTLE_ENDIAN__
#endif	// #ifndef __BYTE_ORDER__


// == ZLENDIAN ==

// ZLENDIAN: endian (端序模式).
#define ZLENDIAN_AUTO	0	//!< Auto endian(自动端序).
#define ZLENDIAN_BIG	1	//!< Big endian(大端端序).
#define ZLENDIAN_LITTLE	2	//!< Little endian(小端端序).
#define ZLENDIAN_MIN	ZLENDIAN_AUTO		//!< Min ZLENDIAN.
#define ZLENDIAN_MAX	ZLENDIAN_LITTLE		//!< Max ZLENDIAN.

#define ZLENDIAN_NET	ZLENDIAN_BIG		//!< Netware endian(网络端序).

/// @def ZLENDIAN_HOST
/// Host endian (主机端序).
///
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
	#define ZLENDIAN_HOST	ZLENDIAN_BIG
#elif __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define ZLENDIAN_HOST	ZLENDIAN_LITTLE
#else	// 未知端序.
	#define ZLENDIAN_HOST	ZLENDIAN_AUTO
#endif


// == Utility (常用函数) ==

/// Make 16bit integer by little endian (根据小端字节序构造16位整数).
#define zlmake16le(by0,by1)	( (uint16_t)( \
			( (uint16_t)(by0) & 0xFFU ) \
			| ( ((uint16_t)(by1) & 0xFFU) << 8 ) \
	) )

/// Make 32bit integer by little endian (根据小端字节序构造32位整数).
#define zlmake32le(by0,by1,by2,by3)	( (uint32_t)( \
			( (uint32_t)(by0) & 0xFFU ) \
			| ( ((uint32_t)(by1) & 0xFFU) << 8 ) \
			| ( ((uint32_t)(by2) & 0xFFU) << 16 ) \
			| ( ((uint32_t)(by3) & 0xFFU) << 24 ) \
	) )

/// Make 64bit integer by little endian (根据小端字节序构造64位整数).
#define zlmake64le(by0,by1,by2,by3,by4,by5,by6,by7)	( (uint64_t)( \
			( (uint64_t)(by0) & 0xFFU ) \
			| ( ((uint64_t)(by1) & 0xFFU) << 8 ) \
			| ( ((uint64_t)(by2) & 0xFFU) << 16 ) \
			| ( ((uint64_t)(by3) & 0xFFU) << 24 ) \
			| ( ((uint64_t)(by4) & 0xFFU) << 32 ) \
			| ( ((uint64_t)(by5) & 0xFFU) << 40 ) \
			| ( ((uint64_t)(by6) & 0xFFU) << 48 ) \
			| ( ((uint64_t)(by7) & 0xFFU) << 56 ) \
	) )

/// Make 16bit integer by big endian (根据大端字节序构造16位整数).
#define zlmake16be(by0,by1)	zlmake16le(by1,by0)

/// Make 32bit integer by big endian (根据大端字节序构造32位整数).
#define zlmake32be(by0,by1,by2,by3)	zlmake32le(by3,by2,by1,by0)

/// Make 64bit integer by big endian (根据大端字节序构造64位整数).
#define zlmake64be(by0,by1,by2,by3,by4,by5,by6,by7)	zlmake64le(by7,by6,by5,by4,by3,by2,by1,by0)

/// Swap byte on 16bit integer (对16位整数翻转字节序).
///
/// @param[in]	x	Value.
/// @return	Return swap byte on 16bit integer (返回翻转字节序后的16位整数值).
///
#define zlswap16(x)	( (uint16_t)( \
			( ((uint16_t)(x) & (uint16_t)0x00ffU) << 8 ) | \
			( ((uint16_t)(x) & (uint16_t)0xff00U) >> 8 ) \
	) )

/// Swap byte on 32bit integer (对32位整数翻转字节序).
///
/// @param[in]	x	Value.
/// @return	Return swap byte on 32bit integer (返回翻转字节序后的32位整数值).
///
#define zlswap32(x)	( (uint32_t)( \
			( ((uint32_t)(x) & (uint32_t)UINT32_C(0x000000ff)) << 24 ) | \
			( ((uint32_t)(x) & (uint32_t)UINT32_C(0x0000ff00)) <<  8 ) | \
			( ((uint32_t)(x) & (uint32_t)UINT32_C(0x00ff0000)) >>  8 ) | \
			( ((uint32_t)(x) & (uint32_t)UINT32_C(0xff000000)) >> 24 ) \
	) )

/// Swap byte on 64bit integer (对64位整数翻转字节序).
///
/// @param[in]	x	Value.
/// @return	Return swap byte on 64bit integer (返回翻转字节序后的64位整数值).
///
#define zlswap64(x)	( (uint64_t)( \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x00000000000000ff)) << 56 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x000000000000ff00)) << 40 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x0000000000ff0000)) << 24 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x00000000ff000000)) <<  8 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x000000ff00000000)) >>  8 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x0000ff0000000000)) >> 24 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0x00ff000000000000)) >> 40 ) | \
			( ((uint64_t)(x) & (uint64_t)UINT64_C(0xff00000000000000)) >> 56 ) \
	) )


/// Load 16bit integer by big endian (根据大端字节序从内存中加载16位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint16_t ZLCALL zlbeload16(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	return zlmake16be(p[0], p[1]);
}

/// Load 32bit integer by big endian (根据大端字节序从内存中加载32位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint32_t ZLCALL zlbeload32(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	return zlmake32be(p[0], p[1], p[2], p[3]);
}

/// Load 64bit integer by big endian (根据大端字节序从内存中加载64位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint64_t ZLCALL zlbeload64(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	return zlmake64be(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
}


/// Load 16bit integer by little endian (根据小端字节序从内存中加载16位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint16_t ZLCALL zlleload16(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	return zlmake16le(p[0], p[1]);
}

/// Load 32bit integer by little endian (根据小端字节序从内存中加载32位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint32_t ZLCALL zlleload32(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	//uint8_t by0 = p[0];
	//uint8_t by1 = p[1];
	//uint8_t by2 = p[2];
	//uint8_t by3 = p[3];
	//return zlmake32le(by0,by1,by2,by3);
	return zlmake32le(p[0], p[1], p[2], p[3]);
}

/// Load 64bit integer by little endian (根据小端字节序从内存中加载64位整数).
///
/// @param[in]	psrc	Source pointeger (源指针).
/// @return	Return load value (返回加载的值).
///
static INLINE uint64_t ZLCALL zlleload64(const void* psrc) {
	const uint8_t* p = (const uint8_t*)psrc;
	return zlmake64le(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
}

/// Save 16bit integer by big endian (根据大端字节序从内存中存储16位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zlbesave16(void* pdst, uint16_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[0] = (uint8_t)( x>>8 );
	p[1] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Save 32bit integer by big endian (根据大端字节序从内存中存储32位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zlbesave32(void* pdst, uint32_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[0] = (uint8_t)( x>>24 );
	p[1] = (uint8_t)( (x>>16)&0xFF );
	p[2] = (uint8_t)( (x>>8)&0xFF );
	p[3] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Save 64bit integer by big endian (根据大端字节序从内存中存储64位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zlbesave64(void* pdst, uint64_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[0] = (uint8_t)( x>>56 );
	p[1] = (uint8_t)( (x>>48)&0xFF );
	p[2] = (uint8_t)( (x>>40)&0xFF );
	p[3] = (uint8_t)( (x>>32)&0xFF );
	p[4] = (uint8_t)( (x>>24)&0xFF );
	p[5] = (uint8_t)( (x>>16)&0xFF );
	p[6] = (uint8_t)( (x>>8)&0xFF );
	p[7] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Save 16bit integer by little endian (根据小端字节序从内存中存储16位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zllesave16(void* pdst, uint16_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[1] = (uint8_t)( x>>8 );
	p[0] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Save 32bit integer by little endian (根据小端字节序从内存中存储32位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zllesave32(void* pdst, uint32_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[3] = (uint8_t)( x>>24 );
	p[2] = (uint8_t)( (x>>16)&0xFF );
	p[1] = (uint8_t)( (x>>8)&0xFF );
	p[0] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Save 64bit integer by little endian (根据小端字节序从内存中存储64位整数).
///
/// @param[out]	pdst	Destination pointeger (目标指针).
/// @param[in]	x	Value (值).
/// @return	Return pdst (返回 pdst ).
///
static INLINE void* ZLCALL zllesave64(void* pdst, uint64_t x) {
	uint8_t* p = (uint8_t*)pdst;
	p[7] = (uint8_t)( x>>56 );
	p[6] = (uint8_t)( (x>>48)&0xFF );
	p[5] = (uint8_t)( (x>>40)&0xFF );
	p[4] = (uint8_t)( (x>>32)&0xFF );
	p[3] = (uint8_t)( (x>>24)&0xFF );
	p[2] = (uint8_t)( (x>>16)&0xFF );
	p[1] = (uint8_t)( (x>>8)&0xFF );
	p[0] = (uint8_t)( x&0xFF );
	return pdst;
}

/// Swap bytes (对一片内存区域进行交换字节).
///
/// @param[in,out]	pdata	Data pointer (数据指针).
/// @param[in]	esize	Item size in bytes (项目字节数).
/// @param[in]	count	Items count (项目数量).
///
static INLINE void ZLCALL zlswapbytes(void* pdata, size_t esize, size_t count) {
	uint8_t* p;
	uint8_t by;
	size_t mid;
	size_t i,j;
	if (NULL==pdata) return;
	if (0==esize) return;
	if (0==count) return;
	p = (uint8_t*)pdata;
	for(i=0; i<count; ++i, p+=esize) {
		mid = esize/2;
		for(j=0; j<mid; ++j) {
			by = p[i];
			p[i] = p[esize-1-i];
			p[esize-1-i] = by;
		}
	}
}

/// Convect load data to host endian (将加载的数据转换为主机端序).
///
/// @param[in,out]	pdata	Data pointer (数据指针).
/// @param[in]	esize	Item size in bytes (项目字节数).
/// @param[in]	count	Items count (项目数量).
/// @param[in]	endian	Endian (字节序). @ref ZLENDIAN_AUTO "ZLENDIAN".
///
static INLINE void ZLCALL zlhostload(void* pdata, size_t esize, size_t count, int endian) {
	if (ZLENDIAN_AUTO==endian) endian=ZLENDIAN_HOST;
	if (endian!=ZLENDIAN_HOST) zlswapbytes(pdata, esize, count);
}

/// Convect host data to save endian (将主机数据转换为存储端序).
///
/// @param[in,out]	pdata	Data pointer (数据指针).
/// @param[in]	esize	Item size in bytes (项目字节数).
/// @param[in]	count	Items count (项目数量).
/// @param[in]	endian	Endian (字节序). @ref ZLENDIAN_AUTO "ZLENDIAN".
///
static INLINE void ZLCALL zlhostsave(void* pdata, size_t esize, size_t count, int endian) {
	if (ZLENDIAN_AUTO==endian) endian=ZLENDIAN_HOST;
	if (endian!=ZLENDIAN_HOST) zlswapbytes(pdata, esize, count);
}



////////////////////////////////////////
// @ref GROUP_ZYLLIBC's Object (对象).
////////////////////////////////////////

// == GUID.
// By: guiddef.h

/// @def ZLGUID
/// GUID.
///
/// See: guiddef.h/GUID .
#ifdef DEFINE_GUID
	// Exists guiddef.h .
	typedef GUID ZLGUID;
#else
	// Not exists guiddef.h .
	typedef struct ZLGUID {
		uint32_t	Data1;
		uint16_t	Data2;
		uint16_t	Data3;
		uint8_t	Data4[8];
	} ZLGUID;
#endif
typedef ZLGUID* PZLGUID;	//!< @ref ZLGUID pointer.
typedef const ZLGUID* PCZLGUID;	//!< @ref ZLGUID const pointer.
typedef PCZLGUID ZLREFGUID;	//!< @ref ZLGUID const reference.
typedef ZLGUID ZLIID;	//!< Interface ID.
typedef ZLIID* PZLIID;	//!< @ref ZLIID "Interface ID" pointer.
typedef const ZLIID* PCZLIID;	//!< @ref ZLIID "Interface ID" const pointer.
typedef PCZLIID ZLREFIID;	//!< @ref ZLIID "Interface ID" const reference.
typedef ZLGUID ZLCLSID;	//!< Class ID.
typedef ZLCLSID* PZLCLSID;	//!< @ref ZLIID "Class ID" pointer.
typedef const ZLCLSID* PCZLCLSID;	//!< @ref ZLIID "Class ID" const pointer.
typedef PCZLCLSID ZLREFCLSID;	//!< @ref ZLIID "Class ID" const reference.

/// Retrieves the GUID attached to the name. 
#define ZLUUIDOF(name)	IID_##name

/// Define ZLGUID const.
///
/// See: guiddef.h/DEFINE_GUID
#define ZLGUID_DEFINE(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        static const ZLGUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

//#define ZLInlineIsEqualGUID(rguid1, rguid2)  \_
//        (((uint32_t*) rguid1)[0] == ((uint32_t*) rguid2)[0] &&   \_
//        ((uint32_t*) rguid1)[1] == ((uint32_t*) rguid2)[1] &&    \_
//        ((uint32_t*) rguid1)[2] == ((uint32_t*) rguid2)[2] &&    \_
//        ((uint32_t*) rguid1)[3] == ((uint32_t*) rguid2)[3])

/// Determines whether two ZLGUID are equal.
#define ZLIsEqualGUID(rguid1, rguid2) (!memcmp(rguid1, rguid2, sizeof(ZLGUID)))
#define ZLIsEqualIID(riid1, riid2) ZLIsEqualGUID(riid1, riid2)	//!< Determines whether two ZLIID are equal.
#define ZLIsEqualCLSID(rclsid1, rclsid2) ZLIsEqualGUID(rclsid1, rclsid2)	//!< Determines whether two ZLCLSID are equal.



// == VTBL (虚函数表).

/// @def CONST_VTBL
/// Virtual table: const.
///
/// By: rpcndr.h
#ifndef CONST_VTBL
#ifdef CONST_VTABLE
#define CONST_VTBL const
#else
#define CONST_VTBL
#endif
#endif

/// Convert object to target type ex (将对象转为目标类型加强版) .
///
/// @param[in]	vtp	Value type (值类型).
/// @param[in]	This	This object (这个对象). 一般为结构体指针.
/// @param[in]	vtblname	Virtual table name (虚函数表名).
/// @return	Return target type's object (返回目标类型的对象).
#define ZLCASTEX(vtp, This, vtblname)	( (vtp*)(void*)&((This)->vtblname) )

/// @def ZLVERIFYVTBLEX
/// Verify virtual functions ex (验证虚函数表加强版).
///
/// @param[in]	This	This object (这个对象). 一般为结构体指针.
/// @param[in]	vtblname	Virtual table name (虚函数表名).
/// @return	若有效便返回非零, 失败时返回0.
#ifdef NDEBUG
#define ZLVERIFYVTBLEX(This, vtblname)	1	// Alway true.
#else
#define ZLVERIFYVTBLEX(This, vtblname)	(assert(NULL!=(This)), assert(NULL!=(This)->vtblname), 1)	// Verify by compile (编译时验证).
//#define ZLVERIFYVTBLEX(This, vtblname)	(NULL!=(This) && NULL!=(This)->vtblname)	// Verify by runtime (运行时验证).
#endif

/// @def ZLVERIFYVFNEX
/// Verify virtual function ex (验证虚函数加强版) .
///
/// @param[in]	This	This object (这个对象). 一般为结构体指针.
/// @param[in]	vtblname	Virtual table name (虚函数表名).
/// @param[in]	fn	Function name (函数名).
/// @return	若有效便返回非零, 失败时返回0.
#ifdef NDEBUG
#define ZLVERIFYVFNEX(This, vtblname, fn)	1	// Alway true.
#else
#define ZLVERIFYVFNEX(This, vtblname, fn)	(assert(NULL!=(This)), assert(NULL!=(This)->vtblname), assert(NULL!=(This)->vtblname->fn), 1)	// Verify by compile (编译时验证).
//#define ZLVERIFYVFNEX(This, vtblname, fn)	(NULL!=(This) && NULL!=(This)->vtblname && NULL!=(This)->vtblname->fn)	// Verify by runtime (运行时验证).
#endif

#define ZLCAST(vtp, This)	ZLCASTEX(vtp, This, pvtbl)	//!< Convert object to target type (将对象转为目标类型) .
#define ZLVERIFYVTBL(This)	ZLVERIFYVTBLEX(This, pvtbl)	//!< Verify virtual table (验证虚函数表).
#define ZLVERIFYVFN(This, fn)	ZLVERIFYVFNEX(This, pvtbl, fn)	//!< Verify virtual function (验证虚函数) .


// == Object control code (对象控制码).

#define ZLOBJCTLCODE_NULL	0	//!< void.
#define ZLOBJCTLCODE_QUERYINTERFACE	1	//!< QueryInterface. pin is interface GUID (*ZLGUID), pout return interface pointeger;
#define ZLOBJCTLCODE_ADDREF	2	//!< AddRef.
#define ZLOBJCTLCODE_RELEASE	3	//!< Release.

#define ZLOBJCTLCODE_USER	INT32_C(0x40000000)	//!< User object control code .
#define ZLOBJCTLCODE_USERMAX	INT32_C(0x7FFFFFFF)	//!< Max user object control code .


// == IZLUnknown (未知对象).

// Forward declaration (前置申明).
struct IZLUnknown;

/// @ref IZLUnknown 's IID.
///
/// MIDL_INTERFACE("00000000-0000-0000-C000-000000000046")
ZLGUID_DEFINE(IID_IZLUnknown,0x0,0x0,0xC000,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/// IZLUnknown virtual table (IZLUnknown的虚函数表) .
typedef struct IZLUnknownVtbl {
	zlresult (ZLCALL *objctl)(struct IZLUnknown* This, unsigned ctlcode, const void* pin, size_t cbin, void* pout, size_t cbout, size_t* pcbouted);	//!< Object control (对象控制). ctlcode is @ref ZLOBJCTLCODE_NULL "ZLOBJCTLCODE"`.
}IZLUnknownVtbl;

/// Unknown object interface (未知对象的接口.) .
typedef struct IZLUnknown {
	CONST_VTBL IZLUnknownVtbl* pvtbl;	//!< Virtual table (虚函数表) .
}IZLUnknown, *PIZLUnknown;	//!< @ref IZLUnknown "Unknown object interface" pointer.


// /// Convert to IZLUnknown* type (转换为 IZLUnknown* 类型) .
//#define IZLUnknown_CASE(This)	ZLCAST(IZLUnknown, This)

// -- object macros

/// Object control (对象控制).
///
/// Prototype: `zlresult IZLUnknown_objctl(IZLUnknown* This, unsigned ctlcode, const void* pin, size_t cbin, void* pout, size_t cbout, size_t* pcbouted);`
///
/// @param[in]	ctlcode	Control code. @ref ZLOBJCTLCODE_NULL "ZLOBJCTLCODE"`.
/// @param[in]	pin	Input buffer (输入缓冲区).
/// @param[in]	cbin	Input buffer bytes (输入缓冲区字节数).
/// @param[in]	pout	Output buffer (输入缓冲区).
/// @param[out]	cbout	Output buffer bytes (输入缓冲区字节数).
/// @param[out]	pcbouted	Returns the bytes actually Output (实际输出的字节数).
/// @return	If successful return a nonegative. A return value of negative indicates an error.
#define IZLUnknown_objctl(This, ctlcode, pin, cbin, pout, cbout, pcbouted)	( ZLVERIFYVFN(This,objctl)?((This)->pvtbl->objctl(ZLCAST(IZLUnknown, This), ctlcode, pin, cbin, pout, cbout, pcbouted)):ZL_E_ERROR )

// By: guiddef.h
//interface IUnKnown {
//virtual HRESULT __stdcall QueryInterface(const IID& iid,void **ppv)=0;
//virtual ULONG __stdcall AddRef()=0;
//virtual ULONG __stdcall Release()=0;
//}

/// Returns pointers to supported interfaces (返回所支持接口的指针).
///
/// Prototype: `zlresult IZLUnknown_QueryInterface(IZLUnknown* This, REFIID riid, void** ppv);`
///
/// @param[in]	riid	REFIID.
/// @param[out]	ppv	Address of pointer variable that receives the interface pointer requested in refiid. If the object does not support the interface specified in iid, *ppvObject is set to NULL. 
/// @return	@ref ZL_E_OK if the interface is supported, @ref ZL_E_NOINTERFACE if not.
#define IZLUnknown_QueryInterface(This, riid, ppv)	IZLUnknown_objctl(This, ZLOBJCTLCODE_QUERYINTERFACE, riid, sizeof(ZLIID), (void*)(ppv), sizeof(void*), NULL)

/// Increments reference count (增加引用计数).
///
/// Prototype: `zlresult IZLUnknown_AddRef(IZLUnknown* This);`
///
/// @return	Returns an integer from 1 to n, the value of the new reference count.
#define IZLUnknown_AddRef(This)	IZLUnknown_objctl(This, ZLOBJCTLCODE_ADDREF, NULL, 0, NULL, 0, NULL)

/// Decrements reference count (减少引用计数).
///
/// Prototype: `zlresult IZLUnknown_Release(IZLUnknown* This);`
///
/// @return	Returns the resulting value of the reference count.
#define IZLUnknown_Release(This)	IZLUnknown_objctl(This, ZLOBJCTLCODE_RELEASE, NULL, 0, NULL, 0, NULL)


// -- short name macros --
#define zlobjctl	IZLUnknown_objctl	//!< @copydoc IZLUnknown_objctl()
#define zlQueryInterface	IZLUnknown_QueryInterface	//!< @copydoc IZLUnknown_QueryInterface
#define zlAddRef	IZLUnknown_AddRef	//!< @copydoc IZLUnknown_AddRef
#define zlRelease	IZLUnknown_Release	//!< @copydoc IZLUnknown_Release


/// @def IZLUnknown_objctl
/// Object control (对象控制).
///
/// Prototype: `zlresult IZLUnknown_objctl(IZLUnknown* This, unsigned ctlcode, const void* pin, size_t cbin, void* pout, size_t cbout, size_t* pcbouted);`
///
/// @param[in]	ctlcode	Control code (控制码). @ref ZLOBJCTLCODE_NULL "ZLOBJCTLCODE".
/// @param[in]	pin	Input buffer (输入缓冲区).
/// @param[in]	cbin	Input buffer bytes (输入缓冲区的字节数).
/// @param[out]	pout	Output buffer (输出缓冲区).
/// @param[in]	cbout	Output buffer bytes (输出缓冲区的字节数).
/// @param[out]	pcbouted	Outed bytes (实际输出的字节数).
/// @return	成功时返回0或正数, 失败时返回负数. @ref ZL_E_OK "zlresult".
///


// -- Common QueryInterface (通用的获取接口) --

/// REFIID and offset .
typedef struct ZLIIDDIFF {
	ZLREFIID riid;	//!< REFIID . 当 riid 为 NULL 时表示列表结束.
	ptrdiff_t offset;	//!< offset (偏移量).
}ZLIIDDIFF, *PZLIIDDIFF;	//!< @ref ZLIIDDIFF "IID and offset" pointer.

/// Common QueryInterface (通用的获取接口).
///
/// @param[in]	ptable	ZLIIDDIFF first item pointer (指向 ZLIIDDIFF 数组的首项). 当 riid 为 NULL 时表示列表结束.
/// @param[in]	This	Interface pointer.
/// @param[in]	riid	REFIID.
/// @param[out]	ppv	Address of pointer variable that receives the interface pointer requested in refiid. If the object does not support the interface specified in iid, *ppvObject is set to NULL. 
/// @return	@ref ZL_E_OK if the interface is supported, @ref ZL_E_NOINTERFACE if not.
static INLINE zlresult zlCommonQueryInterface(const ZLIIDDIFF* ptable, IZLUnknown* This, ZLREFIID riid, void** ppv) {
	zlresult rt = ZL_E_NOINTERFACE;
	void* pv = NULL;
	IZLUnknown* pi;
	do {
		if (NULL==ptable) break;
		if (NULL==This) break;
		if (NULL==riid) break;
		if (NULL==ppv) break;
		while(NULL!=(ptable->riid)) {
			if (ZLIsEqualIID(riid, ptable->riid)) {
				rt = ZL_E_OK;
				pv = ((char*)This) + ptable->offset;
				// AddRef
				pi = (IZLUnknown*)pv;
				zlAddRef(pi);
				break;
			}
			// next.
			++ptable;
		}
	}while(0);
	if (NULL!=ppv) *ppv = pv;
	return rt;
}

/// Common QueryInterface by objctl (通用的获取接口自 objctl).
///
/// @param[in]	ptable	ZLIIDDIFF first item pointer (指向 ZLIIDDIFF 数组的首项). 当 riid 为 NULL 时表示列表结束.
/// @param[in]	This	Interface pointer.
/// @param[in]	ctlcode	Control code (控制码). 忽略, 不进行验证.
/// @param[in]	pin	Input buffer (输入缓冲区). REFIID.
/// @param[in]	cbin	Input buffer bytes (输入缓冲区的字节数).
/// @param[out]	pout	Output buffer (输出缓冲区). Address of pointer variable that receives the interface pointer requested in riid.
/// @param[in]	cbout	Output buffer bytes (输出缓冲区的字节数).
/// @param[out]	pcbouted	Outed bytes (实际输出的字节数).
/// @return	@ref ZL_E_OK if the interface is supported, @ref ZL_E_NOINTERFACE if not.
static INLINE zlresult zlCommonQueryInterfaceObjctl(const ZLIIDDIFF* ptable, IZLUnknown* This, unsigned ctlcode, const void* pin, size_t cbin, void* pout, size_t cbout, size_t* pcbouted) {
	zlresult rt = ZL_E_NOINTERFACE;
	size_t cbouted=0;
	do {
		if (NULL==ptable) break;
		if (NULL==This) break;
		if (NULL==pin) break;
		if (NULL==pout) break;
		if (cbin<sizeof(ZLIID)) break;
		if (cbout<sizeof(void*)) break;
		//
		rt = zlCommonQueryInterface(ptable, This, (ZLREFIID)pin, (void**)pout);
		if (ZLSUCCEEDED(rt)) {
			cbouted = sizeof(void*);
		}
	}while(0);
	if (NULL!=pcbouted) *pcbouted = cbouted;
	return rt;
}

#if defined __cplusplus
};
#endif

#endif	// #ifndef __ZLCORE_H_INCLUDED

/// @}
/// @}
