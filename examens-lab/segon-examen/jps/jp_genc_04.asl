func main()
  var n,i,z : int
  var a : array [9] of int

  n = 0;
  while n<3 do
     i = 0;
     while i<9 do
       read a[i];
       i = i + 1;
     endwhile
  
     z = sum(a[4]*a[1], a[7]*(1+a[0]), a[3]*4);
     i = 0;
     while i<9-1 do
        write sum(i);
        write " ";
        write sum(a[i], 1, -1);
        write " ";
        write sum(i*2, a[i+1], (a[i]-1)/2, -12);
        write "\n";
        i = i + 1;
     endwhile
     n = n + 1;
  endwhile
endfunc
