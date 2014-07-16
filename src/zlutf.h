/// @addtogroup GROUP_ZYLLIBC	zyllibc
/// @{
///

/// @addtogroup GROUP_ZLUTF	zlutf
/// Unicode encoding utility (Unicode 编码工具) .
///
/// @author	[zyl910](mailto:zyl910hero@gmail.com)
/// @version	1.0
/// @date	2014-08-01
///
/// Links:
///
/// * Git:	https://github.com/zyl910/zlutf
/// * Blog:	http://www.cnblogs.com/zyl910/tag/zlutf/
/// 
/// zlutf is a lightweight C/C++ library.
///
/// Features (特性):
/// * Unicode encoding utility (Unicode 编码工具) .
///
/// 
/// Dependent projects (依赖项目):
/// 
/// * [c99int](https://github.com/zyl910/c99int): Auto C99 integer type compliant (让VC等编译器自动兼容C99的整数类型).
/// * [tcharall](https://github.com/zyl910/tcharall): TCHAR on all platforms.
/// * [zlcore](https://github.com/zyl910/zlcore): zyl910's cross platform core library (跨平台核心库) .
///
///
/// ## Usage (用法)
/// 
/// Example code:
/// 
/// 	#define __STDC_LIMIT_MACROS
/// 	#define __STDC_FORMAT_MACROS
/// 	#define __STDC_CONSTANT_MACROS
/// 	
/// 	#include <locale.h>
/// 	
/// 	#include "auto_inttypes.h"
/// 	
/// 	#include "zlutf.h"
/// 	
/// 	#include "prichar.h"
/// 	#include "auto_tmain.h"
/// 	
/// 	int _tmain(int argc, TCHAR* argv[]) {
/// 		// "UTF-*:\u0394\u4E00\U00020000\n" .
/// 		const uint8_t str_u8[] = {'U','T','F','-','8',':', 0xCE,0x94, 0xE4,0xB8,0x80, 0xF0,0xA0,0x80,0x80, '\n'};
/// 		const uint16_t str_u16[] = {'U','T','F','-','1','6',':', 0x394, 0x4E00, 0xD840U,0xDC00U, '\n'};
/// 		const uint32_t str_u32[] = {'U','T','F','-','3','2',':', 0x394, 0x4E00, UINT32_C(0x20000), '\n'};
/// 		const uint32_t str_u32n[] = {'U','T','F','-','3','2',':', 0x394, 0x4E00, UINT32_C(0x20000), '\n', '\0'};	// Null-terminated string.
/// 	
/// 		// init.
/// 		setlocale(LC_ALL, "");	// 使用客户环境的缺省locale.
/// 	
/// 		// show.
/// 		zlutfputius(stdout, NULL, ZLUTF_8, str_u8, sizeof(str_u8));
/// 		zlutfputius(stdout, NULL, ZLUTF_16, str_u16, sizeof(str_u16));
/// 		zlutfputius(stdout, NULL, ZLUTF_32, str_u32, sizeof(str_u32));
/// 		zlutfputius(stdout, NULL, ZLUTF_32, str_u32n, -1);
/// 	
/// 		return 0;
/// 	}
///
///
/// ## Documentation (文档)
/// 
/// You can generate documentation with [doxygen](http://www.stack.nl/~dimitri/doxygen/index.html) (您可以用 doxygen 生成文档).
/// 
/// Use doxywizard to open *.doxygen file (使用doxywizard打开 *.doxygen).
/// 
/// * zlutf_doc.doxygen: Generates documentation from interface files (生成接口的文档) .
/// * zlutf_docfull.doxygen: Generates documentation from interface & implement and example files (生成接口、实现、示例等内容的详细文档).
/// 
/// You may need change INCLUDE_PATH in *.doxyfile with the actual location (您可能需要在 *.doxygen 中调整INCLUDE_PATH为实际路径).
/// 
/// 
/// ## MIT License (MIT许可证)
/// 
/// Copyright (c) 2000-2014 zyl910 \<zyl910hero@gmail.com\>
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
/// * Borland C++: 6.
/// * GCC: 4.6.2~4.7.1(MinGW, MinGW-w64, TDM-GCC), 4.7.0~4.8.1(Fedora 17~19), 4.2~4.2.1(Mac OS X 10.7~10.8).
/// 
/// 
/// 
/// ## Change history (变更日志)
/// 
/// [2014-08-01] v1.0
///
/// * Release v1.0 (发布1.0版).
///
/// @{
///

///
/// @file	zlutf.h
/// @brief	Redirected stream on C/C++ (同时兼容C/C++的可重定向流) .
/// @since	@ref GROUP_ZLUTF 1.0
///
///


#ifndef __ZLUTF_H_INCLUDED
#define __ZLUTF_H_INCLUDED

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "auto_tchar.h"

#include "zlcore.h"

#if defined __cplusplus
extern "C" {
#endif

#define ZLUTF_REPLACEMENT	0xFFFDU	//!< U+FFFD REPLACEMENT CHARACTER.
#define ZLUTF_QUESTION	0x3F	//!< U+003F QUESTION CHARACTER.
#define ZLUTF_DEFAULTCHAR	ZLUTF_QUESTION	//!< Default char (默认字符). 一般可设为 ZLUTF_QUESTION/ZLUTF_REPLACEMENT .

////////////////////////////////////////
// ZLUTF_UNKNOWN: Unicode Translation Format (Unicode 传送格式)
////////////////////////////////////////

#define ZLUTF_UNKNOWN	0	//!< Unknown (未知). 窄字符串时默认为 ZLUTF_NARROW, 宽字符串时默认为 ZLUTF_WIDE.
#define ZLUTF_ERROR	1	//!< Error (错误).
#define ZLUTF_NARROW	2	//!< Narrow char (窄字符). Type: `char`.
#define ZLUTF_8	3	//!< UTF-8 . Type: `uint8_t` or `char`.
#define ZLUTF_16BE	4	//!< UTF-16 Big Endian . Type: `uint16_t` or `char16_t`.
#define ZLUTF_16LE	5	//!< UTF-16 Little Endian . Type: `uint16_t` or `char16_t`.
#define ZLUTF_32BE	6	//!< UTF-32 Big Endian . Type: `uint32_t` or `char32_t`.
#define ZLUTF_32LE	7	//!< UTF-32 Little Endian . Type: `uint32_t` or `char32_t`.

#define ZLUTF_MIN	ZLUTF_UNKNOWN	//!< Min @ref ZLUTF_UNKNOWN "ZLSUTF"`.
#define ZLUTF_MAX	ZLUTF_32LE	//!< Max @ref ZLUTF_UNKNOWN "ZLSUTF"`.
#define ZLUTF_FLUSH	-1	//!< Flush (刷新). 仅用于 @ref zlutfputius 等特殊场合.

#define ZLUTF_ANSI	ZLUTF_NARROW	//!< @copydoc ZLUTF_NARROW

/// @def ZLUTF_16
/// UTF-16 . Type: `uint16_t` or `char16_t`.

/// @def ZLUTF_32
/// UTF-32 . Type: `uint32_t` or `char32_t`.
#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
	#define ZLUTF_16	ZLUTF_16BE
	#define ZLUTF_32	ZLUTF_32BE
#elif __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define ZLUTF_16	ZLUTF_16LE
	#define ZLUTF_32	ZLUTF_32LE
#else	// 未知端序.
	#error Unknown endian!
#endif

/// @def ZLUTF_WIDE
/// Wide char (宽字符). Type: `wchar_t`.
#if ZLWCHAR_BITS==32
	#define ZLUTF_WIDE	ZLUTF_32
#elif ZLWCHAR_BITS==16
	#define ZLUTF_WIDE	ZLUTF_16
#else
	#define ZLUTF_WIDE	ZLUTF_NARROW
#endif

/// @def ZLUTF_TCHAR
/// TCHAR. Type: `TCHAR`.
#ifdef UNICODE
	#define ZLUTF_TCHAR	ZLUTF_WIDE
#else	// #ifdef UNICODE
	#define ZLUTF_TCHAR	ZLUTF_NARROW
#endif	// #ifdef UNICODE



////////////////////////////////////////
// zlutf32i: Unicode code integer (Unicode 代码的整数).
////////////////////////////////////////

/// Unicode code integer (Unicode 代码的整数). Like uint32_t .
///
/// Bits (位):
///
/// * D0~30: Unicode code (Unicode 代码). See @ref ZLUTF32I_CODE_MASK.
/// * D31: Non-normalization flag (非规范标识). See @ref ZLUTF32I_NONORM_MASK.
///
/// Special value(特殊值):
///
/// * @ref ZLUTF32I_ERROR : Error code (无效编码).
/// * @ref ZLUTF32I_NOCHAR : No char (没有字符). 当超过字符串尾部时, 会返回此值.
/// * @ref ZLUTF32I_FLUSH : Flush (强制刷新). 仅对 @ref ZLUtfPutCharProc 有效 .
///
typedef uint32_t zlutf32i;

#define ZLUTF32I_ERROR	UINT32_C(0x80000000)	//!< Error code (无效编码).
#define ZLUTF32I_NOCHAR	UINT32_C(0xFFFFFFFF)	//!< No char (没有字符). 当数据不足以表示一个字符时, 会返回此值.
#define ZLUTF32I_FLUSH	ZLUTF32I_NOCHAR	//!< Flush (强制刷新). 仅对 @ref ZLUtfPutCharProc 有效 .

#define ZLUTF32I_CODE_POS	0	//!< code field's position (代码字段的位移量) . See @ref ZLUTF32I_CODE_MASK.
#define ZLUTF32I_NONORM_POS	31	//!< Non-normalization field's position (非规范字段的位移量) . See @ref ZLUTF32I_NONORM_MASK.

#define ZLUTF32I_CODE_LEN	31	//!< code field's bit length (代码字段的位长) . See @ref ZLUTF32I_CODE_MASK.
#define ZLUTF32I_NONORM_LEN	1	//!< Non-normalization field's bit length (非规范字段的位长) . See @ref ZLUTF32I_NONORM_MASK.

#define ZLUTF32I_CODE_MASK	UINT32_C(0x7FFFFFFF)	//!< code field's mask (代码字段的掩码) . See @ref ZLUTF32I_CODE_POS, @ref ZLUTF32I_CODE_LEN.
#define ZLUTF32I_NONORM_MASK	UINT32_C(0x80000000)	//!< Non-normalization field's mask (非规范字段的掩码) . See @ref ZLUTF32I_NONORM_POS, @ref ZLUTF32I_NONORM_LEN.

#define ZLUTF32I_GETCODE(x)	( ((zlutf32i)(x) & ZLUTF32I_CODE_MASK) >> ZLUTF32I_CODE_POS )	//!< Get code (取得代码) . See @ref ZLUTF32I_CODE_MASK.
#define ZLUTF32I_GETNONORM(x)	( ((zlutf32i)(x) & ZLUTF32I_NONORM_MASK) >> ZLUTF32I_NONORM_POS )	//!< Get non-normalization flag (取得非规范标识) . See @ref ZLUTF32I_NONORM_MASK.

/// Make unicode code integer (生成 Unicode代码整数).
///
/// @param[in] code	Unicode code (Unicode代码).
/// @param[in] nonorm	Is Non-normalization (是否非规范化).
/// @return	Return unicode code integer (返回 Unicode代码整数).
///
#define ZLUTF32I_MAKE(code, nonorm) ((zlutf32i)( \
	( (zlutf32i)(code) & ZLUTF32I_CODE_MASK) \
	| ( (zlutf32i)(0!=(nonorm)) << ZLUTF32I_NONORM_POS) \
	))



////////////////////////////////////////
// Get/Put char function (取得/输出字符的函数).
////////////////////////////////////////

/// @def ZLUTF_CUR_MAX
/// Maximum size of multibyte characters (多字节字符的最大长度).
#define ZLUTF_CUR_MAX	16
//#define ZLUTF_CUR_MAX	MB_CUR_MAX

/// UTF encoding state (UTF转码状态).
typedef struct ZLUtfEncodeState{
	int cntbuf;	//!< Buffer count (缓冲区大小).
	int iuser[3];	//!< User integer (自定义整数).
	uint8_t buf[ZLUTF_CUR_MAX];	//!< Buffer (缓冲区).
#if ZL_CRT_mbstate
	mbstate_t mbstate;	//!< mbstate_t.
#else
	char mbstate;	//!< mbstate_t.
#endif
} ZLUtfEncodeState;


/// Initialize ZLUtfEncodeState (初始化 ZLUtfEncodeState).
///
/// @param	pues	ZLUtfEncodeState.
static INLINE void ZLCALL ZLUtfEncodeState_init(ZLUtfEncodeState* pues) {
	if (NULL==pues) return;
	memset(pues, 0, sizeof(ZLUtfEncodeState));
}

/// Get char function (取得字符的函数).
///
/// @param[in,out] pues	UTF encoding state (UTF转码状态). 由各个函数自己维护.
/// @param[in] p	Pointer to a character in string (字符串中当前字符的地址). 若与 pend 同时为 NULL, 则进行强制刷新操作.
/// @param[in] pend	Pointer to string end (字符串尾端的地址). 若为 NULL, 则到达 '\0' 字符时终止. 若与 p 同时为 NULL, 则进行强制刷新操作.
/// @param[out] pch	Return Unicode code (返回Unicode代码). Return ZLUTF32I_NOCHAR if no char (没有字符时返回 ZLUTF32I_NOCHAR).
/// @return	A pointer to the next character in the string (返回字符串中下一个字符的地址). Return NULL if at the end of the string (当到达字符串尾部时返回 NULL). 如果该位置会产生多个字符，则位置不会改变, 即返回值与p相同.
///
/// Tip (提示):
///
/// * 当到达字符串尾部（指针判断）且存在缓存字符时, 会强制输出缓存字符（返回值为 p, pch为强制返回的字符）, 之后才返回 NULL.
/// * 因上一条的规则，当 p==pend 时，会执行强制刷新操作.
///
typedef const void* (ZLCALL *ZLUtfGetCharProc)(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch);

//typedef const void* (ZLCALL *ZLUtfGetPrevCharProc)(ZLUtfEncodeState* pues, const void* p, const void* pstart, zlutf32i* pch);

/// Put char function (输出字符的函数).
///
/// @param[in,out] pues	UTF encoding state (UTF转码状态). 由各个函数自己维护.
/// @param[out] p	Pointer to a character in string (字符串中当前字符的地址).
/// @param[in] pend	Pointer to string end (字符串尾端的地址). 不能为 NULL.
/// @param[in] ch	Char (字符). 可以加上 ZLUTF32I_FALLBACK_MASK 标识使其尽可能的进行编码回退. 若为 ZLUTF32I_FLUSH, 表示进行强制刷新操作.
/// @param[in, out] pputresult	Return put result (返回输出结果). 输入性标识有 ZLUTFPR_ALLOWFALLBACK . See @ref ZLUTFPR_ACCEPT "ZLUTFPR" .
/// @return	A pointer to the next character in the string (返回字符串中下一个字符的地址).
///
/// Tip (提示):
///
/// * 可通过 pputresult 的 ZLUTFPR_BUFFER 判断是否存在缓存数据, 若有便可根据需要使用 ZLUTF32I_FLUSH 进行强制刷新.
/// * 若在强制刷新时遇到目标缓冲区已满问题, 那么会缓存状态, 返回 ZLUTFPR_BUFFER|ZLUTFPR_ERRBUF. 等准备好新缓冲区后再尝试强制刷新.
/// * 当遇到非规范编码时，若支持该非规范编码，则输出并返回 ZLUTFPR_NONORM 标识 ，否则忽略非规范标识进行输出（无 ZLUTFPR_NONORM）. 均不会设置 ZLUTFPR_FALLBACK . 
///
typedef void* (ZLCALL *ZLUtfPutCharProc)(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult);

// == ZLUTFPR: Put result (输出结果).
#define ZLUTFPR_ACCEPT	1	//!< Accept this char (成功接受了该字符) .
#define ZLUTFPR_BUFFER	2	//!< Have buffer data (存在缓存数据, 事后别忘了执行强制刷新操作) .
#define ZLUTFPR_NONORM	4	//!< Have Non-normalization char (非规范字符，已转为等价形式进行输出) .
#define ZLUTFPR_FALLBACK	8	//!< Have fallback (发生回退，已转为 ZLUTF_DEFAULTCHAR (?, U+FFFD) 或等价的编码进行输出) .
#define ZLUTFPR_ERROUT	0x10	//!< Output buffer is full (输出缓冲区已满) . 因为 p 到达 pend.
#define ZLUTFPR_ERRCODE	0x20	//!< Characters that cannot be encoded (无法编码的字符) .
//#define ZLUTFPR_ERRMORE	0x40	//!< Buffer too more (缓冲太多). 因为 ZLUtfEncodeState 最多只能缓存一个字符. 请尝试 ZLUTF32I_FLUSH 进行强制刷新.

#define ZLUTFPR_ALLOWFALLBACK	0x4000	//!< [in] Allow fallback (允许回退) . 当发现无法编码时, 便自动回退为 ZLUTF_DEFAULTCHAR (?, U+FFFD) 或等价的编码.

#define ZLUTFPR_IN_MARKS	(ZLUTFPR_ALLOWFALLBACK)	//!< In masks (输入性掩码).
#define ZLUTFPR_ERROR_MARKS	(ZLUTFPR_ERROUT|ZLUTFPR_ERRCODE)	//!< Error masks (错误性掩码).



////////////////////////////////////////
// Char functions (字符级函数).
////////////////////////////////////////

// == Char utility (字符工具). ==

#define ZLUTF16_PAIR0	0xD800U	//!< UTF-16 lead surrogates first （UTF16首代理区第一个字符的编码）.
#define ZLUTF16_PAIR0LAST	0xDBFFU	//!< UTF-16 lead surrogates	last （UTF16首代理区最后一个字符的编码）.
#define ZLUTF16_PAIR1	0xDC00U	//!< UTF-16 trail surrogates first （UTF16尾代理区第一个字符的编码）.
#define ZLUTF16_PAIR1LAST	0xDFFFU	//!< UTF-16 trail surrogates last （UTF16尾代理区最后一个字符的编码）.
#define ZLUTF16_PAIRMASK	0x3FF	//!< UTF-16 surrogates mask （UTF16代理对掩码）.
#define ZLUTF16_PAIROFFSET	0x10000	//!< UTF-16 surrogates offset （UTF16代理对偏移）.
#define ZLUTF16_PAIRSHIFT	10	//!< UTF-16 surrogates bits shift （UTF16代理对位移）.

/// Decode UTF-16 surrogates (解码UTF-16的代理对). 不做检查，仅支持代理对字符.
///	@param[in]	w0	lead surrogates (首代理).
///	@param[in]	w1	trail surrogates (尾代理).
/// @return	Return Unicode code (返回Unicode代码).
#define ZLUTF16_PAIRDECODE(w0, w1)	( (zlutf32i)(UINT32_C(0x10000) \
	+ ( ((uint32_t)(w0) &  ZLUTF16_PAIRMASK)<<ZLUTF16_PAIRSHIFT ) \
	+ ( (uint32_t)(w1) ZLUTF16_PAIRMASK ) \
	))

/// Get UTF-16 lead surrogates (取得UTF-16首代理). 不做检查，仅支持代理对字符.
#define ZLUTF16_PAIRGET0(u)	((uint16_t)( ZLUTF16_PAIR0|(((((uint32_t)u&ZLUTF32I_CODE_MASK)-ZLUTF16_PAIROFFSET)>>ZLUTF16_PAIRSHIFT) & ZLUTF16_PAIRMASK) ))

/// Get UTF-16 trail surrogates (取得UTF-16尾代理). 不做检查，仅支持代理对字符.
#define ZLUTF16_PAIRGET1(u)	((uint16_t)( ZLUTF16_PAIR1|((((uint32_t)u&ZLUTF32I_CODE_MASK)-ZLUTF16_PAIROFFSET) & ZLUTF16_PAIRMASK) ))


/// UTF-8 leading byte (UTF-8 前导字节). 索引与 zlutf8checkbyte 的返回值匹配.
static const uint8_t zlutf8leadbyte[] = {0, 0, 0xC0U, 0xE0, 0xF0, 0xF8, 0xFC};

/// Data mask by UTF-8 leading byte (UTF-8 前导字节中的数据掩码). 索引与 zlutf8checkbyte 的返回值匹配.
static const uint8_t zlutf8leaddatamask[] = {0xFF, 0xFF, 0x1F, 0x0F, 0x07, 0x03, 0x01};

/// Check UTF-8 char length by leading byte (根据首字节检测 UTF-8 字符的字节长度 ).
///
/// @param[in]	by	Leading byte.
/// @param[out]	pflags	Return flags (返回标识). @ref ZLUTF32I_NONORM_MASK : 0xC0, 0xC1, 0xFE, 0xFF .
/// @return	Return length (0, 1~6). Return 0 if by is data byte. Return 1 if by is 0xFE, 0xFF.
static INLINE int zlutf8checkbyte(uint8_t by, zlutf32i* pflags) {
	int rt;
	zlutf32i flags=0;
	if (by<=0x7F) {
		rt = 1;
	}
	else if (by<=0xBFU) {
		rt = 0;
	}
	else if (by<=0xC1U) {
		rt = 2;
		flags = ZLUTF32I_NONORM_MASK;
	}
	else if (by<=0xDFU) {
		rt = 2;
	}
	else if (by<=0xEFU) {
		rt = 3;
	}
	else if (by<=0xF7U) {
		rt = 4;
	}
	else if (by<=0xFBU) {
		rt = 5;
	}
	else if (by<=0xFDU) {
		rt = 6;
	}
	else {
		rt = 1;
		flags = ZLUTF32I_NONORM_MASK;
	}
	if (NULL!=pflags) *pflags=flags;
	return rt;
}

/// Get UTF-8 code's byte length (计算 UTF-8 代码的字节长度 ).
///
/// @param[in]	code	Unicode code (Unicode 代码).
/// @return	Return length (1~6). 失败时返回0.
static INLINE int zlutf8codelen(zlutf32i code) {
	int rt=0;
	if (code<0x7F) rt=1;	// 7 bits
	else if (code<0x7FF) rt=2;	// 11 bits
	else if (code<UINT32_C(0xFFFF)) rt=3;	// 16bits
	else if (code<UINT32_C(0x1FFFFF)) rt=4;	// 21 bits
	else if (code<UINT32_C(0x3FFFFFF)) rt=5;	// 26 bits
	else if (code<UINT32_C(0x7FFFFFFF)) rt=6;	// 31 bits
	return rt;
}

/// Unicode char to wchar_t char (将 Unicode 字符转为 wchar_t 字符).
///
/// @param[out]	pw	wchar_t buffer (目标缓冲区). 至少有2个字符.
/// @param[in]	ch	Unicode char (Unicode 字符). 会忽略非规范标识.
/// @return	Return chars count (返回输出的字符数). 失败时返回 0.
static INLINE int ZLCALL zlutfu2w(wchar_t* pw, zlutf32i ch) {
	int rt = 0;
	zlutf32i u = ch&ZLUTF32I_CODE_MASK;
	do{
		if (NULL==pw) break;
#if ZLUTF_WIDE==ZLUTF_16
		if (u<=0xFFFFU) {
			*pw = (wchar_t)(wint_t)u;
			rt = 1;
		}
		else if(u<=UINT32_C(0x10FFFF)) {
			// surrogate pair.
			pw[0] = (wchar_t)(wint_t)ZLUTF16_PAIRGET0(u);
			pw[1] = (wchar_t)(wint_t)ZLUTF16_PAIRGET1(u);
			rt = 2;
		}
#else
		*pw = (wchar_t)(wint_t)u;
		rt = 1;
#endif
	}while(0);
	return rt;
}


// == Get char function implement (取得字符函数的实现). ==

/// Get char by narrow (从窄串流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_a(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const char* q = (const char*)p;
	wchar_t wc;
	size_t len;
	size_t n;
	int cbused = 0;	// 使用了多少字节.
	do {
		if (NULL==pues) break;
		// 判断尾部及强制刷新.
		if ((p==pend) || (pend!=NULL && p>=pend)) {
			if (pues->cntbuf > 0) {
				// 不完整字符, 返回编码错误.
				ch = ZLUTF32I_ERROR;
				pues->cntbuf = 0;
			}
			// 清空状态.
			memset(&pues->mbstate, 0, sizeof(pues->mbstate));
			rt = NULL;
			break;
		}
		// 尝试获取.
		wc = 0;
		len = (const char*)pend - q;
		if (pues->cntbuf > 0) {
			// 将数据复制到缓冲区再获取.
			n = ZLUTF_CUR_MAX - pues->cntbuf;	// 缓冲区剩余长度.
			if (n>len) n=len;
			memcpy(&pues->buf[pues->cntbuf], q, n);
			len = pues->cntbuf + n;
#if ZL_CRT_mbrtowc
			n = mbrtowc(&wc, (char*)pues->buf, len, &pues->mbstate);
#else
			n = mbtowc(&wc, (char*)pues->buf, len);
#endif
		}
		else {
			// 源地址获取.
#if ZL_CRT_mbrtowc
			n = mbrtowc(&wc, q, len, &pues->mbstate);
#else
			n = mbtowc(&wc, q, len);
#endif
		}
		if ((size_t)-1==n) {
			// if an encoding error occurs, in which case the next n or fewer bytes do not contribute to a complete and valid multibyte character (no value is stored); the value of the macro EILSEQ is stored in errno, and the conversion state is unspecified. 
			// 无效编码.
			ch = ZLUTF32I_ERROR;
			cbused = 1;
		}
		else if ((size_t)-2==n) {
			// if the next n bytes contribute to an incomplete (but potentially valid) multibyte character, and all n bytes have been processed (no value is stored).
			// 字符不完整, 尝试缓存.
			if (len<ZLUTF_CUR_MAX) {
				// 缓存.
				rt = q + (len - pues->cntbuf);
				if (pues->cntbuf <= 0) {
					// 因先前采用源地址获取, 所以这里需要复制.
					memcpy(&pues->buf[0], q, len);
				}
				pues->cntbuf = (int)len;
				break;
			}
			else {
				// 超过最大缓存能力, 无效编码.
				ch = ZLUTF32I_ERROR;
				cbused = 1;
			}
		}
		else if (0==n) {
			// if the next n or fewer bytes complete the multibyte character that corresponds to the null wide character (which is the value stored).
			// 空字符, 挪动1字节.
			ch = 0;
			cbused = 1;
		}
		else if (n<=len) {
			// if the next n or fewer bytes complete a valid multibyte character (which is the value stored); the value returned is the number of bytes that complete the multibyte character.
			// 有效字符, 输出.
			ch = (zlutf32i)(wint_t)wc;
			cbused = (int)n;
		}
		else {
			// others.
			// 无效编码.
			ch = ZLUTF32I_ERROR;
			cbused = 1;
		}
		// 挪动指针.
		if (pues->cntbuf > 0) {
			if (cbused < pues->cntbuf) {
				memmove(pues->buf, &pues->buf[cbused], pues->cntbuf - cbused);
				pues->cntbuf -= cbused;
			}
			else {
				rt = q + (cbused - pues->cntbuf);
				pues->cntbuf = 0;
			}
		}
		else {
			rt = q + cbused;
		}
		if (NULL==pend && 0==ch) {
			rt = NULL;
		}
	}while(0);
	if (NULL!=pch) *pch=ch;
	return rt;
}

/// Get char by UTF-8 (从 UTF-8 流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_u8(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const uint8_t* q = (const uint8_t*)p;
	uint32_t u=0;
	uint32_t flag=0;
	int cb=0;	// 已读取的字节数.
	int cbneed=1;	// 所需字节. 即前导字节所描述的字节数.
	int n;
	uint8_t by;	// 当前字节.
	uint8_t bymask;
	do {
		if (NULL==pues) break;
		// 初始验证.
		if (0==cb) {
			// 判断尾部及强制刷新.
			if ((p==pend) || (pend!=NULL && p>=pend)) {
				if (pues->cntbuf > 0) {
					ch = ZLUTF32I_ERROR;
					pues->cntbuf = 0;
				}
				rt = NULL;
				break;
			}
		}
		if (cb>=6) {
			// 超过编码长度.
			rt = NULL;
			break;
		}
		// 读取当前字节.
		if (cb<pues->cntbuf) {	// 从缓存读取.
			by = pues->buf[cb];
		}
		else {	// 从源区读取.
			if (pend!=NULL && (const void*)q>=pend) {
				// 数据不足, 缓存并返回.
				rt = q;
				cb = (int)(q - (const uint8_t*)p);
				memcpy(&pues->buf[pues->cntbuf], p, cb);
				pues->cntbuf += cb;
				break;
			}
			by = *q++;
		}
		++cb;
		// 处理字节.
		if (cb<=1) {	// Leading byte
			cbneed = zlutf8checkbyte(by, &flag);
			bymask = zlutf8leaddatamask[cbneed];
			if (cbneed<=0) {
				// [error] data byte
				rt = q;
				ch = ZLUTF32I_ERROR;
				if (pues->cntbuf > 0) {
					// 缓冲区已用掉1字节.
					--pues->cntbuf;
					memmove(pues->buf, &pues->buf[1], pues->cntbuf);
				}
				break;
			}
			else if (cbneed==1) {
				// single byte.
				rt = q;
				ch = flag| by;
				if (pues->cntbuf > 0) {
					--pues->cntbuf;
					memmove(pues->buf, &pues->buf[1], pues->cntbuf);
				}
				if (NULL==pend && 0==by) {
					rt = NULL;
				}
				break;
			}
			else {
				// multi byte
				u = (uint32_t)(by&bymask) << ((cbneed-1)*6);
			}
		}
		else {	// Data byte
			n = zlutf8checkbyte(by, NULL);
			if (0!=n) {
				// Not data byte!
				ch = ZLUTF32I_ERROR;
				// 指针回退.
				if (cb > pues->cntbuf) {
					// 数据长度大于缓冲区长度，故只需调整指针，缓冲区清零.
					rt = q-1;
					pues->cntbuf = 0;
				}
				else {
					rt = p;
					// 缓冲区已用掉 cb 字节.
					pues->cntbuf -= cb;
					memmove(pues->buf, &pues->buf[cb], pues->cntbuf);
				}
				break;
			}
			else {
				// append.
				u |= (uint32_t)(by&0x3F) << ((cbneed-cb)*6);
				if (cb==cbneed) {
					// 输出完整字符.
					rt = q;
					ch = flag| u;
					pues->cntbuf = 0;
					break;
				}
			}
		}
	}while(1);
	if (NULL!=pch) *pch=ch;
	return rt;
}

/// Get char by UTF-16BE (从 UTF-16BE 流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_u16be(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const uint8_t* q = (const uint8_t*)p;
	uint32_t u, u2;
	size_t cnt;
	int cbchar=2;	// 字符所需字节数. 简单字符只需2个字节, 代理对需4个字节.
	int cntbufreal=0;	// 缓冲区实际已有字节数.
	if (NULL!=pues) {
		cntbufreal = pues->cntbuf;
	}
	do {
		if (NULL==pues) break;
		// 判断尾部及强制刷新.
		if ((p==pend) || (pend!=NULL && p>=pend)) {
			if (pues->cntbuf > 0) {
				ch = ZLUTF32I_ERROR;
				pues->cntbuf = 0;
			}
			rt = NULL;
			break;
		}
		// 将数据加载到缓冲区.
		if (cntbufreal<cbchar) {
			if (NULL==pend) {
				// 无需验证指针越界, 直接加载.
				memcpy(&pues->buf[cntbufreal], &q[cntbufreal - pues->cntbuf], cbchar-cntbufreal);
				cntbufreal = cbchar;
			}
			else {
				// 验证指针越界.
				cnt = (const uint8_t*)pend - q;	// 能加载的最多字节数.
				if (cnt> (size_t)(cbchar - pues->cntbuf)) cnt=(size_t)(cbchar - pues->cntbuf);	// 总需加载的字节数.
				memcpy(&pues->buf[cntbufreal], &q[cntbufreal - pues->cntbuf], cnt-cntbufreal);
				cntbufreal = (int)cnt;
			}
		}
		// 判断.
		if (cntbufreal<2) {
			// 没有足够字节, 退出.
			ch = ZLUTF32I_NOCHAR;
			rt = q + (cntbufreal-pues->cntbuf);
			pues->cntbuf = cntbufreal;
			break;
		}
		u = zlbeload16(pues->buf);
		if (0xD800U<=u && u<=0xDBFFU) {	// lead surrogates.
			if (cntbufreal>=4) {
				// 判断代理对.
				u2 = zlbeload16(&pues->buf[2]);
				if (0xDC00U<=u2 && u2<=0xDFFFU) {	// trail surrogates
					// surrogate pair.
					ch = UINT32_C(0x10000) + ( ((u&0x3FFU)<<10) | (u2&0x3FFU) );
					rt = q + (cntbufreal-pues->cntbuf);
					pues->cntbuf = 0;
				}
				else {
					// surrogates not match! 输出首字符, 当前字符留给下次调用时再返回.
					ch = u;
					if (0==ch && NULL==pend) {
						// 终止.
						rt=NULL;
						pues->cntbuf = 0;
					}
					else {
						// 缓冲区前挪2字节.
						rt = q + (cntbufreal-pues->cntbuf);
						memmove(pues->buf, &pues->buf[2], cntbufreal-2);
						pues->cntbuf = cntbufreal-2;
					}
				}
				break;
			}
			else {
				// UTF16-BE 可提前判断不匹配的代理对.
				if (cntbufreal>=3) {
					u2 = pues->buf[2];	// 判断低代理对的首字节. 应在 DC~DF 范围内.
					if (0xDCU<=u2 && u2<=0xDF) {
						// 符合代理对规则, 不需特殊处理.
					}
					else {
						// surrogates not match! 输出首字符, 当前字符留给下次调用时再返回.
						ch = u;
						if (0==ch && NULL==pend) {
							// 终止.
							rt=NULL;
							pues->cntbuf = 0;
						}
						else {
							// 缓冲区前挪2字节.
							rt = q + (cntbufreal-pues->cntbuf);
							memmove(pues->buf, &pues->buf[2], cntbufreal-2);
							pues->cntbuf = cntbufreal-2;
						}
						break;
					}
				}
				// 尝试缓存更多的字节.
				if (cbchar<4) {
					cbchar = 4;
					continue;
				}
				// 无法缓存所需字节, 退出.
				ch = ZLUTF32I_NOCHAR;
				rt = q + (cntbufreal-pues->cntbuf);
				pues->cntbuf = cntbufreal;
				break;
			}
		}
		// 输出（非代理对的）简单字符.
		ch = u;
		if (0==ch && NULL==pend) {
			// 终止.
			rt=NULL;
			pues->cntbuf = 0;
		}
		else {
			// 缓冲区前挪2字节.
			rt = q + (cntbufreal-pues->cntbuf);
			memmove(pues->buf, &pues->buf[2], cntbufreal-2);
			pues->cntbuf = cntbufreal-2;
		}
		break;
	}while(1);
	if (NULL!=pch) *pch=ch;
	return rt;
}

/// Get char by UTF-16LE (从 UTF-16LE 流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_u16le(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const uint8_t* q = (const uint8_t*)p;
	uint32_t u, u2;
	size_t cnt;
	int cbchar=2;	// 字符所需字节数. 简单字符只需2个字节, 代理对需4个字节.
	int cntbufreal=0;	// 缓冲区实际已有字节数.
	if (NULL!=pues) {
		cntbufreal = pues->cntbuf;
	}
	do {
		if (NULL==pues) break;
		// 判断尾部及强制刷新.
		if ((p==pend) || (pend!=NULL && p>=pend)) {
			if (pues->cntbuf > 0) {
				ch = ZLUTF32I_ERROR;
				pues->cntbuf = 0;
			}
			rt = NULL;
			break;
		}
		// 将数据加载到缓冲区.
		if (cntbufreal<cbchar) {
			if (NULL==pend) {
				// 无需验证指针越界, 直接加载.
				memcpy(&pues->buf[cntbufreal], &q[cntbufreal - pues->cntbuf], cbchar-cntbufreal);
				cntbufreal = cbchar;
			}
			else {
				// 验证指针越界.
				cnt = (const uint8_t*)pend - q;	// 能加载的最多字节数.
				if (cnt> (size_t)(cbchar - pues->cntbuf)) cnt=(size_t)(cbchar - pues->cntbuf);	// 总需加载的字节数.
				memcpy(&pues->buf[cntbufreal], &q[cntbufreal - pues->cntbuf], cnt-cntbufreal);
				cntbufreal = (int)cnt;
			}
		}
		// 判断.
		if (cntbufreal<2) {
			// 没有足够字节, 退出.
			ch = ZLUTF32I_NOCHAR;
			rt = q + (cntbufreal-pues->cntbuf);
			pues->cntbuf = cntbufreal;
			break;
		}
		u = zlleload16(pues->buf);
		if (0xD800U<=u && u<=0xDBFFU) {	// lead surrogates.
			if (cntbufreal>=4) {
				// 判断代理对.
				u2 = zlleload16(&pues->buf[2]);
				if (0xDC00U<=u2 && u2<=0xDFFFU) {	// trail surrogates
					// surrogate pair.
					ch = UINT32_C(0x10000) + ( ((u&0x3FFU)<<10) | (u2&0x3FFU) );
					rt = q + (cntbufreal-pues->cntbuf);
					pues->cntbuf = 0;
				}
				else {
					// surrogates not match! 输出首字符, 当前字符留给下次调用时再返回.
					ch = u;
					if (0==ch && NULL==pend) {
						// 终止.
						rt=NULL;
						pues->cntbuf = 0;
					}
					else {
						// 缓冲区前挪2字节.
						rt = q + (cntbufreal-pues->cntbuf);
						memmove(pues->buf, &pues->buf[2], cntbufreal-2);
						pues->cntbuf = cntbufreal-2;
					}
				}
				break;
			}
			else {
				// 尝试缓存更多的字节.
				if (cbchar<4) {
					cbchar = 4;
					continue;
				}
				// 无法缓存所需字节, 退出.
				ch = ZLUTF32I_NOCHAR;
				rt = q + (cntbufreal-pues->cntbuf);
				pues->cntbuf = cntbufreal;
				break;
			}
		}
		// 输出（非代理对的）简单字符.
		ch = u;
		if (0==ch && NULL==pend) {
			// 终止.
			rt=NULL;
			pues->cntbuf = 0;
		}
		else {
			// 缓冲区前挪2字节.
			rt = q + (cntbufreal-pues->cntbuf);
			memmove(pues->buf, &pues->buf[2], cntbufreal-2);
			pues->cntbuf = cntbufreal-2;
		}
		break;
	}while(1);
	if (NULL!=pch) *pch=ch;
	return rt;
}

/// Get char by UTF-32BE (从 UTF-32BE 流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_u32be(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const uint8_t* q = (const uint8_t*)p;
	uint32_t u;
	int cnt;
	int i;
	do {
		if (NULL==pues) break;
		if (NULL==pend) { // 遇到 '\0' 时结束. 此模式不需要缓存.
			if (NULL==p) break;
			// 获取当前字符.
			u = zlbeload32(q);
			// 输出.
			rt = q + 4;
			ch = u;
			if (0==u) {
				// 终结符.
				rt = NULL;
			}
		}
		else { // 遇到 pend 时结束. 此模式支持缓存.
			// 判断是否到达尾部.
			if (p>=pend) {
				// 强制输出.
				cnt = pues->cntbuf;
				if (cnt>0) {
					ch = ZLUTF32I_ERROR;
					break;	// 先返回缓存数据, 下次再通知终止.
				}
				// 标记结束.
				rt = NULL;
				break;
			}
			// 判断是否足够读取.
			if (NULL==p) break;
			cnt = 4 - pues->cntbuf;
			if (cnt<0) {
				// 数据错误!
				break;
			}
			if ((const void*)(q+cnt) > pend) {
				// 不足够, 于是缓存.
				cnt = (int)((const uint8_t*)pend-q);
				for(i=0; i<cnt; ++i) {
					pues->buf[pues->cntbuf + i] = q[i];
				}
				pues->cntbuf += cnt;
				rt = pend;
				break;
			}
			// 大端获取.
			u = 0;
			if (pues->cntbuf<=0) {
				// 没有缓存, 可一次性读取.
				u = zlbeload32(q);
				rt = q+4;
			}
			else {
				// 将数据读到缓存并获取..
				for(i=0; i<cnt; ++i) {
					pues->buf[pues->cntbuf + i] = q[i];
				}
				u = zlbeload32(pues->buf);
				pues->cntbuf = 0;
				rt = q+cnt;
			}
			ch = u;
		}
	}while(0);
	if (NULL!=pch) *pch=ch;
	return rt;
}

/// Get char by UTF-32LE (从 UTF-32LE 流中取得字符).
static INLINE const void* ZLCALL ZLUtfGetChar_u32le(ZLUtfEncodeState* pues, const void* p, const void* pend, zlutf32i* pch) {
	const void* rt = NULL;
	zlutf32i ch = ZLUTF32I_NOCHAR;
	const uint8_t* q = (const uint8_t*)p;
	uint32_t u;
	int cnt;
	int i;
	do {
		if (NULL==pues) break;
		if (NULL==pend) { // 遇到 '\0' 时结束. 此模式不需要缓存.
			if (NULL==p) break;
			// 获取当前字符.
			u = zlleload32(q);
			// 输出.
			rt = q + 4;
			ch = u;
			if (0==u) {
				// 终结符.
				rt = NULL;
			}
		}
		else { // 遇到 pend 时结束. 此模式支持缓存.
			// 判断是否到达尾部.
			if (p>=pend) {
				// 强制输出.
				cnt = pues->cntbuf;
				if (cnt>0) {
					ch = ZLUTF32I_ERROR;
					break;	// 先返回缓存数据, 下次再通知终止.
				}
				// 标记结束.
				rt = NULL;
				break;
			}
			// 判断是否足够读取.
			if (NULL==p) break;
			cnt = 4 - pues->cntbuf;
			if (cnt<0) {
				// 数据错误!
				break;
			}
			if ((const void*)(q+cnt) > pend) {
				// 不足够, 于是缓存.
				cnt = (int)((const uint8_t*)pend-q);
				for(i=0; i<cnt; ++i) {
					pues->buf[pues->cntbuf + i] = q[i];
				}
				pues->cntbuf += cnt;
				rt = pend;
				break;
			}
			// 小端获取.
			u = 0;
			if (pues->cntbuf<=0) {
				// 没有缓存, 可一次性读取.
				u = zlleload32(q);
				rt = q+4;
			}
			else {
				// 将数据读到缓存并获取..
				for(i=0; i<cnt; ++i) {
					pues->buf[pues->cntbuf + i] = q[i];
				}
				u = zlleload32(pues->buf);
				pues->cntbuf = 0;
				rt = q+cnt;
			}
			ch = u;
		}
	}while(0);
	if (NULL!=pch) *pch=ch;
	return rt;
}

#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
	#define ZLUtfGetChar_u16	ZLUtfGetChar_u16be	//!< @copydoc ZLUtfGetChar_u16be
	#define ZLUtfGetChar_u32	ZLUtfGetChar_u32be	//!< @copydoc ZLUtfGetChar_u32be
#elif __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define ZLUtfGetChar_u16	ZLUtfGetChar_u16le	//!< @copydoc ZLUtfGetChar_u16le
	#define ZLUtfGetChar_u32	ZLUtfGetChar_u32le	//!< @copydoc ZLUtfGetChar_u32le
#else	// 未知端序.
	#error Unknown endian!
#endif

#if ZLWCHAR_BITS==32
	#define ZLUtfGetChar_w	ZLUtfGetChar_u32	//!< @copydoc ZLUtfGetChar_u32
#elif ZLWCHAR_BITS==16
	#define ZLUtfGetChar_w	ZLUtfGetChar_u16	//!< @copydoc ZLUtfGetChar_u16
#else
	#define ZLUtfGetChar_w	ZLUtfGetChar_a	//!< @copydoc ZLUtfGetChar_a
#endif

/// Array of get char function, index is @ref ZLUTF_UNKNOWN "ZLSUTF" (输出字符函数的数组, 索引是 @ref ZLUTF_UNKNOWN "ZLSUTF"`) .
static const ZLUtfGetCharProc zlutfgetprocs[] = {
	NULL,
	NULL,
	ZLUtfGetChar_a,
	ZLUtfGetChar_u8,
	ZLUtfGetChar_u16be,
	ZLUtfGetChar_u16le,
	ZLUtfGetChar_u32be,
	ZLUtfGetChar_u32le,
};


// == Put char function implement - fast (快速版输出字符函数的实现). ==
// 快速版不对输出缓存区进行长度检查（忽略 pend）及缓存，假定总是能输出所有内容.

/// @ref ZLUtfPutCharProc - fast - 输出缓存 (输出字符 - 快速版 - 输出缓存. 注意它不验证参数) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_putbuf(ZLUtfEncodeState* pues, void* p) {
	char* q = (char*)p;
	size_t len;
	if (pues->cntbuf <= 0) return p;
	// 判断能输出的字节数.
	len = pues->cntbuf;
	// 输出.
	if (len>0) {
		memcpy(q, pues->buf, len);
		q += len;
	}
	// 缓冲区前移.
	if ((int)len < pues->cntbuf) memmove(pues->buf, pues->buf + len, pues->cntbuf - (int)len);
	pues->cntbuf -= (int)len;
	return q;
}

/// @ref ZLUtfPutCharProc - fast - narrow (输出字符 - 快速版 - 窄字符串) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_a(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	char* q = (char*)p;
	wchar_t warr[2];
	int cch;
	size_t n;
	size_t len;
	int i;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		else if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			// 忽略非规范编码标识.
			ch &= ZLUTF32I_CODE_MASK;
		}
		// 编码.
		len = 0;	// 输出长度.
		cch = zlutfu2w(warr, ch);	// 源数据与长度.
		if (0==cch) {
			// 无法转为 wchar_t .
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				warr[0] = ZLUTF_DEFAULTCHAR;
				cch = 1;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		for(i=0; i<cch; ++i) {
#if ZL_CRT_SECURE
			wcrtomb_s(&n, q+len, ZLUTF_CUR_MAX-len, warr[i], &pues->mbstate);
#elif ZL_CRT_wcrtomb
			n = wcrtomb(q+len, warr[i], &pues->mbstate);
#else
			n = wctomb(q+len, warr[i]);
#endif
			if (0==n) {	// '\0'
				q[0] = 0;
				len = 1;
				break;
			}
			else if (n<ZLUTF_CUR_MAX) {
				len += n;
			}
			else {
				// 不支持的编码.
				len = 0;
				if (ch==ZLUTF_REPLACEMENT) {
					// 自动将 ZLUTF_REPLACEMENT 转为 ZLUTF_QUESTION, 不报错.
#if ZL_CRT_SECURE
					wcrtomb_s(&n, q, ZLUTF_CUR_MAX, (wchar_t)(wint_t)ZLUTF_QUESTION, &pues->mbstate);
#elif ZL_CRT_wcrtomb
					n = wcrtomb(q, (wchar_t)(wint_t)ZLUTF_QUESTION, &pues->mbstate);
#else
					n = wctomb(q, (wchar_t)(wint_t)ZLUTF_QUESTION);
#endif
				}
				else {
					// 若支持回退则回退.
					if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
						putresult |= ZLUTFPR_FALLBACK;
#if ZL_CRT_SECURE
						wcrtomb_s(&n, q, ZLUTF_CUR_MAX, (wchar_t)(wint_t)ZLUTF_DEFAULTCHAR, &pues->mbstate);
#elif ZL_CRT_wcrtomb
						n = wcrtomb(q, (wchar_t)(wint_t)ZLUTF_DEFAULTCHAR, &pues->mbstate);
#else
						n = wctomb(q, (wchar_t)(wint_t)ZLUTF_DEFAULTCHAR);
#endif
						if (n>ZLUTF_CUR_MAX) {
#if ZL_CRT_SECURE
							wcrtomb_s(&n, q, ZLUTF_CUR_MAX, (wchar_t)(wint_t)ZLUTF_QUESTION, &pues->mbstate);
#elif ZL_CRT_wcrtomb
							n = wcrtomb(q, (wchar_t)(wint_t)ZLUTF_QUESTION, &pues->mbstate);
#else
							n = wctomb(q, (wchar_t)(wint_t)ZLUTF_QUESTION);
#endif
						}
					}
				}
				if (0==n) {
					q[0] = 0;
					len = 1;
				}
				else if (n<ZLUTF_CUR_MAX) {
					len = n;
				}
				else {
					putresult |= ZLUTFPR_ERRCODE;
				}
				break;
			}
		}
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - fast - UTF-8 (输出字符 - 快速版 - UTF-8) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_u8(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	uint8_t* q = (uint8_t*)p;
	size_t len;
	int i;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		// 编码.
		len = 0;	// 输出长度.
		// 先尝试处理非规范字符.
		if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			ch &= ZLUTF32I_CODE_MASK;
			if (ch<=0x7F) {
				// C0..C1 的过长字符.
				len = 2;
				q[0] = 0xC0 | (ch>>6);
				q[1] = 0x80 | (ch&0x3F);
			}
			else if(0xFE<=ch && ch<=0xFF) {
				// FE..FF 字符.
				len = 1;
				q[0] = (uint8_t)ch;
			}
		}
		if (0==len) {
			// 编码UTF-8字符.
			len = zlutf8codelen(ch);
			if (len==1) {
				len = 1;
				q[0] = (uint8_t)ch;
			}
			else if(len>1) {
				for(i=(int)(len-1); i>=1; --i) {
					q[i] = 0x80 | (ch&0x3F);
					ch >>= 6;
				}
				q[0] = zlutf8leadbyte[len] | (ch&0x3F);
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
			}
		}
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - fast - UTF-16BE (输出字符 - 快速版 - UTF-16BE) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_u16be(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	uint8_t* q = (uint8_t*)p;
	uint8_t* pc;
	uint16_t arr[2];
	int cch;
	size_t len;
	int i;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		else if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			// 忽略非规范编码标识.
			ch &= ZLUTF32I_CODE_MASK;
		}
		if (ch>=UINT32_C(0x10FFFF)) {
			// 超过UTF-16的编码范围, 尝试回退.
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		// 编码.
		pc = q;	// 输出区域.
		if ( (q+4) > (const uint8_t*)pend ) pc = pues->buf;
		//len = 0;	// 输出长度.
		if (ch<=UINT32_C(0xFFFF)) {
			arr[0] = (uint16_t)ch;
			cch = 1;
		}
		else {
			// surrogate pair.
			arr[0] = ZLUTF16_PAIRGET0(ch);
			arr[1] = ZLUTF16_PAIRGET1(ch);
			cch = 2;
		}
		for(i=0; i<cch; ++i) {
			zlbesave16(pc+(i*2), arr[i]);
		}
		len = cch*2;
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - fast - UTF-16LE (输出字符 - 快速版 - UTF-16LE) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_u16le(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	uint8_t* q = (uint8_t*)p;
	uint8_t* pc;
	uint16_t arr[2];
	int cch;
	size_t len;
	int i;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		else if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			// 忽略非规范编码标识.
			ch &= ZLUTF32I_CODE_MASK;
		}
		if (ch>=UINT32_C(0x10FFFF)) {
			// 超过UTF-16的编码范围, 尝试回退.
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		// 编码.
		pc = q;	// 输出区域.
		if ( (q+4) > (const uint8_t*)pend ) pc = pues->buf;
		//len = 0;	// 输出长度.
		if (ch<=UINT32_C(0xFFFF)) {
			arr[0] = (uint16_t)ch;
			cch = 1;
		}
		else {
			// surrogate pair.
			arr[0] = ZLUTF16_PAIRGET0(ch);
			arr[1] = ZLUTF16_PAIRGET1(ch);
			cch = 2;
		}
		for(i=0; i<cch; ++i) {
			zllesave16(pc+(i*2), arr[i]);
		}
		len = cch*2;
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - fast - UTF-32BE (输出字符 - 快速版 - UTF-32BE) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_u32be(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	uint8_t* q = (uint8_t*)p;
	uint8_t* pc;
	size_t len;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		else if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			// 忽略非规范编码标识.
			ch &= ZLUTF32I_CODE_MASK;
		}
		// 编码.
		pc = q;	// 输出区域.
		if ( (q+4) > (const uint8_t*)pend ) pc = pues->buf;
		len = 4;	// 输出长度.
		zlbesave32(pc, ch);
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - fast - UTF-32LE (输出字符 - 快速版 - UTF-32LE) .
static INLINE void* ZLCALL ZLUtfPutChar_fast_u32le(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	uint8_t* q = (uint8_t*)p;
	uint8_t* pc;
	size_t len;
	do {
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		q = ZLUtfPutChar_fast_putbuf(pues, q);
		if (pues->cntbuf > 0) {
			// Only by debug.
			putresult |= ZLUTFPR_ERROUT;
			rt = q;
			break;
		}
		if (ch==ZLUTF32I_NOCHAR) break;
		// 判断编码.
		if (ch==ZLUTF32I_ERROR) {
			if (0!=(putresult&ZLUTFPR_ALLOWFALLBACK)) {
				putresult |= ZLUTFPR_FALLBACK;
				ch = ZLUTF_DEFAULTCHAR;
			}
			else {
				putresult |= ZLUTFPR_ERRCODE;
				rt = q;
				break;
			}
		}
		else if (0!=(ch&ZLUTF32I_NONORM_MASK)) {
			// 忽略非规范编码标识.
			ch &= ZLUTF32I_CODE_MASK;
		}
		// 编码.
		pc = q;	// 输出区域.
		if ( (q+4) > (const uint8_t*)pend ) pc = pues->buf;
		len = 4;	// 输出长度.
		zllesave32(pc, ch);
		// 输出.
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		//if (len<=0) break;	// 应该只判断上一条就行了, 若在此处跳出, 则表示上述逻辑有误.
		putresult |= ZLUTFPR_ACCEPT;
		rt = q + len;
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
	#define ZLUtfPutChar_fast_u16	ZLUtfPutChar_fast_u16be	//!< @copydoc ZLUtfPutChar_fast_u16be
	#define ZLUtfPutChar_fast_u32	ZLUtfPutChar_fast_u32be	//!< @copydoc ZLUtfPutChar_fast_u32be
#elif __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define ZLUtfPutChar_fast_u16	ZLUtfPutChar_fast_u16le	//!< @copydoc ZLUtfPutChar_fast_u16le
	#define ZLUtfPutChar_fast_u32	ZLUtfPutChar_fast_u32le	//!< @copydoc ZLUtfPutChar_fast_u32le
#else	// 未知端序.
	#error Unknown endian!
#endif

#if ZLWCHAR_BITS==32
	#define ZLUtfPutChar_fast_w	ZLUtfPutChar_fast_u32	//!< @copydoc ZLUtfPutChar_fast_u32
#elif ZLWCHAR_BITS==16
	#define ZLUtfPutChar_fast_w	ZLUtfPutChar_fast_u16	//!< @copydoc ZLUtfPutChar_fast_u16
#else
	#define ZLUtfPutChar_fast_w	ZLUtfPutChar_fast_a	//!< @copydoc ZLUtfPutChar_fast_a
#endif

/// Array of fast put char function, index is @ref ZLUTF_UNKNOWN "ZLSUTF" (快速版输出字符函数的数组, 索引是 @ref ZLUTF_UNKNOWN "ZLSUTF"`) .
static const ZLUtfPutCharProc zlutffastputprocs[] = {
	NULL,
	NULL,
	ZLUtfPutChar_fast_a,
	ZLUtfPutChar_fast_u8,
	ZLUtfPutChar_fast_u16be,
	ZLUtfPutChar_fast_u16le,
	ZLUtfPutChar_fast_u32be,
	ZLUtfPutChar_fast_u32le,
};


// == Put char function implement (输出字符函数的实现). ==

/// Call fast @ref ZLUtfPutCharProc (调用快速版, 实现输出缓存区检查及缓存).
static INLINE void* ZLCALL ZLUtfPutChar_callfast(ZLUtfPutCharProc proc, ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	void* rt = NULL;
	int putresult = ZLUTFPR_ERROUT;
	char* q = (char*)p;
	char* pc;
	char* pcend;
	size_t n;
	size_t len;
	do {
		if (NULL == proc) break;
		if (NULL == pues) break;
		if (NULL == p) break;
		if (NULL == pend) break;
		// start.
		putresult = 0;
		if (NULL!=pputresult) putresult = *pputresult & ZLUTFPR_IN_MARKS;
		// 输出旧数据.
		if (pues->cntbuf > 0) {
			// 判断能输出的字节数.
			len = pues->cntbuf;
			if (q >= (const char*)pend) {
				len = 0;
			}
			else {
				n = (const char*)pend - q;
				if (len>n) len=n;
			}
			// 输出.
			if (len>0) {
				memcpy(q, pues->buf, len);
				q += len;
			}
			// 缓冲区前移.
			if ((int)len < pues->cntbuf) memmove(pues->buf, pues->buf + len, pues->cntbuf - (int)len);
			pues->cntbuf -= (int)len;
			if (pues->cntbuf > 0) {
				putresult |= ZLUTFPR_ERROUT;
				rt = q;
				break;
			}
		}
		// call.
		pc = q;	// 输出区域.
		pcend = (char*)pend;
		if ( (pc+ZLUTF_CUR_MAX) > pcend ) {
			// 当发现末端空间可能不足时, 使用已清空的 pues->buf 作为临时缓冲区.
			pc = (char*)pues->buf;
			pcend = pc + ZLUTF_CUR_MAX;
		}
		pcend = (char*)proc(pues, pc, pcend, ch, pputresult);
		if (NULL==pcend) {
			rt = NULL;
			break;
		}
		rt = q;
		if (0!=(putresult&ZLUTFPR_ERRCODE)) break;
		// 将临时缓冲区中的数据进行输出.
		putresult |= ZLUTFPR_ACCEPT;
		if (q==pc) {
			// 是直接输出的, 无需处理.
			rt = pcend;
		}
		else {
			// 将数据从缓存复制到目标.
			len = pcend-pc;
			pues->cntbuf = (int)len;
			if (q >= (const char*)pend) {
				len = 0;
			}
			else {
				n = (const char*)pend - q;
				if (len>n) len=n;
			}
			// 输出.
			if (len>0) {
				memcpy(q, pues->buf, len);
				q += len;
			}
			// 缓冲区前移.
			if ((int)len < pues->cntbuf) memmove(pues->buf, pues->buf + len, pues->cntbuf - (int)len);
			pues->cntbuf -= (int)len;
			if (pues->cntbuf > 0) {
				putresult |= ZLUTFPR_ERROUT;
			}
			rt = q;
		}
	}while(0);
	if (pues->cntbuf > 0)  putresult |= ZLUTFPR_BUFFER;
	if (NULL!=pputresult) *pputresult=putresult;
	return rt;
}

/// @ref ZLUtfPutCharProc - narrow (输出字符 - 窄字符串) .
static INLINE void* ZLCALL ZLUtfPutChar_a(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_a, pues, p, pend, ch, pputresult);
}

/// @ref ZLUtfPutCharProc - UTF-8 (输出字符 - UTF-8) .
static INLINE void* ZLCALL ZLUtfPutChar_u8(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_u8, pues, p, pend, ch, pputresult);
}

/// @ref ZLUtfPutCharProc - UTF-16BE (输出字符 - UTF-16BE) .
static INLINE void* ZLCALL ZLUtfPutChar_u16be(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_u16be, pues, p, pend, ch, pputresult);
}

/// @ref ZLUtfPutCharProc - UTF-16LE (输出字符 - UTF-16LE) .
static INLINE void* ZLCALL ZLUtfPutChar_u16le(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_u16le, pues, p, pend, ch, pputresult);
}

/// @ref ZLUtfPutCharProc - UTF-32BE (输出字符 - UTF-32BE) .
static INLINE void* ZLCALL ZLUtfPutChar_u32be(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_u32be, pues, p, pend, ch, pputresult);
}

/// @ref ZLUtfPutCharProc - UTF-32LE (输出字符 - UTF-32LE) .
static INLINE void* ZLCALL ZLUtfPutChar_u32le(ZLUtfEncodeState* pues, void* p, const void* pend, zlutf32i ch, int* pputresult) {
	return ZLUtfPutChar_callfast(ZLUtfPutChar_fast_u32le, pues, p, pend, ch, pputresult);
}

#if __BYTE_ORDER__==__ORDER_BIG_ENDIAN__
	#define ZLUtfPutChar_u16	ZLUtfPutChar_u16be	//!< @copydoc ZLUtfPutChar_u16be
	#define ZLUtfPutChar_u32	ZLUtfPutChar_u32be	//!< @copydoc ZLUtfPutChar_u32be
#elif __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define ZLUtfPutChar_u16	ZLUtfPutChar_u16le	//!< @copydoc ZLUtfPutChar_u16le
	#define ZLUtfPutChar_u32	ZLUtfPutChar_u32le	//!< @copydoc ZLUtfPutChar_u32le
#else	// 未知端序.
	#error Unknown endian!
#endif

#if ZLWCHAR_BITS==32
	#define ZLUtfPutChar_w	ZLUtfPutChar_u32	//!< @copydoc ZLUtfPutChar_u32
#elif ZLWCHAR_BITS==16
	#define ZLUtfPutChar_w	ZLUtfPutChar_u16	//!< @copydoc ZLUtfPutChar_u16
#else
	#define ZLUtfPutChar_w	ZLUtfPutChar_a	//!< @copydoc ZLUtfPutChar_a
#endif

/// Array of put char function, index is @ref ZLUTF_UNKNOWN "ZLSUTF" (输出字符函数的数组, 索引是 @ref ZLUTF_UNKNOWN "ZLSUTF"`) .
static const ZLUtfPutCharProc zlutfputprocs[] = {
	NULL,
	NULL,
	ZLUtfPutChar_a,
	ZLUtfPutChar_u8,
	ZLUtfPutChar_u16be,
	ZLUtfPutChar_u16le,
	ZLUtfPutChar_u32be,
	ZLUtfPutChar_u32le,
};


// == UTF string convert (UTF字符串转换). ==

// 过于复杂，暂不实现.
// // ZLUTFSC: UTF string convert flags (UTF字符串转换的标识).
// #define ZLUTFSC_BREAKSRC	1	//!< Break by decode fail (当源数据解码出错时, 中断处理).
// #define ZLUTFSC_BREAKDST	2	//!< Break by encode fail (当目标数据编码出错时, 中断处理).
// #define ZLUTFSC_FLUSH	4	//!< Flush (强制刷新) . 当处理完源数据后, 执行一次强制刷新操作.
// 
// /// UTF string convert (UTF字符串转换).
// ///
// /// @param[in] flags	Flags (标识). @ref ZLUTFSC_DEFAULTSRC "ZLUTFSC"`.
// /// @param[in] procdst	Put char function (输出字符的函数).
// /// @param[in] procsrc	Get char function (取得字符的函数).
// /// @param[in,out] puesdst	Destination encoding state (目标转码状态). 当 puesdst,pdst 同时为NULL 时，用于检测源字符串中是否含有无法解码的字符, 此时返回1表示全部能解码, 返回0表示存在不能解码的字符.
// /// @param[in,out] puessrc	Source encoding state (源转码状态).
// /// @param[out] pdst	Points to the buffer to receive the translated string. (指向一个缓冲区，用于接收转换后的字符串). 若pdst为NULL、puesdst不为NULL 时，则返回目标缓冲区所需字节数.
// /// @param[in] cbdst	Destination buffer bytes (目标缓冲区字节数).
// /// @param[in] psrc	Points to the source string (指向源字符串的指针). 当具有ZLUTFSC_FLUSH标识时可为NULL.
// /// @param[in] cbsrc	Source string bytes(源字符串字节数).
// /// @param[in] pdef	Points to the default string (指向默认字符串的指针). 注意 ZLUTFSC_BREAKSRC、ZLUTFSC_BREAKDST 的优先级更高, 有时用不到默认字符串.
// /// @param[in] cbdef	Default string bytes (默认字符串字节数).
// /// @param[out] pdefused	Count pdef used (默认字符串的使用次数).
// /// @param[out] psrcread	number of bytes read by psrc (源缓冲区读取的字节数).
// /// @param[out] pcberr	Rrror char bytes  (源字符串中错误字符的长度). 仅在 ZLUTFSC_BREAKSRC、ZLUTFSC_BREAKDST 时有效. 当解码没问题时会返回0，这时有可能是编码的问题.
// /// @param[out] pcherr	Rrror char code (错误字符的编码). 仅在 ZLUTFSC_BREAKSRC、ZLUTFSC_BREAKDST 时有效. 若编解码都没问题会返回 ZLUTF32I_NOCHAR.
// /// @return	Result is the number of bytes written to the buffer pointed to by pdst (返回目标缓冲区输出的字节数). 若pdst为空，则返回目标缓冲区所需字节数. 若 puesdst,pdst 同时为NULL , 则返回1表示全部能解码, 0表示存在不能解码的字符.
// ///
// /// 注意:
// ///
// /// * 当遇到无法解码的字符时, 若具有 ZLUTFSC_BREAKSRC 标识，则中断处理，即 返回值为先前成功编码的字节数、psrcread为先前成功解码的字节数、pccherr
// ///
// static INLINE size_t ZLCALL zlutfconv(int flags, ZLUtfPutCharProc procdst, ZLUtfGetCharProc procsrc, ZLUtfEncodeState* puesdst, ZLUtfEncodeState* puessrc, void* pdst, size_t cbdst, const void* psrc, size_t cbsrc, const void* pdef, size_t cbdef, size_t* pdefused, size_t* psrcread, size_t* pcberr, zlutf32i* pcherr) {
// 	size_t rt = 0;
// 	return rt;
// }


// == zlfputs: Write a string to a file (向文件输出字符串). ==

#define ZLFPUTS_BUFSIZE	64
#define ZLFPUTS_BUFMAX	(ZLFPUTS_BUFSIZE-1)

/// Write a narrow string to a file (向文件输出窄字符串). 支持指定字符数，支持空字符.
///
/// @param[in,out]	file	File(文件) .
/// @param[in]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlfputsA(FILE* file, const char* str, size_t cch) {
	zlresult rt = ZL_E_INVALIDARG;
	char buf[ZLFPUTS_BUFSIZE];
	size_t cnt = 0;
	size_t len;
	size_t i;
	size_t n;
	size_t chlen;
#if ZL_CRT_mbstate
	mbstate_t mbstate;
#endif
	do{
		if (NULL==file) break;
		// main.
		rt = 0;
		if (NULL==str) break;
		if (0==cch) break;
		if ((size_t)-1==cch) {
			cnt = strlen(str);
			fputs(str, file);
		}
		else {
			for(i=0; i<cch; ++i) {
				if (0==str[i]) {
					// 输出之前的字符串.
					fputs((str+cnt), file);
					// 输出 '\0' .
					fputc(0, file);
					cnt = i+1;
				}
			}
			// 输出最后一段未结束的字符串.
			while (cnt<cch) {
				len = cch - cnt;
				if (len>ZLFPUTS_BUFMAX) {
					// 计算一次最多能输出的字符数.
					for(i=ZLFPUTS_BUFMAX-1; i>=0; ++i) {
						n = len - i;
#if ZL_CRT_mbstate
						memset(&mbstate, 0, sizeof(mbstate));
						chlen = mbrlen(str+cnt+i, n, &mbstate);
#else
						chlen = mblen(str+cnt+i, n);
#endif
						if (chlen>=0 && chlen<n && (i+chlen)<ZLFPUTS_BUFMAX) {
							len = i+chlen;
							break;
						}
					}
					if (len>ZLFPUTS_BUFMAX) {
						len = ZLFPUTS_BUFMAX;
					}
				}
				// output.
				memcpy(buf, str+cnt, len);
				buf[len] = 0;
				fputs(buf, file);
				cnt += len;
			}
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	return rt;
}

/// Write a wide string to a file (向文件输出宽字符串). 支持指定字符数，支持空字符.
///
/// @param[in,out]	file	File(文件) .
/// @param[in]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlfputsW(FILE* file, const wchar_t* str, size_t cch) {
	zlresult rt = ZL_E_INVALIDARG;
	wchar_t buf[ZLFPUTS_BUFSIZE];
	size_t cnt = 0;
	size_t len;
	size_t i;
	uint16_t wi0;
	uint16_t wi1;
	do{
		if (NULL==file) break;
		// main.
		rt = 0;
		if (NULL==str) break;
		if (0==cch) break;
		if ((size_t)-1==cch) {
			cnt = wcslen(str);
			fputws(str, file);
		}
		else {
			for(i=0; i<cch; ++i) {
				if (0==str[i]) {
					// 输出之前的字符串.
					fputws((str+cnt), file);
					// 输出 '\0' .
					fputwc(0, file);
					cnt = i+1;
				}
			}
			// 输出最后一段未结束的字符串.
			while (cnt<cch) {
				len = cch - cnt;
				if (len>ZLFPUTS_BUFMAX) {
					// 计算一次最多能输出的字符数.
					if (sizeof(wchar_t)==2) {
						// 避免UTF-16的代理对被截断.
						wi0 = (uint16_t)(wint_t)str[cnt+ZLFPUTS_BUFMAX-1];
						wi1 = (uint16_t)(wint_t)str[cnt+ZLFPUTS_BUFMAX];
						if (0xD800<=wi0 && wi0<0xDC00 && 0xDC00<=wi1 && wi1<0xE000) {
							len = ZLFPUTS_BUFMAX-1;
						}
						else {
							len = ZLFPUTS_BUFMAX;
						}
					}
					else {
						// 其他便直接截断.
						len = ZLFPUTS_BUFMAX;
					}
				}
				// output.
				memcpy(buf, str+cnt, len*sizeof(wchar_t));
				buf[len] = 0;
				fputws(buf, file);
				cnt += len;
			}
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	return rt;
}

/// Write a narrow string to a file, allow dirty (向文件输出窄字符串，允许弄脏源字符串). 支持指定字符数，支持空字符, 性能比 zlfputs 好.
///
/// @param[in,out]	file	File(文件) .
/// @param[in,out]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlfputsdA(FILE* file, char* str, size_t cch) {
	zlresult rt = ZL_E_INVALIDARG;
	char* p;
	size_t cnt = 0;
	do{
		if (NULL==file) break;
		// main.
		rt = 0;
		if (NULL==str) break;
		if (0==cch) break;
		if ((size_t)-1==cch) {
			cnt = strlen(str);
			fputs(str, file);
		}
		else {
			str[cch] = 0;
			p = str;
			do{
				fputs(p, file);
				cnt += strlen(p);
				p = str + cnt;
				// '\0' .
				if (cnt<cch) {
					fputc(0, file);
					++cnt;
				}
			}while(cnt<cch);
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	return rt;
}

/// Write a wide string to a file, allow dirty (向文件输出宽字符串，允许弄脏源字符串). 支持指定字符数，支持空字符, 性能比 zlfputs 好.
///
/// @param[in,out]	file	File(文件) .
/// @param[in,out]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlfputsdW(FILE* file, wchar_t* str, size_t cch) {
	zlresult rt = ZL_E_INVALIDARG;
	wchar_t* p;
	size_t cnt = 0;
	do{
		if (NULL==file) break;
		// main.
		rt = 0;
		if (NULL==str) break;
		if (0==cch) break;
		if ((size_t)-1==cch) {
			cnt = wcslen(str);
			fputws(str, file);
		}
		else {
			str[cch] = 0;
			p = str;
			do{
				fputws(p, file);
				cnt += wcslen(p);
				p = str + cnt;
				// '\0' .
				if (cnt<cch) {
					fputwc(0, file);
					++cnt;
				}
			}while(cnt<cch);
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	return rt;
}

#ifdef UNICODE
	#define zlfputs	zlfputsW
	#define zlfputsd	zlfputsdW
#else	// #ifdef UNICODEs
	#define zlfputs	zlfputsA
	#define zlfputsd	zlfputsdA
#endif	// #ifdef UNICODE

/// @def zlfputs
/// Write a string to a file (向文件输出字符串). 支持指定字符数，支持空字符.
///
/// Prototype: `zlresult ZLCALL zlfputs(FILE* file, const TCHAR* str, size_t cch);`
///
/// @param[in,out]	file	File(文件) .
/// @param[in]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///

/// @def zlfputsd
/// Write a string to a file, allow dirty (向文件输出字符串，允许弄脏源字符串). 支持指定字符数，支持空字符, 性能比 zlfputs 好.
///
/// Prototype: `zlresult ZLCALL zlfputsd(FILE* file, TCHAR* str, size_t cch);`
///
/// @param[in,out]	file	File(文件) .
/// @param[in,out]	str	Output string (输出字符串).
/// @param[in]	cch	Count of characters (字符数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///


// == UTF fput (向文件输出UTF字符串). ==

/// Write a narrow string's function (输出窄字符串的函数).
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in,out]	str	Output string (输出字符串). 允许弄脏.
/// @param[in]	cch	Count of characters (字符数).
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
typedef zlresult (ZLCALL *ZLUtfPutsProcA)(void* poutobj, char* str, size_t cch);

/// Write a wide string's function (输出宽字符串的函数).
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in,out]	str	Output string (输出字符串). 允许弄脏.
/// @param[in]	cch	Count of characters (字符数).
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
typedef zlresult (ZLCALL *ZLUtfPutsProcW)(void* poutobj, wchar_t* str, size_t cch);

/// zlutfputus: @ref ZLUtfPutsProcA .
static INLINE zlresult ZLCALL zlutfputus_putsA(void* poutobj, char* str, size_t cch) {
	return zlfputsdA((FILE*)poutobj, str, cch);
}

/// zlutfputus: @ref ZLUtfPutsProcW .
static INLINE zlresult ZLCALL zlutfputus_putsW(void* poutobj, wchar_t* str, size_t cch) {
	return zlfputsdW((FILE*)poutobj, str, cch);
}

/// Put utf string ex - narrow (输出UTF字符串加强版窄版).
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in] outproc	Output function (输出函数). 若输出函数返回负数的错误码，则提前终止输出.
/// @param[in,out] puesdst	Destination encoding state (目标转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputusexA(void* poutobj, ZLUtfPutsProcA outproc, ZLUtfEncodeState* puesdst, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc) {
	ZLUtfPutCharProc procdst = ZLUtfPutChar_fast_a;
	zlresult rt = ZL_E_INVALIDARG;
	char chbuf[ZLUTF_CUR_MAX];
	size_t cch;
	size_t cnt = 0;	// 所使用的源字节数.
	int noflush = 0;	// 不进行刷新.
	ZLUtfEncodeState uesdst;
	ZLUtfEncodeState uessrc;
	ZLUtfEncodeState* puesd = puesdst;
	ZLUtfEncodeState* puess = puessrc;
	int putresult = ZLUTFPR_ALLOWFALLBACK;
	const void* p = psrc;
	const void* pend = (const char*)psrc+cbsrc;
	void* pd;
	void* pdend = chbuf + sizeof(chbuf);
	zlutf32i ch;
	do {
		// check.
		if (NULL==poutobj) break;
		if (NULL==outproc) break;
		if (NULL==puesd) {
			puesd = &uesdst;
			ZLUtfEncodeState_init(puesd);
		}
		if (NULL==puess) {
			puess = &uessrc;
			ZLUtfEncodeState_init(puess);
		}
		if (NULL!=procsrc) {
			if (NULL==psrc) break;
		}
		if ((size_t)-1==cbsrc) {
			pend = NULL;
		}
		// main.
		rt = 0;
		if (NULL!=procsrc) {
			do{
				// Get.
				p = procsrc(puess, p, pend, &ch);
				// Put.
				if (ch==ZLUTF32I_NOCHAR) continue;	// 继续取字符, 而不是执行强制刷新操作.
				if (ch==0 && (size_t)-1==cbsrc) break;	// '\0' .
				pd = procdst(puesd, chbuf, pdend, ch, &putresult);
				if (NULL==pd) break;
				cch = (char*)pd-chbuf;
				if (outproc(poutobj, chbuf, cch)<0) {
					noflush = 1;
					break;
				}
				if (NULL!=p) cnt = (const char*)p-(const char*)psrc;
			}while(NULL!=p);
			if (!noflush && (size_t)-1!=cbsrc) cnt=cbsrc;	// 不是提前退出, 且不是空字符判断长度时，使用源长度.
		}
		// flush src.
		if (!noflush && (NULL==procsrc || NULL==puessrc)) {
			// Get.
			procsrc(puess, NULL, NULL, &ch);
			if (ch!=ZLUTF32I_NOCHAR) {
				// Put.
				pd = procdst(puesd, chbuf, pdend, ch, &putresult);
				if (NULL!=pd) {
					cch = (char*)pd-chbuf;
					if (outproc(poutobj, chbuf, cch)<0) {
						noflush = 1;
						break;
					}
				}
			}
		}
		// flush dst.
		if (!noflush && (NULL==procsrc || NULL==puesdst)) {
			// Put.
			pd = procdst(puesd, chbuf, pdend, ZLUTF32I_FLUSH, &putresult);
			if (NULL!=pd) {
				cch = (char*)pd-chbuf;
				if (outproc(poutobj, chbuf, cch)<0) {
					noflush = 1;
					break;
				}
			}
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	//_tprintf(_T("%d\n"), rt);	// [Debug]
	return rt;
}

/// Put utf string ex - wide (输出UTF字符串加强版宽版).
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in] outproc	Output function (输出函数). 若输出函数返回负数的错误码，则提前终止输出.
/// @param[in,out] puesdst	Destination encoding state (目标转码状态). 可为NULL表示使用临时的状态缓冲区，并最后自动执行刷新操作.
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL表示使用临时的状态缓冲区，并最后自动执行刷新操作.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputusexW(void* poutobj, ZLUtfPutsProcW outproc, ZLUtfEncodeState* puesdst, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc) {
	ZLUtfPutCharProc procdst = ZLUtfPutChar_fast_w;
	zlresult rt = ZL_E_INVALIDARG;
	wchar_t chbuf[ZLUTF_CUR_MAX];
	size_t cch;
	size_t cnt = 0;	// 所使用的源字节数.
	int noflush = 0;	// 不进行刷新.
	ZLUtfEncodeState uesdst;
	ZLUtfEncodeState uessrc;
	ZLUtfEncodeState* puesd = puesdst;
	ZLUtfEncodeState* puess = puessrc;
	int putresult = ZLUTFPR_ALLOWFALLBACK;
	const void* p = psrc;
	const void* pend = (const char*)psrc+cbsrc;
	void* pd;
	void* pdend = chbuf + sizeof(chbuf);
	zlutf32i ch;
	do {
		// check.
		if (NULL==poutobj) break;
		if (NULL==outproc) break;
		if (NULL==puesd) {
			puesd = &uesdst;
			ZLUtfEncodeState_init(puesd);
		}
		if (NULL==puess) {
			puess = &uessrc;
			ZLUtfEncodeState_init(puess);
		}
		if (NULL!=procsrc) {
			if (NULL==psrc) break;
		}
		if ((size_t)-1==cbsrc) {
			pend = NULL;
		}
		// main.
		rt = 0;
		if (NULL!=procsrc) {
			do{
				// Get.
				p = procsrc(puess, p, pend, &ch);
				// Put.
				if (ch==ZLUTF32I_NOCHAR) continue;	// 继续取字符, 而不是执行强制刷新操作.
				if (ch==0 && (size_t)-1==cbsrc) break;	// '\0' .
				pd = procdst(puesd, chbuf, pdend, ch, &putresult);
				if (NULL==pd) break;
				cch = (wchar_t*)pd-chbuf;
				if (outproc(poutobj, chbuf, cch)<0) {
					noflush = 1;
					break;
				}
				if (NULL!=p) cnt = (const char*)p-(const char*)psrc;
			}while(NULL!=p);
			if (!noflush && (size_t)-1!=cbsrc) cnt=cbsrc;	// 不是提前退出, 且不是空字符判断长度时，使用源长度.
		}
		// flush src.
		if (!noflush && (NULL==procsrc || NULL==puessrc)) {
			// Get.
			procsrc(puess, NULL, NULL, &ch);
			if (ch!=ZLUTF32I_NOCHAR) {
				// Put.
				pd = procdst(puesd, chbuf, pdend, ch, &putresult);
				if (NULL!=pd) {
					cch = (wchar_t*)pd-chbuf;
					if (outproc(poutobj, chbuf, cch)<0) {
						noflush = 1;
						break;
					}
				}
			}
		}
		// flush dst.
		if (!noflush && (NULL==procsrc || NULL==puesdst)) {
			// Put.
			pd = procdst(puesd, chbuf, pdend, ZLUTF32I_FLUSH, &putresult);
			if (NULL!=pd) {
				cch = (wchar_t*)pd-chbuf;
				if (outproc(poutobj, chbuf, cch)<0) {
					noflush = 1;
					break;
				}
			}
		}
		if (cnt<INT32_MAX) rt = (zlresult)cnt;
	}while(0);
	//_tprintf(_T("%d\n"), rt);	// [Debug]
	return rt;
}

/// Put utf string to file - narrow (向文件输出UTF字符串窄版).
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputusA(FILE* file, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc) {
	// 因为解码时总能解出一个完整的字符，且向文件输出宽窄字符串时不会造成半个字符问题，故不需要 puesdst.
	return zlutfputusexA(file, zlutfputus_putsA, NULL, puessrc, procsrc, psrc, cbsrc);
}

/// Put utf string to file - wide (向文件输出UTF字符串宽版).
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL表示使用临时的状态缓冲区，并最后自动执行刷新操作.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputusW(FILE* file, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc) {
	return zlutfputusexW(file, zlutfputus_putsW, NULL, puessrc, procsrc, psrc, cbsrc);
}

/// Put utf string to file by @ref ZLUTF_UNKNOWN "ZLSUTF" - narrow (根据 @ref ZLUTF_UNKNOWN "ZLSUTF" 常数向文件输出UTF字符串窄版).
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in] utfmode	Source string's Utf mode (源字符串的UTF模式). @ref ZLUTF_UNKNOWN "ZLSUTF"`. 为 @ref ZLUTF_FLUSH (-1) 时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputiusA(FILE* file, ZLUtfEncodeState* puessrc, int utfmode, const void* psrc, size_t cbsrc) {
	ZLUtfGetCharProc procsrc = NULL;
	if (ZLUTF_FLUSH!=utfmode) {
		if (utfmode<ZLUTF_MIN || utfmode>ZLUTF_MAX) return ZL_E_INVALIDARG;
		if (ZLUTF_UNKNOWN==utfmode) utfmode=ZLUTF_NARROW;
		if (utfmode==ZLUTF_NARROW) {
			return zlfputsA(file, psrc, cbsrc);
		}
		procsrc = zlutfgetprocs[utfmode];
		if (NULL==procsrc) return ZL_E_INVALIDARG;
	}
	return zlutfputusA(file, puessrc, procsrc, psrc, cbsrc);
}

/// Put utf string to file by @ref ZLUTF_UNKNOWN "ZLSUTF" - wide (根据 @ref ZLUTF_UNKNOWN "ZLSUTF" 常数向文件输出UTF字符串宽版).
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL表示使用临时的状态缓冲区，并最后自动执行刷新操作.
/// @param[in] utfmode	Source string's Utf mode (源字符串的UTF模式). @ref ZLUTF_UNKNOWN "ZLSUTF"`. 为 @ref ZLUTF_FLUSH (-1) 时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///
static INLINE zlresult ZLCALL zlutfputiusW(FILE* file, ZLUtfEncodeState* puessrc, int utfmode, const void* psrc, size_t cbsrc) {
	ZLUtfGetCharProc procsrc = NULL;
	if (ZLUTF_FLUSH!=utfmode) {
		if (utfmode<ZLUTF_MIN || utfmode>ZLUTF_MAX) return ZL_E_INVALIDARG;
		if (ZLUTF_UNKNOWN==utfmode) utfmode=ZLUTF_WIDE;
		//if (utfmode==ZLUTF_WIDE) {	// 实测发现 fputws 在遇到无法编码的字符时会截断整个字符串，导致排版错误，故还是编解码一遍吧.
		//	return zlfputsW(file, psrc, cbsrc/sizeof(wchar_t));
		//}
		procsrc = zlutfgetprocs[utfmode];
		if (NULL==procsrc) return ZL_E_INVALIDARG;
	}
	return zlutfputusW(file, puessrc, procsrc, psrc, cbsrc);
}

#ifdef UNICODE
	#define ZLUtfPutsProc	ZLUtfPutsProcW
	#define zlutfputusex	zlutfputusexW
	#define zlutfputus	zlutfputusW
	#define zlutfputius	zlutfputiusW
#else	// #ifdef UNICODEs
	#define ZLUtfPutsProc	ZLUtfPutsProcA
	#define zlutfputusex	zlutfputusexA
	#define zlutfputus	zlutfputusA
	#define zlutfputius	zlutfputiusA
#endif	// #ifdef UNICODE

/// @def ZLUtfPutsProc
/// Write a string's function (输出字符串的函数).
///
/// Prototype: `typedef zlresult (ZLCALL ZLUtfPutsProc)(void* poutobj, TCHAR* str, size_t cch);`
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in,out]	str	Output string (输出字符串). 允许弄脏.
/// @param[in]	cch	Count of characters (字符数).
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字符数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///

/// @def zlutfputusex
/// Put utf string ex (输出UTF字符串加强版).
///
/// Prototype: `zlresult ZLCALL zlutfputusex(void* poutobj, ZLUtfPutsProc outproc, ZLUtfEncodeState* puesdst, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc);`
///
/// @param[in,out]	poutobj	Output object pointer(输出对象的指针) .
/// @param[in] outproc	Output function (输出函数). 若输出函数返回负数的错误码，则提前终止输出.
/// @param[in,out] puesdst	Destination encoding state (目标转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///

/// @def zlutfputus
/// Put utf string to file (向文件输出UTF字符串).
///
/// Prototype: `zlresult ZLCALL zlutfputus(FILE* file, ZLUtfEncodeState* puessrc, ZLUtfGetCharProc procsrc, const void* psrc, size_t cbsrc);`
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puesdst	Destination encoding state (目标转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL使用临时的状态缓冲区.
/// @param[in] procsrc	Get char function (取得字符的函数). 为NULL时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///

/// @def zlutfputius
/// Put utf string to file by @ref ZLUTF_UNKNOWN "ZLSUTF" (根据 @ref ZLUTF_UNKNOWN "ZLSUTF" 常数向文件输出UTF字符串).
///
/// Prototype: `zlresult ZLCALL zlutfputius(FILE* file, ZLUtfEncodeState* puessrc, int utfmode, const void* psrc, size_t cbsrc);`
///
/// @param[in,out] file	File pointer (文件指针).
/// @param[in,out] puessrc	Source encoding state (源转码状态). 可为NULL表示使用临时的状态缓冲区，并最后自动执行刷新操作.
/// @param[in] utfmode	Source string's Utf mode (源字符串的UTF模式). @ref ZLUTF_UNKNOWN "ZLSUTF"`. 为 @ref ZLUTF_FLUSH (-1) 时表示执行刷新操作, 会忽略 psrc/cbsrc .
/// @param[in] psrc	Points to the source string (指向源字符串的指针).
/// @param[in] cbsrc	Source string bytes(源字符串字节数). 为 -1 时自动根据空字符判断长度.
/// @return	Returns a nonnegative value if it is successful (成功时返回非负数. 一般为所使用的源字节数, 0表示未知数量). A return value of negative indicates an error (出错时返回负数的错误码).
///


#if defined __cplusplus
};
#endif

#endif // #ifndef __ZLUTF_H_INCLUDED

/// @}
/// @}
