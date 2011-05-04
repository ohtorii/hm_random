#pragma once
#include"hm_def.h"
#include<string>


enum HM_MODE{
	HM_MODE_u8 = 0,
	HM_MODE_u16,
	HM_MODE_u32,
	HM_MODE_u64,
	HM_MODE_s8,
	HM_MODE_s16,
	HM_MODE_s32,
	HM_MODE_s64,
	HM_MODE_ERROR,
};

enum HM_RND{
	HM_RND_XOR128=0,
	HM_RND_XOR,
	HM_RND_XOR64,
	HM_RND_XORWOW,
	HM_RND_SFMT,
};

struct HmArg{
	s64				m_num;
	HM_RND			m_rnd;
	HM_MODE			m_mode;	
	std::wstring	m_fmt;
	u64				m_mask;
};


bool HmParseArg(HmArg &out, int argc, _TCHAR*argv[]);
