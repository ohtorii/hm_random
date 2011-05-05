#pragma once

/*xorshift

(注意)
間違った実装を行っているかもしれません、その辺は注意して下さい。

(References)
Xorshift RNGs, George Marsaglia, The Florida State University.
http://www.jstatsoft.org/v08/i14/
*/



#include"hm_def.h"

//周期：2^128-1
class xs_xor128 : public random_interface{
public:
	xs_xor128(){
		/*初期値の設定方法。
		「x <- y <- z <- w 」と伝搬するのでwのみ初期化すると、乱数列の先頭に似た
		数値が現れるのでよくない。

		x/y/z/w全てを初期化することにしました。
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

		//
		//The seed set for xor128 is four 32-bit integers x,y,z,w not all 0.
		//
		//論文にxyzw全てを0にするなと書かれている。
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
private:
	u32 x,y,z,w;
};


//周期：2^32-1
class xs_xor : public random_interface{
public:
	xs_xor(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		y = li.LowPart ^ li.HighPart ^ _getpid() ^ GetTickCount();
	}
	u32 gen32(){
		y^=(y<<13);

		/*note 論文中の間違いを修正。（2011/05/03）
		（誤）y=(y>>17);
		（正）y^=(y>>17);
		*/
		y^=(y>>17);

		return (y^=(y<<5));
	};
	u64 gen64(){
		return (((u64)gen32())<<32) | ((u64)gen32());
	};
private:
	u32 y;
};



//周期：x^64-1
class xs_xor64 : public random_interface{
public:
	xs_xor64(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);

		//QueryPerformanceCounterで６４ビット全体を
		//pidで上位３２ビットを、GetTickCountで下位３２ビットを。
		x = li.QuadPart ^ (((u64)_getpid())<<32) ^ GetTickCount();
	};
	u32 gen32(){
		return (u32)gen64();
	};
	u64 gen64(){
		x^=(x<<13);
		x^=(x>>7);
		return (x^=(x<<17));
	};
private:
	u64 x;
};



//周期：2^192-2^32
class xs_xorwow : public random_interface{
public:
	xs_xorwow(){
		//論文に初期値の指定が無いのでいい感じに。

		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		u32 qpc_l = li.LowPart;
		u32 qpc_h = li.HighPart;

		u32 seed1 = _getpid() ^ qpc_l;
		u32 seed2 = GetTickCount() ^ qpc_h;

		x=seed1;
		y=seed2;
		z=qpc_l;
		w=qpc_h;

		//念のため、x/y/z/w/v が全て0になるのを避ける。
		v=~w;

		//>with any odd constant replacing 362437
		//とりあえずそのままに
		d=6615241;
	};
	u32 gen32(){
		u32 t=(x^(x>>2));
		x=y;
		y=z;
		z=w;
		w=v;
		v=(v^(v<<4))^(t^(t<<1));
		return (d+=362437)+v;
	};
	u64 gen64(){
		return (((u64)gen32())<<32) | ((u64)gen32());
	};
private:
	u32 x,y,z,w,v,d;
};


#if 0
//
//初期化の条件が複雑なので実装を見送り。
//
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

