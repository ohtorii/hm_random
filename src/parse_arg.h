#pragma once
#include"hm_def.h"
#include<string>


enum HM_RND{
	HM_RND_XOR128=0,
	HM_RND_XOR,
	HM_RND_XOR64,
	HM_RND_XORWOW,
	HM_RND_SFMT,
};

class HmArg{
public:
	HmArg(){
		m_num=10;
		m_rnd=HM_RND_XOR128;
		m_min=0;
		m_max=100;
		m_in_base=10;
		m_out_base=10;
		m_prefix=L"";
		m_delimiter=L"\n";
	};
	s64				m_num;
	HM_RND			m_rnd;
	s64				m_min;
	s64				m_max;
	int				m_in_base;
	int				m_out_base;
	std::wstring	m_prefix;
	std::wstring	m_delimiter;
};


bool HmParseArg(HmArg &out, int argc, _TCHAR*argv[]);
