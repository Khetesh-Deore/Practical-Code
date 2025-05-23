// Source code is decompiled from a .class file using FernFlower decompiler.
package calculator;

public class Fibonacci {
   public Fibonacci() {
   }

   public static int fibo(int var0) {
      if (var0 <= 1) {
         return var0;
      } else {
         int var1 = 0;
         int var2 = 1;
         int var3 = 0;

         for(int var4 = 2; var4 <= var0 + 1; ++var4) {
            var3 = var1 + var2;
          //  System.out.print("" + var3 + " ");
            var1 = var2;
            var2 = var3;
         }

         return var3;
      }
   }
}
