#define OFFC                    "\033[0m"
#define RFGC                    "\033[1;31m"
#define YFGC                    "\033[1;33m"
#define GFGC                    "\033[1;32m"
#define CFGC                    "\033[1;36m"
#define BFGC                    "\033[1;34m"
#define MFGC                    "\033[1;35m"
#define KFGC                    "\033[0;30m"
#define DFGC                    "\033[1;30m"
#define LFGC                    "\033[0;37m"
#define WFGC                    "\033[1;37m"
#define WHITEFG  LOG(WFGC)
#define DRFGC                   "\033[0;31m"
#define DYFGC                   "\033[0;33m"
#define DGFGC                   "\033[0;32m"
#define DCFGC                   "\033[0;36m"
#define DBFGC                   "\033[0;34m"
#define DMFGC                   "\033[0;35m"
#define NUMCOLOURS    12

//#define CYANFOREGROUND  "\033[38;5;45m"
//#define CYANFG          LOG(CYANFOREGROUND)
#define CYANFG          LOG(CFGC)

#define RBGC            "\033[41m"
#define REDBG           LOG(RBGC)
#define YBGC            "\033[43m"
#define YELLOWBG        LOG(YBGC)
#define GBGC            "\033[42m"
#define GREENBG         LOG(GBGC)
#define CBGC            "\033[46m"
#define CYANBG          LOG(CBGC)
#define BBGC            "\033[44m"

//#define FC3BACKGROUND   "\033[48;5;220m"
//#define FC3BG           LOG(FC3BACKGROUND)

#define BLUEBG          LOG(BBGC)
#define FC3BG           BLUEBG

#define MBGC            "\033[45m"
#define MAGENTABG       LOG(MBGC)
#define KBGC            "\033[40m"
#define BLACKBG         LOG(KBGC)
#define WBGC            "\033[47m"
#define WHITEBG         LOG(WBGC)
#define NBGC            "\033[0m"
#define CLEARBG         LOG(NBGC)
#define CLS             "\033[2J"
#define CLEARSCREEN     LOG(CLS)

//CH flag1value = '\0';
//CH flag2value = '\0';
//IN colourindex = 0;
//CH colourchar = '-';
//VD LOGCOLOUR(CH flag1, CH flag2) {
//  IF (flag1 != flag1value || flag2 != flag2value) {
//    flag1value = flag1;
//    flag2value = flag2; // update flags
//    colourindex++;
//  }
//  IF (colourindex >= NUMCOLOURS) {
//    colourindex = 0;
//  }
VD LOGCOLOURBLOCK(CH colourindex, IN selectedblock) {
  CH colourchar = '@';
  IF (selectedblock) {
    colourindex = ((colourindex - 1) * 6) + 1; // no/only dark backgrounds
    IF (colourindex ==  0) { LOG("%s%c%s",  WBGC, BFGC, colourchar, OFFC); }
    IF (colourindex ==  1) { LOG("%s%c%s",  RBGC, BFGC, colourchar, OFFC); }
    EF (colourindex ==  2) { LOG("%s%c%s",  YBGC, BFGC, colourchar, OFFC); }
    EF (colourindex ==  3) { LOG("%s%c%s",  GBGC, BFGC, colourchar, OFFC); }
    EF (colourindex ==  4) { LOG("%s%c%s",  CBGC, BFGC, colourchar, OFFC); }
    EF (colourindex ==  5) { LOG("%s%c%s",  BBGC, BFGC, colourchar, OFFC); }
    EF (colourindex ==  6) { LOG("%s%c%s",  MBGC, BFGC, colourchar, OFFC); }
  } EL {
    IF (colourindex ==  0) { LOG("%s%c%s",  LFGC, colourchar, OFFC); }
    IF (colourindex ==  1) { LOG("%s%c%s",  RFGC, colourchar, OFFC); }
    EF (colourindex ==  2) { LOG("%s%c%s",  YFGC, colourchar, OFFC); }
    EF (colourindex ==  3) { LOG("%s%c%s",  GFGC, colourchar, OFFC); }
    EF (colourindex ==  4) { LOG("%s%c%s",  CFGC, colourchar, OFFC); }
    EF (colourindex ==  5) { LOG("%s%c%s",  BFGC, colourchar, OFFC); }
    EF (colourindex ==  6) { LOG("%s%c%s",  MFGC, colourchar, OFFC); }
    EF (colourindex ==  7) { LOG("%s%c%s", DRFGC, colourchar, OFFC); }
    EF (colourindex ==  8) { LOG("%s%c%s", DYFGC, colourchar, OFFC); }
    EF (colourindex ==  9) { LOG("%s%c%s", DGFGC, colourchar, OFFC); }
    EF (colourindex == 10) { LOG("%s%c%s", DCFGC, colourchar, OFFC); }
    EF (colourindex == 11) { LOG("%s%c%s", DBFGC, colourchar, OFFC); }
    EF (colourindex == 12) { LOG("%s%c%s", DMFGC, colourchar, OFFC); }
    EL                     { LOG("%s%c%s",  DFGC, colourchar, OFFC); }
  }
}


// A for ASCII Char Code .. K for Kernel Code String
#define Kmoveup      "\033[A"
#define Kmovedown    "\033[B"
#define Kmoveleft    "\033[D"
#define Kmoveright   "\033[C"
#define MOVEUP(n)     n ? fprintf(stdout, "\033[%dA", n) : 0;
#define MOVEDOWN(n)   n ? fprintf(stdout, "\033[%dB", n) : 0;
//#define MOVETOSOL     fprintf(stdout, "\n\033[1A");
//#define MOVETOEOL     fprintf(stdout, "\n\033[1D");
#define LINEBREAK(w)  fprintf(stdout, "\033[%dD\033[1B", w);
#define MOVERIGHT(n)  n ? fprintf(stdout, "\033[%dC", n) : 0;
#define MOVELEFT(n)   n ? fprintf(stdout, "\033[%dD", n) : 0;
#define SETCHAR(c)    fprintf(stdout, "%c\033[1D", c);
#define WRITECHAR(c)  fprintf(stdout, "%c", c);
#define LWRITECHAR(c) fprintf(stdout, "%c\033[2D", c);
#define FLUSHBUFFER   LOG0
#define CLEARLINE     fprintf(stdout, "\033[2K");
#define FRESHENLINE   fprintf(stdout, "\033[K");
// http://linux.about.com/library/cmd/blcmdl4_console_codes.htm
// www.systutorials.com/docs/linux/man/4-console_codes/
#define MOVETO(x,y)   fprintf(stdout, "\033[%d;%dH", y, x)
#define MOVETOX(x)    fprintf(stdout, "\033[%dG", x)
#define GOTOCOL(x)    MOVETOX(x)
#define SAVEPOS       fprintf(stdout, "\033[s")
#define RESTOREPOS    fprintf(stdout, "\033[u")

IN MOVECURSORDOWN(IN n)  { IF (n < 0) { MOVEUP(n);    } EL { MOVEDOWN(n);  } }
IN MOVECURSORUP(IN n)    { IF (n < 0) { MOVEDOWN(n);  } EL { MOVEUP(n);    } }
IN MOVECURSORLEFT(IN n)  { IF (n < 0) { MOVERIGHT(n); } EL { MOVELEFT(n);  } }
IN MOVECURSORRIGHT(IN n) { IF (n < 0) { MOVELEFT(n);  } EL { MOVERIGHT(n); } }

IN hereposx = 0;
IN hereposy = 0;
IN consolewidth = 0;
IN consoleheight = 0;
IN responsewidth = 0;
IN responseheight = 0;
// consider scroll offsets
VD SETCONSOLESIZE(IN width, IN height) {
  consolewidth = width;
  responsewidth = consolewidth;
  consoleheight = height;
  responseheight = consoleheight;
}
VD SETRESPONSESIZE(IN width, IN height) {
  responsewidth = width;
  IF (!consolewidth)
    { consolewidth = responsewidth; }
  responseheight = height;
  IF (!consoleheight)
    { consoleheight = responseheight; }
  // assume line break at end of response for prompt row, move to bottom left
  hereposx = 0; // assume bottom left cursor location
  MOVEUP(1);    // after the final linebreak of the table
  hereposy = responseheight - 1; // -1 because MOVEUP(1) !
}
VD GOTOTOPLEFTXY(IN xoff, IN yoff) {
  IF (responseheight) { MOVECURSORUP(hereposy);                        }
  IF (responsewidth)  { MOVECURSORLEFT(hereposx);  } // responsewidth - 1 - hereposx);  }
  MOVECURSORDOWN(yoff);
  MOVECURSORRIGHT(xoff);
  hereposx = 0 + xoff;
  hereposy = 0 + yoff;
}
VD GOTOTOPRIGHTXY(IN xoff, IN yoff) {
  IF (responseheight) { MOVECURSORUP(hereposy);                        }
  IF (responsewidth)  { MOVECURSORRIGHT(responsewidth - 1 - hereposx); }
  MOVECURSORDOWN(yoff);
  MOVECURSORLEFT(xoff);
  hereposx = responsewidth - 1 - xoff;
  hereposy = 0 + yoff;
}
VD GOTOBOTTOMLEFTXY(IN xoff, IN yoff) {
  IF (responseheight) { MOVECURSORDOWN(responseheight - 1 - hereposy); }
  IF (responsewidth)  { MOVECURSORLEFT(hereposx);                      }
  MOVECURSORUP(yoff);
  MOVECURSORRIGHT(xoff);
  hereposx = 0 + xoff;
  hereposy = responseheight - 1 - yoff;
}

VD GOTOBOTTOMRIGHTXY(IN xoff, IN yoff) {
  IF (responseheight) { MOVECURSORDOWN(responseheight - 1 - hereposy); }
  IF (responsewidth)  { MOVECURSORRIGHT(responsewidth - 1 - hereposx); }
  MOVECURSORUP(yoff);
  MOVECURSORLEFT(xoff);
  hereposx = responsewidth  - 1 - xoff;
  hereposy = responseheight - 1 - yoff;
}

#define GOTOTOPLEFT()      GOTOTOPLEFTXY(0, 0)
#define GOTOTOPRIGHT()     GOTOTOPRIGHTXY(0, 0)
#define GOTOBOTTOMLEFT()   GOTOBOTTOMLEFTXY(0, 0)
#define GOTOBOTTOMRIGHT()  GOTOBOTTOMRIGHTXY(0, 0)

struct termios CONSOLEPARAMS;

VD RESETCONSOLE() {
  tcsetattr(STDIN_FILENO, TCSANOW,   &CONSOLEPARAMS);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &CONSOLEPARAMS);
}

VD UNBLOCKCONSOLE() {
  struct termios newparams;
  tcgetattr(STDIN_FILENO, &CONSOLEPARAMS);
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  newparams = CONSOLEPARAMS;
  newparams.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newparams);
  atexit(RESETCONSOLE);
}

#define CURSORDELAY 100000
CH CURSORVALUE = '\0';
CH CURSORCOLOUR = 0;
CH CURSORSELECTED = 0;
CH CURSORWIDTH = 0;
VD QUICKSPINCURSOR() {
  IF (!CURSORVALUE       ) { CURSORVALUE = '/'  ; }
  EF (CURSORVALUE == '/' ) { CURSORVALUE = '-'  ; }
  EF (CURSORVALUE == '-' ) { CURSORVALUE = '\\' ; }
  EF (CURSORVALUE == '\\') { CURSORVALUE = '|'  ; }
  EF (CURSORVALUE == '|' ) { CURSORVALUE = '/'  ; }
  CURSORCOLOUR = (CURSORCOLOUR % 4) + 1;
  IF (CURSORSELECTED) { BLUEBG;  }
  LOG("%c", CURSORVALUE);
  MOVELEFT(1);
  IF (CURSORSELECTED) { CLEARBG; }
  IF (CURSORWIDTH) {
    MOVERIGHT(CURSORWIDTH);
    IF (CURSORSELECTED) { BLUEBG;  }
    LOG("%c", CURSORVALUE);
    IF (CURSORSELECTED) { CLEARBG; }
    MOVELEFT(CURSORWIDTH + 1);
  }
//  MOVELEFT(2);
}

VD SPINCURSOR() {
  QUICKSPINCURSOR();
  usleep(CURSORDELAY);
}

IN POSTPUSHX = 0;
IN POSTPUSHY = 0;
VD GOTOPOST() {
  POSTPUSHX = hereposx;
  POSTPUSHY = hereposy;
  GOTOBOTTOMLEFT();
//LOG("BOTTOMLEFTISHERE");
  MOVEDOWN(1);
}

VD POSTRETURN() {
  FRESHENLINE; // saves including for every log function
  MOVEUP(1);
  LOG("\n");
//  MOVETOSOL;
  MOVEUP(1);
//  GOTOBOTTOMRIGHT();
  GOTOTOPLEFT();
  MOVECURSORDOWN(POSTPUSHY);
  MOVECURSORRIGHT(POSTPUSHX);
  hereposx = POSTPUSHX;
  hereposy = POSTPUSHY;
}

VD POSTLOG(CS str) {
  GOTOPOST();
  LOG(str); // expect no \n
  POSTRETURN();
  QUICKSPINCURSOR();
}

VD POSTLOGs(CS str, CS v1) {
  GOTOPOST();
  LOG(str, v1); // expect no \n
  POSTRETURN();
  QUICKSPINCURSOR();
}

VD POSTLOGc(CS str, CH v1) {
  GOTOPOST();
  LOG(str, v1); // expect no \n
  POSTRETURN();
  QUICKSPINCURSOR();
}

VD POSTLOGi(CS str, IN v1) {
  GOTOPOST();
  LOG(str, v1); // expect no \n
  POSTRETURN();
  QUICKSPINCURSOR();
}

VD STOPLOG(CS str) {
  GOTOPOST();
  LOG(str); // expect no \n
  FRESHENLINE; // keep fresh
  LOG("\n");
} // no return

VD RIGHTLOG(CS msg) {
  LOG("%s", msg); // no \n
  MOVECURSORLEFT(strlen(msg));
}

VD LEFTLOG(CS msg) {
  MOVECURSORLEFT(strlen(msg) - 1);
  LOG("%s", msg); // no \n
  MOVECURSORLEFT(1); // 1 pad olumn required
}

VD GOTOEXIT(IN signum) {
  STOPLOG("CTRL+C EXIT");
  exit(0);
}

IN MODIFIERPRESSED() {
  CH shiftstate = 6;
  IF (ioctl(0, TIOCLINUX, &shiftstate) < 0) {
    fprintf(stdout, "\033[17~");

    IN inch = getc(stdin);
    LOG("KEY DETECTED: %d\n", inch);
// check for a 2;~ or a ~


//    RT 0;
    // TODO: SEND F6 TO CONSOLE

//    STOPLOG("IOCTL SHIFTSTATE FAIL");
//    exit(0);
  } EL { RT shiftstate; }
}

#define ISSHIFTPRESSED()      (MODIFIERPRESSED() |  (1 << KG_SHIFT))
#define ISONLYSHIFTPRESSED()  (MODIFIERPRESSED() == (1 << KG_SHIFT))
