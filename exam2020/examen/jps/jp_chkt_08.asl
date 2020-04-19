func main()
  var i,j: int
  var a,b: array [10] of char
  var z: float

  for z in range(10) do
      a[j] = f(b, a[j+2*i]);
  endfor
endfunc

func f(a: array [10] of char, i: int): int
  var m: char
  var j,k: int

  for m in range(1, 10, 2*j) do
     for k in range(i+1, j) do
        if m>a[k+i] then m=a[i+1];
        else return a[m-1];
        endif
     endfor
  endfor
  return k;
endfunc

