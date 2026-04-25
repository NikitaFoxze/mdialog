/*

	About: modern dialog system
	Author: ziggi

*/

#if defined _mdialog_included
	#endinput
#endif

#define _mdialog_included

/*
	MySQL
*/

#tryinclude "a_mysql"
#tryinclude <a_mysql>

#if !defined MDIALOG_USE_MYSQL
	#if defined mysql_format
		#define MDIALOG_USE_MYSQL
	#endif
#endif

#if defined MDIALOG_USE_MYSQL
	#if !defined mysql_format
		#undef MDIALOG_USE_MYSQL
	#endif
#endif

/*
	Defines
*/

// external defines
#if !defined MDIALOG_DIALOG_ID
	#define MDIALOG_DIALOG_ID 32700
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if !defined MAX_LENGTH_FORMAT
	#define MAX_LENGTH_FORMAT 4096
#endif

#if !defined MDIALOG_MAX_LINES
	#define MDIALOG_MAX_LINES 100
#endif

#if !defined MDIALOG_MAX_SPACES
	#define MDIALOG_MAX_SPACES 200
#endif

#if !defined MDIALOG_MIN_DIALOG_WIDTH
	#define MDIALOG_MIN_DIALOG_WIDTH 200.0
#endif

#if !defined MDIALOG_COLOR_NONE
	#define MDIALOG_COLOR_NONE 0x00000000
#endif

#if !defined MDIALOG_MAX_FORMAT_STRING
	#define MDIALOG_MAX_FORMAT_STRING 144
#endif

#if !defined MDIALOG_MAX_CAPTION_SIZE
	#define MDIALOG_MAX_CAPTION_SIZE 64
#endif

#if !defined MDIALOG_MAX_LINE_SIZE 
	#define MDIALOG_MAX_LINE_SIZE 288
#endif

#if !defined MDIALOG_MAX_INFO_SIZE
	#define MDIALOG_MAX_INFO_SIZE MAX_LENGTH_FORMAT
#endif

#if !defined MDIALOG_MAX_COLOR_SIZE
	#define MDIALOG_MAX_COLOR_SIZE 8
#endif

// pagination
#if !defined MDIALOG_PAGIN_INVALID_LINE_ID
	#define MDIALOG_PAGIN_INVALID_LINE_ID (-1)
#endif

#if !defined MDIALOG_PAGIN_MAX_STATIC_LINES
	#define MDIALOG_PAGIN_MAX_STATIC_LINES 10
#endif

#if !defined MDIALOG_PAGIN_MAX_LINE_NAME
	#define MDIALOG_PAGIN_MAX_LINE_NAME 144
#endif

#if !defined MDIALOG_PAGIN_STYLE_MESSAGE
	#define MDIALOG_PAGIN_STYLE_MESSAGE \
		DIALOG_STYLE_MSGBOX
#endif

#if !defined MDIALOG_PAGIN_STYLE_LIST
	#define MDIALOG_PAGIN_STYLE_LIST \
		DIALOG_STYLE_LIST, \
		DIALOG_STYLE_TABLIST, \
		DIALOG_STYLE_TABLIST_HEADERS
#endif

// pagination texts
#if !defined MDIALOG_MESSAGE_TEXT_NEXT
	#define MDIALOG_MESSAGE_TEXT_NEXT "õõ"
#endif

#if !defined MDIALOG_MESSAGE_TEXT_BACK
	#define MDIALOG_MESSAGE_TEXT_BACK "ãã"
#endif

#if !defined MDIALOG_LIST_TEXT_NEXT
	#define MDIALOG_LIST_TEXT_NEXT "{A0A0A0}>>>"
#endif

#if !defined MDIALOG_LIST_TEXT_BACK
	#define MDIALOG_LIST_TEXT_BACK "{A0A0A0}<<<"
#endif

#if !defined MDIALOG_TEXT_CLOSE
	#define MDIALOG_TEXT_CLOSE "X"
#endif

#if !defined MDIALOG_TEXT_SELECT
	#define MDIALOG_TEXT_SELECT "O"
#endif

#if defined MDIALOG_ZLANG_MODE
	#if !defined MDIALOG_MAX_BUTTON_SIZE
		#define MDIALOG_MAX_BUTTON_SIZE 16
	#endif

	#if MDIALOG_MAX_FORMAT_STRING > MAX_LANG_FORMAT_STRING
		#undef MDIALOG_MAX_FORMAT_STRING
		#define MDIALOG_MAX_FORMAT_STRING MAX_LANG_FORMAT_STRING
	#endif

	#if MDIALOG_MAX_CAPTION_SIZE > MAX_LANG_VALUE_STRING
		#undef MDIALOG_MAX_CAPTION_SIZE
		#define MDIALOG_MAX_CAPTION_SIZE MAX_LANG_VALUE_STRING
	#endif

	#if MDIALOG_MAX_INFO_SIZE > MAX_LANG_MVALUE_STRING
		#undef MDIALOG_MAX_INFO_SIZE
		#define MDIALOG_MAX_INFO_SIZE MAX_LANG_MVALUE_STRING
	#endif

	#if MDIALOG_MAX_BUTTON_SIZE > MAX_LANG_VALUE_STRING
		#undef MDIALOG_MAX_BUTTON_SIZE
		#define MDIALOG_MAX_BUTTON_SIZE MAX_LANG_VALUE_STRING
	#endif
#endif

#if defined MDIALOG_USE_MYSQL
	#if !defined MDIALOG_MAX_QUERY_SIZE
		#define MDIALOG_MAX_QUERY_SIZE MAX_LENGTH_FORMAT
	#endif
#endif

#if !defined FIX_const
	#define FIX_const 0
	#define MDIALOG_FIX_CLEAR
#endif

native MDialogFix_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

#if !FIX_const
	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		#define _ALS_ShowPlayerDialog
	#endif

	#define ShowPlayerDialog MDialogFix_ShowPlayerDialog

	#if defined MDIALOG_FIX_CLEAR
		#undef MDIALOG_FIX_CLEAR
		#undef FIX_const
	#endif
#endif

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

// internal defines
#define DialogInit:%0(%1) \
	forward dit_%0(%1); \
	public dit_%0(%1)

#define DialogCreate:%0(%1) \
	forward dcr_%0(%1); \
	public dcr_%0(%1)

#define DialogResponse:%0(%1) \
	forward dre_%0(%1); \
	public dre_%0(%1)

#define DialogInterrupt:%0(%1) \
	forward din_%0(%1); \
	public din_%0(%1)

#define Dialog: #

#define dialog_args<%0> {Float, _}:...
#define dialog_start<%0> (dialog_:(%0))

/*
	Enums
*/

enum E_MDIALOG_DATA {
	e_mdFunction[MAX_FUNCTION_NAME + 1],
	e_mdOpeningFunction[MAX_FUNCTION_NAME + 1],
	e_mdType,
	e_mdStyle,
	bool:e_mdIsOpen,
	bool:e_mdIsInit,
};

enum E_MDIALOG_PAGINATION {
	e_mpListOffset,
	e_mpTotalLines,
	e_mpTotalLinesReserve,
	e_mpLinesOnPage,
	e_mpStaticLinesOnPage,
	e_mpMaxLinesOnPage,
	bool:e_mpIsAddedNoneLine,

#if defined MDIALOG_USE_MYSQL
	MySQL:e_mpMySQLHandle,
#endif
};

enum E_MDIALOG_TAG {
	E_MDIALOG_TAG_NONE = -1,
	E_MDIALOG_TAG_CENTER,
	E_MDIALOG_TAG_RIGHT,
};

enum {
	MDIALOG_TYPE_DEFAULT = 0,
	MDIALOG_TYPE_PAGINATION,
};

enum {
	MDIALOG_BUTTON_1 = 0,
	MDIALOG_BUTTON_2,
};

enum {
	MDIALOG_PAGIN_OPEN = 0,
	MDIALOG_PAGIN_NEXT,
	MDIALOG_PAGIN_BACK,
	MDIALOG_PAGIN_CURRENT,
};

/*
	Vars
*/

#if !defined MDIALOG_DISABLE_TAGS
static
	Float:gCharSize[256] = {
		-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
		4.4453125, // space
		5.328125, // !
		7.5859375, // "
		8.8984375, // #
		8.8984375, // $
		14.2265625, // %
		11.5546875, // &
		3.8046875, // '
		5.328125, // (
		5.328125, // )
		6.2265625, // *
		9.34375, // +
		4.4453125, // ,
		5.328125, // -
		4.4453125, // .
		4.4453125, // /
		8.8984375, // 0
		8.8984375, // 1
		8.8984375, // 2
		8.8984375, // 3
		8.8984375, // 4
		8.8984375, // 5
		8.8984375, // 6
		8.8984375, // 7
		8.8984375, // 8
		8.8984375, // 9
		5.328125, // :
		5.328125, // ;
		9.34375, // <
		9.34375, // =
		9.34375, // >
		9.7734375, // ?
		15.6015625, // @
		11.5546875, // A
		11.5546875, // B
		11.5546875, // C
		11.5546875, // D
		10.671875, // E
		9.7734375, // F
		12.4453125, // G
		11.5546875, // H
		4.4453125, // I
		8.8984375, // J
		11.5546875, // K
		9.7734375, // L
		13.328125, // M
		11.5546875, // N
		12.4453125, // O
		10.671875, // P
		12.4453125, // Q
		11.5546875, // R
		10.671875, // S
		9.7734375, // T
		11.5546875, // U
		10.671875, // V
		15.1015625, // W
		10.671875, // X
		10.671875, // Y
		9.7734375, // Z
		5.328125, // [
		4.4453125, // backslash
		5.328125, // ]
		9.34375, // ^
		8.8984375, // _
		5.328125, // `
		8.8984375, // a
		9.7734375, // b
		8.8984375, // c
		9.7734375, // d
		8.8984375, // e
		5.328125, // f
		9.7734375, // g
		9.7734375, // h
		4.4453125, // i
		4.4453125, // j
		8.8984375, // k
		4.4453125, // l
		14.2265625, // m
		9.7734375, // n
		9.7734375, // o
		9.7734375, // p
		9.7734375, // q
		6.2265625, // r
		8.8984375, // s
		5.328125, // t
		9.7734375, // u
		8.8984375, // v
		12.4453125, // w
		8.8984375, // x
		8.8984375, // y
		8.0, // z
		6.2265625, // {
		4.4765625, // |
		6.2265625, // }
		9.34375, // ~
		8.0, // 
		14.1640625, // Ä
		9.0703125, // Å
		4.4453125, // Ç
		6.6640625, // É
		8.0, // Ñ
		16.0, // Ö
		8.8984375, // Ü
		8.8984375, // á
		8.8984375, // à
		16.0, // â
		17.5, // ä
		5.328125, // ã
		17.0, // å
		9.765625, // ç
		14.0, // é
		11.5, // è
		9.7734375, // ê
		4.4453125, // ë
		4.4453125, // í
		8.0, // ì
		8.0, // î
		5.6015625, // ï
		8.8984375, // ñ
		16.0, // ó
		16.0, // ô
		15.5, // ö
		5.328125, // õ
		14.5, // ú
		8.0078125, // ù
		9.7734375, // û
		9.6640625, // ü
		4.4453125, //
		9.953125, // °
		8.8984375, // ¢
		8.8984375, // £
		8.8984375, // §
		7.7890625, // •
		4.4765625, // ¶
		8.8984375, // ß
		-1.0,
		10.703125, // ®
		11.7890625, // ©
		11.3828125, // ™
		8.8984375, // ´
		9.34375, // ¨
		0.0, // ≠
		11.7890625, // Æ
		4.4140625, // Ø
		6.3984375, // ∞
		8.78125, // ±
		4.4453125, // ≤
		4.4453125, // ≥
		7.1484375, // ¥
		9.21875, // µ
		8.8984375, // ∂
		5.328125, // ∑
		8.8984375, // ∏
		17.8359375, // π
		8.8359375, // ∫
		8.8984375, // ª
		4.4453125, // º
		10.671875, // Ω
		8.8984375, // æ
		4.5, // ø
		11.5546875, // ¿
		11.5, // ¡
		11.5546875, // ¬
		9.0703125, // √
		11.3984375, // ƒ
		10.671875, // ≈
		14.4609375, // ∆
		10.0234375, // «
		11.5, // »
		11.5, // …
		9.765625, //  
		11.2265625, // À
		13.328125, // Ã
		11.5546875, // Õ
		12.4453125, // Œ
		11.5, // œ
		10.671875, // –
		11.5546875, // —
		9.7734375, // “
		9.953125, // ”
		13.65625, // ‘
		10.671875, // ’
		11.6875, // ÷
		11.2421875, // ◊
		16.078125, // ÿ
		16.3046875, // Ÿ
		13.9140625, // ⁄
		15.6640625, // €
		11.5, // ‹
		11.3828125, // ›
		16.5, // ﬁ
		11.5, // ﬂ
		8.8984375, // ‡
		9.8828125, // ·
		9.8359375, // ‚
		6.6640625, // „
		10.15625, // ‰
		8.8984375, // Â
		11.34375, // Ê
		7.953125, // Á
		9.8359375, // Ë
		9.8359375, // È
		8.0078125, // Í
		10.1640625, // Î
		11.8359375, // Ï
		9.6640625, // Ì
		9.7734375, // Ó
		9.6640625, // Ô
		9.7734375, // 
		8.8984375, // Ò
		7.8359375, // Ú
		8.8984375, // Û
		14.0, // Ù
		8.8984375, // ı
		9.8359375, // ˆ
		9.2890625, // ˜
		13.3359375, // ¯
		13.5, // ˘
		11.6640625, // ˙
		13.6640625, // ˚
		9.8359375, // ¸
		8.8359375, // ˝
		13.6640625, // ˛
		9.3359375 // ˇ
	};

static
	gTag[E_MDIALOG_TAG][] = {
		"\\c",
		"\\r"
	},
	gTagLength[E_MDIALOG_TAG];

#endif

static
	gDialogData[MAX_PLAYERS][E_MDIALOG_DATA],
	gPaginData[MAX_PLAYERS][E_MDIALOG_PAGINATION];

static
	gTotalLinesCountID[MAX_PLAYERS],
	gTotalLinesCountName[MAX_PLAYERS],
	gAddedLinesCountID[MAX_PLAYERS],
	gAddedLinesCountName[MAX_PLAYERS],
	gListLineID[MAX_PLAYERS][MDIALOG_MAX_LINES],
	gListLineName[MAX_PLAYERS][MDIALOG_MAX_LINES][MDIALOG_PAGIN_MAX_LINE_NAME + 1],
	gSelectLineID[MAX_PLAYERS],
	gSelectLineName[MAX_PLAYERS][MDIALOG_PAGIN_MAX_LINE_NAME + 1];

static
	gStrDialogBuffer[MAX_PLAYERS][MDIALOG_MAX_INFO_SIZE + 1];

#if defined MDIALOG_USE_MYSQL

static
	gStrDialogQuery[MAX_PLAYERS][MDIALOG_MAX_QUERY_SIZE + 1];

#endif

/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	#if !defined MDIALOG_DISABLE_TAGS
		for (new tag = 0; tag < sizeof(gTag); tag++) {
			gTagLength[E_MDIALOG_TAG:tag] = strlen(gTag[E_MDIALOG_TAG:tag]);
		}
	#endif

	for (new i = 0; i < MAX_PLAYERS; i++) {
		_MDialogPagin_ClearData(i);
	}

	#if defined MDialog_OnGameModeInit
		return MDialog_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit MDialog_OnGameModeInit
#if defined MDialog_OnGameModeInit
	forward MDialog_OnGameModeInit();
#endif

/*
	ShowPlayerDialog
*/

stock MDialog_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[])
{
	if (dialogid != -1 && dialogid != MDIALOG_DIALOG_ID) {
		if (Dialog_IsOpen(playerid)) {
			Dialog_Close(playerid, gDialogData[playerid][e_mdFunction][4], false);
		}
	}

	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog MDialog_ShowPlayerDialog

/*
	Dialog_Open
*/

static stock _Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[])
{
	if (Dialog_IsOpen(playerid)) {
		Dialog_Interrupt(playerid, gDialogData[playerid][e_mdFunction][4]);
	}

	gDialogData[playerid][e_mdIsOpen] = true;
	gDialogData[playerid][e_mdStyle] = style; 

	format(gDialogData[playerid][e_mdFunction], MAX_FUNCTION_NAME + 1, "dre_%s", function);

	switch (style) {
		case DIALOG_STYLE_MSGBOX, DIALOG_STYLE_INPUT, DIALOG_STYLE_PASSWORD: {
			#if defined MDIALOG_DISABLE_TAGS
				return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
			#else
				static info_result[MDIALOG_MAX_INFO_SIZE];
				_MDialog_ProcessTags(info, info_result);
				return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info_result, button1, button2);
			#endif
		}
	}

	return ShowPlayerDialog(playerid, MDIALOG_DIALOG_ID, style, caption, info, button1, button2);
}

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (!isnull(button2)) {
		Lang_GetText(lang, button2, temp_button2);
	} else {
		temp_button2[0] = '\0';
	}

	if (numargs() > 7) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<7>);
	}

	return _Dialog_Open(playerid, function, style, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[])
{
	return _Dialog_Open(playerid, function, style, caption, info, button1, button2);
}

#endif

/*
	Dialog_Close
*/

stock Dialog_Close(playerid, const function[] = "", showDialog = true)
{
	gDialogData[playerid][e_mdIsOpen] =
	gDialogData[playerid][e_mdIsInit] = false;

	gDialogData[playerid][e_mdFunction][0] =
	gDialogData[playerid][e_mdOpeningFunction][0] = '\0';

	Dialog_Interrupt(playerid, function);

	if (showDialog) {
	#if defined _INC_open_mp
		return HidePlayerDialog(playerid);
	#else
		return MDialogFix_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
	#endif
	}

	return 1;
}

stock Dialog_Interrupt(playerid, const function[])
{
	if (!isnull(function)) {
		new call_func[MAX_FUNCTION_NAME char] = !"din_";
		strcat(call_func, function);
		return CallLocalFunction(call_func, "d", playerid);
	}
	return 0;
}

/*
	Dialog_IsOpen
*/

stock Dialog_IsOpen(playerid, const function[] = "")
{
	if (isnull(function)) {
		return _:gDialogData[playerid][e_mdIsOpen];
	}

	if (!isnull(gDialogData[playerid][e_mdFunction]) && gDialogData[playerid][e_mdIsOpen] && strcmp(gDialogData[playerid][e_mdFunction][4], function) == 0) {
		return 1;
	}

	return 0;
}

/*
	Dialog_Show
*/

stock Dialog_Show(playerid, const function[])
{
	_MDialog_strcpy(gDialogData[playerid][e_mdOpeningFunction], function);

	if (_Dialog_Init(playerid, function)) {
		return _Dialog_Show(playerid, function);
	}
	else {
		return 0;
	}
}

static stock _Dialog_Show(playerid, const function[])
{
	new call_func[MAX_FUNCTION_NAME char] = !"dcr_";
	strcat(call_func, function);

	_MDialog_InitDialogData(playerid);
	return CallLocalFunction(call_func, "d", playerid);
}

/*
	Dialog init
*/

static stock _Dialog_Init(playerid, const function[])
{
	if (gDialogData[playerid][e_mdIsInit]) {
		return 1;
	}

	new call_func[MAX_FUNCTION_NAME char] = !"dit_";
	strcat(call_func, function);

	gDialogData[playerid][e_mdType] = MDIALOG_TYPE_DEFAULT;

	CallLocalFunction(call_func, "d", playerid);
	gDialogData[playerid][e_mdIsInit] = true;

	return _MDialog_ProcessInit(playerid);
}

static stock _MDialog_ProcessInit(playerid)
{
	switch (gDialogData[playerid][e_mdType]) {
		case MDIALOG_TYPE_PAGINATION: {
			_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_OPEN);
			return 0;
		}
	}
	return 1;
}

static stock _MDialog_InitDialogData(playerid)
{
	switch (gDialogData[playerid][e_mdType]) {
		case MDIALOG_TYPE_PAGINATION: {
			_MDialogPagin_InitDialogData(playerid);
		}
	}
}

/*
	Dialog_GetCurrent
*/

stock Dialog_GetCurrent(playerid, function[], const size = sizeof(function))
{
	if (gDialogData[playerid][e_mdFunction][0] == '\0') {
		function[0] = '\0';
		return 0;
	}

	return _MDialog_strcpy(function, gDialogData[playerid][e_mdFunction][4], size);
}

/*
	Dialog_Message
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_Message(playerid, const caption[], const info[], const button1[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (numargs() > 4) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<4>);
	}

	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, "");
}

#else

stock Dialog_Message(playerid, const caption[], const info[], const button1[])
{
	return _Dialog_Open(playerid, Dialog:Message, DIALOG_STYLE_MSGBOX, caption, info, button1, "");
}

#endif

/*
	Dialog_MessageEx
*/

#if defined MDIALOG_ZLANG_MODE

stock Dialog_MessageEx(playerid, const response[], const caption[], const info[], const button1[], const button2[], lang_args<>)
{
	static
		Lang:lang,
		temp_caption[MDIALOG_MAX_CAPTION_SIZE],
		temp_button1[MDIALOG_MAX_BUTTON_SIZE],
		temp_button2[MDIALOG_MAX_BUTTON_SIZE],
		temp_info[MDIALOG_MAX_INFO_SIZE];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, caption, temp_caption);
	Lang_GetText(lang, info, temp_info);
	Lang_GetText(lang, button1, temp_button1);

	if (!isnull(button2)) {
		Lang_GetText(lang, button2, temp_button2);
	} else {
		temp_button2[0] = '\0';
	}

	if (numargs() > 6) {
		Lang_format(temp_info, sizeof(temp_info), temp_info, lang_start<6>);
	}

	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, temp_caption, temp_info, temp_button1, temp_button2);
}

#else

stock Dialog_MessageEx(playerid, const response[], const caption[], const info[], const button1[], const button2[])
{
	return _Dialog_Open(playerid, response, DIALOG_STYLE_MSGBOX, caption, info, button1, button2);
}

#endif

/*
	OnDialogResponse
*/

static stock _MDialog_ProcessResponse(playerid, &response, listitem)
{
	switch (gDialogData[playerid][e_mdType]) {
		case MDIALOG_TYPE_PAGINATION: {
			return _MDialogPagin_ProcessButtons(playerid, response, listitem);
		}
	}
	return 1;
}

static stock _MDialog_OnDialogResponse(playerid, response, listitem, const inputtext[])
{
	gDialogData[playerid][e_mdIsOpen] =
	gDialogData[playerid][e_mdIsInit] = false;

	gDialogData[playerid][e_mdOpeningFunction][0] = '\0';
	return CallLocalFunction(gDialogData[playerid][e_mdFunction], "ddds", playerid, response, listitem, inputtext);
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	static temp[128];
	_MDialog_strcpy(temp, inputtext);

	if (dialogid == MDIALOG_DIALOG_ID) {
		if (temp[0] == '\0') {
			if (Dialog_IsOpen(playerid)) {
				if (!_MDialog_ProcessResponse(playerid, response, listitem)) {
					return 0;
				}
				return _MDialog_OnDialogResponse(playerid, response, listitem, "\1");
			}
			return 0;
		}

		for (new i = strlen(temp) - 1; i != -1; i--) {
			if (temp[i] == '%') {
				temp[i] = '#';
			}
		}

		if (Dialog_IsOpen(playerid)) {
			if (!_MDialog_ProcessResponse(playerid, response, listitem)) {
				return 0;
			}
			return _MDialog_OnDialogResponse(playerid, response, listitem, temp);
		}
		return 0;
	}

	#if defined MDialog_OnDialogResponse
		return MDialog_OnDialogResponse(playerid, dialogid, response, listitem, temp);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse MDialog_OnDialogResponse
#if defined MDialog_OnDialogResponse
	forward MDialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

/*
	MDialog_OnAnswerToQuery
*/

#if defined MDIALOG_USE_MYSQL

forward MDialog_OnAnswerToQuery(playerid, const function[]);
public MDialog_OnAnswerToQuery(playerid, const function[])
{
	if (strcmp(gDialogData[playerid][e_mdOpeningFunction], function) == 1) {
		return;
	}

	_Dialog_Show(playerid, function);
}

#endif

/*
	Pagination
*/

stock DialogPagin_Init(playerid, max_lines_on_page)
{
	if (max_lines_on_page == 0 || max_lines_on_page > MDIALOG_MAX_LINES) {
		max_lines_on_page = MDIALOG_MAX_LINES;
	}

	_MDialogPagin_ResetData(playerid);

	gDialogData[playerid][e_mdType] = MDIALOG_TYPE_PAGINATION;
	gPaginData[playerid][e_mpMaxLinesOnPage] = max_lines_on_page;
	return 1;
}

#if defined MDIALOG_USE_MYSQL

stock DialogPagin_SetQuery(playerid, MySQL:handle, const query[], const length = sizeof(query), dialog_args<>)
{
	if (handle == MYSQL_INVALID_HANDLE) {
		printf("mdialog: incorrect handle %i", _:handle);
		return 0;
	}

	if (isnull(query)) {
		printf("mdialog: incorrect query");
		return 0;
	}

	gPaginData[playerid][e_mpMySQLHandle] = handle;

	if (numargs() > 4) {
		Dialog_format(gStrDialogQuery[playerid], length, query, dialog_start<4>);
	}
	else {
		_MDialog_strcpy(gStrDialogQuery[playerid], query);
	}
	return 1;
}

static stock _MDialogPagin_LoadItems(playerid, handle, offset)
{
	static
		query[MDIALOG_MAX_QUERY_SIZE + 1];

	mysql_format(MySQL:handle, query, sizeof(query),
		"%s LIMIT %i, %i",
		gStrDialogQuery[playerid], offset, gPaginData[playerid][e_mpMaxLinesOnPage]);

	mysql_tquery(MySQL:handle, query, "MDialog_OnAnswerToQuery", "ds", playerid, gDialogData[playerid][e_mdOpeningFunction]);
}

#endif

stock DialogPagin_IsValidLine(playerid)
{
#if defined MDIALOG_USE_MYSQL
	if (gPaginData[playerid][e_mpMySQLHandle] != MYSQL_INVALID_HANDLE) {
		return 1;
	}
#endif

	gPaginData[playerid][e_mpTotalLines]++;

	if (gPaginData[playerid][e_mpLinesOnPage] >= gPaginData[playerid][e_mpMaxLinesOnPage]) {
		return 0;
	}

	if (!_MDialogPagin_IsValidLine(playerid, gPaginData[playerid][e_mpTotalLines] - 1)) {
		return 0;
	}

	return 1;
}

static stock _MDialogPagin_IsValidLine(playerid, total_lines)
{
	static
		list_offset,
		max_lines_on_page;

	list_offset = gPaginData[playerid][e_mpListOffset];
	max_lines_on_page = gPaginData[playerid][e_mpMaxLinesOnPage];

	return (total_lines >= list_offset) && (total_lines < (list_offset + max_lines_on_page));
}

stock DialogPagin_GetTotalItems(playerid)
{
	if (gPaginData[playerid][e_mpTotalLines] > 0) {
		return gPaginData[playerid][e_mpTotalLines];
	}

	return gPaginData[playerid][e_mpTotalLinesReserve];
}

stock DialogPagin_SaveLineID(playerid, abstractid)
{
	// Checking to see if the `DialogPagin_IsValidLine` function is called before it is called
	if (gPaginData[playerid][e_mpTotalLines] <= 0) {
		gTotalLinesCountID[playerid]++;

		if (!_MDialogPagin_IsValidLine(playerid, gTotalLinesCountID[playerid] - 1)) {
			return 0;
		}
	}

	gListLineID[playerid][gAddedLinesCountID[playerid]] = abstractid;
	gAddedLinesCountID[playerid]++;
	return 1;
}

stock DialogPagin_SaveLineName(playerid, const abstract_name[])
{
	// Checking to see if the `DialogPagin_IsValidLine` function is called before it is called
	if (gPaginData[playerid][e_mpTotalLines] <= 0) {
		gTotalLinesCountName[playerid]++;

		if (!_MDialogPagin_IsValidLine(playerid, gTotalLinesCountName[playerid] - 1)) {
			return 0;
		}
	}

	_MDialog_strcpy(gListLineName[playerid][gAddedLinesCountName[playerid]], abstract_name);
	gAddedLinesCountName[playerid]++;
	return 1;
}

stock DialogPagin_GetSelectLineID(playerid)
{
	return gSelectLineID[playerid];
}

stock DialogPagin_GetSelectLineName(playerid, output[], const size = sizeof(output))
{
	_MDialog_strcpy(output, gSelectLineName[playerid], size);
}

stock DialogPagin_AddTablist(playerid, const text[], dialog_args<>)
{
	static
		temp[MDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_MDialog_strcpy(temp, text);
#endif

	if (numargs() > 3) {
		Dialog_format(temp, sizeof(temp), temp, dialog_start<3>);
	}

	strcat(temp, "\n");
	strins(gStrDialogBuffer[playerid], temp, 0);
}

stock DialogPagin_AddColor(playerid, const color[])
{
	strcat(gStrDialogBuffer[playerid], color);
}

stock DialogPagin_AddLine(playerid, color, const text[], dialog_args<>)
{
	// Checking to see if the `DialogPagin_IsValidLine` function is called before it is called
	if (gPaginData[playerid][e_mpTotalLines] <= 0) {
		gPaginData[playerid][e_mpTotalLinesReserve]++;

		if (!_MDialogPagin_IsValidLine(playerid, gPaginData[playerid][e_mpTotalLinesReserve] - 1)) {
			return 0;
		}
	}

	gPaginData[playerid][e_mpLinesOnPage]++;

	static
		temp[MDIALOG_MAX_LINE_SIZE + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_MDialog_strcpy(temp, text);
#endif

	if (numargs() > 3) {
		Dialog_format(temp, sizeof(temp), temp, dialog_start<3>);
	}

	if (color != MDIALOG_COLOR_NONE) {
		static
			previous_color,
			string_nums[MDIALOG_MAX_COLOR_SIZE + 11],
			string_color[MDIALOG_MAX_COLOR_SIZE + 1];

		// Optimization
		if (previous_color != color) {
			previous_color = color;
			_MDialog_IntToHex(string_color, color);
		}

		format(string_nums, sizeof(string_nums),
			"%s[%i] ",
			string_color,
			gPaginData[playerid][e_mpListOffset] + gPaginData[playerid][e_mpLinesOnPage]);

		strins(temp, string_nums, 0);
	}

	if (gPaginData[playerid][e_mpStaticLinesOnPage] > 0) {
		if (!gPaginData[playerid][e_mpIsAddedNoneLine]) {
			strins(temp, " \n", 0);
			gPaginData[playerid][e_mpIsAddedNoneLine] = true;
		}
	}

	strcat(temp, "\n");
	strcat(gStrDialogBuffer[playerid], temp);
	return 1;
}

stock DialogPagin_AddStaticLine(playerid, color, const text[], dialog_args<>)
{
	if (!DialogPagin_IsFirstPage(playerid)) {
		return 0;
	}

	if (gPaginData[playerid][e_mpStaticLinesOnPage] >= MDIALOG_PAGIN_MAX_STATIC_LINES) {
		return 0;
	}

	gPaginData[playerid][e_mpStaticLinesOnPage]++;

	static
		temp[MDIALOG_MAX_LINE_SIZE + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_MDialog_strcpy(temp, text);
#endif

	if (numargs() > 3) {
		Dialog_format(temp, sizeof(temp), temp, dialog_start<3>);
	}

	if (color != MDIALOG_COLOR_NONE) {
		static
			previous_color,
			string_nums[MDIALOG_MAX_COLOR_SIZE + 11],
			string_color[MDIALOG_MAX_COLOR_SIZE + 1];

		// Optimization
		if (previous_color != color) {
			previous_color = color;
			_MDialog_IntToHex(string_color, color);
		}

		format(string_nums, sizeof(string_nums),
			"%s[%i] ",
			string_color,
			gPaginData[playerid][e_mpStaticLinesOnPage]);

		strins(temp, string_nums, 0);
	}

	strcat(temp, "\n");
	strcat(gStrDialogBuffer[playerid], temp);
	return 1;
}

stock DialogPagin_IsFirstPage(playerid)
{
	return (gPaginData[playerid][e_mpListOffset] <= 0);
}

stock DialogPagin_IsLastPage(playerid)
{
	return ((gPaginData[playerid][e_mpListOffset] + gPaginData[playerid][e_mpMaxLinesOnPage]) >= gPaginData[playerid][e_mpTotalLines]);
}

stock DialogPagin_Open(playerid, const function[], style, const caption[], dialog_args<>)
{
	if (gDialogData[playerid][e_mdType] != MDIALOG_TYPE_PAGINATION) {
		return 0;
	}

	if (gPaginData[playerid][e_mpLinesOnPage] <= 0 && gPaginData[playerid][e_mpStaticLinesOnPage] <= 0) {
		strcat(gStrDialogBuffer[playerid], " \n");
	}

	if (gPaginData[playerid][e_mpTotalLines] <= 0) {
		gPaginData[playerid][e_mpTotalLines] = gPaginData[playerid][e_mpTotalLinesReserve];
	}

	switch (style) {
		case MDIALOG_PAGIN_STYLE_MESSAGE: {}
		case MDIALOG_PAGIN_STYLE_LIST: {
			if (gPaginData[playerid][e_mpLinesOnPage] > 0) {
				// Button Next
				if (!DialogPagin_IsLastPage(playerid)) {
					#if defined MDIALOG_ZLANG_MODE
						static
							buttonNext[MDIALOG_MAX_FORMAT_STRING + 1];

						if (Lang_GetPlayerText(playerid,
							MDIALOG_LIST_TEXT_NEXT,
							buttonNext)) {

							strins(buttonNext, "\n", 0);
							strcat(gStrDialogBuffer[playerid], buttonNext);
						}
						else {
							strcat(gStrDialogBuffer[playerid], "\n"MDIALOG_LIST_TEXT_NEXT"");
						}
					#else
						strcat(gStrDialogBuffer[playerid], "\n"MDIALOG_LIST_TEXT_NEXT"");
					#endif
				}

				// Button Back
				if (!DialogPagin_IsFirstPage(playerid)) {
					#if defined MDIALOG_ZLANG_MODE
						static
							buttonBack[MDIALOG_MAX_FORMAT_STRING + 1];

						if (Lang_GetPlayerText(playerid,
							MDIALOG_LIST_TEXT_BACK,
							buttonBack)) {

							strins(buttonBack, "\n", 0);
							strcat(gStrDialogBuffer[playerid], buttonBack);
						}
						else {
							strcat(gStrDialogBuffer[playerid], "\n"MDIALOG_LIST_TEXT_BACK"");
						}
					#else
						strcat(gStrDialogBuffer[playerid], "\n"MDIALOG_LIST_TEXT_BACK"");
					#endif
				}
			}
		}
		// Invalid
		default: {
			return 0;
		}
	}

	static
		string_caption[MDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, caption, string_caption);
#else
	_MDialog_strcpy(string_caption, caption);
#endif

	if (numargs() > 4) {
		Dialog_format(string_caption, sizeof(string_caption), string_caption, dialog_start<4>);
	}

	static
		button1[MDIALOG_MAX_FORMAT_STRING + 1],
		button2[MDIALOG_MAX_FORMAT_STRING + 1];

	_MDialogPagin_GetButtonText(playerid, style, MDIALOG_BUTTON_1, button1);
	_MDialogPagin_GetButtonText(playerid, style, MDIALOG_BUTTON_2, button2);

	return _Dialog_Open(playerid, function, style, string_caption,
		gStrDialogBuffer[playerid],
		button1,
		button2);
}

static stock _MDialogPagin_InitDialogData(playerid)
{
	gPaginData[playerid][e_mpTotalLines] =
	gPaginData[playerid][e_mpTotalLinesReserve] =
	gPaginData[playerid][e_mpLinesOnPage] =
	gPaginData[playerid][e_mpStaticLinesOnPage] = 0;

	gPaginData[playerid][e_mpIsAddedNoneLine] = false;

	gTotalLinesCountID[playerid] =
	gTotalLinesCountName[playerid] =
	gAddedLinesCountID[playerid] =
	gAddedLinesCountName[playerid] = 0;

	gStrDialogBuffer[playerid][0] = '\0';

#if defined MDIALOG_USE_MYSQL
	if (gPaginData[playerid][e_mpMySQLHandle] != MYSQL_INVALID_HANDLE) {
		if (!cache_get_value_int(0, "total_count", gPaginData[playerid][e_mpTotalLines])) {
			printf("mdialog: the [total_count] column is not loaded");
		}
	}
#endif
}

static stock _MDialogPagin_ProcessButtons(playerid, &response, listitem)
{
	if (gPaginData[playerid][e_mpLinesOnPage] <= 0 && gPaginData[playerid][e_mpStaticLinesOnPage] <= 0) {
		response = 0;
		return 1;
	}

	switch (gDialogData[playerid][e_mdStyle]) {
		case MDIALOG_PAGIN_STYLE_MESSAGE: {
			if (response) {
				if (!DialogPagin_IsFirstPage(playerid)) {
					_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_BACK);
					return 0;
				}
				else {
					response = 0;
				}
			}
			else {
				if (!DialogPagin_IsLastPage(playerid)) {
					_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_NEXT);
					return 0;
				}
				else {
					response = 0;
				}
			}
		}
		case MDIALOG_PAGIN_STYLE_LIST: {
			if (!response) {
				return 1;
			}

			static
				itemsOnPage,
				staticLines,
				buttonPosition;

			itemsOnPage = gPaginData[playerid][e_mpLinesOnPage];
			staticLines = gPaginData[playerid][e_mpStaticLinesOnPage];
			buttonPosition = staticLines > 0 ? itemsOnPage + staticLines + 1 : itemsOnPage + staticLines;

			if (listitem == buttonPosition) {
				if (!DialogPagin_IsLastPage(playerid)) {
					_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_NEXT);
				}
				else {
					_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_BACK);
				}
				return 0;
			}
			else if (listitem == buttonPosition + 1) {
				_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_BACK);
				return 0;
			}

			static
				index;

			if (staticLines > 0) {
				if (listitem < staticLines) {
					return 1;
				}
				else if (listitem == staticLines) {
					_MDialogPagin_ProcessPagination(playerid, MDIALOG_PAGIN_CURRENT);
					return 0;
				}

				index = listitem - staticLines - 1;
			}
			else {
				index = listitem;
			}

			if (gAddedLinesCountID[playerid] > 0) {
				gSelectLineID[playerid] = gListLineID[playerid][index];
			}

			if (gAddedLinesCountName[playerid] > 0) {
				_MDialog_strcpy(gSelectLineName[playerid], gListLineName[playerid][index]);
			}
		}
	}
	return 1;
}

static stock _MDialogPagin_ResetData(playerid)
{
#if defined MDIALOG_USE_MYSQL
	gPaginData[playerid][e_mpMySQLHandle] = MYSQL_INVALID_HANDLE;
#else
	#pragma unused playerid
#endif
}

static stock _MDialogPagin_ClearData(playerid)
{
	_MDialogPagin_ResetData(playerid);

	gPaginData[playerid][e_mpListOffset] =
	gPaginData[playerid][e_mpTotalLines] =
	gPaginData[playerid][e_mpTotalLinesReserve] =
	gPaginData[playerid][e_mpLinesOnPage] =
	gPaginData[playerid][e_mpStaticLinesOnPage] =
	gPaginData[playerid][e_mpMaxLinesOnPage] = 0;

	gPaginData[playerid][e_mpIsAddedNoneLine] = false;

	gTotalLinesCountID[playerid] =
	gTotalLinesCountName[playerid] =
	gAddedLinesCountID[playerid] =
	gAddedLinesCountName[playerid] = 0;

	gSelectLineID[playerid] = MDIALOG_PAGIN_INVALID_LINE_ID;
	gSelectLineName[playerid][0] = '\0';

	for(new i = 0; i < MDIALOG_MAX_LINES; i++) {
		gListLineID[playerid][i] = MDIALOG_PAGIN_INVALID_LINE_ID;
		gListLineName[playerid][i][0] = '\0';
	}

	gStrDialogBuffer[playerid][0] = '\0';

#if defined MDIALOG_USE_MYSQL
	gStrDialogQuery[playerid][0] = '\0';
#endif
}

static stock _MDialogPagin_ProcessPagination(playerid, actionid)
{
	switch (actionid) {
		case MDIALOG_PAGIN_OPEN: {
			gPaginData[playerid][e_mpListOffset] = 0;
		}
		case MDIALOG_PAGIN_NEXT: {
			gPaginData[playerid][e_mpListOffset] += gPaginData[playerid][e_mpMaxLinesOnPage];
		}
		case MDIALOG_PAGIN_BACK: {
			gPaginData[playerid][e_mpListOffset] -= gPaginData[playerid][e_mpMaxLinesOnPage];

			if (gPaginData[playerid][e_mpListOffset] < 0) {
				gPaginData[playerid][e_mpListOffset] = 0;
			}
		}
	}

#if defined MDIALOG_USE_MYSQL
	if (gPaginData[playerid][e_mpMySQLHandle] != MYSQL_INVALID_HANDLE) {
		_MDialogPagin_LoadItems(playerid,
			_:gPaginData[playerid][e_mpMySQLHandle],
			gPaginData[playerid][e_mpListOffset]);

		return;
	}
#endif

	_Dialog_Show(playerid, gDialogData[playerid][e_mdOpeningFunction]);
}

static stock _MDialogPagin_GetButtonText(playerid, style, buttonid, output[], const size = sizeof(output))
{
	switch (style) {
		case MDIALOG_PAGIN_STYLE_MESSAGE: {
			if (buttonid == MDIALOG_BUTTON_1) {
				if (!DialogPagin_IsFirstPage(playerid)) {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_MESSAGE_TEXT_BACK,
						output, size)) {

						_MDialog_strcpy(output, MDIALOG_MESSAGE_TEXT_BACK, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_MESSAGE_TEXT_BACK, size);
				#endif
				}
				else {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_TEXT_CLOSE,
						output, size)) {

						_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
				#endif
				}
			}
			else {
				if (DialogPagin_IsLastPage(playerid)) {
					if (gPaginData[playerid][e_mpListOffset] > 0) {
					#if defined MDIALOG_ZLANG_MODE
						if (!Lang_GetPlayerText(playerid,
							MDIALOG_TEXT_CLOSE,
							output, size)) {
							
							_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
						}
					#else
						_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
					#endif
					}
					else {
						output[0] = '\0';
					}
				}
				else {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_MESSAGE_TEXT_NEXT,
						output, size)) {
						
						_MDialog_strcpy(output, MDIALOG_MESSAGE_TEXT_NEXT, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_MESSAGE_TEXT_NEXT, size);
				#endif
				}
			}
		}
		case MDIALOG_PAGIN_STYLE_LIST: {
			if (gPaginData[playerid][e_mpLinesOnPage] > 0 || gPaginData[playerid][e_mpStaticLinesOnPage] > 0) {
				if (buttonid == MDIALOG_BUTTON_1) {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_TEXT_SELECT,
						output, size)) {

						_MDialog_strcpy(output, MDIALOG_TEXT_SELECT, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_TEXT_SELECT, size);
				#endif
				}
				else {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_TEXT_CLOSE,
						output, size)) {

						_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
				#endif
				}
			}
			else {
				if (buttonid == MDIALOG_BUTTON_1) {
				#if defined MDIALOG_ZLANG_MODE
					if (!Lang_GetPlayerText(playerid,
						MDIALOG_TEXT_CLOSE,
						output, size)) {

						_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
					}
				#else
					_MDialog_strcpy(output, MDIALOG_TEXT_CLOSE, size);
				#endif
				}
				else {
					output[0] = '\0';
				}
			}
		}
	}
}

/*
	_MDialog_ProcessTags
*/

#if !defined MDIALOG_DISABLE_TAGS

static stock _MDialog_ProcessTags(const info[], result_info[], const size = sizeof(result_info))
{
	static
		line_lengths[MDIALOG_MAX_LINES],
		Float:line_sizes[MDIALOG_MAX_LINES],
		line_pos[MDIALOG_MAX_LINES],
		sep_pos,
		prev_sep_pos,
		E_MDIALOG_TAG:tag,
		tag_pos,
		tag_length,
		E_MDIALOG_TAG:tag_line[MDIALOG_MAX_LINES],
		lines_count,
		length,
		Float:max_size,
		i,
		Float:temp_size;

	// if string is packed
	if (info{0} != 0) {
		strunpack(result_info, info, size);
	} else {
		_MDialog_strcpy(result_info, info, size);
	}

	// reset variables
	lines_count = 0;
	sep_pos = 0;
	prev_sep_pos = 0;
	max_size = 0.0;

	// get biggest line and save line sizes
	while (sep_pos >= 0) {
		// get line length
		sep_pos = strfind(result_info, "\n", false, prev_sep_pos + 1);
		if (sep_pos == -1) {
			length = strlen(result_info) - prev_sep_pos - 1;
		} else {
			length = sep_pos - prev_sep_pos - _:(lines_count != 0);
			line_pos[lines_count + 1] = sep_pos + 1;
		}

		// check for tag
		tag_line[lines_count] = E_MDIALOG_TAG_NONE;

		for (tag = E_MDIALOG_TAG:0; tag < E_MDIALOG_TAG; tag++) {
			tag_pos = line_pos[lines_count] - 1;
			if (tag_pos < 0) {
				tag_pos = 0;
			}

			tag_pos = strfind(result_info, gTag[tag], false, tag_pos);

			// if tag exists
			if (tag_pos != -1 && (sep_pos == -1 || tag_pos < line_pos[lines_count + 1])) {
				tag_line[lines_count] = tag;

				// remove the tag
				tag_length = gTagLength[tag];

				strdel(result_info, tag_pos, tag_pos + tag_length);
				length -= tag_length;
				sep_pos -= tag_length;
				line_pos[lines_count + 1] -= tag_length;

				break;
			}
		}

		// remember length
		line_lengths[lines_count] = length;

		// get line size
		line_sizes[lines_count] = 0;

		for (i = prev_sep_pos; i <= prev_sep_pos + length; i++) {
			if (result_info[i] == '{') {
				i += 7;
				continue;
			}

			temp_size = gCharSize[ result_info[i] ];
			if (temp_size != -1) {
				line_sizes[lines_count] += temp_size;
			}
		}

		// update max size
		temp_size = line_sizes[lines_count];
		if (temp_size > max_size) {
			max_size = temp_size;
		}

		// save separator position for the future
		prev_sep_pos = sep_pos;

		// check for array borders
		lines_count++;
		if (lines_count >= MDIALOG_MAX_LINES) {
			break;
		}
	}

	if (max_size < MDIALOG_MIN_DIALOG_WIDTH) {
		max_size = MDIALOG_MIN_DIALOG_WIDTH;
	}

	// add spaces to the string
	static
		spaces_string[MDIALOG_MAX_SPACES],
		spaces,
		j;

	for (i = 0; i < lines_count; i++) {
		// get spaces count by tag
		switch (tag_line[i]) {
			case E_MDIALOG_TAG_NONE: {
				continue;
			}
			case E_MDIALOG_TAG_CENTER: {
				spaces = floatround((max_size - line_sizes[i]) / 2.0 / gCharSize[' ']);
			}
			case E_MDIALOG_TAG_RIGHT: {
				spaces = floatround((max_size - line_sizes[i]) / gCharSize[' ']);
			}
		}

		// is spaces are needed
		if (spaces == 0) {
			continue;
		}

		// make spaces string
		for (j = 0; j <= spaces; j++) {
			spaces_string[j] = ' ';
		}

		spaces_string[spaces + 1] = '\0';
		line_sizes[i] += spaces * gCharSize[' '];

		// insert spaces into the string
		format(result_info, size, "%.*s%s%s", line_pos[i], result_info, spaces_string, result_info[ line_pos[i] ]);

		// update line positions
		for (j = i + 1; j < lines_count; j++) {
			line_pos[j] += spaces + 1;
		}
	}
}

#endif

/*
	Other functions
*/

static stock _MDialog_strcpy(result[], const source[], const size = sizeof(result))
{
	result[0] = 0;
	return strcat(result, source, size);
}

static stock _MDialog_IntToHex(result[], color, const size = sizeof(result))
{
	format(result, size, "{%02x%02x%02x}", color & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF);
}

/*
	strlen
*/

stock MDialog_strlen(const string[])
{
	if (isnull(string)) {
		return 0;
	}

	return strlen(string);
}
#if defined _ALS_strlen
	#undef strlen
#else
	#define _ALS_strlen
#endif

#define strlen MDialog_strlen

// taken from YSI
stock Dialog_format(out[], size, const fmat[], dialog_:STATIC_ARGS)
{
	static
		YSI_g_sHeap,
		YSI_g_sStack,
		YSI_g_sArgCount,
		YSI_g_sArgs[5];

	//P:C(if (_:STATIC_ARGS < 1) P:W("No static args found, please add a dummy local"););
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.

	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.

	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD

	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         16 // (n + 1) * 4

	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        16 // (n + 1) * 4
	#emit SCTRL        4

	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH.S       size
	#emit PUSH.S       out
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.

	// Modify the heap to hold "locals".
	#emit HEAP         0
	#emit STOR.alt     YSI_g_sHeap
	#emit LCTRL        4
	#emit SCTRL        2

	// Call the function.
	#emit SYSREQ.C     format
	#emit STOR.pri     YSI_g_sArgCount

	// Copy the data back.
	#emit LOAD.pri     YSI_g_sHeap
	#emit SCTRL        2
	#emit STACK        0
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         16
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4

	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN

	return 0;
}