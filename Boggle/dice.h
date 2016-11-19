#pragma once
#if  BIG_BOGGLE
#define DIE1 "YQYSWF"
#define DIE2 "SZTLLP"
#define DIE3 "XOLRQL"
#define DIE4 "HCTHJT"
#define DIE5 "JKHHWF"
#define DIE6 "AEIOUA"
#define DIE7 "QBRLPR"
#define DIE8 "GGNETN"
#define DIE9 "AAEOOU"
#define DIE10 "AAEEIO"
#define DIE11 "BVTNTS"
#define DIE12 "SCYWSJ"
#define DIE13 "EEEIOU"
#define DIE14 "AAEEIO"
#define DIE15 "CMHKZN"
#define DIE16 "HGBMGN"
#define DIE17 "AEIOUO"
#define DIE18 "SYSYFD"
#define DIE19 "MLGMCP"
#define DIE20 "UIEEOO"
#define DIE21 "DBXVDY"
#define DIE22 "FNRDDW"
#define DIE23 "OAEEUU"
#define DIE24 "VMRGZR"
#define DIE25 "DKXMPK"

const char8_t* Dice[] = { DIE1, DIE2, DIE3, DIE4, DIE5, DIE6, DIE7, DIE8, DIE9, DIE10, DIE11, DIE12, DIE13, DIE14, DIE15, DIE16, DIE17, DIE18, DIE19, DIE20, DIE21, DIE22, DIE23, DIE24, DIE25 };

#else
#define DIE1 "YQYSWF"
#define DIE2 "SZTLLP"
#define DIE3 "XOLRQL"
#define DIE4 "HCTHJT"
#define DIE5 "JKHHWF"
#define DIE6 "AEIOUA"
#define DIE7 "QBRLPR"
#define DIE8 "GGNETN"
#define DIE9 "AAEOOU"
#define DIE10 "AAEEIO"
#define DIE11 "BVTNTS"
#define DIE12 "SCYWSJ"
#define DIE13 "EEEIOU"
#define DIE14 "AAEEIO"
#define DIE15 "CMHKZN"
#define DIE16 "HGBMGN"

const char* Dice[] = { DIE1, DIE2, DIE3, DIE4, DIE5, DIE6, DIE7, DIE8, DIE9, DIE10, DIE11, DIE12, DIE13, DIE14, DIE15, DIE16 }

#endif

#define DIE_NUM_CHAR 6