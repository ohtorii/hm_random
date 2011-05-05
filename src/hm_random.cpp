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
		"usage: hm_random num func base_in min max prefix base_out delimiter\n"
		"Argments:\n"
		"num    : number of genrate random values.\n"
		"func   : xorshift (period 2^128-1)           default=xorshift\n"
		"         xor      (period 2^32-1)\n"
		"         xor64    (period 2^64-1)\n"
		"         xorwow   (period 2^192-2^32)\n"
		"         sfmt     (SIMD-oriented Fast Mersenne Twister. period 2^19937-1)\n"
		"         drand48  (period 2^48)\n"
		"base_in: min/max base.(2/8/10/16/...36)      default=10\n"
		"min    ; min value(signed).                  default=0\n"
		"max    : max value(signed). [min,max]        default=100\n"
		"prefix : prefix.                             default=\"\"\n"
		"base_out: output base.(2/8/10/16/...36)      default=10\n"
		"delimiter : Blank for newline,printf format. default=\"\\n\"\n"		
	);
}

static random_interface* new_rand_obj(HM_RND type){
	switch(type){
	case HM_RND_XOR128:
		//printf("HM_RND_XOR128\n");
		return new xs_xor128;
	case HM_RND_XOR:
		//printf("HM_RND_XOR\n");
		return new xs_xor;
	case HM_RND_XOR64:
		//printf("HM_RND_XOR64\n");
		return new xs_xor64;
	case HM_RND_XORWOW:
		//printf("HM_RND_XORWOW\n");
		return new xs_xorwow;
	case HM_RND_SFMT:
		//printf("HM_RND_SFMT\n");
		return new sfmt;
	case HM_RND_DRAND48:
		//printf("HM_RND_DRAND48\n");
		return new drand48;
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

	random_interface	*obj	= new_rand_obj(arg.m_rnd);
	const u64			range	= 1 + (arg.m_max - arg.m_min);
	s64 				value	= 0;
	wchar_t 			out_buf[256];

	while(0 < arg.m_num){
		value = arg.m_min + ((s64)(obj->gen64()%range));
		_i64tow_s(value,out_buf,sizeof(out_buf)/sizeof(out_buf[0]),arg.m_out_base);
		wprintf_s(L"%s%s%s", arg.m_prefix.c_str(), out_buf, arg.m_delimiter.c_str());
		--(arg.m_num);
	}

	delete_rand_obj(obj);
	obj=0;

	return 0;
}

