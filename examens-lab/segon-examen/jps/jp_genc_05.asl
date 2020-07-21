func fusio(ai : array [10] of int,
           af : array [10] of float) : float
  var j,k : int
  var s : float

  j = 0;
  s = 0;
  while j<10 do
     s = sum(s, ai[j]);
     if j<9 then k = ai[j+1];
     else if j>0 then k = ai[j-1];
     else k = -4;
     endif
     endif
     s = sum(s, af[j], k);
     write s; write "\n";
     j = j+1;
  endwhile
  
  return s;  
endfunc

func main()
  var i,z : int
  var a : array [10] of int
  var b : array [10] of float
  var x : float
  var c,d : char

  i = 0;
  while i<10 do
    a[i] = 2*i + 1;
    b[10-i] = sum(3*i, -1);
    i = i + 1;
  endwhile

  i = 0;
  while i<10 do
    write b[i]; write " ";
    i = i + 1;
  endwhile
  write "\n";

  write fusio(a,b);  write "\n";
endfunc
