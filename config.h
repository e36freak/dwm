/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-13-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#142e56";
static const char normbgcolor[]     = "#142e56";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#ffffff";
static const char selbgcolor[]      = "#184281";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title         tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,         0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,         1 << 0,       False,       -1 },
        { NULL,       NULL,       "Scratchpad", 1 << 4,       True,        -1 },
        { NULL,       NULL,       "Editor",     1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */
static const int nmaster      = 1;    /* Default number of tiles in main area for ntile, nbstack, and ncol */

static const Layout layouts[] = {
	/* symbol     arrange function */
        { "-|=",      ntile }    /* first entry is default */,
        { "-|-",      nbstack },
        { "|||",      ncol },
        { "[@]",      spiral },
        { "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]=",      tile },
        { "TTT",      bstack },
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
static const char *dmenucmd[]   = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { "gnome-terminal", NULL };
static const char *scratcmd[]   = { "gnome-terminal", "-t", "Scratchpad", "--geometry=80x20+190+140", NULL };
static const char *editcmd[]    = { "gnome-terminal", "-t", "Editor", "-e", "vim", NULL };
static const char *browsecmd[]  = { "firefox", NULL };
static const char *chromcmd[]   = { "chromium", NULL };
static const char *filecmd[]    = { "nautilus", "--no-desktop", NULL };
static const char *chatcmd[]    = { "pidgin", NULL };
static const char *musicmd[]    = { "gnome-terminal", "-x", "ncmpcpp", NULL };
static const char *videocmd[]   = { "vlc", NULL };

/* volume control */
static const char *volup[]      = { "setvol", "up", NULL };
static const char *voldown[]    = { "setvol", "down", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scratcmd } },
	{ MODKEY,                       XK_grave,  toggleview,     {.ui = 1 << 4 } },
        { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = editcmd } },
        { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = browsecmd } },
        { MODKEY|ShiftMask|ControlMask, XK_f,      spawn,          {.v = chromcmd } },
        { MODKEY|ShiftMask,             XK_h,      spawn,          {.v = filecmd } },
        { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = chatcmd } },
        { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = musicmd } },
        { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = videocmd } },
        { MODKEY,                       XK_Right,  spawn,          {.v = volup } },
        { MODKEY,                       XK_Left,   spawn,          {.v = voldown } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_x,      setnmaster,     {.i = 2 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[7]} },
        { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[8]} },
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
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

