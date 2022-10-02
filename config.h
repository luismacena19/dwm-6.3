/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          	 = { "Terminus:size=14" };
static const char dmenufont[]       	 =	 "Terminus:size=14"  ;
static const char lu_chan[]       	 	 = "lu_chan_:";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       	 = "#000000";
static const char col_rich_black[]  	 = "#010203"; 
static const char col_arch_blue[]   	 = "#1793d1";
static const char col_red_wine[]    	 = "#910c1b";
static const char col_brilliant_white[]  = "#edf1ff";
static const char col_gray_black[]       = "#0d1719";
static const char col_new_bridge[]		 = "#006c7f";
static const char *colors[][3]      = {
	/*               fg         bg			  	 border		
	[SchemeNorm] = { col_gray3, col_gray_black,  col_gray2 },*/
	/*[SchemeNorm] = { col_gray3, col_rich_black,  col_gray2 },*/
	[SchemeNorm] = { col_gray3, col_rich_black,  col_gray2 },
	[SchemeSel]  = { col_gray4, col_rich_black,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      					instance    title       			tags mask     		isfloating   monitor */
	{ "Gimp",     					NULL,       NULL,       			0,            		1,           -1 },
	{ "firefox",				   "Toolkit",  "Picture-in-Picture",	0,					1,           -1 },
	{ "Onboard",         			NULL,       NULL,       			0,					1,           -1 },
	{ "PacketTracer",     			NULL,       "Cisco Packet Tracer",  0,            		1,			 -1  },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define XF86AudioMicMute			0x1008ffb2
#define XF86AudioMute				0x1008ff12
#define XF86AudioLowerVolume		0x1008ff11
#define XF86AudioRaiseVolume		0x1008ff13
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
static const char *dmenucmd[] 			= { "dmenu_run", "-m", dmenumon,"-p", lu_chan, "-fn", dmenufont, "-nb", col_rich_black, NULL };
static const char *termcmd[]            = { "xterm", NULL };
static const char *termuxcmd[]          = { "xfce4-terminal", NULL };
static const char *lockcmd[]            = { "i3lock-fancy", NULL };
static const char *browsercmd[]         = { "browser_chooser", NULL };
static const char *filecmd[]            = { "pcmanfm",  NULL };
static const char *cmdsoundup[]         = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *cmdsounddown[]       = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *cmdsoundtoggle[] 	= { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *cmdmictoggle[] 	    = { "amixer", "set", "Capture", "toggle", NULL };
static const char *cmdluzup[]			= { "xbacklight", "-inc",  "10", NULL };
static const char *cmdluzdown[]			= { "xbacklight", "-dec", "10", NULL };
static const char *cmdmonitor[]			= { "tela", NULL };
static const char *cmdcafeina[]			= { "cafeina.sh", NULL };
static const char *cmdscreenshot[]		= { "xfce4-screenshooter", NULL };
static const char *cmdclip[]			= { "clipmenu", "-fn", dmenufont, "-nb", col_rich_black, NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			            XK_Print,  spawn,          {.v = cmdscreenshot } },
	{ MODKEY,			            XK_p,      spawn,          {.v = cmdclip } },
	{ MODKEY,                       XK_Up,     spawn,          {.v = cmdluzup } },
	{ MODKEY,			            XK_c,      spawn,          {.v = cmdcafeina } },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = cmdmonitor } },
	{ MODKEY,                       XK_Down,   spawn,          {.v = cmdluzdown } },
	{ MODKEY,                       XK_Right,  spawn,          {.v = cmdsoundup } },
	{ MODKEY,                       XK_Left,   spawn,          {.v = cmdsounddown } },
    { MODKEY,                       XK_End,    spawn,          {.v = cmdsoundtoggle } },
    { MODKEY,                       XK_Home,   spawn,          {.v = cmdmictoggle } },
    { 0,                            XF86AudioMute,             spawn,          {.v = cmdsoundtoggle } },
	{ 0,                            XF86AudioRaiseVolume,      spawn,          {.v = cmdsoundup } },
	{ 0,                            XF86AudioLowerVolume,      spawn,          {.v = cmdsounddown } },
	{ 0,                       		XF86AudioMicMute,   spawn,          {.v = cmdmictoggle } },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termuxcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_equal,  setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

