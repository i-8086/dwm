/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "Symbola:size=14" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char selflcolor[]	     = "#eeeeee";
static char normflcolor[]	     = "#444444";
static char *colors[][4]      = {
       /*               fg         bg         border     float */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor, normflcolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor, selflcolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 8,       1,             1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            1,             0,           -1 },
	{ NULL,	      NULL,       "khal",     0,            1,             1,           -1 },
	{ NULL,	      NULL,     "galculator", 0,            1,             1,           -1 },
	{ "Gnome-calendar", NULL, NULL,       0,            1,             1,           -1 },
	{ NULL,       NULL,     "Steam - News", 0,          1,             1,           -1 },
	{ NULL,       NULL,     "Friends List", 0,          1,             1,           -1 },
	{ "Nitrogen", NULL, 	  NULL,       0,            1,             1,           -1 },
	{ "Arandr", NULL,       NULL,         0,            1,             1,           -1 },
	{ NULL,	      NULL,     "amixer",     0,            1,             1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 0;    /* 1 means attach after the currently active window */
static int warpcursor = 0;	/*1 means warp cursor to center of active window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
//	{ "><>",      NULL },    /* no layout function means floating behavior */
//	{ "[M]",      monocle },
// 	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "><>",      NULL },
	{ NULL,       NULL }
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_h,	   tagmon,	   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_h,      focusmon,       {.i = -1} },
	{ MODKEY,                       XK_l,      focusmon,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    /*view*/toggleAttachBelow,           {0} },
	{ MODKEY,			XK_Tab,	   toggleWarpCursor, {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY /*|ShiftMask*/,        XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,			XK_bracketleft, setmfact,  {.f = -0.05} },
	{ MODKEY,                       XK_bracketright, setmfact,  {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_bracketleft, resetmfact, {.f = 0.50} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
	{ MODKEY,			XK_Escape, spawn,          SHCMD("telegram") },
	{ MODKEY,		        XK_F1,     spawn,          SHCMD("google-chrome-stable") },
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_F3,     spawn,          SHCMD("pcmanfm") },
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("st -e ranger") },
	{ MODKEY,			XK_Page_Up, spawn,	   SHCMD("amixer sset Master 2%+; refbar; pkill -RTMIN+11 dwmblocks &") },
	{ MODKEY,                       XK_Page_Down, spawn,       SHCMD("amixer sset Master 2%-; refbar; pkill -RTMIN+11 dwmblocks &") },
	{ MODKEY, 			XK_Up,	   focusstack, 	   {.i = -1 } },
	{ MODKEY,			XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY, 			XK_Left,   focusmon,	   {.i = -1 } },
	{ MODKEY, 			XK_Right,  focusmon,	   {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,     rotatestack,    {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Down,   rotatestack,    {.i = +1 } },
        { MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("displayoff") },
	{ MODKEY,			XK_F12,    spawn,	   SHCMD("slock; displayoff") },
	{ MODKEY, 			XK_F8,	   spawn,	   SHCMD("displayselect") },
	{ MODKEY,			XK_Print,  spawn,	   SHCMD("scrot '%Y%m%d-%H%M%S_screenshot.png' -e 'mv $f ~/Pictures/screenshots/'; notify-send screenshot") },
	{ MODKEY|ControlMask,		XK_m,	   spawn,	   SHCMD("st -e alsamixer") },
	{ MODKEY,          	        XK_F5,     spawn,          SHCMD("st -e khal interactive") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

