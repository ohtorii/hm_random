#pragma once
#include"hm_def.h"
#include<string>


enum HM_MODE{
	HM_MODE_8 = 0,
	HM_MODE_16,
	HM_MODE_32,
	HM_MODE_64,
	HM_MODE_ERROR,
};


struct HmArg{
	HM_MODE			m_mode;
	s64				m_num;
	std::wstring	m_fmt;
	u64				m_mask;
};


bool HmParseArg(HmArg &out, int argc, _TCHAR*argv[]);
