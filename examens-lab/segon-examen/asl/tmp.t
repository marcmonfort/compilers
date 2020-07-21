function ff
  params
    _result
    n
  endparams

   %1 = 2
   %2 = n * %1
   %3 = 3
   %4 = %2 / %3
   %4 = %4 * %3
   %4 = %2 - %4
   %5 = 1
   %6 = %4 == %5
   %6 = not %6
   _result = %6
   return
   return
endfunction

function main
  vars
    a 1
    b 1
    t 1
  endvars

     %1 = 12
     t = %1
     %2 = 0
     %3 = 23
     %4 = %3 * t
     a[%2] = %4
     %5 = 0
     %6 = a[%5]
     writei %6
     writeln
     %8 = 4
     %9 = t - %8
     %14 = 1
     %13 = 0
     %10 = 0
     %16 = 0
  label while1 :
     %12 = %13 <= %10
     ifFalse %12 goto endwhile1
     %15 = a[%10]
     pushparam 
     pushparam %15
     call ff
     popparam 
     popparam %11
     %12 = %13 <= %11
     ifFalse %12 goto else1
     %16 = %16 + %14
  label else1 :
     b[%10] = %11
     %10 = %10 - %14
     goto while1
  label endwhile1 :
     %17 = 2
     %18 = %16 + %17
     %19 = %9 * %18
     writei %19
     writeln
     %21 = 0
     %22 = b[%21]
     %23 = not %22
     ifFalse %23 goto else2
     %24 = 'n'
     writec %24
     %24 = 'o'
     writec %24
     writeln
     goto endif2
  label else2 :
     %25 = 'y'
     writec %25
     %25 = 'e'
     writec %25
     %25 = 's'
     writec %25
     writeln
  label endif2 :
     %26 = 0
     %27 = 0
     %28 = a[%27]
     %29 = 2
     %30 = %28 + %29
     a[%26] = %30
     %35 = 1
     %34 = 0
     %31 = 0
     %37 = 0
  label while2 :
     %33 = %34 <= %31
     ifFalse %33 goto endwhile2
     %36 = a[%31]
     pushparam 
     pushparam %36
     call ff
     popparam 
     popparam %32
     %33 = %34 <= %32
     ifFalse %33 goto else3
     %37 = %37 + %35
  label else3 :
     b[%31] = %32
     %31 = %31 - %35
     goto while2
  label endwhile2 :
     writei %37
     writeln
     %39 = 4
     %40 = t - %39
     %41 = 0
     %42 = 2
     %43 = %41 + %42
     %44 = %40 * %43
     writei %44
     writeln
     %46 = 0
     %47 = b[%46]
     ifFalse %47 goto else4
     %48 = 'n'
     writec %48
     %48 = 'o'
     writec %48
     writeln
     goto endif4
  label else4 :
     %49 = 'y'
     writec %49
     %49 = 'e'
     writec %49
     %49 = 's'
     writec %49
     writeln
  label endif4 :
     return
endfunction


