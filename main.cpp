/////////////////////////////////////////////
//                                         //
//    Copyright (C) 2019-2019 Julian Uy    //
//  https://sites.google.com/site/awertyb  //
//                                         //
//   See details of license at "LICENSE"   //
//                                         //
/////////////////////////////////////////////

#include "ncbind/ncbind.hpp"
#include <string.h>

tjs_uint8 *octoct(const tjs_uint8 *haystack, size_t haystack_len, const tjs_uint8 *needle, size_t needle_len)
{
	const tjs_uint8 *begin = haystack;
	const tjs_uint8 *last_possible = begin + haystack_len - needle_len;
	const tjs_uint8 *tail = needle;
	tjs_uint8 point;

	if (needle_len == 0)
	{
		return (tjs_uint8 *)begin;
	}

	if (haystack_len < needle_len)
	{
		return NULL;
	}
	point = *tail++;
	for (; begin <= last_possible; begin++)
	{
		if (*begin == point && !TJS_octetcmp(begin + 1, tail, needle_len - 1))
		{
			return (tjs_uint8 *)begin;
		}
	}
	return NULL;
}

class Octet
{
public:
	static tTVInteger indexOf(tTJSVariant inoct, tTJSVariant suboct, tTVInteger start)
	{
		tTJSVariantOctet *inoctptr = inoct.AsOctetNoAddRef();
		tTJSVariantOctet *suboctptr = suboct.AsOctetNoAddRef();
		if (!inoctptr || !suboctptr)
		{
			return -1;
		}
		const tjs_uint8 *indata = inoctptr->GetData();
		size_t inlen = inoctptr->GetLength();
		const tjs_uint8 *subdata = suboctptr->GetData();
		size_t sublen = suboctptr->GetLength();
		if(start >= inlen)
		{
			return -1;
		}
		indata += start;
		inlen -= start;
		tjs_uint8 *loc = octoct(indata, inlen, subdata, sublen);
		if (!loc)
		{
			return -1;
		}
		return (loc - indata);
	}

	static tTJSVariant substring(tTJSVariant inoct, tTVInteger startind, tTVInteger countind)
	{
		tTJSVariantOctet *inoctptr = inoct.AsOctetNoAddRef();
		if (!inoctptr)
		{
			return tTJSVariant();
		}
		const tjs_uint8 *indata = inoctptr->GetData();
		size_t inlen = inoctptr->GetLength();
		if((startind < 0) || (startind >= inlen))
		{
			return tTJSVariant();
		}
		indata += startind;
		inlen -= startind;
		if((countind < 0) || (countind >= inlen))
		{
			return tTJSVariant();
		}
		tTJSVariant v((const tjs_uint8 *)&indata[0], countind);
		return v;
	}
};

NCB_REGISTER_CLASS(Octet)
{
	NCB_METHOD(indexOf);
	NCB_METHOD(substring);
};
