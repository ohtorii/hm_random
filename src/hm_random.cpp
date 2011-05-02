/*xorshift�ŗ������R�}���h���C���֏o�͂���B

�G�ۃG�f�B�^��ŗ����𐶐�����̂��ړI�ł��B
�������P���ł���Ȃ�̌��ʂ�������xorshirt���g�p���Ă��܂��B

�R�}���h���C������w�肳�ꂽ���̗����𐶐����܂��B
�i���̌Ăяo���łP�O�O�O�̗����𐶐��Ƃ��j

������seed�͎����Őݒ肵�܂��A�����������番�z�ɕ΂肪�o�邩������܂��񂪁A
�K�`�ł������G�ۃG�f�B�^�ŏ�������Ƃ͍l���Ȃ��̂ŁA����y����D�悵�܂����B


(References)
Xorshift RNGs, George Marsaglia, The Florida State University.
http://www.jstatsoft.org/v08/i14/
*/


#include "stdafx.h"



//�����F2^128-1
//The seed set for xor128 is four 32-bit integers x,y,z,w not all 0.
class xor128{
public:
	u32 x,y,z,w;
	
	xor128(){
		/*�����l�̐ݒ���@�B

		�ux <- y <- z <- w �v�Ɠ`������̂�w�̂ݏ����������Ƃ���A
		�擪�����񎗂���������̐��l�ɂȂ�̂ŋp���B

		���ǁAx/y/z/w�S�Ă�������ۂ����������邱�Ƃɂ��܂����B
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
		
		//���_����xyzw�S�Ă�0�ɂ���ȂƏ�����Ă���B
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
};



#if 0
//�����F2^32-1
u32 xor(){
	static u32 y=2463534242UL;
	y^=(y<<13); 
	y=(y>>17); 
	return (y^=(y<<5)); 
}

//�����Fx^64-1
u64 xor64(){
	static u64 x=88172645463325252ULL;
	x^=(x<<13); 
	x^=(x>>7); 
	return (x^=(x<<17));
}

//�����F2^192-2^32
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

