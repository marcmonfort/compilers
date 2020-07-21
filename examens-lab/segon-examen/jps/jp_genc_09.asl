func ff(n : int): bool
   return n*2 % 3 != 1;
endfunc

func main()
  var a : array [1] of int
  var b : array [1] of bool
  var t : int

  t = 12;
  a[0] = 23*t;

  write a[0];
  write "\n";
  write (t - 4) * (filter a into b using ff + 2);
  write "\n";

  if not b[0] then 
    write "no\n";
  else 
    write "yes\n";
  endif

  a[0] = a[0] + 2;
  
  write (t - 4) * (filter a into b using ff + 2);
  write "\n";

  if b[0] then 
    write "no\n";
  else 
    write "yes\n";
  endif
endfunc
