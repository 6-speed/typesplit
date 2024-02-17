typedef struct _List {
  IN itemnumber; // NULL item maintains a count
  CH itemname[BUFFERLEN];
  CH itemcolour;
  struct _List *previtem;
  struct _List *nextitem;
} LIST;

#define EMPTYLIST(listname)    LIST listname;               \
                               listname.itemnumber = 0;     \
                               listname.itemname[0] = '\0'; \
                               listname.itemcolour = 0;     \
                               listname.nextitem = NULL;    \
                               listname.previtem = NULL;

LIST *ADDALPHABETICLISTITEM(LIST *listname, CS itemname) {
  LW(listname->nextitem)    // start at end of list
    { listname = listname->nextitem; }
  IF (listname->itemname[0] != '\0') { LOG("no null item!\n"); RT NULL; } // no action
  LIST *nullitem = listname;
  LW(listname->previtem) {  // find alphabetical location
//    LOG("itemname is %s\n", itemname);
//    LOG("previtemname is %s\n", listname->previtem->itemname);
    IN compare = strcmp(listname->previtem->itemname, itemname);
    IF (!compare) { LOG("duplicated filename!\n"); RT NULL; } // memory not allocated
    EF (compare > 0) { // itemname is less
      listname = listname->previtem;
    } EL { BK; } // itemname is not less
  } // allocate, and append or insert



#define EMPTYLIST(listname)    LIST listname;               \
                               listname.itemnumber = 0;     \
                               listname.itemname[0] = '\0'; \
                               listname.itemcolour = 0;     \
                               listname.nextitem = NULL;    \
                               listname.previtem = NULL;

  LIST *newitem = (LIST *)malloc(sizeof(LIST));
  IF (!newitem) { LOG("list memory error!\n"); RT NULL; } // memory not allocated
  newitem->itemnumber = (nullitem->itemnumber + 1); // no +1 if lists start at 0 (they don't)
  sprintf(newitem->itemname, "%s", itemname);
//  IF (listname->nextitem) { // insert before, not append
  newitem->nextitem = listname;           // set this next to existing item
  IF ((newitem->previtem = listname->previtem)) // may be NULL (if start of list), or may not
    { newitem->previtem->nextitem = newitem; }  // if not, set its next to this
  newitem->nextitem->previtem = newitem;  // set next item prev to this
//  } EL { // append -- this listname->itemname should be "\0"
//    newitem->nextitem = listname; // point to NULL entry (todo: include item counter)
//    IF ((newitem->previtem = listname->previtem)) // may be NULL (if start of list), or may not
//      { newitem->previtem->nextitem = newitem; }  // if not, set its next to this
//    newitem->nextitem->previtem = newitem;        // set NULL item prev to this
//  } // insert and append have the same operation
  nullitem->itemnumber = newitem->itemnumber; // + 1 if lists start at 0 (they don't)
  RT newitem;
} // (but matrices do)
// ADDALPHABETICLISTITEM works from anywhere in the list and returns the new item
// ADDLISTITEM returns true if an item was added, false if not. it cannot iterate
// the list without a temporary storage variable for the result of ADDALPHABETICLISTITEM
#define ADDLISTITEM(listname, itemname) \
  (ADDALPHABETICLISTITEM(&listname, itemname) ? 1 : 0)
#define ENDOFLIST(listname)   \
  LW(listname->nextitem)      \
    { listname = listname->nextitem; }
#define STARTOFLIST(listname) \
  LW(listname->previtem)      \
    { listname = listname->previtem; }
#define DISPLAYLIST(listname) \
  STARTOFLIST(listname)       \
  LOG("TEST\n"); \
  LW(listname->nextitem) {    \
    IF (listname->itemname[0] == '\0') { LOG("NULL ENTRY\n"); } \
    EL { LOG("ITEM: %s\n", listname->itemname); }               \
    listname = listname->nextitem;                              \
  }
// ENDOFLIST, STARTOFLIST and DISPLAYLIST require a LIST *item pointer. ADDLISTITEM does not.
// it can point anywhere in the list -- todo: DISPLAYSUBLIST and DISPLAYLISTITEM and DISPLAYLISTRANGE
LIST *LISTITEM(LIST *referenceitem, IN offset) {
  IF (!referenceitem) { RT NULL; }
  LW(offset < 0) {
    referenceitem = referenceitem->previtem;
    IF (!referenceitem) { RT NULL; }
    offset++;
  }
  LW(offset > 0) {
    referenceitem = referenceitem->nextitem;
    IF (!referenceitem) { RT NULL; }
    offset--;
  }
  RT referenceitem; //->itemname;
}

LIST *INSERTDIVIDER(LIST *referenceitem) {
  IF (!referenceitem) { RT NULL; }
  // need width of current column but what if first in list for this column ??




#define EMPTYLIST(listname)    LIST listname;               \
                               listname.itemnumber = 0;     \
                               listname.itemname[0] = '\0'; \
                               listname.itemcolour = 0;     \
                               listname.nextitem = NULL;    \
                               listname.previtem = NULL;

  LIST *newitem = (LIST *)malloc(sizeof(LIST));
  IF (!newitem) { LOG("list memory error!\n"); RT NULL; } // memory not allocated
  newitem->itemnumber = 0; // zero item until otherwise specified
  CS itemname =

  sprintf(newitem->itemname, "%s", itemname);
//  IF (listname->nextitem) { // insert before, not append
  newitem->nextitem = listname;           // set this next to existing item
  IF ((newitem->previtem = listname->previtem)) // may be NULL (if start of list), or may not
    { newitem->previtem->nextitem = newitem; }  // if not, set its next to this
  newitem->nextitem->previtem = newitem;  // set next item prev to this
//  } EL { // append -- this listname->itemname should be "\0"
//    newitem->nextitem = listname; // point to NULL entry (todo: include item counter)
//    IF ((newitem->previtem = listname->previtem)) // may be NULL (if start of list), or may not
//      { newitem->previtem->nextitem = newitem; }  // if not, set its next to this
//    newitem->nextitem->previtem = newitem;        // set NULL item prev to this
//  } // insert and append have the same operation
  nullitem->itemnumber = newitem->itemnumber; // + 1 if lists start at 0 (they don't)
  RT newitem;




}

