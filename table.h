
typedef struct _Column {
  LIST *firstitem;
  LIST *lastitem;
  IN itemcount;
  IN columnwidth;
} COLUMN;

#define MAXCOLUMNS 100
typedef struct _Table {
  COLUMN column[MAXCOLUMNS];
  IN numcolumns;
  IN selectedrow;
  IN selectedcolumn;
} TABLE;



#define COLUMNPAD  3
TABLE BUILDTABLE(LIST *list, IN linewidth) {
  ENDOFLIST(list);
  IN itemcount = list->itemnumber;
  STARTOFLIST(list);
  IN minlen = linewidth; // if the minimum length is greater than line width, expect the unexpected
  CH colourflag1 = '\0';
  CH colourflag2 = '\0';
  CH colourindex = 0;
  LW(list->nextitem) {
    CS name = list->itemname;
    IN namelen = strlen(name);
    IF (namelen < minlen) { minlen = namelen; }
    IF (namelen > 9 && name[4] == '.' && name[7] == '.') {
      IF (daycolourflag1 != name[8] || daycolourflag2 != name[9]) {
        daycolourflag1 = name[8];
        daycolourflag2 = name[9];
        IF (++daycolourindex > NUMCOLOURS) { daycolourindex = 1 + monthcolourindex; } // loop
      } // EL colour stays the same
    } // day change and month change will both happen at same transition
    IF (namelen > 9 && name[4] == '.' && name[7] == '.') {
      IF (monthcolourflag1 != name[5] || monthcolourflag2 != name[6]) {
        monthcolourflag1 = name[5];
        monthcolourflag2 = name[6];
        LIST *monthline = INSERTDIVIDER(list);
        monthline->itemnumber = 100 + monthcolourindex;
        IF (++monthcolourindex > NUMCOLOURS) { monthcolourindex = 1; } // loop
      } // EL not a month transition
    }
    list->itemcolour = colourindex;
    list = list->nextitem;
  }
  IN maxcols = linewidth / minlen;
  IN numrows = itemcount / maxcols;
  TABLE t;
  t.numcolumns = 0;
  IN totalwidth = 0; // cannot exceed linewidth; increment rows until everything fits
  STARTOFLIST(list);
  IN columnlen = 0;
  IN columnwidth = minlen + COLUMNPAD;
  LIST *columnstart = list;
  LW(list->nextitem) { // last item may not be at end of last column
    IN namelen = strlen(list->itemname);
    IF (namelen + COLUMNPAD > columnwidth) { columnwidth = namelen + COLUMNPAD; } // expect to run out of columns !
    LIST *nextnextitem = list->nextitem->nextitem;
    IF (++columnlen == numrows || !nextnextitem) {
      t.column[t.numcolumns].firstitem = columnstart;
      t.column[t.numcolumns].lastitem = list;
      t.column[t.numcolumns].itemcount = columnlen;
      t.column[t.numcolumns].columnwidth = columnwidth;
      t.numcolumns++;
      IF ((totalwidth += columnwidth) > linewidth) { // start again
        ++numrows; // increment rows until everything fits
        t.numcolumns = 0;
        STARTOFLIST(list);
        totalwidth = 0;
        columnstart = list;
        columnlen = 0;
        columnwidth = minlen + COLUMNPAD;
        CT; // skip the nextitem increment
      } //EL {
      columnstart = list->nextitem; // } // or just start a new column
      columnlen = 0;
      columnwidth = minlen + COLUMNPAD;
    }
    list = list->nextitem;
  }
  RT t;
}

VD DISPLAYCOLUMN(CS itemname, IN columnwidth, CH itemcolour, IN selectedblock, IN selectedname) {
  IN itemlen = strlen(itemname);
//  LOGCOLOUR(itemname[8], itemname[9]);
  IF (selectedname) { WHITEBG; } // behind colour block
  LOGCOLOURBLOCK(itemcolour, selectedblock);
  IF (selectedname) { FC3BG; CYANFG; }  // after colour block
  IN x = -1;
  LW(++x < itemlen)
    { LOG("%c", itemname[x]); }
  LW(++x < columnwidth - 1) // +1 due to extra increment from previous loop
    { LOG(" "); }           // balanced by extra colour char
  IF (selectedname) { CLEARBG; }
  LOG(" "); // last space has no highlight
}

VD DISPLAYTABLEDATA(TABLE *t) {
  IF (t->numcolumns < 1) { RT; } // no table
  IN r = -1; // rows start at 1 for listing but not in cursor logic
  IN c = -1; // columns start at 0 for addressing
  IN rmax = t->column[0].itemcount;
  LW(++r < rmax) {
    LW(++c < t->numcolumns) {
      IN colwidth = t->column[c].columnwidth;
      IF (c + 1 == t->numcolumns) {
        IF (r < t->column[c].itemcount) {
          LIST *item = LISTITEM(t->column[c].firstitem, r);
          DISPLAYCOLUMN(item->itemname, colwidth, item->itemcolour, 0, 0);
        } EL { DISPLAYCOLUMN("-----", colwidth, 0, 0, 0); }
      } EL { // expect an item
        LIST *item = LISTITEM(t->column[c].firstitem, r);
        DISPLAYCOLUMN(item->itemname, colwidth, item->itemcolour, 0, 0);
      }
    }
    c = -1;    // reset column index for next row
    LOG("\n"); // line break after each row
  }
}
#define DISPLAYTABLE(table)  DISPLAYTABLEDATA(&table)

VD SELECTDATAITEM(TABLE *t, IN columnix, IN rowix, IN nameselected) {
  // consider feedback in cases of bad row or bad column
  IF (columnix < 0 || columnix >= t->numcolumns) { RT; } // bad column
  IN numitems = t->column[columnix].itemcount;
  IF (rowix    < 0 || rowix    >= numitems     ) { RT; } // bad row
// MOVESELECTORRIGHT() needs to jump up on last column
  GOTOTOPLEFT();
  IN herex = 0;
  IN herey = rowix;
  MOVEDOWN(rowix);
  IN col = -1;
  LW(++col < columnix) {
    IN colwidth = t->column[col].columnwidth;
    MOVERIGHT(colwidth);
    herex += colwidth;
  }
  IN colwidth = t->column[columnix].columnwidth;
  LIST *item = LISTITEM(t->column[columnix].firstitem, rowix);
// if the selected item is in the same set as an unselect, then the block is selected
// need to overwrite whole block sets anyway so unselect and reselect for now
  DISPLAYCOLUMN(item->itemname, colwidth, item->itemcolour, 0, nameselected);
  MOVELEFT(2);
  CURSORSELECTED = 0; // first draw is unselected, then reselect to double-draw
  CURSORWIDTH = 0;    // don't double draw the first draw
  QUICKSPINCURSOR();
  MOVELEFT(colwidth - 2);
  hereposx = herex;
  hereposy = herey;
  CURSORSELECTED = 1;
  CURSORWIDTH = colwidth - 2;
  t->selectedrow = rowix;
  t->selectedcolumn = columnix;
//  LOG("\n");
//  MOVEUP(rowix + 1);
//  GOTOBOTTOMRIGHT();
}
#define UNSELECTDATAITEM(tablep, colix, rowix)  SELECTDATAITEM(tablep, colix, rowix, 0)
#define DOSELECTDATAITEM(tablep, colix, rowix)  SELECTDATAITEM(tablep, colix, rowix, 1)
#define SELECTITEM(table, column, row)    DOSELECTDATAITEM(&table, column - 1, row - 1)
#define UNSELECTITEM(table, column, row)  UNSELECTDATAITEM(&table, column - 1, row - 1)

VD SELECTNEXTDATAITEM(TABLE *t) {
  IN rowix = t->selectedrow;
  IN columnix = t->selectedcolumn;
  UNSELECTDATAITEM(t, columnix, rowix); // still the selected index
  IN numitems = t->column[columnix].itemcount;
  IN numcolumns = t->numcolumns;
  IF (rowix + 1 >= numitems) {
    IF (columnix + 1 >= numcolumns) {
      t->selectedcolumn = columnix = 0;
      t->selectedrow    = rowix    = 0;
    } EL {
      t->selectedcolumn = columnix = columnix + 1;
      t->selectedrow    = rowix    = 0;
    }
  } EL { t->selectedrow = rowix = rowix + 1; }
  DOSELECTDATAITEM(t, columnix, rowix);
}

VD SELECTPREVITEM(TABLE *t) {

}

VD SELECTNEXTCOLUMN() {

}

VD SELECTPREVCOLOUMN() {

}

#define SELECTNEXTITEM(table)  SELECTNEXTDATAITEM(&table)
