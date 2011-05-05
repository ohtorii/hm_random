#include "stdafx.h"


static bool argv_func(HmArg&out, _TCHAR*p){
	if(0 == wcscmp(L"xorshift",p)){
		out.m_rnd = HM_RND_XOR128;
		return true;
	}
	if(0 == wcscmp(L"xor",p)){
		out.m_rnd = HM_RND_XOR;
		return true;
	}
	if(0 == wcscmp(L"xor64",p)){
		out.m_rnd = HM_RND_XOR64;
		return true;
	}
	if(0 == wcscmp(L"xorwow",p)){
		out.m_rnd = HM_RND_XORWOW;
		return true;
	}
	if(0 == wcscmp(L"sfmt",p)){
		out.m_rnd = HM_RND_SFMT;
		return true;
	}
	if(0 == wcscmp(L"drand48",p)){
		out.m_rnd = HM_RND_DRAND48;
		return true;
	}
	return false;
}

/*�R�}���h���C����������󂯎�����Aprintf�̃t�H�[�}�b�g���𐮌`�B

\n -> ���s�̕����R�[�h��
\t -> �^�u�̕����R�[�h��

in	= foo\n
out = foo + ���s�R�[�h

int = bar\\
out = bar\
*/
static void Replace(std::wstring&out, _TCHAR*argv){
	out.clear();
	bool has_yen=false;
	while(*argv){
		if(L'\\'==(*argv)){
			if(has_yen){
				out.push_back(L'\\');
				has_yen=false;
			}else{
				has_yen=true;
			}
		}else{
			if(has_yen){
				if(L'n'==(*argv)){
					out.push_back(L'\n');
				}else if(L't'==(*argv)){
					out.push_back(L'\t');
				}else{
					//�s���ȃG�X�P�[�v�V�[�P���X
					//���O��\�𖳎�����B
					out.push_back(*argv);
				}
				has_yen=false;
			}else{
				out.push_back(*argv);
			}
		}
		++argv;
	}
}

static bool CheckBase(int v, const char* str){
	if((v < HM_MIN_BASE) || (HM_MAX_BASE<v)){
		wprintf(L"ErrArg: Invalid base balue %s.\n"
				L"Input value   = %d\n"
				L"Correct range = %d-%d\n", str, v, HM_MIN_BASE,HM_MAX_BASE);
		return false;
	}
	return true;
}

bool HmParseArg(HmArg &out, int argc, _TCHAR*argv[]){
	if(argc<2){
		wprintf(L"ErrArg: Invalid arg num.\n");
		return false;
	}

	if(1<argc){
		out.m_num  = _wtoi64(argv[1]);
	}
	if(2<argc){
		if(! argv_func(out, argv[2])){
			wprintf(L"ErrArg: func\n");
			return false;
		}
	}

	if(3<argc){
		out.m_in_base=_wtoi(argv[3]);
	}
	if(! CheckBase(out.m_in_base,"in_base")){
		return false;
	}

	if(4<argc){
		out.m_min = _wcstoi64(argv[4],0,out.m_in_base);
	}
	if(5<argc){
		out.m_max = _wcstoi64(argv[5],0,out.m_in_base);
	}
	if(out.m_max < out.m_min){
		wprintf(L"ErrArg: max<min\n");
		return false;
	}
	if(6<argc){
		out.m_prefix.assign(argv[6]);
	}
	if(7<argc){
		out.m_out_base=_wtoi(argv[7]);
	}
	if(! CheckBase(out.m_out_base,"out_base")){
		return false;
	}
	if(8<argc){
		Replace(out.m_delimiter, argv[8]);
	}

	return true;
}