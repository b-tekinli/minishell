**func is_builtin -->** Bu fonksiyon "command" değişkeninde verilen komutun, shell tarafından yerleşik olarak desteklenen bir komut olup olmadığını kontrol eder. Her bir yerleşik komut için bir dönen değer vardır. Örneğin, "cd" komutu için CD değeri, "exit" komutu için EXIT değeri vb. Eğer verilen komut yerleşik bir komut değilse, fonksiyon 0 döner.


**func run_builtin -->** Bu fonksiyon, çalıştırılmak istenen komutun bir iç yapı komutu olup olmadığını belirler ve eğer iç yapı komutu ise, o komutun çalışmasını sağlar. Örneğin, çalıştırılmak istenen komut "cd" ise, "builtin_cd" fonksiyonu çağrılır ve klasör değiştirme işlemi yapılır.
