#pragma once

/*xorshift

(����)
�Ԉ�����������s���Ă��邩������܂���A���̕ӂ͒��ӂ��ĉ������B

(References)
Xorshift RNGs, George Marsaglia, The Florida State University.
http://www.jstatsoft.org/v08/i14/
*/



#include"hm_def.h"

//�����F2^128-1
class xs_xor128 : public random_interface{
public:
	xs_xor128(){
		/*�����l�̐ݒ���@�B
		�ux <- y <- z <- w �v�Ɠ`������̂�w�̂ݏ���������ƁA������̐擪�Ɏ���
		���l�������̂ł悭�Ȃ��B

		x/y/z/w�S�Ă����������邱�Ƃɂ��܂����B
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
		//�_����xyzw�S�Ă�0�ɂ���ȂƏ�����Ă���B
		//�r�b�g���]���Ƃ��ƁAz==0�̂Ƃ��ɁAw!=0�ƂȂ�̂ŏ����𖞂�����B
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


//�����F2^32-1
class xs_xor : public random_interface{
public:
	xs_xor(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		y = li.LowPart ^ li.HighPart ^ _getpid() ^ GetTickCount();
	}
	u32 gen32(){
		y^=(y<<13);

		/*note �_�����̊ԈႢ���C���B�i2011/05/03�j
		�i��jy=(y>>17);
		�i���jy^=(y>>17);
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



//�����Fx^64-1
class xs_xor64 : public random_interface{
public:
	xs_xor64(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);

		//QueryPerformanceCounter�łU�S�r�b�g�S�̂�
		//pid�ŏ�ʂR�Q�r�b�g���AGetTickCount�ŉ��ʂR�Q�r�b�g���B
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



//�����F2^192-2^32
class xs_xorwow : public random_interface{
public:
	xs_xorwow(){
		//�_���ɏ����l�̎w�肪�����̂ł��������ɁB

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

		//�O�̂��߁Ax/y/z/w/v ���S��0�ɂȂ�̂������B
		v=~w;

		//>with any odd constant replacing 362437
		//�Ƃ肠�������̂܂܂�
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
//�������̏��������G�Ȃ̂Ŏ�����������B
//
//�����Fxor128��蒷���悤������������Ă��Ȃ��H
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

