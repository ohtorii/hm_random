/*xorshift�ŗ������R�}���h���C���֏o�͂���B

�G�ۃG�f�B�^��ŗ����𐶐�����̂��ړI�ł��B
�������P���ł���Ȃ�̌��ʂ�������xorshirt���g�p���Ă��܂��B

�R�}���h���C������w�肳�ꂽ���̗����𐶐����܂��B
�i���̌Ăяo���łP�O�O�O�̗����𐶐��Ƃ��j

������seed�͎����Őݒ肵�܂��A�����������番�z�ɕ΂肪�o�邩������܂��񂪁A
�K�`�ł������G�ۃG�f�B�^�ŏ�������Ƃ͍l���Ȃ��̂ŁA����y����D�悵�܂����B
*/


#include "stdafx.h"




void usage(){
	printf(
		"usage: hm_random type num format\n"
		"Options and argments:\n"		
		"type   :  u8   unsigned 8bit.\n"
		"         u16   unsigned 16bit.\n"
		"         u32   unsigned 32bit.\n"
		"         u64   unsigned 64bit.\n"
		"          s8   signed   8bit.\n"
		"         s16   signed   16bit.\n"
		"         s32   signed   32bit.\n"
		"         s64   signed   64bit.\n"
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

	//random_interface*obj=new xs_xor128;
	//random_interface*obj=new xs_xor;
	//random_interface*obj=new xs_xor64;
	random_interface*obj=new xs_xorwow;
	const wchar_t* fmt = arg.m_fmt.c_str();

	while(0 < arg.m_num){
		switch(arg.m_mode){
		case HM_MODE_u8:						
			wprintf_s(fmt, (u8)obj->gen32());
			break;
		case HM_MODE_u16:
			wprintf_s(fmt, (u16)obj->gen32());
			break;
		case HM_MODE_u32:
			wprintf_s(fmt, (u32)obj->gen32());
			break;
		case HM_MODE_u64:		
			wprintf_s(fmt, (u64)obj->gen64());
			break;
		case HM_MODE_s8:						
			wprintf_s(fmt, (s8)obj->gen32());
			break;
		case HM_MODE_s16:
			wprintf_s(fmt, (s16)obj->gen32());
			break;
		case HM_MODE_s32:
			wprintf_s(fmt, (s32)obj->gen32());
			break;
		case HM_MODE_s64:	
		default:
			wprintf_s(fmt, (s64)obj->gen64());
			break;
		}
		
		--(arg.m_num);
	}
	
	delete obj;
	obj=0;
	
	return 0;
}

