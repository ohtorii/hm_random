#include "stdafx.h"




static bool argv_model(HmArg&out, _TCHAR*p){	
	if(0 == wcscmp(L"u8",p)){
		out.m_mode = HM_MODE_u8;
		out.m_mask = 0x00000000000000ffULL;
		return true;
	}
	if(0 == wcscmp(L"u16",p)){
		out.m_mode = HM_MODE_u16;
		out.m_mask = 0x000000000000ffffULL;
		return true;
	}
	if(0 == wcscmp(L"u32",p)){
		out.m_mode = HM_MODE_u32;
		out.m_mask = 0x00000000ffffffffULL;
		return true;
	}
	if(0 == wcscmp(L"u64",p)){
		out.m_mode = HM_MODE_u64;
		out.m_mask = 0xffffffffffffffffULL;
		return true;
	}


	if(0 == wcscmp(L"s8",p)){
		out.m_mode = HM_MODE_s8;
		out.m_mask = 0x00000000000000ffULL;
		return true;
	}
	if(0 == wcscmp(L"s16",p)){
		out.m_mode = HM_MODE_s16;
		out.m_mask = 0x000000000000ffffULL;
		return true;
	}
	if(0 == wcscmp(L"s32",p)){
		out.m_mode = HM_MODE_s32;
		out.m_mask = 0x00000000ffffffffULL;
		return true;
	}
	if(0 == wcscmp(L"s64",p)){
		out.m_mode = HM_MODE_s64;
		out.m_mask = 0xffffffffffffffffULL;
		return true;
	}
	return false;
}

/*�R�}���h���C����������󂯎�����Aprintf�̃t�H�[�}�b�g���𐮌`�B

\n -> ���s�̕����R�[�h��
\t -> �^�u�̕����R�[�h��

in  = foo\n
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

bool HmParseArg(HmArg &out, int argc, _TCHAR*argv[]){
	if(argc != 4){
		return false;
	}
		
	if(! argv_model(out,argv[1])){
		wprintf(L"ErrArg: mode\n");
		return false;
	}
	
	out.m_num  = _wtoi64(argv[2]);
	Replace(out.m_fmt, argv[3]);
	return true;
}