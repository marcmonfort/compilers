func ff(n : int): bool
   return true;
endfunc

func main()
  var a : array [1] of int
  var b : array [1] of bool
  var t : int

  a[0] = 23;
  t = 12;

  write a[0];
  write "\n";
  write t + filter a into b using ff * 3;
  write "\n";

  if b[0] then 
    write "yes\n";
  endif
endfunc
