// Morse Code generator. Feed me text and I will spit out cw.

////// This table based code system is from Mark VandeWettering. His original
////// Comment is below.
// Simple Arduino Morse Beacon
// Written by Mark VandeWettering K6HX
// Email: k6hx@arrl.net
// 
// This code is so trivial that I'm releasing it completely without 
// restrictions.  If you find it useful, it would be nice if you dropped
// me an email, maybe plugged my blog @ http://brainwagon.org or included
// a brief acknowledgement in whatever derivative you create, but that's
// just a courtesy.  Feel free to do whatever.
//
struct t_mtab { char c, pat;  } ;

struct t_mtab morsetab[] = {
  {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;
