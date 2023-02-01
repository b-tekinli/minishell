# MINISHELL

## PDF Mandatory Part

1.  Display a prompt: Bu, kullanıcının komut girdiğinde görünecek olan bir satır olmalıdır. <br>
Örnek olarak "$" kullanabilirsiniz. Bu satırı her komut girişinde ekrana yazdırmak için while döngüsü kullanabilirsiniz.

        while (1) {
	        printf("$ ");
	        fgets(input, 100, stdin);
	        // process input
	    }


<br>


2.  Working history: Kullanıcının girdiği komutların geçmişini tutmak için bir dizi veya liste kullanabilirsiniz. Her komut girişinde, kullanıcının girdiği komutu bu diziye veya listenin sonuna ekleyebilirsiniz.

        char history[100][100];
    	int history_count = 0;
    
    	// add current input to history
    	strcpy(history[history_count++], input);
    
    	// display history
    	for (int i = 0; i < history_count; i++) {
    		printf("%d %s", i+1, history[i]);
    	}


<br>


3.  Search and launch the right executable: Kullanıcının girdiği komutun PATH değişkeninde aranması gerekir veya komutun mutlak veya göreli bir yolu kullanılabilir. Bu komutu çalıştırmak için "system" fonksiyonu kullanabilirsiniz.

        if (input[0] == '/' || input[0] == '.') {
            // input is a relative or absolute path
            system(input);
        } else {
            // input is a command, search in PATH
            char path[100];
            strcpy(path, getenv("PATH"));
            char *token = strtok(path, ":");
            while (token != NULL) {
                char command[100];
                sprintf(command, "%s/%s", token, input);
                if (system(command) == 0) {
                    break;
                }
                token = strtok(NULL, ":");
            }
        }

    
<br>


4.  Global variable: Projede sadece bir global değişken kullanmalısınız ve bu değişkenin amacını açıklamalısınız. Örneğin, komutların geçmişini tutmak için kullanılan bir değişken.

        char history[100][100];
        int history_count = 0;


<br>


5.  Unclosed quotes and special characters: Projede kapatılmamış tırnak ve özel karakterlerin yorumlanmaması gerekir. Bu karakterleri algılamak ve kullanıcının girdiği komutu uygun şekilde işlemek için string fonksiyonlarını kullanabilirsiniz.

        int len = strlen(input);
        if (input[len-1] == '\n') {
            input[len-1] = '\0';
        }

    
<br>


6.  Handle ' and ": Projede ' (tek tırnak) ve " (çift tırnak) karakterlerinin işlenmesi gerekir. Bu karakterleri algılamak ve kullanıcının girdiği komutu uygun şekilde işlemek için string fonksiyonlarını kullanabilirsiniz.


        int len = strlen(input);
        if(input[0] == '"' || input[0] == '\'' ){
            input[len-1] = '\0';
            input++;
        }


<br>


- Komutları beklerken bir prompt görüntülemelidir.
- Çalışan bir geçmişi olmalıdır.
- PATH değişkeni veya göreli veya mutlak bir yol kullanarak doğru çalıştırılabilir dosyayı aramalı ve başlatmalıdır.
- Tek bir global değişken kullanmamalıdır.
- Kapatılmamış tırnak işaretleri veya konuya gerek olmayan özel karakterleri yorumlamamalıdır, örneğin \ (ters eğik) veya ; (noktalı virgül).
- ' (tek tırnak) işaretini işaretli dizide metakarakterleri yorumlamamasını sağlamalıdır.
- " (çift tırnak) işaretini işaretli dizide metakarakterleri yorumlamamasını sağlamalıdır, ancak $ (dolar işareti) hariç olmalıdır.


<br>


**A. Implement Redirections:** <br>

Komutların çıktısını veya girdisini başka dosyalara veya kaynaklara yönlendirmek için kullanılan operatörleri içermektedir.

***Örnek olarak:*** <br>
> 1. "<" operatorü (input redirection) kullanılarak komutun girdisi başka bir dosyadan okunabilir.
<br />
Örnek: "cat < input.txt" komutu input.txt dosyasındaki içeriği ekrana yazdırır.***

> 2. ">" operatorü (output redirection) kullanılarak komutun çıktısı başka bir dosyaya yazılabilir. 
<br>
Örnek: "ls > output.txt" komutu listedeki dosyaları output.txt dosyasına yazar.

> 3. "<<" operatorü (heredoc) kullanılarak komutun girdisi, belirlenen bir ayraç satırına kadar okunur ve ekrandaki çıktı güncellenmez. 
<br>
Örnek: "cat output.txt" komutu output.txt dosyasına "hello" yazısını ekler. 

> 4. ">>" operatorü (append output redirection) kullanılarak komutun çıktısı başka bir dosyaya eklenir. 
Örnek: "echo "hello" >> output.txt" komutu output.txt dosyasına "hello" yazısını ekler.


<br />
<br />


**B. Pipes** <br>

"|" karakteri olarak bilinen pipe işareti, komut satırında kullanılır ve komutların çıktılarını bir sonraki komutun girdisi olarak kullanmasını sağlar. <br>
***Örneğin,*** `"command1 | command2"` komutu, command1'in çıktısını command2'nin girdisi olarak kullanır. Bu, birden fazla komutun bir arada kullanılmasını ve çıktıların birbirleriyle işlenmesini sağlar.


<br />
<br />


**C. Environment Variables**

Sistemde tanımlı olan ortam değişkenlerini ($ işareti ile başlayan bir dizi karakter) kullanmanızı istemektedir. <br> 
***Örneğin,*** `$HOME` değişkeni kullanıcının ev dizinini ifade eder ve komut satırında $HOME olarak kullanıldığında, gerçek değeri olan kullanıcının ev dizininin yolu olarak değiştirilmelidir. Bu işlem, komut satırında kullanılan ortam değişkenlerinin gerçek değerlerine çevrilmesini içerir.


<br />
<br />


**D. $?**

"$?" değişkeni, son çalıştırılan arka plandaki veya ön plandaki pipeline'ın çıkış durumunu temsil eder. <br>
***Örneğin,*** bir komut çalıştırıldıktan sonra "$?" değişkeni, o komutun çıkış durumunu içerecektir. 0 çıkış durumu başarılı bir çıkış anlamına gelirken, 1 veya daha yüksek bir değer başarısız bir çıkış anlamına gelir. Bu talimatta, $? değişkeni en son çalıştırılan ön plandaki pipeline'ın çıkış durumunu temsil etmeli ve kullanıcının kullanabileceği bir değişken olarak ele alınmalıdır.


<br />
<br />


**E. CTRL-C, CTRL-D**

`"ctrl-C, ctrl-D ve ctrl-\"` gibi klavye kısayollarının nasıl çalıştığını bash gibi yapmanız gerekmektedir. <br> 
***Örneğin,*** ctrl-C genellikle bir işlemi iptal etmek için kullanılır. ctrl-D genellikle komut satırından çıkmak için kullanılır. ctrl-\ genellikle programın çalışmasını durdurmak için kullanılır.


<br />
<br />


**F. BUILTIN**

Kullanıcının shell'de kullanabileceği bazı komutlar: 
- echo with option -n: Echo komutu, kullanıcı tarafından verilen argümanları ekrana yazdırır. -n seçeneği ile kullanıldığında, argümanlar ekrana yazdırılırken sonunda bir satır atlaması yapılmaz.
- cd with only a relative or absolute path: cd komutu, kullanıcının çalışma dizinini değiştirir. Sadece yol olarak relative veya absolute path kullanılması istenmektedir.
- pwd with no options: pwd komutu, kullanıcının çalışma dizininin yolunu ekrana yazdırır.
- export with no options: export komutu, kullanıcının sistemde tanımladığı bir değişkeni dış ortama aktarmasını sağlar.
- unset with no options: unset komutu, kullanıcının sistemde tanımlı bir değişkeni siler.
- env with no options or arguments: env komutu, sistemde tanımlı tüm ortam değişkenlerini ekrana yazdırır.
- exit with no options: exit komutu, kabuk programını sonlandırır.


<br>
<br>


