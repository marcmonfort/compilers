func esvocal(c : char): bool
   return c=='a' or c=='e' or
          c=='i' or c=='o' or c=='u';
endfunc

func esmult3(n : int): bool
   return n%3 == 0;
endfunc

func main()
  var ac : array [20] of char
  var bc : array [20] of bool
  var ai : array [10] of int
  var bi : array [10] of bool
  var i,n,s,t : int

  // fill arrays ac and ai
  i = 0;
  while i<10 do
     read ai[i];
     read ac[2*i];
     read ac[2*i+1];
     i = i + 1;
  endwhile

  // use filter on the arrays,
  // with changing contents
  n = 0;
  while n<10 do
    s = filter ac into bc using esvocal;
    t = s*2 - filter ai into bi using esmult3*5;
    write s; write " "; write t; write "\n";

    // change array content for next iteration
    ai[n] = 33 * s - 10;
    if t%2 == 0 then
       ac[2*n] = 'k'; ac[2*n+1] = 'x';
    else
       ac[2*n]='e'; ac[2*n+1] = 'o';
    endif
    n = n + 1;
  endwhile

  if s>t then write "bad\n";
  else write "very good\n";
  endif
endfunc
