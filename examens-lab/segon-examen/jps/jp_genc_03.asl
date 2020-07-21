func main()
  var i,z : int

  z = sum();
  i = 10;
  while i>z do
     write i;
     write " ";
     write sum(2*(i+1));
     write "\n";
     i = i-1;
  endwhile
endfunc
