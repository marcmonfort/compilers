func main()
  var i,j: int
  var a,b: array [10] of char
  var c: char

  for j in range(10) do
      a[j] = f(a,i);
  endfor
  i = j*c;
  for j in range(1,i) do
      a[j-1] = f(b,i+1);
  endfor
endfunc

func f(a: array [10] of char, i: int): char
  var m: char
  var j,k: int

  a[m] = 3; 
  for i in range(1, 10, 2*j) do
     for k in range(i+1, j) do
        if m>a[k+i] then m=a[i+1];
        else return a[i-1];
        endif
     endfor
  endfor
  return j>a;
endfunc
