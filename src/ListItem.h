

/***********************************************************************************************
 * OpenGL Window and Animation Library (formerly the Open Art Engine)                          *
 ***********************************************************************************************
 * This software is copyrighted software.  Use of this code is given only with permission to   *
 * parties who have been granted such permission by its author, Herbert Elwood Gilliland III   *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/

#pragma once
#include <string>
using namespace std;
#include "string_functions.h"
#include "macros.h"
#include "ZeroTypes.h"

#define MAX_INT (INT_MAX)

class BinaryFile;
class KeyedDataStore;

class ListItem {
public:
 Zint leashes;
 ListItem *next;
 ListItem *prev;
 ListItem(void) { next=prev=null; }
 virtual ~ListItem() {} // Source: Meyers Effective C++, removed due to vile reprocussions, then re-added due to complaints.
 virtual void Virtual(void) {}
 virtual string identity() { ///RTTI///
  string classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual bool is( const char *named ) {
  string id=identity();
  return ( !str_cmp(id.c_str(),named) );
 }
 void fromString( string in ) { fromString(in.c_str()); }
 virtual void fromString( const char *in ) {
  const char *p=in;
  while ( *p != '\0' ) {
   string key=string("");
   p=string_argument( p, &key );
   p=ParseKey( p, key );
  }
 }
 virtual const char *ParseKey( const char *p, string key ) {
  OUTPUT("ListItem: fromString() called on base class with key `%s`.\n",
   key.c_str() );
  return p;
 }
 virtual string toString() {
  return identity()+string("WARNING: default virtual toString\n");
 }
 virtual void BinaryRead( BinaryFile *open ) {} // read data from an already open binary file (ifstream method)
 virtual void BinaryWrite( BinaryFile *open ) {} // write the data to an already open binary file (ifstream method)
 virtual void KeyedRead( KeyedDataStore *open ) {}
 virtual void KeyedWrite( KeyedDataStore *open ) {}
 bool isAfter( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->next;
   if ( c==this ) return true;
  }
  return false;
 }
 bool isBefore( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->prev;
   if ( c==this ) return true;
  }
  return false;
 }
};


// See HANDLE and related macro options in LinkedList.h
template <class T> class Handle : public ListItem {
public:
 T *p;
 Handle():ListItem(){
  p=null;
 }
// This cannot be done:
// Handle( T *p ) : ListItem() {
//  this->p=p;
// }
 void fromString(char *st) {
  if (p) delete p;
  p=new T;
  p->fromString(st);
 }
 virtual string toString() { 
  if (p) return p->toString();
  else return string("");
 }
};

template <class T>
class NamedHandle : public Handle<T> {
public:
 Zstring name;
 NamedHandle() {}
 NamedHandle( string name ) { this->name=name; }
 NamedHandle( const char *n ) { name=string(n); }
};

void recycle( ListItem *p );
