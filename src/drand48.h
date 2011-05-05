#pragma once

#include"hm_def.h"

//�����F2^48
class drand48 : public random_interface{
public:
	drand48(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);

		//QueryPerformanceCounter�łU�S�r�b�g�S�̂�
		//pid�ŏ�ʂR�Q�r�b�g���AGetTickCount�ŉ��ʂR�Q�r�b�g���B
		x = li.QuadPart ^ (((u64)_getpid())<<32) ^ GetTickCount();
	};

	u32 gen32(){
		x = x*0x5DEECE66D + 0xB;
		return (u32)(x>>17);
	};

	u64 gen64(){
		return (((u64)gen32())<<32) | gen32();
	};

private:
	s64 x;
};