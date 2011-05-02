/*xorshiftで乱数をコマンドラインへ出力する。

秀丸エディタ上で乱数を生成するのが目的です。
実装が単純でそれなりの結果が得られるxorshirtを使用しています。

コマンドラインから指定された個数の乱数を生成します。
（一回の呼び出しで１０００個の乱数を生成とか）

乱数のseedは自動で設定します、もしかしたら分布に偏りが出るかもしれませんが、
ガチでやる方が秀丸エディタで処理するとは考えないので、お手軽さを優先しました。


(References)
Xorshift RNGs, George Marsaglia, The Florida State University.
http://www.jstatsoft.org/v08/i14/
*/


#include "stdafx.h"



//周期：2^128-1
//The seed set for xor128 is four 32-bit integers x,y,z,w not all 0.
class xor128{
public:
	u32 x,y,z,w;
	
	xor128(){
		/*初期値の設定方法。

		「x <- y <- z <- w 」と伝搬するのでwのみ初期化したところ、
		先頭が毎回似たり寄ったりの数値になるので却下。

		結局、x/y/z/w全てをそれっぽく初期化することにしました。
		*/		
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		u32 qpc_l = li.LowPart;
		u32 qpc_h = li.HighPart;		
		
		u32 seed1 = _getpid() ^ qpc_l;
		u32 seed2 = GetTickCount() ^ qpc_h;

		x=seed1;
		y=seed2;
		z=qpc_l;
		
		//元論文にxyzw全てを0にするなと書かれている。
		//ビット反転しとくと、z==0のときに、w!=0となるので条件を満たせる。
		w=~z;
	};		

	u32 gen32(){
		u32 t=(x^(x<<11));
		x=y;
		y=z;
		z=w;
		return( w=(w^(w>>19))^(t^(t>>8)) );
	};
	u64 gen64(){
		return (((u64)gen32())<<32) | ((u64)gen32());
	};
};



#if 0
//周期：2^32-1
u32 xor(){
	static u32 y=2463534242UL;
	y^=(y<<13); 
	y=(y>>17); 
	return (y^=(y<<5)); 
}

//周期：x^64-1
u64 xor64(){
	static u64 x=88172645463325252ULL;
	x^=(x<<13); 
	x^=(x>>7); 
	return (x^=(x<<17));
}

//周期：2^192-2^32
unsigned long xorwow(){
	static unsigned long x=123456789,y=362436069,z=521288629,
	w=88675123,v=5783321, d=6615241;
	unsigned long t=(x^(x>>2));
	x=y;
	y=z;
	z=w;
	w=v;
	v=(v^(v<<4))^(t^(t<<1)); 
	return (d+=362437)+v;
}

//周期：xor128より長いようだが明言されていない？
//the seed set forMWCis three 32-bit integers x,y,z and an initial c<a, 
//excluding the two cases x=y=z=c=0, and x=y=z=b-1,c=a-1.
unsigned long mwc(){
	static unsigned long x=123456789,y=362436069,z=77465321,c=13579;
	unsigned long long t;
	t=916905990LL*x+c; 
	x=y; 
	y=z; 
	c=(t>>32); 
	return z=(t&0xffffffff);
}
#endif 


void usage(){
	printf(
		"usage: hm_random mode num format\n"
		"Options and argments:\n"
		"mode   :  8    8bit random value.\n"
		"         16   16bit.\n"
		"         32   32bit.\n"
		"         64   64bit.\n"
		"num    : number of genrate random values.\n"
		"format : printf format string.(Ex \"%%d\")\n"
	);
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


	xor128	obj;
	while(0 < arg.m_num){		
		wprintf_s(arg.m_fmt.c_str(), arg.m_mask & obj.gen64());
		--(arg.m_num);
	}
	
	return 0;
}

