#pragma once

typedef unsigned 	char	u8;
typedef unsigned 	short	u16;
typedef unsigned 	int		u32;
typedef unsigned 	__int64	u64;

typedef signed 		char	s8;
typedef signed 		short	s16;
typedef signed 		int		s32;
typedef signed 		__int64	s64;

class random_interface{
public:
	virtual u32 gen32()=0;
	virtual u64 gen64()=0;
};

#define HM_MIN_BASE	2
#define HM_MAX_BASE	36
