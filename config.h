/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:size=12";
//static const char col_gray1[]       = "#222222";
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
static const char col_gray4[]       = "#4c566a";
//static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#81a1c1";
static const char col_red[]         = "#BF616A";
static const char col_purple[]      = "#bd93f9";
static const char *colors[][3]      = {

	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_red,   col_red   },
};

/* tagging */
static const char *tags[] = { "爵", "", "", "", "", "", "", "", "" };
static const char *alttags[] = { "◆爵", "◆", "◆", "◆", "◆", "◆", "◆", "◆", "◆" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance     title               tags mask     isfloating   monitor */
    { "",               NULL,       NULL,               0,            0,           -1 },
    { "",               NULL,       "floatingterminal", 0,            1,           -1 },
    { "",               NULL,       "pulsemixer",       0,            1,           -1 },
    { "Pavucontrol",    NULL,       NULL,               0,            1,           -1 },
    { "Brave-browser",  NULL,       NULL,               1 << 0,       0,           -1 },
    { "",               NULL,       "Alacritty",        1 << 1,       0,           -1 },
    { "",               NULL,       "ranger",           1 << 2,       0,           -1 },
    { "Zathura",        NULL,       NULL,               1 << 3,       0,           -1 },
    { "Vmware",         NULL,       NULL,               1 << 6,       0,           -1 },
    { "Signal",         NULL,       NULL,               1 << 7,       0,           -1 },
    { "Spotify",        NULL,       NULL,               1 << 8,       0,           -1 },
		//{ "Gimp",         NULL,       NULL,               0,            1,           -1 },
    //{ "Firefox",      NULL,       NULL,               1 << 1,       0,           -1 },
    //{ "st-256color",  NULL,       NULL,               1 << 0,       0,           -1 },
    //{ "Pcmanfm",      NULL,       NULL,               1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /*[> 1 means respect size hints in tiled resizals <]*/
/*static const int resizehints = 0;    [> 1 means respect size hints in tiled resizals <]*/

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "  ",      tile },    /* first entry is default */
	{ "  ",      NULL },    /* no layout function means floating behavior */
	{ "  ",      monocle },
	{ " ﱖ ",      gaplessgrid },
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
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", "-t", "Alacritty", NULL };
static const char *floattermcmd[]  = { "alacritty", "-t", "floatingterminal", NULL };
static const char *ranger[]  = { "alacritty", "-t", "ranger", "-e", "ranger", NULL };
static const char *brave[]  = { "brave-browser", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *logout[]  = { "logout.sh", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                        function        argument */
	{ MODKEY,                       XK_r,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,                 spawn,          {.v = floattermcmd } },
	{ MODKEY,                       XK_backslash,              spawn,          {.v = ranger } },
	{ MODKEY,                       XK_w,                      spawn,          {.v = brave } },
	{ MODKEY,                       XK_Escape,                 spawn,          {.v = slock } },
	{ MODKEY,                       XK_o,                      spawn,          SHCMD("setLayout.sh us") },
	{ MODKEY,                       XK_p,                      spawn,          SHCMD("setLayout.sh \"-layout hu -variant qwerty\"") },
  { 0,                            XF86XK_AudioMute,          spawn,		       SHCMD("pulsemixer --toggle-mute; pkill -RTMIN+2 dwmblocks)") },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,		       SHCMD("pulsemixer --change-volume +3; pkill -RTMIN+2 dwmblocks)") },
  { 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD("pulsemixer --change-volume -3; pkill -RTMIN+2 dwmblocks)") },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,                  zoom,           {0} },
	{ MODKEY,                       XK_Tab,                    view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,                      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_Return,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,                  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,                  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,                  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,                  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                                      0)
	TAGKEYS(                        XK_2,                                      1)
	TAGKEYS(                        XK_3,                                      2)
	TAGKEYS(                        XK_4,                                      3)
	TAGKEYS(                        XK_5,                                      4)
	TAGKEYS(                        XK_6,                                      5)
	TAGKEYS(                        XK_7,                                      6)
	TAGKEYS(                        XK_8,                                      7)
	TAGKEYS(                        XK_9,                                      8)
	//{ MODKEY|ShiftMask,           XK_q,                      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,                      spawn,          {.v = logout } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

