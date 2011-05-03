#pragma once
#include"hm_def.h"

extern "C"{
#include"sfmt.h"
};

class sfmt : public random_interface{
public:
	sfmt(){
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
				
		uint32_t x = li.LowPart ^ li.HighPart^ _getpid() ^ GetTickCount();
		init_gen_rand(x);
	};
	u32 gen32(){
		return gen_rand32();
	};
	u64 gen64(){
		return gen_rand64();
	};
};

