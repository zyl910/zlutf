/// @addtogroup GROUP_ZYLLIBC	zyllibc
/// @{
///

/// @addtogroup GROUP_ZLUTF	zlutf
/// @{
///

/// @addtogroup GROUP_ZLUTF_EXAMPLE	example
/// @{
///


/// @addtogroup GROUP_ZLUTF_EXAMPLE_TEST	zlstream_test
/// Test @ref GROUP_ZLUTF for C (测试C下使用 @ref GROUP_ZLUTF).
///
/// @author	[zyl910](mailto:zyl910hero@gmail.com)
/// @since	@ref GROUP_ZLUTF 1.0
/// @version	1.0
/// @date	2013-08-01
///
/// Links:
///
/// * Git: https://github.com/zyl910/zlutf
/// * Blog: http://www.cnblogs.com/zyl910/tag/zlutf/
///
///
///
/// ## Tested compiler (测试过的编译器)
/// 
/// * Virtual C++: 6, 7.1(2003), 8(2005), 9(2008), 10(2010), 11(2012), 12(2013).
/// * Borland C++: 6.
/// * GCC: 4.6.2~4.7.1(MinGW, MinGW-w64, TDM-GCC), 4.7.0~4.8.1(Fedora 17~19), 4.2~4.2.1(Mac OS X 10.7~10.8).
///
///
/// ## Change history (变更日志)
///
/// [2014-08-01] V1.0
///
/// * Release v1.0 (发布1.0版).
///
/// @{
///

///
/// @file	zlutf_test.c
/// @brief	Test @ref GROUP_ZLUTF for C (测试C下使用 @ref GROUP_ZLUTF).
/// @since	@ref GROUP_ZLUTF 1.0
///

#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS
#define __STDC_CONSTANT_MACROS

#include <locale.h>

#include "auto_inttypes.h"

#include "zlutf.h"

#include "prichar.h"
#include "auto_tmain.h"

/// Print Bytes (打印字节).
static void fprintbytes(FILE* f, const void* psrc, size_t cbsrc, TCHAR* pjoin) {
	const uint8_t* p = (const uint8_t*)psrc;
	uint8_t by;
	size_t i;
	if (NULL==f) return;
	if (NULL==psrc) return;
	if (cbsrc<=0) return;
	for(i=0; i<cbsrc; ++i) {
		if (NULL!=pjoin && i>0) {
			_fputts(pjoin, f);
		}
		by = p[i];
		_ftprintf(f, _T("%.2X"), by);
	}
}

/// Test (测试).
static void dotest(void) {
	//// test zlutf32i
	//zlutf32i u = ZLUTF32I_MAKE('U', 1, 0, 1);
	//_tprintf(_T("code:\tU+%X\n"), ZLUTF32I_GETCODE(u) );
	//_tprintf(_T("error:\t%X\n"), ZLUTF32I_GETERROR(u) );
	//_tprintf(_T("nonorm:\t%X\n"), ZLUTF32I_GETNONORM(u) );
	//_tprintf(_T("fallback:\t%X\n"), ZLUTF32I_GETFALLBACK(u) );

	// 缓存测试时所用的位置.
	size_t postable[] = {2, 3, 2, 4, 9, 3};
	size_t n;
	zlresult rt;
	int idx;

	// test mbrtowc.
	wchar_t wc;
	const char* q;
	size_t len;

	uint8_t bufsrc[] = {0xEF,0xBB,0xBF, 0x55, 0xCE,0x94, 0xE4,0xB8,0x80, 0xF0,0xA0,0x80,0x80, 0xFE,0xFF, 0xC0,0x81, 0x80, 0xE4,0xB8, 0x00, 0xFC,0xA0,0x80,0x80,0x80,0x80, 0xFC};	// utf8. U+FEFF, U+0055, U+0394, U+4E00, U+20000, 编码外的FE/FF, 过长编码C081(U+0001), 孤立后续字节80, 缺少后续字节E4B8, \0, 六字节, 六字节头字节.
	//uint8_t bufsrc[] = {0x40,0xD8,0x12,0xDC, 0x56,0xD8,0x00,0x00, 0x00,0x00,0x00,0x00, 0x01,0xD8,0x03};	// utf16le
	//uint8_t bufsrc[] = {0xD8,0x40,0xDC,0x12, 0x00,0x00,0xD8,0x56, 0x00,0x00,0x00,0x00, 0xD8,0x01,0x03};	// utf16be
	ZLUtfEncodeState ues;
	zlutf32i ch;
	//ZLUtfGetCharProc proc=ZLUtfGetChar_a;
	ZLUtfGetCharProc proc=ZLUtfGetChar_u8;
	//ZLUtfGetCharProc proc=ZLUtfGetChar_u16be;
	//ZLUtfGetCharProc proc=ZLUtfGetChar_u16le;
	//ZLUtfGetCharProc proc=ZLUtfGetChar_u32be;
	//ZLUtfGetCharProc proc=ZLUtfGetChar_u32le;
	const void* pendmax=&bufsrc[sizeof(bufsrc)];
	const void* p=&bufsrc[0];
	const void* pend=pendmax;
	//const void* pend=NULL;

	// destination buffer.
	uint8_t	dst[0x1000];
	const void* pdstend=dst+sizeof(dst);
	void* pd;
	void* pd2;
	ZLUtfEncodeState uesd;
	//ZLUtfPutCharProc procd=ZLUtfPutChar_a;
	ZLUtfPutCharProc procd=ZLUtfPutChar_u8;
	//ZLUtfPutCharProc procd=ZLUtfPutChar_u16be;
	//ZLUtfPutCharProc procd=ZLUtfPutChar_u16le;
	//ZLUtfPutCharProc procd=ZLUtfPutChar_u32be;
	//ZLUtfPutCharProc procd=ZLUtfPutChar_u32le;
	int putresult;

	// file.
	FILE* hf = stdout;

	_tprintf(_T("U+4E00:\t%")_T(PRIcW)_T("\n"), (wint_t)0x4E00);
	_tprintf(_T("begin\t\t\t%pH\n"), p);
	_tprintf(_T("end\t\t\t%pH\n"), pendmax);
	fprintbytes(stdout, bufsrc, sizeof(bufsrc), _T(" "));
	_tprintf(_T("\n"));

	// 非缓存读取.
	if (1) {
		_tprintf(_T("[ZLUtfGetCharProc]\n"));
		ZLUtfEncodeState_init(&ues);
		do{
			p = proc(&ues, p, pend, &ch);
			_tprintf(_T("0x%.8X\t%u\t%pH\n"), ch, ch, p);
		}while(NULL!=p);
	}

	// 缓存读取.
	if (0) {
		_tprintf(_T("[ZLUtfGetCharProc:b]\n"));
		idx = 0;
		p = &bufsrc[0];
		pend = p;
		ZLUtfEncodeState_init(&ues);
		do{
			// 当前段的位置、长度.
			p = pend;
			if (idx<(sizeof(postable)/sizeof(postable[0]))) {
				n = postable[idx++];
				pend = (const uint8_t*)pend + n;
				if (pend>=pendmax) pend=pendmax;
			}
			else {
				if (pend>=pendmax) break;
				pend = pendmax;
			}
			// 枚举当前段.
			do{
				p = proc(&ues, p, pend, &ch);
				_tprintf(_T("0x%.8X\t%u\t%pH\n"), ch, ch, p);
			}while(NULL!=p && p<pend);
		}while(NULL!=p);
		// flush.
		//p = proc(&ues, pendmax, pendmax, &ch);
		p = proc(&ues, NULL, NULL, &ch);
		_tprintf(_T("0x%.8X\t%u\t%pH\n"), ch, ch, p);
	}

	// 转码.
	if (1) {
		p = bufsrc;
		pend = pendmax;
		pd = dst;
		putresult = ZLUTFPR_ALLOWFALLBACK;
		ZLUtfEncodeState_init(&ues);
		ZLUtfEncodeState_init(&uesd);
		_tprintf(_T("[ZLUtfPutCharProc]\n"));
		_tprintf(_T("p:\t%pH\n"), p);
		_tprintf(_T("pd:\t%pH\n"), pd);
		do{
			_tprintf(_T("\n"));
			// Get.
			p = proc(&ues, p, pend, &ch);
			_tprintf(_T("0x%.8X, %pH:"), ch, p);
			// Put.
			if (ch==ZLUTF32I_NOCHAR) continue;	// 继续取字符, 而不是执行强制刷新操作.
			pd2 = pd;
			pd = procd(&uesd, pd, pdstend, ch, &putresult);
			_tprintf(_T("\t%pH, 0x%X:\t"), pd, putresult);
			fprintbytes(stdout, pd2, ((char*)pd-(char*)pd2), _T(" "));
			if (0!=(putresult&ZLUTFPR_ERROR_MARKS)) break;
		}while(NULL!=p);
		_tprintf(_T("\n"));
	}

	// test mbrtowc.
#if ZL_CRT_mbrtowc
	if (0) {
		_tprintf(_T("[mbrtowc]\n"));
		q = (const char*)bufsrc;
		len = sizeof(bufsrc);
		//mbsinit(&ues.mbstate);
		ZLUtfEncodeState_init(&ues);
		do {
			wc = 0;
			n = mbrtowc(&wc, q, len, &ues.mbstate);
			_tprintf(_T("0x%.4X\t%u\t%ld\t%pH\n"), wc, wc, (long)n, q);
			if (n>=(size_t)(-2)) {
				break;
			}
			if (0==n) {
				n=1;	// '\0'
			}
			q += n;
			len -= n;
		}while(len>0);
		// each byte.
		if (1) {
			_tprintf(_T("[mbrtowc: Each byte]\n"));
			q = (const char*)bufsrc;
			len = sizeof(bufsrc);
			//mbsinit(&ues.mbstate);
			ZLUtfEncodeState_init(&ues);
			do {
				wc = 0;
				n = mbrtowc(&wc, q, len, &ues.mbstate);
				_tprintf(_T("0x%.4X\t%u\t%ld\t%pH\n"), wc, wc, (long)n, q);
				q += 1;
				len -= 1;
			}while(len>0);
		}
	}
#endif

	// zlutfputus.
	if (1) {
		_tprintf(_T("[zlutfputus]\n"));
		rt = zlutfputus(hf, NULL, ZLUtfGetChar_u8, bufsrc, sizeof(bufsrc));
		_tprintf(_T("\nzlutfputus:\t%")_T(PRId32)_T("\n"), rt);
	}

}

/// main .
int _tmain(int argc, TCHAR* argv[]) {
	// "UTF-*:\u0394\u4E00\U00020000\n" .
	const uint8_t str_u8[] = {'U','T','F','-','8',':', 0xCE,0x94, 0xE4,0xB8,0x80, 0xF0,0xA0,0x80,0x80, '\n'};
	const uint16_t str_u16[] = {'U','T','F','-','1','6',':', 0x394, 0x4E00, 0xD840U,0xDC00U, '\n'};
	const uint32_t str_u32[] = {'U','T','F','-','3','2',':', 0x394, 0x4E00, UINT32_C(0x20000), '\n'};
	const uint32_t str_u32n[] = {'U','T','F','-','3','2',':', 0x394, 0x4E00, UINT32_C(0x20000), '\n', '\0'};	// Null-terminated string.

	// init.
	setlocale(LC_ALL, "");	// 使用客户环境的缺省locale.

	// title.
	_tprintf(_T("zlutf v1.0 (%dbit)\n"), (int)(8*sizeof(int*)));
	_tprintf(_T("Compiler: %")_T(PRIsA)_T("\n"), ZL_COMPILER_NAME);
	_tprintf(_T("\n"));

	// test.
	dotest();

	// show.
	zlutfputius(stdout, NULL, ZLUTF_8, str_u8, sizeof(str_u8));
	zlutfputius(stdout, NULL, ZLUTF_16, str_u16, sizeof(str_u16));
	zlutfputius(stdout, NULL, ZLUTF_32, str_u32, sizeof(str_u32));
	zlutfputius(stdout, NULL, ZLUTF_32, str_u32n, -1);

	return 0;
}


/// @}
/// @}
/// @}
/// @}
