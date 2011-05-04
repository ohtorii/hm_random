/*xorshiftで乱数をコマンドラインへ出力する。

秀丸エディタ上で乱数を生成するのが目的です。
実装が単純でそれなりの結果が得られるxorshirtを使用しています。

コマンドラインから指定された個数の乱数を生成します。
（一回の呼び出しで１０００個の乱数を生成とか）

乱数のseedは自動で設定します、もしかしたら分布に偏りが出るかもしれませんが、
ガチでやる方が秀丸エディタで処理するとは考えないので、お手軽さを優先しました。
*/


#include "stdafx.h"




static void usage(){
	printf(
		"usage: hm_random num func type format\n"
		"Argments:\n"
		"num    : number of genrate random values.\n"
		"func   : xorshift (period 2^128-1)\n"
		"         xor      (period 2^32-1)\n"
		"         xor64    (period 2^64-1)\n"
		"         xorwow   (period 2^192-2^32)\n"
		"         sfmt     (SIMD-oriented Fast Mersenne Twister. period 2^19937-1)\n"
		"type   :  u8   unsigned 8bit.\n"
		"         u16   unsigned 16bit.\n"
		"         u32   unsigned 32bit.\n"
		"         u64   unsigned 64bit.\n"
		"          s8   signed   8bit.\n"
		"         s16   signed   16bit.\n"
		"         s32   signed   32bit.\n"
		"         s64   signed   64bit.\n"
		"format : printf format string.(Ex %%d\\n)\n"
		"Examples.\n"
		"(1) hm_random.exe 10 xorshift s32 %%d\\n\n"
		"(2) hm_random.exe 3 xorshift u64 \"%%I64u,\\n\"\n"
		"(3) hm_random.exe 10 sfmt u64 \"0x%%016I64x / \"\n"
	);
}

static random_interface* new_rand_obj(HM_RND type){
	switch(type){
	case HM_RND_XOR128:
		return new xs_xor128;
	case HM_RND_XOR:
		return new xs_xor;
	case HM_RND_XOR64:
		return new xs_xor64;
	case HM_RND_XORWOW:
		return new xs_xorwow;
	case HM_RND_SFMT:
		return new sfmt;
	default:
		//pass
		break;
	}
	return 0;
}

static void delete_rand_obj(random_interface *p){
	delete p;
}
	
int _tmain(int argc, _TCHAR* argv[])
{
#if 0	/*debug*/
	for(int i=0 ; i<argc ; ++i){
		wprintf(L"%d/%s\n",i,argv[i]);
	}
#endif

	HmArg arg;
	if(! HmParseArg(arg, argc, argv)){
		usage();
		return 1;
	}
	random_interface*obj = new_rand_obj(arg.m_rnd);
	const wchar_t* fmt = arg.m_fmt.c_str();

	while(0 < arg.m_num){
		switch(arg.m_mode){
		case HM_MODE_u8:
			wprintf_s(fmt, (u8)obj->gen32());
			break;
		case HM_MODE_u16:
			wprintf_s(fmt, (u16)obj->gen32());
			break;
		case HM_MODE_u32:
			wprintf_s(fmt, (u32)obj->gen32());
			break;
		case HM_MODE_u64:
			wprintf_s(fmt, (u64)obj->gen64());
			break;
		case HM_MODE_s8:
			wprintf_s(fmt, (s8)obj->gen32());
			break;
		case HM_MODE_s16:
			wprintf_s(fmt, (s16)obj->gen32());
			break;
		case HM_MODE_s32:
			wprintf_s(fmt, (s32)obj->gen32());
			break;
		case HM_MODE_s64:
		default:
			wprintf_s(fmt, (s64)obj->gen64());
			break;
		}

		--(arg.m_num);
	}

	delete_rand_obj(obj);
	obj=0;

	return 0;
}

