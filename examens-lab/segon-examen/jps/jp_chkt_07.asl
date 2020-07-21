func esvocal(c : char): bool
   return c=='a' or c=='e' or c=='i' or c=='o' or c=='u';
endfunc

func esmult3(n : int): bool
   return n%3 == 0;
endfunc

func main()
  var ac : array [10] of char
  var bc : array [10] of bool
  var ai : array [20] of int
  var bi : array [20] of bool

  var s,t : int

  s = filter ac into bc using esvocal;
  
  t = s*2 - (filter ac into bi using esvocal) * 5;

  if filter ac into bc using esmult3 then
     s = 4 * (filter ac into bi using esmult3 + 1);
  endif

  ac = filter s into t using r;
endfunc
