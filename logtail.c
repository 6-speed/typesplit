#if 0
gcc -o logtail logtail.c
return
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/keyboard.h>
#define logtail main
#define VD      void
#define IN      int
#define CH      char
#define CS      CH *
#define RT      return
#define BK      break
#define CT      continue
#define IF      if
#define EF      else if
#define EL      else
#define LP      while (1)
#define LW(p)   while (p)
#define LOG printf
#define BUFFERLEN       128
#include "list.h"
#include "colour.h"
#include "table.h"

//#define LISTBUFFERLEN   65536

IN logtail(IN argc, CH **argv) {
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);
  CH width[10], height[10];
  sprintf(width,  "%d", ws.ws_col);
  sprintf(height, "%d", ws.ws_row);
  setenv("LINES",  height, 1); // still not set
  setenv("COLUMNS", width, 1); // for system
  IN linewidth = atoi(width);
  IN consoleheight = atoi(height);
  // todo: use LINES for scroll feature

  CH codename[BUFFERLEN];
  IN codelen = 0;
  FILE *code = popen("cat run-server.txt | grep FERR: | sed -e 's|.*web-logs/||' -e 's|/stop-error.txt$||'", "r");
  LP {
    IN inch = fgetc(code);
    IF (inch == EOF) { BK; }
    EF (++codelen < BUFFERLEN) {
      codename[codelen - 1] = (CH)inch;
      codename[codelen]     = '\0';
    } EL { BK; }
  }
  pclose(code);
  IF (codename[codelen - 1] == '\n')
    { codename[codelen - 1] = '\0'; }
//  CH logcommand[BUFFERLEN];
  CH logpath[BUFFERLEN];
  sprintf(logpath, "./web-/web-logs/%s/", codename);
  LOG("logpath is %s\n", logpath);
  EMPTYLIST(logfiles);
  LIST *logfilep = &logfiles;
  DIR *dir = opendir(logpath);
  IF (!dir) { LOG("dir not available.\n"); RT 1; }
  struct dirent *entity = readdir(dir);
  LW(entity) {
    CS entname = entity->d_name;
    IF (entity->d_type != DT_REG) {
      IF (entity->d_type == DT_DIR) {
        IF (0 == strcmp(entname, ".") || 0 == strcmp(entname, ".."))
          { }
        EL { LOG("todo: recurse on directories\n"); }
      } EL {
        LOG("todo: detect special files\n");
      }
    } EF (!ADDLISTITEM(logfiles, entity->d_name)) {
      LOG("error adding itemname to filelist\n");
      BK; // stop and close
    } // all continue
    ENDOFLIST(logfilep); // should still be at list end anyway despite additions
    entity = readdir(dir);
  } ; closedir(dir);
//  DISPLAYLIST(logfilep);
  IN tablewidth = linewidth - 2;

  TABLE t = BUILDTABLE(logfilep, tablewidth); // extra -1 for safety


  DISPLAYTABLE(t);


  SETCONSOLESIZE(linewidth, consoleheight);
  SETRESPONSESIZE(tablewidth, t.column[0].itemcount);



  GOTOTOPLEFTXY(2, 2);
  RIGHTLOG("|ARBITRARYOVERWRITE ");
  GOTOBOTTOMLEFTXY(2, 2);
  RIGHTLOG("|ANOTHEROVERWRITE ");
  GOTOTOPRIGHTXY(2, 2);
  LEFTLOG(" TOPRIGHTMESSAGE|");
  GOTOBOTTOMRIGHTXY(2, 2);
  LEFTLOG(" BOTTOMRIGHTMESSAGE|");

  GOTOTOPLEFT();
  RIGHTLOG("X");

  GOTOTOPLEFTXY(1, 1);
  RIGHTLOG("|ARBITRARYOVERWRITE");
  GOTOBOTTOMLEFTXY(1, 1);
  RIGHTLOG("|ANOTHEROVERWRITE");
  GOTOTOPRIGHTXY(1, 1);
  LEFTLOG("TOPRIGHTMESSAGE|");
  GOTOBOTTOMRIGHTXY(1, 1);
  LEFTLOG("BOTTOMRIGHTMESSAGE|");


//  IF (1) RT 0;


  signal(SIGINT, GOTOEXIT);
  UNBLOCKCONSOLE();
  SELECTITEM(t, 3, 3);
  LP {
    IN ch = getc(stdin);
    IF (ch <  0) { SPINCURSOR(); }
    EF (ch == 27) {
      IN ch = getc(stdin);
      IF (ch < 0) { STOPLOG("ESCAPE EXIT"); BK; }
      EF (ch == '[') {
        IN ch = getc(stdin);
        IF (ch < 0) { STOPLOG("BAD ESCAPE SEQUENCE"); BK; }
        EF (ch == 'A') {
          POSTLOG("UP    ");
        } EF (ch == 'B') {
          IF (!ISONLYSHIFTPRESSED()) {
            SELECTNEXTITEM(t);
            POSTLOG("NEXT ITEM");
          } EL { POSTLOG("SELECT NEXT ITEM... TODO"); }
        } EF (ch == 'C') {
          POSTLOG("RIGHT ");
        } EF (ch == 'D') {
          POSTLOG("LEFT  ");
        } EL {
          POSTLOGc("unrecognised escape sequence code %c\n", ch);
        }
      } EL { POSTLOGc("escape sequence char %c\n", ch); }
    } EF (ch < 32) {
      POSTLOGi("received key %d\n", ch);
    } EL {
      POSTLOGc("received key %c\n", ch);
    }
  }
//  LW(read(STDIN_FILENO, &ch, 1) > 0) {
//  }
  RT 0;
}

// columns is still ignored therefore write new program for ls -- maxitemwidth + 2, as many columns as will fit.

//  sprintf(logcommand, "cat ./web-/web-logs$s/" "* | tail -n 100 | rev", codename);
//  sprintf(logcommand, "export COLUMNS=%s ; ls ./web-/web-logs/%s/", width, codename);
//  printf("LOGCOMMAND: %s\n", logcommand);

/*
  CH listbuffer[LISTBUFFERLEN];
  memset(listbuffer, LISTBUFFERLEN, 0);
  IN listbufferlen = 0;
  FILE *list = popen(logcommand, "r");
  LP {
    IN inch = fgetc(list);
    IF (inch == EOF) { BK; }
    EF (++listbufferlen < LISTBUFFERLEN) {
      listbuffer[listbufferlen - 1] = (CH)inch;
      listbuffer[listbufferlen]     = '\0';
    } EL { BK; }
  }
  printf("%s", listbuffer);
*/
//  system("cat ./web-/web-logs/
//$(cat run-server.txt | grep FERR: | sed 's|.*web-logs/||')");

//  RT 0;
//}
