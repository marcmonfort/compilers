func main()
  var i,j: int
  var a: array [10] of char
  var c: char

  for j in range(10) do
      a[j] = f(a,i);
  endfor
  for j in range(1,i,z-3,j+3) do
      a[j-1] = f(a,i+1);
  endfor
endfunc

func f(a: array [10] of char, i: int): char
  var m: char
  var j,k: int

  for i in range(1, 10, 2*j) do
     for k in range(i+1, j) do
        if m>a[k+i] then m = a[i+1];
        else return a[i-1];
        endif
	k = k/2.0;
     endfor
  endfor
  return -1;
endfunc
